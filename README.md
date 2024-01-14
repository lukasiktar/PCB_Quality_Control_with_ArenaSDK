# PCB_YOLOv8_Quality_Control

This is a special Visual Studio C++ project for object detection, extraction, inspection and OCR on printed circuit boards (PCBs).

Project uses ONNX model of YOLOv8 convolutional neural network. The source provided by Ultralytics. Neural network is used to detect objects on Printed Curcuit Boards ( USB, Ethernet, HDMI ports, pins and their soldering patterns, text and other elements). OpenCV is used to load images and performing extraction and inspection. Inspection is performed using adaptive thresholding methods. For specific detected elements OCR is performed. Results are shown in easy-to-use Qt GUI.

Project requirements: Visual Studio 2019/2022 OpenCV 4.8.0 + CUDA compatible with OpenCV version
CuDNN compatible with OpenCV and CUDA
Qt 6.x.x configured in Visual studio
Tesseract configured in Visual studio (used for OCR)

YOLOv8 CNN model is stored in Source file. Model is trained to detect and inspect Arduino UNO, Raspberry Pi, Jetson Nano, Jetson Xavier, Up board, STM32.
Dataset for YOLOv8 training using Roboflow: https://universe.roboflow.com/fmena-dwmmh/pcb_detector_main_v02

YOLOv8Model.ipynb - Google Colab script to train YOLOv8 model on created PCB_detector_main dataset

#  Results:
1. Jetson Nano:
(Detection)
![Snimka zaslona 2024-01-02 103912](https://github.com/robosiki/PCB_Quality_Control_with_ArenaSDK/assets/108216309/0fc59faa-b472-45f8-a5da-2b2047558ab2)
![Snimka zaslona 2024-01-02 103926](https://github.com/robosiki/PCB_Quality_Control_with_ArenaSDK/assets/108216309/d6c6c974-edf0-4af8-9e27-601fc1c48e28)

(Complete Quality Control)
![image](https://github.com/robosiki/PCB_Quality_Control_with_ArenaSDK/assets/108216309/11a5194d-3339-4dad-b0e5-206d4897b377)
![image](https://github.com/robosiki/PCB_Quality_Control_with_ArenaSDK/assets/108216309/b5616b62-ba2e-43c8-ab26-1a175d19ec7f)

3. Jetson Xavier
(Detection)
![Snimka zaslona 2024-01-02 103840](https://github.com/robosiki/PCB_Quality_Control_with_ArenaSDK/assets/108216309/0fd5a0bc-7dbb-4236-88fe-fff0eb329011)
![Snimka zaslona 2024-01-02 103857](https://github.com/robosiki/PCB_Quality_Control_with_ArenaSDK/assets/108216309/7fe63f73-02a8-490e-82fb-18bb3819ca72)

(Complete Quality Control)
![image](https://github.com/robosiki/PCB_Quality_Control_with_ArenaSDK/assets/108216309/4c9aa289-2a89-43ba-b5e4-dbe93a70743e)
![image](https://github.com/robosiki/PCB_Quality_Control_with_ArenaSDK/assets/108216309/8c63802b-fba9-4171-a61d-b30765afecd2)

5. Raspberry Pi
(Detection)
![Snimka zaslona 2024-01-02 103713](https://github.com/robosiki/PCB_Quality_Control_with_ArenaSDK/assets/108216309/c28faab7-b51f-433d-bd9f-068885a354f2)
![Snimka zaslona 2024-01-01 142933](https://github.com/robosiki/PCB_Quality_Control_with_ArenaSDK/assets/108216309/7537508e-7488-4904-a31e-0a92ae68ec96)

(Complete Quality Control)
![image](https://github.com/robosiki/PCB_Quality_Control_with_ArenaSDK/assets/108216309/76579533-a4d8-49e7-be4f-3cff28d5307c)
![image](https://github.com/robosiki/PCB_Quality_Control_with_ArenaSDK/assets/108216309/b4bce7c2-b8a6-42be-b1e1-2cd1f57c40a0)
 
7. Up board
(Detection)
![Snimka zaslona 2024-01-02 103814](https://github.com/robosiki/PCB_Quality_Control_with_ArenaSDK/assets/108216309/13464f32-a57e-4ffe-8dc5-4788dc0cd4f8)
![Snimka zaslona 2024-01-02 103826](https://github.com/robosiki/PCB_Quality_Control_with_ArenaSDK/assets/108216309/a34a3270-a153-4d0b-acd3-26519ff1c021)

(Complete Quality Control)
![image](https://github.com/robosiki/PCB_Quality_Control_with_ArenaSDK/assets/108216309/10fd1f99-5298-4d0f-b5cc-3f74ed732bf7)
![image](https://github.com/robosiki/PCB_Quality_Control_with_ArenaSDK/assets/108216309/476ff5f2-a695-486e-b807-97d21be002fe)

9. Arduino UNO
(Detection)
![Snimka zaslona 2024-01-02 103745](https://github.com/robosiki/PCB_Quality_Control_with_ArenaSDK/assets/108216309/b820d644-8bf7-4f66-9718-b7f4a61a4006)
![Snimka zaslona 2024-01-02 103801](https://github.com/robosiki/PCB_Quality_Control_with_ArenaSDK/assets/108216309/548e06d8-601a-4a81-bbbe-3ad303f30e96)

(Complete Quality Control)
![image](https://github.com/robosiki/PCB_Quality_Control_with_ArenaSDK/assets/108216309/e8197a89-099d-4fa8-b872-6cd31503e9c9)
![image](https://github.com/robosiki/PCB_Quality_Control_with_ArenaSDK/assets/108216309/0f25bf16-f4f7-4f74-9452-c38f110b17af)

11. STM32
(Detection)
![Snimka zaslona 2024-01-02 103946](https://github.com/robosiki/PCB_Quality_Control_with_ArenaSDK/assets/108216309/86cf9ea9-7f16-4130-9ebc-af7bf8927263)
![Snimka zaslona 2024-01-02 104000](https://github.com/robosiki/PCB_Quality_Control_with_ArenaSDK/assets/108216309/812868fa-356d-4c28-a0b6-1fadbc2fd140)

(Complete Quality Control)
![image](https://github.com/robosiki/PCB_Quality_Control_with_ArenaSDK/assets/108216309/3e475215-b1c0-4789-ab41-2917451cb387)
![image](https://github.com/robosiki/PCB_Quality_Control_with_ArenaSDK/assets/108216309/b2a1f306-bdd1-404a-bcd6-b9d9f3dc5319)











