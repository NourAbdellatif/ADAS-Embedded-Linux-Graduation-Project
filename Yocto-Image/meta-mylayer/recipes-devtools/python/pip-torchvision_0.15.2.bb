DESCRIPTION = "Open-source software for mathematics, science, and engineering. It includes modules for statistics, optimization, integration, linear algebra, Fourier transforms, signal and image processing, ODE solvers, and more."
SECTION = "devel/python"
HOMEPAGE = "https://www.scipy.org"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://${S}/torchvision-0.15.2.dist-info/LICENSE;md5=bd7749a3307486a4d4bfefbc81c8b796"

PYTHON_PACKAGE = "torchvision-0.15.2-cp310-cp310-manylinux2014_aarch64.whl"

SRC_URI = "https://files.pythonhosted.org/packages/16/5e/51c5fde550161edcfa3e131c51a8b4261775ebb2b118b3560116fa9f7a73/${PYTHON_PACKAGE};subdir=${BP}"
SRC_URI[md5sum] = "513171e835ee64bf210a028320e22eac"


DEPENDS = "python3 python3-pip-native python3-wheel-native"

RDEPENDS:${PN} = "${PYTHON_PN} \
                  python3-numpy \
                  ${PYTHON_PN}-pillow"


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
    cp -r ${S}/torchvision ${D}/${PYTHON_SITEPACKAGES_DIR}
    cp -r ${S}/torchvision-0.15.2.dist-info ${D}/${PYTHON_SITEPACKAGES_DIR}

}

RPROVIDES:${PN} = "libc10.so()(64bit) \
                   libtorch.so()(64bit) \
                   libtorch_cpu.so()(64bit) \
                   libtorch_python.so()(64bit)"

FILES:${PN} += "\
    ${libdir}/${PYTHON_DIR}/site-packages/* \
"

INSANE_SKIP:${PN} += "already-stripped"

COMPATIBLE_MACHINE = "(-)"
COMPATIBLE_MACHINE:aarch64 = "(.*)"
