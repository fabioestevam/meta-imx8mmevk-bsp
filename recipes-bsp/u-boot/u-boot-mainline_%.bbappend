FILESEXTRAPATHS_prepend := "${THISDIR}/files/common:${THISDIR}/files/${MACHINE}:${THISDIR}/files:"
SRC_URI_append = "file://fw_env.config"
RPROVIDES_${PN} = "virtual/bootloader"

DEPENDS_append_imx8mmevk = "u-boot-mainline-tools-native"

SRC_URI_append_imx8mmevk = " \
	file://0001-Revert-imx8mm_evk-switch-to-use-binman-to-pack-image.patch \
	file://0002-imx8mm-evk-Adjust-boot-environment.patch \
	file://0003-imx8mm_evk-Add-redundand-environment-support.patch \
	"
EXTRA_OEMAKE_append_imx8mmevk = " ATF_LOAD_ADDR=0x920000 "

# This is needed by binman during U-Boot build
DEPENDS_append_imx8mmevk = " python3-setuptools-native "

do_compile[depends] += "${@'imx-firmware:do_deploy trusted-firmware-a:do_deploy' if ('imx8mmevk' in d.getVar('MACHINEOVERRIDES', True).split(':')) else ' '}"

do_compile_prepend_imx8mmevk () {
        cp -Lv ${DEPLOY_DIR_IMAGE}/lpddr4_pmu_train_*mem.bin ${B}/
        cp -Lv ${DEPLOY_DIR_IMAGE}/bl31-imx8mm.bin ${B}/bl31.bin
}
