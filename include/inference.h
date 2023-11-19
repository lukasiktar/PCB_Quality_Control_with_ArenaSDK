/*
This is the header file for performing inference using YOLOv8 neural network. Header file is originally cloned from official Ultralytics repository (https://github.com/ultralytics/ultralytics/tree/main/examples/YOLOv8-CPP-Inference)
Ultralytics is the creator of YOLOv5, YOLOv8, YOLO-NAS etc.

Originally from Ultralytics, modified by Luka Siktar
10.05.2023.
*/

#ifndef INFERENCE_H
#define INFERENCE_H

// Cpp native
#include <fstream>
#include <vector>
#include <string>
#include <random>

// OpenCV / DNN / Inference
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>

struct Detection
{
    int class_id{ 0 };
    int detection_id{ 0 };
    std::string className{};
    float confidence{ 0.0 };
    cv::Scalar color{};
    cv::Rect box{};
};

class Inference
{
public:
    Inference(const std::string& onnxModelPath, const cv::Size2f& modelInputShape, const std::string& classesTxtFile, const bool& runWithCuda = true);
    std::vector<Detection> runInference(const cv::Mat& input);

private:
    void loadClassesFromFile();
    void loadOnnxNetwork();
    cv::Mat formatToSquare(const cv::Mat& source);

    std::string modelPath{};
    std::string classesPath{};
    bool cudaEnabled{};

    std::vector<std::string> classes{};
    cv::Size2f modelShape{};

    float modelConfidenseThreshold{ 0.25 };
    float modelScoreThreshold{ 0.45 };
    float modelNMSThreshold{ 0.50 };

    bool letterBoxForSquare = true;

    cv::dnn::Net net;
};

#endif // INFERENCE_H
