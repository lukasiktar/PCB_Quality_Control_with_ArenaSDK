/*
This is OpenCV project for detection, localization, inspection and OCR of PCBs (Printed Circuit Boards).
The project requires installation and importing some libraries:
* OpenCV with CUDA and cuDNN
* Tesseract with Leptonica

Developed by Luka Siktar
10.05.2023.
*/
#include "ArenaApi.h"
#include <iostream>
//#include <chrono>
#include <opencv2/opencv.hpp>
#include "MyWidget.h"
#include "colors.h"
#include "inference.h"
#include "Inspection.h"
#include "OCRcustom.h"

#define TIMEOUT 2000
#define EXPOSURE_TIME 17000.0 //in microseconds

//Function to convert image from Arena format to OpenCV
cv::Mat ConvertArenaImageToMat(Arena::IImage* pImage) {
    size_t width = pImage->GetWidth();
    size_t height = pImage->GetHeight();

    // Create an OpenCV Mat for a 3-channel RGB image
    cv::Mat cvImage = cv::Mat(height, width, CV_8UC3);

    // Copy data from Arena image to OpenCV Mat
    const uint8_t* pData = static_cast<const uint8_t*>(pImage->GetData());
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            // OpenCV uses BGR format, so the order of channels should be arranged accordingly
            cvImage.at<cv::Vec3b>(y, x)[0] = pData[(y * width + x) * 3 + 2]; // Blue channel
            cvImage.at<cv::Vec3b>(y, x)[1] = pData[(y * width + x) * 3 + 1]; // Green channel
            cvImage.at<cv::Vec3b>(y, x)[2] = pData[(y * width + x) * 3];     // Red channel
        }
    }
    return cvImage;
}


cv::Mat AcquireImages(Arena::IDevice* pDevice) {
    Arena::IImage* pImage = pDevice->GetImage(TIMEOUT);
    cv::Mat cvImage = ConvertArenaImageToMat(pImage);
    pDevice->RequeueBuffer(pImage);
    return cvImage;
}

int main(int argc, char* argv[])
{
    //Initialization of Qt GUI application:
    QApplication app(argc, argv);
    MyWidget widget;


    //Creating an instance for performing inference (loading YOLOv8 neural network and file with its classes)
    bool runOnGPU = false;
    std::string projectBasePath = "C:\\Users\\lukas\\OneDrive\\Desktop\\Projekt\\VisualStudio\\Qt_PCB_detecton_with_LUCID";
    Inference inf(projectBasePath + "\\source\\models\\YOLOv8m_PCB.onnx", cv::Size(640, 640), projectBasePath + "\\source\\classes\\YOLOv8m_PCB_classes.txt", runOnGPU);

    //Loading classes for inspection and OCR
    std::ifstream inputFile1(projectBasePath + "\\source\\classes\\inspection_classes.txt");
    std::vector<std::string> inspection_elements;
    if (inputFile1.is_open()) {
        std::string line;
        while (std::getline(inputFile1, line)) { inspection_elements.push_back(line); }
        inputFile1.close();
    }
    std::ifstream inputFile2(projectBasePath + "\\source\\classes\\OCR_classes.txt");
    std::vector<std::string> OCR_elements;
    if (inputFile2.is_open()) {
        std::string line;
        while (std::getline(inputFile2, line)) { OCR_elements.push_back(line); }
        inputFile2.close();
    }

    //Additional modification for constant detection and bounding box colors
    Colors color(projectBasePath + "\\source\\classes\\YOLOv8m_PCB_classes.txt");
    std::map<std::string, cv::Scalar> dictionary = color.dictionary;

    //Inintialization of video stream
    Arena::ISystem* pSystem = Arena::OpenSystem();
    pSystem->UpdateDevices(100);
    std::vector<Arena::DeviceInfo> deviceInfos = pSystem->GetDevices();
    if (deviceInfos.size() == 0) {
        std::cout << "\nNo camera connected\nPress enter to complete\n";
        return 0;
    }
    Arena::IDevice* pDevice = pSystem->CreateDevice(deviceInfos[0]);
    GenICam::gcstring acquisitionModeInitial = Arena::GetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "AcquisitionMode");
    Arena::SetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "AcquisitionMode", "Continuous");

    Arena::SetNodeValue<GenICam::gcstring>(pDevice->GetTLStreamNodeMap(), "StreamBufferHandlingMode", "NewestOnly");
    GenApi::CEnumerationPtr pTransportStreamProtocolEnum = pDevice->GetNodeMap()->GetNode("TransportStreamProtocol");
    Arena::SetNodeValue<bool>(pDevice->GetTLStreamNodeMap(), "StreamAutoNegotiatePacketSize", true);
    Arena::SetNodeValue<bool>(pDevice->GetTLStreamNodeMap(), "StreamPacketResendEnable", true);
    
    //Set exposure time
    GenApi::CFloatPtr pExposureTime = pDevice->GetNodeMap()->GetNode("ExposureTime");
    double exposureTime = EXPOSURE_TIME;
    pExposureTime->SetValue(exposureTime);
    //Set Pixel format
    GenApi::CEnumerationPtr pPixelFormat = pDevice->GetNodeMap()->GetNode("PixelFormat");
    GenApi::CEnumEntryPtr pPixelFormatEntry = pPixelFormat->GetEntryByName("RGB8"); // Replace with your desired pixel format
    pPixelFormat->SetIntValue(pPixelFormatEntry->GetValue());
    //Set Gain
    GenApi::CFloatPtr pGain = pDevice->GetNodeMap()->GetNode("Gain");
    double gainValue = 2.0; // Set gain value
    pGain->SetValue(gainValue);
    //Set Gamma
    GenApi::CFloatPtr pGamma = pDevice->GetNodeMap()->GetNode("Gamma");
    double gammaValue = 0.52; // Set gamma value
    pGamma->SetValue(gammaValue);
    

    cv::Mat img;
    pDevice->StartStream();

    //Segment of code performed after the "Capture" button is pressed
    cv::Mat capturedFrame;
    QObject::connect(&widget, &MyWidget::captureRequested, [&]() {
        //auto start = std::chrono::high_resolution_clock::now();

        capturedFrame= AcquireImages(pDevice);

        //Check if captured image is sent and read properly
        if (!capturedFrame.empty()) {
            //Running the inference using YOLOv8
            std::vector<Detection> output = inf.runInference(capturedFrame);
            int detections = output.size();

            std::vector<cv::Mat> inspections;       //Stores all the inspecions images
            std::vector<cv::Mat> OCR_read_images;   //Stores all the images for OCR inspection
            std::vector<std::string> OCR_reads;     //Stores all reads for OCR_read_images
            std::vector<int> inspections_num;
            std::vector<std::string> inspections_name;

            //Loop through detections
            int a = 0;
            for (int i = 0; i < detections; ++i)
            {
                Detection detection = output[i];
                cv::Rect box = detection.box;                   //bounding box for detection
                Scalar color = dictionary[detection.className]; //color for bounding box

                Mat image1 = capturedFrame(box).clone();    //Extraction of object from captured image
                detection.detection_id = a++;                   //rewrite detection class_id-s to enable inspection of element with the same class_name and class_id          

                //Inspection
                for (auto obj : inspection_elements) {
                    //if (detection.className == "40_pins" or detection.className == "6_pins" or detection.className == "Check_pattern_1" or detection.className == "Check_pattern_2" or detection.className == "Check_pattern_3" or detection.className == "Check_pattern_4" or detection.className == "CN7" or detection.className == "CN8" or detection.className == "CN9" or detection.className == "CN10") {
                    if (detection.className == obj) {
                        Inspection photo;
                        inspections.push_back(photo.inspect(image1, detection));
                        inspections_num.push_back(photo.boxes_number);
                        inspections_name.push_back(detection.className);
                    }
                }

                //OCR read
                for (auto obj : OCR_elements) {
                    if (detection.className == obj) {
                        //if (detection.className == "ARDUINO" or detection.className == "UNO_white" or detection.className == "NVIDIA." or detection.className == "Arduino_UNO_model" or detection.className == "RaspberryPi_model" or detection.className == "STM32_model") {
                        OCRread OCRobject(image1);
                        OCR_reads.push_back(OCRobject.outputText);
                        if (image1.cols > 100 or image1.rows > 100) {
                            cv::resize(image1, image1, cv::Size(image1.cols / 2.5, image1.rows / 2.5));
                        }
                        OCR_read_images.push_back(image1);
                    }
                }
            }
            widget.showDetectionCounter(detections);
            widget.showInspections(inspections, inspections_name, inspections_num);
            widget.showOCRdetections(OCR_read_images, OCR_reads);


            //Draw the bounding boxes and labels on captured image
            for (int i = 0; i < detections; ++i)
            {
                Detection detection = output[i];
                cv::Rect box = detection.box;
                cv::Scalar color = dictionary[detection.className];

                // Detection bounding box
                cv::rectangle(capturedFrame, box, color, 2);

                // Detection bounding box text
                //std::string classString = detection.className + ' ' + std::to_string(detection.confidence).substr(0, 4);  //Class name and confidence
                std::string classString = detection.className;  //Class name

                cv::Size textSize = cv::getTextSize(classString, cv::FONT_HERSHEY_DUPLEX, 1, 2, 0);
                cv::Rect textBox(box.x, box.y - 40, textSize.width + 10, textSize.height + 20);

                cv::rectangle(capturedFrame, textBox, color, cv::FILLED);
                cv::putText(capturedFrame, classString, cv::Point(box.x + 5, box.y - 10), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(0, 0, 0), 2, 0);
                //auto end = std::chrono::high_resolution_clock::now();
                //auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                //cv::putText(capturedFrame, to_string(duration.count()), cv::Point(300, 300), cv::FONT_HERSHEY_DUPLEX, 10, cv::Scalar(0, 0, 0), 2, 0);


            }
        }
        cv::resize(capturedFrame, capturedFrame, cv::Size(capturedFrame.cols / 4, capturedFrame.rows / 4));

        widget.caputureDisplayImage(capturedFrame);
        });
    //Segment of a code performed after "Exit" button is pressed
    QObject::connect(&widget, &MyWidget::exitRequested, [&]() { 
    pDevice->StopStream();
    Arena::SetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "AcquisitionMode", acquisitionModeInitial);
    pSystem->DestroyDevice(pDevice);
    Arena::CloseSystem(pSystem);
    app.closeAllWindows();
    exit(1);
        });


    //Main infinite loop ( loop reads image and streams it to the GUI)
    while (true) {
        cv::Mat frame;
        frame=AcquireImages(pDevice);

        //Check if the there is any frame to read
        if (frame.empty())
        {
            qDebug() << "Error: Unable to load image!";
            return -1;
        }

        cv::resize(frame, frame, cv::Size(frame.cols / 10, frame.rows / 10));
        //Streaming frame to the GUI
        widget.videoDisplayImage(frame);
        cv::waitKey(2);

        //Display GUI
        widget.show();
    }

    return app.exec();
}

//Additional function for transforming QImage format (used for Qt GUI) to Mat format (used for OpenCV)
cv::Mat QImageToCvMat(const QImage& image)
{
    cv::Mat mat;
    switch (image.format()) {
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, const_cast<uchar*>(image.bits()), image.bytesPerLine());
        cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB); // Optional: Convert BGR to RGB format
        break;
    default:
        mat = cv::Mat();
        break;
    }
    return mat;
}

//Additional function for transforming Mat format (used fot OpenCV) to QImage format (used for GUI)
QImage CvMatToQImage(const cv::Mat& mat)
{
    QImage image;
    switch (mat.type()) {
    case CV_8UC3:
        image = QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        break;
    default:
        image = QImage();
        break;
    }
    return image;
}