SUMMARY = "A recipe for The Qt GUI Application"
LICENSE = "CLOSED"
FILESEXTRAPATHS:prepend := "${THISDIR}/systemd:"
RDEPENDS:${PN}:append = " qtbase-tools qtbase qtdeclarative qtimageformats qtmultimedia qtquickcontrols2 qtquickcontrols qtbase-plugins liberation-fonts qtwayland openssl"
DEPENDS:append = " qtbase"
SRC_URI:append = " file://CarDashboard.service \
                   file://CarDashboard.env"
SRC_URI:append = " git://github.com/Hussam82/CarDashboard;protocol=https;branch=master"
SRCREV = "4b1de22c18a01d3178431dbccf455a59c2653121"

S = "${WORKDIR}/git"

inherit systemd
inherit qmake5

do_install:append(){
install -d ${D}${bindir}
install -m 0755 CarDashboard ${D}${bindir}

install -d ${D}${systemd_system_unitdir}
install -m 0644 ../CarDashboard.service ${D}${systemd_system_unitdir}

install -d ${D}/etc
install -m 0644 ../CarDashboard.env ${D}/etc

}


SYSTEMD_SERVICE:${PN} = "CarDashboard.service"
SYSTEMD_AUTO_ENABLE:${PN} = "enable"


FILES:${PN}:append = " ${systemd_system_unitdir}/CarDashboard.service"
FILES:${PN}:append = " /etc/CarDashboard.env"
FILES:${PN}:append = " ${bindir}/CarDashboard"
