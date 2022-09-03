#@TYPE: Machine
#@NAME: Compulab i.MX8MM EVK
#@SOC:  Freescale i.MX8MM
#@DESCRIPTION: Machine configuration for NXP i.MX8MM EVk

DEFAULTTUNE ?= "aarch64"
SOC_FAMILY ?= "imx8mm"

MACHINEOVERRIDES =. "mx8:mx8m:mx8mm:"

require conf/machine/include/arm/armv8a/tune-cortexa53.inc
require conf/machine/include/soc-family.inc

MACHINE_FEATURES ?= "apm alsa ext2 keyboard screen serial touchscreen usbhost wifi bluetooth"

SERIAL_CONSOLE = "115200 ttymxc1"

# U-Boot bootloader
UBOOT_ENTRYPOINT := "0x44000000"
UBOOT_MAKE_TARGET := "flash.bin"
UBOOT_BINARY := "flash.bin"
UBOOT_SUFFIX ?= "bin"
UBOOT_DTB_LOADADDRESS = "0x7ff00000"
UBOOT_DTBO_LOADADDRESS = "0x7ff80000"
UBOOT_MACHINE = "imx8mm_evk_defconfig"

PREFERRED_PROVIDER_virtual/bootloader ?= "u-boot-mainline"
PREFERRED_PROVIDER_u-boot ?= "u-boot-mainline"
PREFERRED_PROVIDER_u-boot-native ?= "u-boot-mainline"
PREFERRED_PROVIDER_u-boot-fw-utils ?= "u-boot-mainline-fw-utils"
PREFERRED_PROVIDER_u-boot-fw-utils-native ?= "u-boot-mainline-fw-utils-native"
PREFERRED_PROVIDER_u-boot-tools ?= "u-boot-mainline-tools"
PREFERRED_PROVIDER_u-boot-tools-native ?= "u-boot-mainline-tools-native"
PREFERRED_VERSION_u-boot-mainline ?= "2022.07%"
PREFERRED_VERSION_u-boot-mainline-native ?= "2022.07%"
PREFERRED_VERSION_u-boot-mainline-fw-utils ?= "2022.07%"
PREFERRED_VERSION_u-boot-mainline-fw-utils-native ?= "2022.07%"
PREFERRED_VERSION_u-boot-mainline-tools ?= "2022.07%"
PREFERRED_VERSION_u-boot-mainline-tools-native ?= "2022.07%"

# Linux kernel
KERNEL_IMAGETYPE = "Image"
FIT_KERNEL_COMP_ALG = "lzo"
FIT_KERNEL_COMP_ALG_EXTENSION = ".lzo"
KERNEL_MODULE_AUTOLOAD += " \
	ci_hdrc \
	ci_hdrc_imx \
	edt-ft5x06 \
	ehci_hcd \
	ehci_mxc \
	i2c_imx \
	uinput \
	usbcore \
	usbmisc_imx \
	usb_phy_generic \
	usb_storage \
	cfg80211 \
	iwlwifi \
	"

PREFERRED_PROVIDER_virtual/kernel ?= "linux-stable"
PREFERRED_VERSION_linux-stable ?= "5.19%"

KERNEL_DEVICETREE = " \
	freescale/imx8mm-evk.dtb \
	"

# Ship kernel modules
MACHINE_ESSENTIAL_EXTRA_RDEPENDS += " \
	kernel-modules kernel-devicetree \
	u-boot-default-env \
	imx-firmware-sdma-imx7d \
	"

# List of images to be built
IMAGE_FSTYPES ?= "wic.gz wic.xz ext4.gz wic.bmap"
INITRAMFS_FSTYPES ?= "cpio.xz"

EXTRA_IMAGEDEPENDS += "virtual/bootloader"
WKS_FILE = "emmcimage-imx8mmevk.wks"
IMAGE_BOOT_FILES ?= "${KERNEL_IMAGETYPE}"
IMAGE_INSTALL:append = " kernel-devicetree virtual/bootloader rng-tools u-boot-default-env btrfs-tools mmc-utils pciutils \
			  wireless-regdb-static iw wpa-supplicant "
do_image_wic[depends] += "mtools-native:do_populate_sysroot dosfstools-native:do_populate_sysroot virtual/bootloader:do_deploy"

