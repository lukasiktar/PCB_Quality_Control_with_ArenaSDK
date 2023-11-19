#include "MyWidget.h"

//Custom button style for Capture button
QString buttonStyle1 = "QPushButton {"
"    background-color: white; /* Green background */"
"    color: black; /* White text color */"
"    border-style: outset;\n"
"    border-width: 1px;\n"
"    border-color: gray;\n"
"    border-radius: 5px;"
"    font: bold 14px;\n"
"    padding: 10px 20px; /* Padding */"
"}"
"QPushButton:pressed {"
"    background-color: blue; /* Darker green on hover */"
"    color: white; /* White text color */"
"}";
//Custom button style for Exit button
QString buttonStyle2 = "QPushButton {"
"    background-color: white; /* Green background */"
"    color: black; /* White text color */"
"    border-style: outset;\n"
"    border-width: 1px;\n"
"    border-color: gray;\n"
"    border-radius: 5px;"
"    font: bold 14px;\n"
"    padding: 10px 20px; /* Padding */"
"}"
"QPushButton:pressed {"
"    background-color: red; /* Darker green on hover */"
"    color: white; /* White text color */"
"}";


MyWidget::MyWidget(QWidget* parent) : QWidget(parent)
{
    //Adding img label:
    img = new QLabel(this);
    QVBoxLayout* layout = new QVBoxLayout;
    img->setGeometry(10, 10, 400, 200);
    layout->addWidget(img);
    QFont heading_font;
    heading_font.setPixelSize(18);
    QFont text_font;
    text_font.setPixelSize(16);


    //Adding Capture button:
    QHBoxLayout* layout1 = new QHBoxLayout;
    captureButton = new QPushButton("Capture Photo", this);
    captureButton->setStyleSheet(buttonStyle1);
    captureButton->setGeometry(10, 220, 150, 40);
    layout1->addWidget(captureButton);
    layout1->addLayout(layout);
    connect(captureButton, &QPushButton::clicked, this, &MyWidget::capturePhoto);

    //Adding Exit button:
    exitButton = new QPushButton("Exit", this);
    exitButton->setStyleSheet(buttonStyle2);
    exitButton->setGeometry(180, 220, 150, 40);
    layout->addWidget(exitButton);
    connect(exitButton, &QPushButton::clicked, this, &MyWidget::exitApplication);

    //Adding cap label:
    cap = new QLabel(this);
    cap->setGeometry(10, 300, 800, 500);
    layout->addWidget(cap);

    //Adding text to GUI:
    captured_image_sign = new QLabel(this);
    captured_image_sign->setText("Captured Image:");
    captured_image_sign->setGeometry(10, 270, 200, 30);
    captured_image_sign->setFont(heading_font);
    layout->addWidget(captured_image_sign);


    OCR_detection_sign = new QLabel(this);
    OCR_detection_sign->setText("OCR detections:");
    OCR_detection_sign->setGeometry(380, 1, 300, 30);
    OCR_detection_sign->setFont(heading_font);
    layout->addWidget(OCR_detection_sign);

    inspection_sign = new QLabel(this);
    inspection_sign->setText("Inspected elements: ");
    inspection_sign->setGeometry(820, 1, 300, 30);
    inspection_sign->setFont(heading_font);
    layout->addWidget(inspection_sign);

    //Adding OCR detections and the object on which the OCR is performed:
    OCRdetection1_sign = new QLabel(this);
    OCRdetection1_sign->setGeometry(380, 160, 200, 50);
    //OCRdetection1_sign->setFont(text_font);
    layout->addWidget(OCRdetection1_sign);
    OCRdetection1 = new QLabel(this);
    OCRdetection1->setGeometry(380, 20, 200, 120);
    layout->addWidget(OCRdetection1);

    OCRdetection2_sign = new QLabel(this);
    OCRdetection2_sign->setGeometry(520, 160, 200, 50);
    //OCRdetection2_sign->setFont(text_font);
    layout->addWidget(OCRdetection2_sign);
    OCRdetection2 = new QLabel(this);
    OCRdetection2->setGeometry(520, 20, 100, 120);
    layout->addWidget(OCRdetection2);

    OCRdetection3_sign = new QLabel(this);
    OCRdetection3_sign->setGeometry(640, 160, 200, 50);
    //OCRdetection3_sign->setFont(text_font);
    layout->addWidget(OCRdetection3_sign);
    OCRdetection3 = new QLabel(this);
    OCRdetection3->setGeometry(640, 20, 100, 120);
    layout->addWidget(OCRdetection3);

    //Adding inspecitons:
    inspection1_name = new QLabel(this);
    inspection1_name->setFont(text_font);
    layout->addWidget(inspection1_name);
    inspection1_number = new QLabel(this);
    inspection1_number->setFont(text_font);
    layout->addWidget(inspection1_number);
    inspection1 = new QLabel(this);
    inspection1->setGeometry(820, 50, 400, 180);
    layout->addWidget(inspection1);

    inspection2_name = new QLabel(this);
    inspection2_name->setFont(text_font);
    layout->addWidget(inspection2_name);
    inspection2_number = new QLabel(this);
    inspection2_number->setFont(text_font);
    layout->addWidget(inspection2_number);
    inspection2 = new QLabel(this);
    inspection2->setGeometry(820, 270, 400, 180);
    layout->addWidget(inspection2);

    inspection3_name = new QLabel(this);
    inspection3_name->setFont(text_font);
    layout->addWidget(inspection3_name);
    inspection3_number = new QLabel(this);
    inspection3_number->setFont(text_font);
    layout->addWidget(inspection3_number);
    inspection3 = new QLabel(this);
    inspection3->setGeometry(820, 490, 400, 180);
    layout->addWidget(inspection3);

    inspection4_name = new QLabel(this);
    inspection4_name->setFont(text_font);
    layout->addWidget(inspection4_name);
    inspection4_number = new QLabel(this);
    inspection4_number->setFont(text_font);
    layout->addWidget(inspection4_number);
    inspection4 = new QLabel(this);
    inspection4->setGeometry(1240, 50, 400, 180);
    layout->addWidget(inspection4);

    inspection5_name = new QLabel(this);
    inspection5_name->setFont(text_font);
    layout->addWidget(inspection5_name);
    inspection5_number = new QLabel(this);
    inspection5_number->setFont(text_font);
    layout->addWidget(inspection5_number);
    inspection5 = new QLabel(this);
    inspection5->setGeometry(1240, 270, 400, 100);
    layout->addWidget(inspection5);

    setLayout(layout);

}

void MyWidget::videoDisplayImage(cv::Mat frame)
{
    QImage qtImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_BGR888);  //Transform cv::Mat -> QImage
    image = qtImage;
    img->setPixmap(QPixmap::fromImage(qtImage));

}
void MyWidget::caputureDisplayImage(cv::Mat frame)
{
    QImage qtImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_BGR888);  //Transform cv::Mat -> QImage
    cap_image = qtImage;
    cap->setPixmap(QPixmap::fromImage(qtImage));


}
void MyWidget::showInspections(std::vector<cv::Mat> inspections, std::vector<std::string> inspections_name, std::vector<int> inspections_num) {
    inspection1->clear();
    inspection1_name->clear();
    inspection1_number->clear();
    inspection2->clear();
    inspection2_name->clear();
    inspection2_number->clear();
    inspection3->clear();
    inspection3_name->clear();
    inspection3_number->clear();
    inspection4->clear();
    inspection4_name->clear();
    inspection4_number->clear();
    inspection5->clear();
    inspection5_name->clear();
    inspection5_number->clear();

    for (auto i = 0; i < inspections.size(); i++) {
        if (i == 0) {
            inspection1_name->setGeometry(820, 40, 140, 30);
            inspection1_name->setText(QString::fromStdString(inspections_name[i]));
            std::string inspections_printed = "Inspected: " + std::to_string(inspections_num[i]);
            inspection1_number->setGeometry(820, 70, 140, 20);
            inspection1_number->setText(QString::fromStdString(inspections_printed));
            QImage qtImage(inspections[i].data, inspections[i].cols, inspections[i].rows, inspections[i].step, QImage::Format_BGR888);
            inspection1->setGeometry(820, 100, inspections[i].cols, inspections[i].rows);
            inspection1->setPixmap(QPixmap::fromImage(qtImage));
        }
        else if (i == 1) {
            inspection2_name->setGeometry(820, 270, 140, 30);
            inspection2_name->setText(QString::fromStdString(inspections_name[i]));

            std::string inspections_printed = "Inspected: " + std::to_string(inspections_num[i]);
            inspection2_number->setGeometry(820, 300, 140, 30);
            inspection2_number->setText(QString::fromStdString(inspections_printed));

            QImage qtImage(inspections[i].data, inspections[i].cols, inspections[i].rows, inspections[i].step, QImage::Format_BGR888);
            inspection2->setGeometry(820, 330, inspections[i].cols, inspections[i].rows);
            inspection2->setPixmap(QPixmap::fromImage(qtImage));
        }
        else if (i == 2) {
            inspection3_name->setGeometry(820, 500, 140, 30);
            inspection3_name->setText(QString::fromStdString(inspections_name[i]));

            std::string inspections_printed = "Inspected: " + std::to_string(inspections_num[i]);
            inspection3_number->setGeometry(820, 530, 140, 30);
            inspection3_number->setText(QString::fromStdString(inspections_printed));

            QImage qtImage(inspections[i].data, inspections[i].cols, inspections[i].rows, inspections[i].step, QImage::Format_BGR888);
            inspection3->setGeometry(820, 560, inspections[i].cols, inspections[i].rows);
            inspection3->setPixmap(QPixmap::fromImage(qtImage));
        }
        else if (i == 3) {
            inspection4_name->setGeometry(980 + inspections[1].cols, 40, 140, 30);
            inspection4_name->setText(QString::fromStdString(inspections_name[i]));

            std::string inspections_printed = "Inspected: " + std::to_string(inspections_num[i]);
            inspection4_number->setGeometry(980 + inspections[1].cols, 70, 140, 30);
            inspection4_number->setText(QString::fromStdString(inspections_printed));

            QImage qtImage(inspections[i].data, inspections[i].cols, inspections[i].rows, inspections[i].step, QImage::Format_BGR888);
            inspection4->setGeometry(980 + inspections[1].cols, 100, inspections[i].cols, inspections[i].rows);
            inspection4->setPixmap(QPixmap::fromImage(qtImage));
        }
        else if (i == 4) {
            inspection5_name->setGeometry(980 + inspections[2].cols, 270, 140, 30);
            inspection5_name->setText(QString::fromStdString(inspections_name[i]));

            std::string inspections_printed = "Inspected: " + std::to_string(inspections_num[i]);
            inspection5_number->setGeometry(980 + inspections[1].cols, 300, 140, 30);
            inspection5_number->setText(QString::fromStdString(inspections_printed));

            QImage qtImage(inspections[i].data, inspections[i].cols, inspections[i].rows, inspections[i].step, QImage::Format_BGR888);
            inspection5->setGeometry(980 + inspections[1].cols, 330, inspections[i].cols, inspections[i].rows);
            inspection5->setPixmap(QPixmap::fromImage(qtImage));
        }
    }
}

void MyWidget::showOCRdetections(std::vector<cv::Mat> OCRdetections, std::vector<std::string> OCRreads) {
    OCRdetection1->clear();
    OCRdetection1_sign->clear();
    OCRdetection2->clear();
    OCRdetection2_sign->clear();
    OCRdetection3->clear();
    OCRdetection3_sign->clear();
    for (auto i = 0; i < OCRdetections.size(); i++) {
        if (i == 0) {
            QImage qtImage(OCRdetections[i].data, OCRdetections[i].cols, OCRdetections[i].rows, OCRdetections[i].step, QImage::Format_BGR888);
            OCRdetection1->setPixmap(QPixmap::fromImage(qtImage));
            OCRdetection1_sign->setText(QString::fromStdString(OCRreads[i]));

        }
        else if (i == 1) {
            QImage qtImage(OCRdetections[i].data, OCRdetections[i].cols, OCRdetections[i].rows, OCRdetections[i].step, QImage::Format_BGR888);
            OCRdetection2->setPixmap(QPixmap::fromImage(qtImage));
            OCRdetection2_sign->setText(QString::fromStdString(OCRreads[i]));
        }
        else if (i == 2) {
            QImage qtImage(OCRdetections[i].data, OCRdetections[i].cols, OCRdetections[i].rows, OCRdetections[i].step, QImage::Format_BGR888);
            OCRdetection3->setPixmap(QPixmap::fromImage(qtImage));
            OCRdetection3_sign->setText(QString::fromStdString(OCRreads[i]));
        }
    }
}

void MyWidget::capturePhoto()
{
    //Emit the capture signal to main.cpp
    emit captureRequested(image);
}

void MyWidget::exitApplication()
{
    //Emit the exit signal to main.cpp
    emit exitRequested();
}

void MyWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    //painter.drawImage(0, 0, image);
}
