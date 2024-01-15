#include "OCRcustom.h"

OCRread::OCRread() {}

OCRread::OCRread(cv::Mat image) : OCRimage0(image) {
    OCRreadText();
}

std::vector<std::string> OCRread::inputOCRFile(const std::string& OCRListPath) {
    std::ifstream inputFile2(OCRListPath);
    std::vector<std::string> OCR_elements;
    if (inputFile2.is_open()) {
        std::string line;
        while (std::getline(inputFile2, line)) { OCR_elements.push_back(line); }
        inputFile2.close();
    }
    return OCR_elements;
}

void OCRread::OCRreadText() {
    //Image on which OCR will be performed
    cv::Mat OCRimage = OCRimage0;
    cv::cvtColor(OCRimage, OCRimage, cv::COLOR_BGR2GRAY);
  
    char* outText;

    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
    if (api->Init(NULL, "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }
    PIX* pixS = pixCreate(OCRimage.size().width, OCRimage.size().height, 8);
    for (int i = 0; i < OCRimage.rows; i++)
        for (int j = 0; j < OCRimage.cols; j++)
            pixSetPixel(pixS, j, i, (l_uint32)OCRimage.at<uchar>(i, j));

    api->SetImage(pixS);

    //Result of OCR
    outText = api->GetUTF8Text();
    //printf("OCR output:\n");

    outputText = outText;

    // Destroy used object and release memory
    api->End();
    delete api;
    delete[] outText;
    pixDestroy(&pixS);
}