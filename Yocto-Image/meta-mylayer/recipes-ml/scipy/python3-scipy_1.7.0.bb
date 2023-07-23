DESCRIPTION = "Open-source software for mathematics, science, and engineering. It includes modules for statistics, optimization, integration, linear algebra, Fourier transforms, signal and image processing, ODE solvers, and more."
SECTION = "devel/python"
HOMEPAGE = "https://www.scipy.org"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://${S}/scipy-1.11.0.dist-info/LICENSE.txt;md5=1c243faf9bae0db3ce940e26164c7852"

PYTHON_PACKAGE = "scipy-1.11.0-cp310-cp310-manylinux_2_17_aarch64.manylinux2014_aarch64.whl"

SRC_URI = "https://files.pythonhosted.org/packages/fc/17/49b393887ab0d8df6ea1d5d0a55c13c87008510762b0f6d128cfd338416c/${PYTHON_PACKAGE};subdir=${BP}"
SRC_URI[md5sum] = "bbab95fed977823e90fcc9c03986f389"


DEPENDS = "python3 python3-pip-native python3-wheel-native"

RDEPENDS:${PN} = "${PYTHON_PN} \
                  ${PYTHON_PN}-numpy \
"
RPROVIDES:${PN} += "\
    libgfortran-daac5196.so.5.0.0(GFORTRAN_8)(64bit) \
"

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
    cp -r ${S}/scipy ${D}/${PYTHON_SITEPACKAGES_DIR}
    cp -r ${S}/scipy.libs ${D}/${PYTHON_SITEPACKAGES_DIR}
    cp -r ${S}/scipy-1.11.0.dist-info ${D}/${PYTHON_SITEPACKAGES_DIR}

}

FILES:${PN} += "\
    ${libdir}/${PYTHON_DIR}/site-packages/* \
"

INSANE_SKIP:${PN} += "already-stripped"

COMPATIBLE_MACHINE = "(-)"
COMPATIBLE_MACHINE:aarch64 = "(.*)"
