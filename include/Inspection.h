/*
This is a header file which provides code for inspection of PCB elements. It is primarly used to inspect the quality of GPIO and soldering quality inspeciton.

Developed by Luka Siktar
10.05.2023.
*/
#ifndef INSPECTION_H
#define INSPECTION_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include <opencv2/imgproc.hpp>
#include "opencv2/core.hpp"
#include "inference.h"

class Inspection {
public:
	int boxes_number;
	cv::Mat inspect(cv::Mat frame, Detection detection);
	std::vector<std::string> inputInspectionFile(const std::string& inspectionListPath);

};

#endif // INSPECTION_H