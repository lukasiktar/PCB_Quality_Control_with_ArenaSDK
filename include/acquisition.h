/*
This is a header file that contains methods for acquisition of image from camera,image conversion from Arena API to OpenCV and converisons between Qt formats and OpenCV
*/

#ifndef ACQUISITION_H
#define ACQUISITION_H

#include <iostream>
#include <fstream>
#include "ArenaApi.h"
#include <opencv2/opencv.hpp>
#include "MyWidget.h"

class acquisition
{
public:
	cv::Mat ConvertArenaImageToMat(Arena::IImage* pImage);
	cv::Mat AcquireImages(Arena::IDevice* pDevice);
	cv::Mat QImageToCvMat(const QImage& image);
	QImage CvMatToQImage(const cv::Mat& mat);

};
#endif // ACQUISITION_H
