/*
This header file performs OCR read on specified PCB elements.

Developed by Luka Siktar
10.05.2023.
*/
#ifndef OCRCUSTOM_H
#define OCRCUSTOM_H

#include <iostream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>

class OCRread {
public:
    char* outputText;
    cv::Mat OCRimage0;

    OCRread(cv::Mat image);

    void OCRreadText();
};

#endif // OCRCUSTOM_H

