#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QFont>
#include <QtWidgets/QVBoxLayout>
#include <opencv2/opencv.hpp>


class MyWidget : public QWidget
{
    Q_OBJECT

public:
    MyWidget(QWidget* parent = nullptr);

    void videoDisplayImage(cv::Mat frame);      //Function to display video stream
    void caputureDisplayImage(cv::Mat frame);   //Function to display captured image after inference 
    void showDetectionCounter(int detections);  //Function to display the number of detections
    void showInspections(std::vector<cv::Mat> inspections, std::vector<std::string> inspections_name, std::vector<int> inspections_num);     //Function to display object's image af ter inpection
    void showOCRdetections(std::vector<cv::Mat> OCRdetections, std::vector<std::string> OCRreads);  //Function to display objects for OCR and OCR readings

signals:
    void captureRequested(const QImage& image);  //Capture signal
    void exitRequested();   //Exit signal

private slots:
    void capturePhoto();    //Capture button functionality
    void exitApplication(); //Exit function functionality

private:
    //Labels -> elements of GUI
    QLabel* img;    //Stream label
    QLabel* cap;    //Capture label
    QImage image;
    QImage cap_image;
    QLabel* captured_image_sign;

    QPushButton* captureButton;
    QPushButton* exitButton;
    
    
    QLabel* detection_counter;

    QLabel* inspection_sign;
    QLabel* inspection1_name;
    QLabel* inspection1_number;
    QLabel* inspection1;
    QLabel* inspection2_name;
    QLabel* inspection2_number;
    QLabel* inspection2;
    QLabel* inspection3_name;
    QLabel* inspection3_number;
    QLabel* inspection3;
    QLabel* inspection4_name;
    QLabel* inspection4_number;
    QLabel* inspection4;
    QLabel* inspection5_name;
    QLabel* inspection5_number;
    QLabel* inspection5;

    QLabel* OCR_detection_sign;
    QLabel* OCRdetection1;
    QLabel* OCRdetection2;
    QLabel* OCRdetection3;
    QLabel* OCRdetection1_sign;
    QLabel* OCRdetection2_sign;
    QLabel* OCRdetection3_sign;



protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif // MYWIDGET_H
