#include "colors.h"

//Constructor
Colors::Colors(const string& classesTxtFile) : classPath(classesTxtFile) {
    colorDet();
}

//Method to create dictionary with classes and respectable colors
void Colors::colorDet() {
    ifstream inputFile(classPath);
    if (inputFile.is_open()) {
        string classLine;
        while (getline(inputFile, classLine)) {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> dis(100, 255);
            dictionary[classLine] = cv::Scalar(dis(gen), dis(gen), dis(gen));
            classes.push_back(classLine);
        }
        inputFile.close();
    }
}
