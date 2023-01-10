FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

PV .= "+git${SRCPV}"

SRCBRANCH = "lf_v2.6"
SRC_URI = "git://github.com/nxp-imx/imx-atf.git;protocol=https;branch=${SRCBRANCH}"
SRCREV = "3c1583ba0a5d11e5116332e91065cb3740153a46"

S = "${WORKDIR}/git"

LIC_FILES_CHKSUM = "file://${COREBASE}/meta/files/common-licenses/BSD-3-Clause;md5=550794465ba0ec5312d6919e203a55f9"

#
# mbed TLS source
# Those are used in trusted-firmware-a.inc if TFA_MBEDTLS is set to 1
#

SRC_URI_MBEDTLS = "git://github.com/ARMmbed/mbedtls.git;name=mbedtls;protocol=https;destsuffix=git/mbedtls"

# mbed TLS v2.16.2
SRCREV_mbedtls = "d81c11b8ab61fd5b2da8133aa73c5fe33a0633eb"

LIC_FILES_CHKSUM_MBEDTLS += " \
    file://mbedtls/apache-2.0.txt;md5=3b83ef96387f14655fc854ddc3c6bd57 \
    file://mbedtls/LICENSE;md5=302d50a6369f5f22efdb674db908167a \
    "

SRC_URI[mbedtls.md5sum] = "37cdec398ae9ebdd4640df74af893c95"
SRC_URI[mbedtls.sha256sum] = "a6834fcd7b7e64b83dfaaa6ee695198cb5019a929b2806cb0162e049f98206a4"

require trusted-firmware-a.inc

# The following hack is needed to fit properly in yocto build environment
# TFA is forcing the host compiler and its flags in the Makefile using :=
# assignment for GCC and CFLAGS.
# To properly use the native toolchain of yocto and the right libraries we need
# to pass the proper flags to gcc. This is achieved here by creating a gcc
# script to force passing to gcc the right CFLAGS and LDFLAGS
do_compile:prepend() {
    #Create an host gcc build parser to ensure the proper include path is used
    mkdir -p bin
    echo "#!/usr/bin/env bash" > bin/gcc
    echo "$(which ${BUILD_CC}) ${BUILD_CFLAGS} ${BUILD_LDFLAGS} \$@" >> bin/gcc
    chmod a+x bin/gcc
    export PATH="$PWD/bin:$PATH"
}
