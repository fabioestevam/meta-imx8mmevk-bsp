#@TYPE: Machine
#@NAME: NXP i.MX8MM EVK
#@SOC:  Freescale i.MX8MM
#@DESCRIPTION: Machine configuration for NXP i.MX8MM EVk

DEFAULTTUNE ?= "aarch64"
SOC_FAMILY ?= "imx8mm"

MACHINEOVERRIDES =. "mx8:mx8m:mx8mm:"

require conf/machine/include/arm/armv8a/tune-cortexa53.inc
require conf/machine/include/soc-family.inc

MACHINE_FEATURES ?= "apm alsa ext2 keyboard screen serial touchscreen usbhost wifi bluetooth"

SERIAL_CONSOLES = "115200;ttymxc1"

# U-Boot bootloader
UBOOT_ENTRYPOINT := "0x44000000"
UBOOT_MAKE_TARGET := "flash.bin"
UBOOT_BINARY := "flash.bin"
UBOOT_SUFFIX ?= "bin"
UBOOT_DTB_LOADADDRESS = "0x7ff00000"
UBOOT_DTBO_LOADADDRESS = "0x7ff80000"
UBOOT_MACHINE = "imx8mm_evk_defconfig"

UBOOT_EXTLINUX = "1"
UBOOT_EXTLINUX_LABELS = "default"
UBOOT_EXTLINUX_DEFAULT_LABEL = "i.MX8M Mini EVK"

UBOOT_EXTLINUX_MENU_DESCRIPTION = "i.MX8M Mini EVK"
UBOOT_EXTLINUX_FDT     = "../imx8mm-evk.dtb"
UBOOT_EXTLINUX_CONSOLE = "console=${console}"
UBOOT_EXTLINUX_ROOT   = "root=/dev/mmcblk1p${mmcpart}"

U-BOOT-VERSION = "2025.07%"

PREFERRED_PROVIDER_virtual/bootloader ?= "u-boot-mainline"
PREFERRED_PROVIDER_u-boot ?= "u-boot-mainline"
PREFERRED_PROVIDER_u-boot-native ?= "u-boot-mainline"
PREFERRED_PROVIDER_u-boot-fw-utils ?= "u-boot-mainline-fw-utils"
PREFERRED_PROVIDER_u-boot-fw-utils-native ?= "u-boot-mainline-fw-utils-native"
PREFERRED_PROVIDER_u-boot-tools ?= "u-boot-mainline-tools"
PREFERRED_PROVIDER_u-boot-tools-native ?= "u-boot-mainline-tools-native"
PREFERRED_VERSION_u-boot-mainline ?= "${U-BOOT-VERSION}"
PREFERRED_VERSION_u-boot-mainline-native ?= "${U-BOOT-VERSION}"
PREFERRED_VERSION_u-boot-mainline-fw-utils ?= "${U-BOOT-VERSION}"
PREFERRED_VERSION_u-boot-mainline-fw-utils-native ?= "${U-BOOT-VERSION}"
PREFERRED_VERSION_u-boot-mainline-tools ?= "${U-BOOT-VERSION}"
PREFERRED_VERSION_u-boot-mainline-tools-native ?= "${U-BOOT-VERSION}"

# Mesa
PREFERRED_PROVIDER_virtual/egl ?= "mesa-mainline"
PREFERRED_PROVIDER_virtual/libgl ?= "mesa-mainline"
PREFERRED_PROVIDER_virtual/libgles1 ?= "mesa-mainline"
PREFERRED_PROVIDER_virtual/libgles2 ?= "mesa-mainline"
PREFERRED_PROVIDER_virtual/libgles3 ?= "mesa-mainline"
PREFERRED_PROVIDER_virtual/mesa ?= "mesa-mainline"
PREFERRED_PROVIDER_drm ?= "libdrm-mainline"
PREFERRED_PROVIDER_libdrm ?= "libdrm-mainline"
PREFERRED_PROVIDER_nativesdk-libdrm ?= "nativesdk-libdrm-mainline"
PREFERRED_PROVIDER_wayland-protocols ?= "wayland-protocols-mainline"
PREFERRED_PROVIDER_nativesdk-wayland-protocols ?= "nativesdk-wayland-protocols-mainline"

# Linux kernel
KERNEL_IMAGETYPE = "Image"
FIT_KERNEL_COMP_ALG = "lzo"
FIT_KERNEL_COMP_ALG_EXTENSION = ".lzo"

PREFERRED_PROVIDER_virtual/kernel ?= "linux-stable"
PREFERRED_VERSION_linux-stable ?= "6.12%"

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
IMAGE_NAME_SUFFIX = ""
EXTRA_IMAGEDEPENDS += "u-boot-mainline"
WKS_FILE = "emmcimage-imx8mmevk.wks"
IMAGE_BOOT_FILES ?= "${KERNEL_IMAGETYPE} extlinux.conf;extlinux/extlinux.conf"
IMAGE_INSTALL:append = " kernel-devicetree u-boot-mainline rng-tools u-boot-default-env btrfs-tools mmc-utils pciutils \
			  wireless-regdb-static iw wpa-supplicant "
do_image_wic[depends] += "mtools-native:do_populate_sysroot dosfstools-native:do_populate_sysroot u-boot-mainline:do_deploy"

