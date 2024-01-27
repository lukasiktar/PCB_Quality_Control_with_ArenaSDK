/*
This is a header file created as addition to a inference. It enables a constant colors of bounding boxes while performing detection of PCBs.
*/
#ifndef COLORS_H
#define COLORS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>

using namespace std;
using namespace cv;

class Colors 
{
public:
    map<string, Scalar> dictionary;
    vector<string> classes;
    string classPath;

    Colors(const string& classesTxtFile);

    void colorDet();

};
#endif // COLORS_H