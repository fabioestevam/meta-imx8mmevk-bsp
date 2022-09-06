FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
DEFAULT_PREFERENCE:imx8mmevk = "1"
PACKAGECONFIG:append:imx8mmevk = " \
	etnaviv kmsro gallium \
	${@bb.utils.contains('DISTRO_FEATURES', 'wayland', 'wayland', '', d)} \
	"

