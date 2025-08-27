FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
PACKAGECONFIG:append:imx8mmevk = " \
	etnaviv gallium \
	${@bb.utils.contains('DISTRO_FEATURES', 'wayland', 'wayland', '', d)} \
	"

