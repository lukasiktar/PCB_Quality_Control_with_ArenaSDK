#include "Inspection.h"
/*
Inspect function stores the image, converts it into grayscale and performs adaptive thresholding with a range of thresholding values and seeking for the contours which represents pins or soldering points.

*/
cv::Mat Inspection::inspect(cv::Mat frame, Detection detection) {
	//Converting image to grayscale
	std::string class_name = std::to_string(detection.detection_id);
	cv::Mat image = frame;
	cv::Mat grey_image;
	if (image.channels() == 3) {
		cvtColor(image, grey_image, cv::COLOR_BGR2GRAY);
	}

	double thresholdValue = cv::mean(grey_image)[0];
	int thresholdType = (thresholdValue < 140) ? cv::THRESH_BINARY : cv::THRESH_BINARY_INV;
	int C = (thresholdValue < 140) ? -18 : 10;
	std::vector<int> thresh_values;
	if (thresholdValue < 140) {
		thresh_values = { 41,61,81};

	}
	else {
		thresh_values = {41,61,81,101};
	}
	cv::Scalar color;
	if (thresholdValue < 140) {
		color = cv::Scalar(0.0, 100.0, 255.0);

	}
	else {
		color = cv::Scalar(200.0, 100.0, 0.0);

	}

	cv::Mat binary_image;
	//std::vector<int> thresh_values = { 181,201,241 };		//Set up descrete range of threshold for adaptive thresholding
	std::vector<std::vector<std::vector<cv::Point>>> contours_all;	//Stores the results for all thresh_values
	std::vector<cv::Point> approx;

	//Find contours for the discrete range of thresholds
	for (auto thresh : thresh_values) {
		//threshold(grey_image, binary_image, thresh, 225, cv::THRESH_TOZERO);
		cv::adaptiveThreshold(grey_image, binary_image, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, thresholdType, thresh, C);
		//cv:imshow(std::to_string(thresh), binary_image);
		std::vector<std::vector<cv::Point>> contours;
		findContours(binary_image, contours, cv::RETR_EXTERNAL, 1);
		contours_all.push_back(contours);
	}

	//FILTERING THE CONTOURS: START -----------------------------------------------------------------------------------------------------------

	//Searching for the threshold with least contours (this threshold gives the best inspection)
	std::vector<std::vector<cv::Point>> min_contours;
	min_contours = contours_all[0];
	for (auto num : contours_all) {
		if (num.size() < min_contours.size()) {
			min_contours = num;
		}
	}

	//Merging of contours that intersect:
	std::vector<cv::Rect> bounding_boxes_zero;			//Stores all bounding boxes created around contours
	std::vector<cv::Rect> bounding_boxes_zero_merged;	//Stores merged bounding boxes created around contours

	int intersect = 0;
	int a = 0;
	bool inter = false;
	for (int i = 0; i < min_contours.size(); i++) {
		if (contourArea(min_contours.at(i)) > 30) {		//Filtering the contours with area smaller than 20 pixels	
			cv::Rect bounding = boundingRect(min_contours.at(i));
			bounding_boxes_zero.push_back(bounding);
			intersect = 0;
			a++;
			for (auto b : bounding_boxes_zero) {
				cv::Rect intersection = bounding & b;
				if (!intersection.empty() && intersection != bounding) {
					intersect = 1;
					bounding = bounding | b;
					bounding_boxes_zero_merged.push_back(bounding);
					bool inter = true;
				}
			}
			if (inter == false)
				bounding_boxes_zero_merged.push_back(bounding);
			else {
				inter = false;
			}
		}
	}



	// Sort the bounding boxes based on their areas
	std::sort(bounding_boxes_zero_merged.begin(), bounding_boxes_zero_merged.end(), [](const cv::Rect& a, const cv::Rect& b) {
		return a.area() > b.area();  // Sort in descending order based on area
		});

	//If there is bounding boxes that intersects, remove the smaller
	std::vector<cv::Rect> bounding_boxes;
	bool inter_1 = false;
	for (auto a : bounding_boxes_zero_merged) {
		for (auto b : bounding_boxes_zero_merged) {
			if (a.x != b.x && a.y != b.y && a.width != b.width && a.height != b.height && a.area() != b.area()) {
				if (a.x >= b.x && (a.x + a.width) <= (b.x + b.width) && a.y >= b.y && (a.y + a.height) <= (b.y + b.height) && a.area() < b.area()) {
					inter_1 = true;

					continue;
				}
			}
		}
	if (inter_1 == false) {
		bounding_boxes.push_back(a);
	}
	else {
		inter_1 = false;
	}
	}

	//FILTERING THE CONTOURS: END -----------------------------------------------------------------------------------------------------------

	//Draw bounding boxes 
	boxes_number = 0;
	for (int i = 0; i < bounding_boxes.size(); i++) {

		//cv::Scalar color(100.0, 200.0, 200.0);
		cv::Rect bounding = bounding_boxes[i];
		if (bounding.height > 2 && bounding.width > 2 && (bounding.height / bounding.width < 2.5 && bounding.width / bounding.height < 2.5)) {
			cv::rectangle(image, bounding, color, 2, cv::LINE_8, 0);
			boxes_number++;
		}
	}
	boxes_number = static_cast<int>(boxes_number);
	if (image.cols > 200 or image.rows > 200) {
		cv::resize(image, image, cv::Size(image.cols / 2, image.rows / 2));
	}
	if (image.cols > 200 or image.rows > 200) {
		cv::resize(image, image, cv::Size(image.cols / 1.2, image.rows / 1.2));
	}
	return image;
}
