DESCRIPTION = "Open-source software for mathematics, science, and engineering. It includes modules for statistics, optimization, integration, linear algebra, Fourier transforms, signal and image processing, ODE solvers, and more."
SECTION = "devel/python"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://${S}/numpy-1.25.1.dist-info/LICENSE.txt;md5=cf83c905bb72780bfb15646fc1c1b33a"

PYTHON_PACKAGE = "numpy-1.25.1-cp310-cp310-manylinux_2_17_aarch64.manylinux2014_aarch64.whl"

SRC_URI = "https://files.pythonhosted.org/packages/3c/81/90d13a812268943226a9ca8d4967343f9e273a5d9a1063f8a99736816eba/${PYTHON_PACKAGE};subdir=${BP}"
SRC_URI[md5sum] = "1007893b1a8bfd97d445a63d29d33642"


DEPENDS = "python3 python3-pip-native python3-wheel-native"

RDEPENDS:${PN} = "${PYTHON_PN}"
                  
                 
RPROVIDES:${PN} = "/bin/bash"
inherit python3native

do_unpack[depends] += "unzip-native:do_populate_sysroot"

do_unpack_extra(){
    [ -d ${S} ] || mkdir -p ${S}
    cd ${S}
    unzip -q -o ${S}/${PYTHON_PACKAGE} -d ${S}
}
addtask unpack_extra after do_unpack before do_patch

do_install() {
    # Install pip package
    install -d ${D}/${PYTHON_SITEPACKAGES_DIR}
    cp -r ${S}/numpy ${D}/${PYTHON_SITEPACKAGES_DIR}
    cp -r ${S}/numpy.libs ${D}/${PYTHON_SITEPACKAGES_DIR}
    cp -r ${S}/numpy-1.25.1.dist-info ${D}/${PYTHON_SITEPACKAGES_DIR}

}

RPROVIDES:${PN} = "libgfortran-daac5196.so.5.0.0(GFORTRAN_8)(64bit)"

FILES:${PN} += "\
    ${libdir}/${PYTHON_DIR}/site-packages/* \
"

INSANE_SKIP:${PN} += "already-stripped staticdev"

COMPATIBLE_MACHINE = "(-)"
COMPATIBLE_MACHINE:aarch64 = "(.*)"
