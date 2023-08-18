FILESEXTRAPATHS:prepend := "${THISDIR}/files/common:${THISDIR}/files/${MACHINE}:${THISDIR}/files:"
RPROVIDES:${PN} = "virtual/bootloader"

DEPENDS:append:imx8mmevk = "u-boot-mainline-tools-native"

SRC_URI:append:imx8mmevk = " \
        file://0001-imx8mm-evk-Adjust-boot-environment.patch \
        file://0002-mx8mm_evk-Add-redundand-environment-support.patch \
        file://fw_env.config \
	"
EXTRA_OEMAKE:append:imx8mmevk = " ATF_LOAD_ADDR=0x920000 "

# This is needed by binman during U-Boot build
DEPENDS:append:imx8mmevk = " python3-setuptools-native imx-firmware trusted-firmware-a "

do_compile[depends] += "${@'imx-firmware:do_deploy trusted-firmware-a:do_deploy' if ('imx8mmevk' in d.getVar('MACHINEOVERRIDES', True).split(':')) else ' '}"

do_compile:prepend:imx8mmevk () {
        cp -Lv ${DEPLOY_DIR_IMAGE}/lpddr4_pmu_train_*mem.bin ${B}/
        cp -Lv ${DEPLOY_DIR_IMAGE}/bl31-imx8mm.bin ${B}/bl31.bin
}
