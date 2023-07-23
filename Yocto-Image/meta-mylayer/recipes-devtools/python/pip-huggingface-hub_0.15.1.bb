DESCRIPTION = "Open-source software for mathematics, science, and engineering. It includes modules for statistics, optimization, integration, linear algebra, Fourier transforms, signal and image processing, ODE solvers, and more."
SECTION = "devel/python"
HOMEPAGE = "https://www.scipy.org"
LICENSE = "Apache"
LIC_FILES_CHKSUM = "file://${S}/huggingface_hub-0.15.1.dist-info/LICENSE;md5=86d3f3a95c324c9479bd8986968f4327"

PYTHON_PACKAGE = "huggingface_hub-0.15.1-py3-none-any.whl"

SRC_URI = "https://files.pythonhosted.org/packages/62/a2/8a416d167216403ceeef3aaf8c22b0c61b1ae571644473d67eb7fecbb69e/${PYTHON_PACKAGE};subdir=${BP}"
SRC_URI[md5sum] = "40716f5f15a1e4bcf9663ac5c0cfed54"


DEPENDS = "python3 python3-pip-native python3-wheel-native"



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
    cp -r ${S}/huggingface_hub ${D}/${PYTHON_SITEPACKAGES_DIR}
    cp -r ${S}/huggingface_hub-0.15.1.dist-info ${D}/${PYTHON_SITEPACKAGES_DIR}

}

FILES:${PN} += "\
    ${libdir}/${PYTHON_DIR}/site-packages/* \
"

INSANE_SKIP:${PN} += "already-stripped"

COMPATIBLE_MACHINE = "(-)"
COMPATIBLE_MACHINE:aarch64 = "(.*)"
