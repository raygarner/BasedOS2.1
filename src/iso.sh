#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/basedos.kernel isodir/boot/basedos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "BasedOS" {
	multiboot /boot/basedos.kernel
}
EOF
grub-mkrescue -o basedos.iso isodir
