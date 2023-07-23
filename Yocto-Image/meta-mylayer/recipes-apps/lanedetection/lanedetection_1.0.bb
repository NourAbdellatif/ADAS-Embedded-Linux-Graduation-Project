DESCRIPTION   = " This is The Lane Detection Application Recipe"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://main.cpp \
	   file://lane-detection.cpp \
	   file://lane-detection.h \
	   file://regression.h \
	   file://CMakeLists.txt \
	   file://dashcam4.mp4 "



DEPENDS = "opencv"
RDEPENDS_${PN} = "libopencv-core libopencv-imgproc libopencv-highgui libopencv-videoio libopencv-imgcodecs"
S = "${WORKDIR}"

inherit cmake


FILES_${PN} = "/etc/Models/*"
