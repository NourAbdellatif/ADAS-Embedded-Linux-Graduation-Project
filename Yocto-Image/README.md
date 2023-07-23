# Yocto-Image (Graduation Project)
This repository contains code and instructions for building a custom Linux distribution using Yocto Project. The resulting image can be used on embedded devices such as Raspberry Pi 4. It contains recipes for computer vision application like Lane Detection, Pedestrian Detection, Vehicle Detection, Traffic Signs/Light Detection. Also, it contains some recipes to install some dependecies that is required by these applications.

## Features
Customizable Linux distribution
Support for various hardware platforms
Cross-compilation support
Automatic dependency resolution
Custom kernel and bootloader configuration
## Installation
Clone the repository
Install dependencies (see the Yocto Project documentation for details)
Configure the build environment (source the oe-init-build-env script)
Build the image (bitbake <image-name>)
## Usage
Flash the resulting image to the target device
Boot the device and log in using the credentials specified in the image configuration

## Demo
A demo for the project working in action will be found on the next google drive link:

https://drive.google.com/file/d/11ztduhAdvdS94qrDeQF4aJ3HlVZTIkJh/view?usp=drive_link


## Limitations
Requires some familiarity with the Yocto Project and Linux system administration
Builds can take a long time on slower hardware
Device compatibility may vary depending on the selected options and configurations
## Acknowledgments
This project was inspired and influenced by the work of the Yocto Project community and developers.
Also, it was mentored by Eng. Moatassem ElSayed a Senior Embedded Linux Engineer at Valeo

## Contributors
This project was the graduation project of a group of 5 from Faculty of Engineering, EECE department, Cairo University, Class of 2023.

My teammates are:

Ahmed Osama Abdulmaksoud

LinkedIn Link: https://www.linkedin.com/in/ahmed-osama-73a37820a/

Abdulrahman Yousry

LinkedIn Link: https://www.linkedin.com/in/abdelrahman-yousry-323baa194/

Abdulrahman Farid

LinkedIn Link: https://www.linkedin.com/in/abdelrahman-farid-218708217/

Nour Abdelatif

LinkedIn Link: https://www.linkedin.com/in/nourabdellatif/

## References
ADAS.API ↗: A RESTful API for accessing advanced driver assistance system (ADAS) data and its GitHub Repo Link: https://github.com/NourAbdellatif/ADAS.API

CarDashboard ↗: A Qt-based dashboard for displaying ADAS data and other vehicle information.
GitHub Repo Link: https://github.com/Hussam82/CarDashboard
