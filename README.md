# PCB_YOLOv8_Quality_Control

This is a special Visual Studio C++ project for object detection, extraction, inspection and OCR on printed circuit boards.

Project uses ONNX model of YOLOv8 convolutional neural network. The source provided by Ultralytics. Neural network is used to detect objects on Printed Curcuit Boards ( USB, Ethernet, HDMI ports, pins and their soldering patterns, text and other elements). OpenCV is used to load images and performing extraction and inspection. Inspection is performed using adaptive thresholding methods. For specific detected elements OCR is performed. Results are shown in easy-to-use Qt GUI.

Project requirements: Visual Studio 2019/2022 OpenCV 4.8.0 + CUDA compatible with OpenCV version
CuDNN compatible with OpenCV and CUDA
Qt 6.x.x configured in Visual studio
Tesseract configured in Visual studio (used for OCR)

YOLOv8 CNN model is stored in Source file. Model is trained to detect and inspect Arduino UNO, Raspberry Pi, Jetson Nano, Jetson Xavier, Up board, STM32.
Dataset for YOLOv8 training: https://universe.roboflow.com/fmena-dwmmh/pcb_detector_main

#  Results:
1. Jetson Nano:

![image](https://github.com/robosiki/PCB_YOLOv8_Quality_Control/assets/108216309/4b3fc143-0747-4b10-b5e0-77e257a2e397)
![image](https://github.com/robosiki/PCB_YOLOv8_Quality_Control/assets/108216309/591a2f1f-1574-4367-bcd6-e478d366fcdd)

2. Jetson Xavier
   
![image](https://github.com/robosiki/PCB_YOLOv8_Quality_Control/assets/108216309/01ad800e-24fa-4ad8-b6b8-af495b12bc4a)
![image](https://github.com/robosiki/PCB_YOLOv8_Quality_Control/assets/108216309/f17849b4-cd21-442b-b7fe-19eb296eae8e)

3. Raspberry Pi
   
![image](https://github.com/robosiki/PCB_YOLOv8_Quality_Control/assets/108216309/8b7da8cf-4cc9-42b2-9069-dd5cd2e8503f)
![image](https://github.com/robosiki/PCB_YOLOv8_Quality_Control/assets/108216309/f53d5978-b24f-4fbf-b2ae-0a26c8ab3049)

4. Up board
   
![image](https://github.com/robosiki/PCB_YOLOv8_Quality_Control/assets/108216309/1b6542f5-a3c8-40fd-8a61-4a761dbac350)
![image](https://github.com/robosiki/PCB_YOLOv8_Quality_Control/assets/108216309/e0fc3c7f-a869-41ab-b045-6043c20a6192)

5. Arduino UNO
    
![image](https://github.com/robosiki/PCB_YOLOv8_Quality_Control/assets/108216309/e3935b72-3f7e-4dc2-b551-a575414f8a3e)
![image](https://github.com/robosiki/PCB_YOLOv8_Quality_Control/assets/108216309/6469d5c4-0516-4adc-9453-96216b2dd307)

6. STM32
![image](https://github.com/robosiki/PCB_YOLOv8_Quality_Control/assets/108216309/c0249d78-dbcc-428b-8372-fe80c0524979)
![image](https://github.com/robosiki/PCB_YOLOv8_Quality_Control/assets/108216309/8ef88333-b12a-4386-93d3-5ff54b8cac84)










