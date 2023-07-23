# The is automatic generated Code by "makePipRecipes.py"
# (build by Robin Sebastian (https://github.com/robseb) (git@robseb.de) Vers.: 1.2) 

SUMMARY = "Recipe to embedded the Python PiP Package torch-vision"
HOMEPAGE ="https://pypi.org/project/torch-vision"
LICENSE = "BSD-3"
LIC_FILES_CHKSUM = "file://README.rst;md5=cee985d4e81018c3b96a6ec836e628b5"
RDEPENDS:${PN} = "python3-pillow"


inherit pypi setuptools3
PYPI_PACKAGE = "torch-vision"
SRC_URI[md5sum] = "726f4a66c3953ba3971f938cf42b20ea"
SRC_URI[sha256sum] = "c3f682bc21ef59da0543aeba8191c6a1bbe95ccf18747b636769078ab3fe86d1"
