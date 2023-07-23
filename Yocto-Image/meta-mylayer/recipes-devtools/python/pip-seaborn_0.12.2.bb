DESCRIPTION = "Open-source software for mathematics, science, and engineering. It includes modules for statistics, optimization, integration, linear algebra, Fourier transforms, signal and image processing, ODE solvers, and more."
SECTION = "devel/python"
HOMEPAGE = "https://www.scipy.org"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://${S}/seaborn-0.12.2.dist-info/LICENSE.md;md5=a6bb18b889620c6cb9f24aa008bcb365"

PYTHON_PACKAGE = "seaborn-0.12.2-py3-none-any.whl"

SRC_URI = "https://files.pythonhosted.org/packages/8f/2e/17bbb83fbf102687bb2aa3d808add39da820a7698159302a1a69bb82e01c/${PYTHON_PACKAGE};subdir=${BP}"
SRC_URI[md5sum] = "e3d6ea484a1b494eb5bfe01f68ba41f5"


DEPENDS = "python3 python3-pip-native python3-wheel-native"

RDEPENDS:${PN} = "${PYTHON_PN} \
                  python3-numpy "


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
    cp -r ${S}/seaborn ${D}/${PYTHON_SITEPACKAGES_DIR}
    cp -r ${S}/seaborn-0.12.2.dist-info ${D}/${PYTHON_SITEPACKAGES_DIR}

}

FILES:${PN} += "\
    ${libdir}/${PYTHON_DIR}/site-packages/* \
"

INSANE_SKIP:${PN} += "already-stripped"

COMPATIBLE_MACHINE = "(-)"
COMPATIBLE_MACHINE:aarch64 = "(.*)"
