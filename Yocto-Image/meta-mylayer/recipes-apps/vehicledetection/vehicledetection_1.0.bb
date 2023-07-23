SUMMARY = "A recipe to build and install vehicle detection application"
LICENSE = "CLOSED"
RDEPENDS:${PN}:append = " python3-tensorflow-lite python3-opencv"
DEPENDS:append = " opencv"
SRC_URI:append = " file://vehicledetection.py \
		           file://videoplayback_2.mp4 \
                   file://custom_model_lite"

S = "${WORKDIR}"


do_install:append(){
install -d ${D}/etc/Models
cp ${S}/vehicledetection.py ${D}/etc/Models

install -d ${D}/etc/VehicleDetection
cp -r ${S}/custom_model_lite ${D}/etc/VehicleDetection
cp ${S}/videoplayback_2.mp4 ${D}/etc/VehicleDetection

}
FILES:${PN}:append = " /etc/Models/*"
FILES:${PN}:append = " /etc/VehicleDetection/*"
