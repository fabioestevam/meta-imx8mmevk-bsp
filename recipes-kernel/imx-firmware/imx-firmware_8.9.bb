SUMMARY = "Firmware files for use with Linux kernel for i.MX CPUs"
SECTION = "kernel"
LICENSE = "Firmware-nxp-imx-firmware"

inherit allarch deploy

LIC_FILES_CHKSUM = "file://firmware-imx-${PV}/COPYING;md5=983e4c77621568488dd902b27e0c2143"

SRC_URI = "http://www.freescale.com/lgfiles/NMG/MAD/YOCTO/firmware-imx-${PV}.bin"
SRC_URI[md5sum] = "7b36242be60a882f9b5f74bb6e2c6aa1"
SRC_URI[sha256sum] = "a72f70fd2ecaa58800bb88ed672fddc322ab9843ee7777eb89b82016b0aa3614"

do_unpack_extra() {
	dd if=${S}/../firmware-imx-${PV}.bin of=${S}/firmware-imx-${PV}.tar.bz2 \
		bs=$(grep -boam 1 'BZh' ${S}/../firmware-imx-${PV}.bin | cut -d ":" -f 1) \
		skip=1
	tar -C ${S} -xf ${S}/firmware-imx-${PV}.tar.bz2
}
addtask unpack_extra after do_unpack before do_patch

do_compile[noexec] = "1"

do_install() {
	cd ${S}/firmware-imx-${PV}/
	install -d ${D}${nonarch_base_libdir}/firmware/

	# License
	install -d ${D}${nonarch_base_libdir}/firmware/imx/
	install -m 0644 COPYING ${D}${nonarch_base_libdir}/firmware/imx/

	# SDMA firmware
	install -d ${D}${nonarch_base_libdir}/firmware/imx/sdma/
	install -m 0644 firmware/sdma/sdma-imx6q.bin ${D}${nonarch_base_libdir}/firmware/imx/sdma/
	install -m 0644 firmware/sdma/sdma-imx7d.bin ${D}${nonarch_base_libdir}/firmware/imx/sdma/
}

do_deploy() {
	cd ${S}/firmware-imx-${PV}/
	install -m 0644 firmware/ddr/synopsys/*.bin ${DEPLOYDIR}
	install -m 0644 firmware/hdmi/cadence/*.bin ${DEPLOYDIR}
}
addtask deploy after do_install before do_build

NO_GENERIC_LICENSE[Firmware-nxp-imx-firmware] = "firmware-imx-${PV}/COPYING"

LICENSE_${PN}-nxp-imx-license = "Firmware-nxp-imx-firmware"
FILES_${PN}-nxp-imx-license = "${nonarch_base_libdir}/firmware/imx/COPYING"

ALLOW_EMPTY_${PN} = "1"
PACKAGES = " \
	${PN}-nxp-imx-license \
	${PN}-sdma-imx6q ${PN}-sdma-imx7d \
	"

FILES_${PN}-sdma-imx6q = " ${nonarch_base_libdir}/firmware/imx/sdma/sdma-imx6q.bin "
LICENSE_${PN}-sdma-imx6q = "Firmware-nxp-imx-firmware"
RDEPENDS_${PN}-sdma-imx6q += "${PN}-nxp-imx-license"

FILES_${PN}-sdma-imx7d = " ${nonarch_base_libdir}/firmware/imx/sdma/sdma-imx7d.bin "
LICENSE_${PN}-sdma-imx7d = "Firmware-nxp-imx-firmware"
RDEPENDS_${PN}-sdma-imx7d += "${PN}-nxp-imx-license"
