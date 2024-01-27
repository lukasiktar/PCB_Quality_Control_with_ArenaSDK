#include "acquisition.h"
#define TIMEOUT 2000    //camera acquisition timeout

//Method for image acquisition from LUCID PHX064S industrial camera
cv::Mat acquisition::AcquireImages(Arena::IDevice* pDevice) {
    Arena::IImage* pImage = pDevice->GetImage(TIMEOUT);
    cv::Mat cvImage = ConvertArenaImageToMat(pImage);
    pDevice->RequeueBuffer(pImage);
    return cvImage;
}

//Method for image transformation from Arena image to OpenCV Mat
cv::Mat acquisition::ConvertArenaImageToMat(Arena::IImage* pImage) {
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


//Method for image transformation from Qt image to OpenCV Mat
cv::Mat acquisition::QImageToCvMat(const QImage& image) {
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

//Method for image transformation from OpenCV Mat to Qt image
QImage acquisition::CvMatToQImage(const cv::Mat& mat){
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
