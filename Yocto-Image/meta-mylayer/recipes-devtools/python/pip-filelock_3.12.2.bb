DESCRIPTION = "Open-source software for mathematics, science, and engineering. It includes modules for statistics, optimization, integration, linear algebra, Fourier transforms, signal and image processing, ODE solvers, and more."
SECTION = "devel/python"
HOMEPAGE = "https://www.scipy.org"
LICENSE = "Unlicense"
LIC_FILES_CHKSUM = "file://${S}/filelock-3.12.2.dist-info/licenses/LICENSE;md5=911690f51af322440237a253d695d19f"

PYTHON_PACKAGE = "filelock-3.12.2-py3-none-any.whl"

SRC_URI = "https://files.pythonhosted.org/packages/00/45/ec3407adf6f6b5bf867a4462b2b0af27597a26bd3cd6e2534cb6ab029938/${PYTHON_PACKAGE};subdir=${BP}"
SRC_URI[md5sum] = "4ff1be60b3d76c6764c29c73d766ca09"


DEPENDS = "python3 python3-pip-native python3-wheel-native"

RDEPENDS:${PN} = "${PYTHON_PN}"

                  
                 

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
    cp -r ${S}/filelock ${D}/${PYTHON_SITEPACKAGES_DIR}
    cp -r ${S}/filelock-3.12.2.dist-info ${D}/${PYTHON_SITEPACKAGES_DIR}

}


FILES:${PN} += "\
    ${libdir}/${PYTHON_DIR}/site-packages/* \
"

INSANE_SKIP:${PN} += "already-stripped"

COMPATIBLE_MACHINE = "(-)"
COMPATIBLE_MACHINE:aarch64 = "(.*)"
