DESCRIPTION = "Open-source software for mathematics, science, and engineering. It includes modules for statistics, optimization, integration, linear algebra, Fourier transforms, signal and image processing, ODE solvers, and more."
SECTION = "devel/python"
HOMEPAGE = "https://www.scipy.org"
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://${S}/scikit_learn-1.3.0.dist-info/COPYING;md5=e087d8348a7a6d2b63e1f305d7acf1a9"

PYTHON_PACKAGE = "scikit_learn-1.3.0-cp310-cp310-manylinux_2_17_aarch64.manylinux2014_aarch64.whl"

SRC_URI = "https://files.pythonhosted.org/packages/a0/61/970fbef9dcb224023f2c2ddf19b13e5a96b5185705c4a075108bbe7fa7f9/${PYTHON_PACKAGE};subdir=${BP}"
SRC_URI[md5sum] = "bba86429a0e57500055b449d98cb8d43"


DEPENDS = "python3 python3-pip-native python3-wheel-native"

RDEPENDS:${PN} = "${PYTHON_PN} \
	          ${PYTHON_PN}-scipy \
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
    cp -r ${S}/sklearn ${D}/${PYTHON_SITEPACKAGES_DIR}
    cp -r ${S}/scikit_learn.libs ${D}/${PYTHON_SITEPACKAGES_DIR}
    cp -r ${S}/scikit_learn-1.3.0.dist-info ${D}/${PYTHON_SITEPACKAGES_DIR}

}

RPROVIDES:${PN} = "libgomp-d22c30c5.so.1.0.0(GOMP_4.0)(64bit) \
                   libgomp-d22c30c5.so.1.0.0(OMP_1.0)(64bit) \
                   libgomp-d22c30c5.so.1.0.0(OMP_4.5)(64bit) \
                   libgomp-d22c30c5.so.1.0.0(OMP_3.0)(64bit) \
                   libgomp-d22c30c5.so.1.0.0(GOMP_1.0)(64bit)"
                   
FILES:${PN} += "\
    ${libdir}/${PYTHON_DIR}/site-packages/* \
"

INSANE_SKIP:${PN} += "already-stripped"

COMPATIBLE_MACHINE = "(-)"
COMPATIBLE_MACHINE:aarch64 = "(.*)"
