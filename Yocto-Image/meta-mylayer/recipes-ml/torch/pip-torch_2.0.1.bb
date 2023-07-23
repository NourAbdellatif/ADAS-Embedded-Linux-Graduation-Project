# The is automatic generated Code by "makePipRecipes.py"
# (build by Robin Sebastian (https://github.com/robseb) (git@robseb.de) Vers.: 1.2) 

SUMMARY = "PyTorch package for pip"
DESCRIPTION = "PyTorch is an optimized tensor library for deep learning using GPUs and CPUs."
LICENSE = "BSD-3-Clause"
LIC_FILES_CHKSUM = "file://${S}/torch-2.0.1.dist-info/LICENSE;md5=a3f0ab8676e02692c14a5a1b617efde1"

PYTHON_PACKAGE = "torch-2.0.1-cp310-cp310-manylinux2014_aarch64.whl"
inherit cmake

SRC_URI = "https://files.pythonhosted.org/packages/21/33/4925decd863ce88ed9190a4bd872b01c146243ee68db08c72923984fe335/${PYTHON_PACKAGE};subdir=${BP}"
SRC_URI += "file://CMakeLists.txt"
SRC_URI[md5sum] = "0e1035ad5717c1b9f2dbfa659385e5ee"


do_unpack[depends] += "unzip-native:do_populate_sysroot"

do_unpack_extra(){
    cp ${WORKDIR}/CMakeLists.txt ${S}/
    [ -d ${S} ] || mkdir -p ${S}
    cd ${S}
    unzip -q -o ${S}/${PYTHON_PACKAGE} -d ${S}
}
addtask unpack_extra after do_unpack before do_patch


RDEPENDS:${PN} = "pip-astunparse pip-expecttest pip-types-dataclasses pip-fsspec python3-hypothesis python3-numpy python3-psutil python3-pyyaml python3-requests python3-setuptools python3-typing-extensions python3-sympy python3-networkx python3-jinja2"

FILES:${PN} += "/usr/lib/python3.10/site-packages/*"

RPROVIDES:${PN} = "libgomp-d22c30c5.so.1.0.0(GOMP_4.0)(64bit) \
                   libgomp-d22c30c5.so.1.0.0(OMP_1.0)(64bit) \
                   libgomp-d22c30c5.so.1.0.0(OMP_4.5)(64bit) \
                   libgomp-d22c30c5.so.1.0.0(GOMP_1.0)(64bit)"
            
INSANE_SKIP:${PN} = "already-stripped"


