DESCRIPTION = "Open-source software for mathematics, science, and engineering. It includes modules for statistics, optimization, integration, linear algebra, Fourier transforms, signal and image processing, ODE solvers, and more."
SECTION = "devel/python"
HOMEPAGE = "https://www.scipy.org"
LICENSE = "GPL"
LIC_FILES_CHKSUM = "file://${S}/yolov5-7.0.12.dist-info/LICENSE;md5=97ff9683aa36f333c7d2295d6520090f"

PYTHON_PACKAGE = "yolov5-7.0.12-py37.py38.py39.py310-none-any.whl"

SRC_URI = "https://files.pythonhosted.org/packages/ba/6f/52449e79074fc4a319ec384e02bfbb812e3d5ca0a14a5ebc6c2dd04aa089/${PYTHON_PACKAGE};subdir=${BP}"
SRC_URI[md5sum] = "cc965558e2c0d929810a608272c466c6"


DEPENDS = "python3 python3-pip-native python3-wheel-native"

RDEPENDS:${PN} = "${PYTHON_PN} \
                  ${PYTHON_PN}-pillow \
                  ${PYTHON_PN}-matplotlib \
                  ${PYTHON_PN}-psutil \
                  ${PYTHON_PN}-pyyaml \
                  ${PYTHON_PN}-scipy \
                  ${PYTHON_PN}-requests \
                  ${PYTHON_PN}-tqdm \
                  pip-ultralytics \
                  pip-torch \
                  pip-huggingface-hub \
                  python3-numpy \
                  pip-torchvision"
                  
                 
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
    cp -r ${S}/yolov5 ${D}/${PYTHON_SITEPACKAGES_DIR}
    cp -r ${S}/yolov5/models ${D}/${PYTHON_SITEPACKAGES_DIR}
    cp -r ${S}/yolov5-7.0.12.dist-info ${D}/${PYTHON_SITEPACKAGES_DIR}

}


FILES:${PN} += "\
    ${libdir}/${PYTHON_DIR}/site-packages/* \
"

INSANE_SKIP:${PN} += "already-stripped"

COMPATIBLE_MACHINE = "(-)"
COMPATIBLE_MACHINE:aarch64 = "(.*)"
