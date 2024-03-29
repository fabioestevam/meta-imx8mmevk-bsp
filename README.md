OpenEmbedded BSP layer for the i.MX8MM EVK
==========================================

This layer provides BSP for the i.MX8MM EVK

Dependencies
------------

This layer depends on:

* URI: git://git.yoctoproject.org/poky
  - branch: kirkstone
  - layers: meta

* URI: https://source.denx.de/denx/meta-mainline-common.git
  - branch: dunfell-3.1

Building the image
------------------

A good starting point for setting up the build environment is is the official
Yocto Project wiki.

* https://www.yoctoproject.org/docs/3.1/brief-yoctoprojectqs/brief-yoctoprojectqs.html

Before attempting the build, the following metalayer git repositories shall
be cloned into a location accessible to the build system and a branch listed
below shall be checked out. The examples below will use /path/to/OE/ as a
location of the metalayers.

* https://source.denx.de/denx/meta-mainline-common.git	(branch: dunfell-3.1)
* https://github.com/fabioestevam/meta-imx8mmevk-bsp.git	(branch: kirkstone)
* git://git.yoctoproject.org/poky				(branch: kirkstone)

With all the source artifacts in place, proceed with setting up the build
using oe-init-build-env as specified in the Yocto Project wiki:
/path/to/OE/poky $ source oe-init-build-env

In addition to the content in the wiki, the aforementioned metalayers shall
be referenced in bblayers.conf in this order:

```
BBLAYERS ?= " \
  /path/to/OE/poky/meta \
  /path/to/OE/meta-mainline-common \
  /path/to/OE/meta-imx8mmevk-bsp \
  "
```

The following specifics should be placed into local.conf:

```
MACHINE = "imx8mmevk"
DISTRO = "nodistro"
```

Note that MACHINE must be:

* imx8mmevk

Adapt the suffixes of all the files and names of directories further in
this documentation according to MACHINE.

Both local.conf and bblayers.conf are included verbatim in full at the end
of this readme.

Once the configuration is complete, a basic demo system image suitable for
evaluation can be built using:

```
$ bitbake core-image-minimal
```

Once the build completes, the images are available in:

```
tmp-glibc/deploy/images/imx8mmevk/
```
The SD card is specifically in:

```
core-image-minimal-imx8mmevk.wic.gz
```

And shall be written to the SD card via the following
commands from the U-Boot prompt:

```
gunzip core-image-minimal-imx8mmevk.wic.gz
dd if=core-image-minimal-imx8mmevk.wic of=/dev/sdX; sync
```

Example local.conf
------------------
```
MACHINE = "imx8mmevk"
DL_DIR = "/path/to/OE/downloads"
DISTRO ?= "nodistro"
PACKAGE_CLASSES ?= "package_rpm"
EXTRA_IMAGE_FEATURES = "debug-tweaks"
USER_CLASSES ?= "buildstats"
PATCHRESOLVE = "noop"
BB_DISKMON_DIRS = "\
    STOPTASKS,${TMPDIR},1G,100K \
    STOPTASKS,${DL_DIR},1G,100K \
    STOPTASKS,${SSTATE_DIR},1G,100K \
    STOPTASKS,/tmp,100M,100K \
    HALT,${TMPDIR},100M,1K \
    HALT,${DL_DIR},100M,1K \
    HALT,${SSTATE_DIR},100M,1K \
    HALT,/tmp,10M,1K"
PACKAGECONFIG:append:pn-qemu-native = " sdl"
PACKAGECONFIG:append:pn-nativesdk-qemu = " sdl"
CONF_VERSION = "1"
```

Example bblayers.conf
---------------------
```
# LAYER_CONF_VERSION is increased each time build/conf/bblayers.conf
# changes incompatibly
POKY_BBLAYERS_CONF_VERSION = "2"

BBPATH = "${TOPDIR}"
BBFILES ?= ""

BBLAYERS ?= " \
	/path/to/OE/poky/meta \
	/path/to/OE/meta-mainline-common \
	/path/to/OE/meta-imx8mmevk-bsp \
	"
```
