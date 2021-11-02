#!/bin/bash

# allocate 50M file
fallocate lofs.img -l 100M

# detect free device
DEVICE=$(sudo losetup -f)

sudo losetup $DEVICE lofs.img

# create filesystem
sudo mkfs.ext4 $DEVICE

mkdir -p lofsdisk
sudo mount $DEVICE lofsdisk

# and demonstrate our points:
df -h | grep lofsdisk