#!/bin/sh

# ------------------------------------------------------------------------
# Author     : Weilun Fong | wlf@zhishan-iot.tk
# Date       : 2020-04-11
# Description: config environment for making sure to run sdcc rightly
# E-mail     : mcu@zhishan-iot.tk
# Page       : https://hw.zhishan-iot.tk/page/hml/detail/fwlib_stc11.html
# ------------------------------------------------------------------------

# ------------------------------------------------------------------------
#  usge: source env.sh
# ------------------------------------------------------------------------

# add target sdcc path into $PATH
export PATH="$PATH:/opt/sdcc-4.0.0/bin"

# config toolchain
export ARCH=8051
export CROSS_COMPILE=sd

export AR=${CROSS_COMPILE}ar
export AS=${CROSS_COMPILE}as8051
export CC=${CROSS_COMPILE}cc
export CPP=${CROSS_COMPILE}cpp
export LD=${CROSS_COMPILE}ld
export NM=${CROSS_COMPILE}nm
export MAKEBIN=makebin
export OBJCOPY=${CROSS_COMPILE}objcopy
export PACKIHX=packihx
export RANLIB=${CROSS_COMPILE}ranlib

# Done!
echo "Done!"
