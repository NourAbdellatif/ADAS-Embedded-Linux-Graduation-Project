SUMMARY = "This is a hello world kernel module recipe"
DESCRIPTION = "${SUMMARY}"
LICENSE = "CLOSED"


inherit module

SRC_URI = "file://Makefile \
           file://test_driver.c \
          "

S = "${WORKDIR}"

KERNEL_MODULE_AUTOLOAD += "test_driver"

# The inherit of module.bbclass will automatically name module packages with
# "kernel-module-" prefix as required by the oe-core build environment.

RPROVIDES:${PN} += "kernel-module-test_driver"
