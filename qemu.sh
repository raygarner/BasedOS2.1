#!/bin/sh
cd src
set -e
. ./iso.sh

qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom basedos.iso
