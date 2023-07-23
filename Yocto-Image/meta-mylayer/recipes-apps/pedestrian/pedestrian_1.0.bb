SUMMARY = "A recipe to build and install pedestrian detection application"
LICENSE = "CLOSED"
RDEPENDS:${PN}:append = " python3-opencv pip-yolov5"
DEPENDS:append = " opencv"
SRC_URI:append = " file://pedestrian.py \
                   file://best_ped.pt \
                   file://cross.mp4"

S = "${WORKDIR}"


do_install:append(){
install -d ${D}/etc/Models
cp ${S}/pedestrian.py ${D}/etc/Models

install -d ${D}/etc/PedestrianDetection
cp -r ${S}/best_ped.pt ${D}/etc/PedestrianDetection
cp ${S}/cross.mp4 ${D}/etc/PedestrianDetection

}
FILES:${PN}:append = " /etc/Models/*"
FILES:${PN}:append = " /etc/PedestrianDetection/*"
