FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

KBRANCH:imx8mmevk ?= "linux-6.6.y"
KMACHINE:imx8mmevk ?= "imx8mmevk"
COMPATIBLE_MACHINE = "(imx8mmevk)"

SRC_URI:append:imx8mmevk = " \
	file://${BPV}/imx8mmevk;type=kmeta;destsuffix=${BPV}/imx8mmevk \
	file://common/imx8mmevk;type=kmeta;destsuffix=common/imx8mmevk \
	"
KERNEL_FEATURES:imx8mmevk = " imx8mmevk-standard.scc "
