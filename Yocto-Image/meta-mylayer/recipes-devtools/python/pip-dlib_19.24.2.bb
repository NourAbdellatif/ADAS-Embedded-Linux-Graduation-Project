# SPDX-License-Identifier: MIT
# Copyright (C) 2021 iris-GmbH infrared & intelligent sensors

SUMMARY = "A toolkit for making real world machine learning and data analysis applications"
HOMEPAGE = "http://dlib.net"
SECTION = "libs"

LICENSE = "BSL-1.0"
LIC_FILES_CHKSUM = "file://LICENSE.txt;md5=2c7a3fa82e66676005cd4ee2608fd7d2"

SRC_URI = "git://github.com/davisking/dlib.git;protocol=https;branch=master"
SRCREV = "074ab8bdbadbee1afb95653c3ce46867ed32dfa1"
S = "${WORKDIR}/git"

inherit cmake setuptools3


