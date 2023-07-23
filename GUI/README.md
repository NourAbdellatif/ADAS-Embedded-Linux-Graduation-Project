# ADAS GUI with Machine Learning Models

![ADAS GUI](adas_gui.png)

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Modes of Operation](#modes-of-operation)
- [Machine Learning Models](#machine-learning-models)
- [Contributing](#contributing)
- [License](#license)

## Introduction

The ADAS GUI is a Graphical User Interface (GUI) developed using the QT framework, designed to provide Advanced Driver Assistance System (ADAS) functionalities. It interfaces with five different machine learning models to enhance the safety and awareness of drivers on the road. The GUI enables users to monitor and receive real-time insights on various aspects of the driving environment.

## Features

- Real-time Drowsiness Detection: The ADAS GUI employs a machine learning model to detect driver drowsiness and alerts the driver when signs of drowsiness are detected.

- Lane Detection: The GUI uses a machine learning model to detect lane boundaries and provides visual feedback to the driver, ensuring they stay within the designated lanes.

- Pedestrian Detection: The ADAS GUI is equipped with a machine learning model that detects pedestrians in the vicinity of the vehicle, providing essential alerts to the driver.

- Traffic Light Detection: This feature utilizes a machine learning model to detect traffic lights and provides real-time information to the driver about upcoming traffic signals.

- Traffic Sign Detection: The GUI uses a machine learning model to recognize and interpret traffic signs, aiding the driver in adhering to traffic regulations.

- Two Modes of Operation:
  - Programmer Mode: In this mode, advanced users and developers have access to additional features and settings, allowing them to fine-tune the system and perform debugging.
  - Customer Mode: This mode is designed for regular users who want a simple and user-friendly interface without the complexities of the programmer mode.

## Installation

To run the ADAS GUI, follow these steps:

1. Clone the repository: `git clone https://github.com/your-username/adas-gui.git`
2. Install the necessary dependencies by running `pip install -r requirements.txt`.
3. Ensure you have QT installed on your system. You can download it from [QT's official website](https://www.qt.io/download).
4. Build and compile the project using QT Creator or the appropriate QT commands for your platform.

## Usage

Once the installation is complete, launch the ADAS GUI application on your device. The main interface will display the real-time camera feed and ADAS information. Depending on the mode of operation selected, different features and settings will be available to the user.

## Modes of Operation

### 1. Programmer Mode

Programmer mode is designed for developers and advanced users who want to customize and fine-tune the ADAS system. It provides the following additional functionalities:

- Access to machine learning model parameters and configurations.
- Debugging options to monitor the performance of individual components.
- Authentication by the agency to login and change the application configuration for the customer.

### 2. Customer Mode

Customer mode offers a simplified interface, making it easy for regular users to benefit from the ADAS system without dealing with technical complexities. It provides essential functionalities such as:

- Real-time drowsiness detection alerts.
- Lane departure warnings and assistance.
- Pedestrian and traffic sign alerts.
- Traffic light status and alerts.

## Machine Learning Models

The ADAS GUI interfaces with the following machine learning models:

1. Drowsiness Detection Model: Detects driver drowsiness based on facial cues and eye movement patterns.

2. Lane Detection Model: Identifies lane boundaries in the camera feed to ensure the driver stays within the correct lane.

3. Pedestrian Detection Model: Detects pedestrians in the vicinity of the vehicle to warn the driver of potential hazards.

4. Traffic Light Detection Model: Recognizes traffic lights in the camera feed and provides real-time information about their status.

5. Traffic Sign Detection Model: Recognizes and interprets traffic signs to assist the driver in obeying traffic regulations.

additional features unique to your implementation. Include appropriate credits, references, and licenses for the machine learning models used in the project.
