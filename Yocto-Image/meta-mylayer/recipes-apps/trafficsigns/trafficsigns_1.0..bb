SUMMARY = "A recipe to build and install traffic signs detection application"
LICENSE = "CLOSED"
RDEPENDS:${PN}:append = " python3-opencv pip-yolov5"
DEPENDS:append = " opencv"
SRC_URI:append = " file://trafficsigns.py \
                   file://best_ts.pt \
                   file://videoplayback_5_Trim.mp4"

S = "${WORKDIR}"


do_install:append(){
install -d ${D}/etc/Models
cp ${S}/trafficsigns.py ${D}/etc/Models

install -d ${D}/etc/TrafficSignsDetection
cp -r ${S}/best_ts.pt ${D}/etc/TrafficSignsDetection
cp ${S}/videoplayback_5_Trim.mp4 ${D}/etc/TrafficSignsDetection

}
FILES:${PN}:append = " /etc/Models/*"
FILES:${PN}:append = " /etc/TrafficSignsDetection/*"
