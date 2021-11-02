#!/bin/bash

# this script expects ex1.sh to be executed before
if ! mount | grep lofsdisk >/dev/null; then
	echo "Please, execute ex1.sh first"
	exit 1
fi

sudo echo Emil > lofsdisk/file1
sudo echo Latypov > lofsdisk/file2

gcc ex2.c -o ex2.out

# copy needed files to lofsdisk
mkdir -p lofsdisk/bin
programs="ls echo bash cat"
for prog in $programs; do
	sudo cp /bin/$prog lofsdisk/bin/$prog
done

libs="/lib/x86_64-linux-gnu/libselinux.so.1 \
/lib/x86_64-linux-gnu/libc.so.6 \
/usr/lib/x86_64-linux-gnu/libpcre2-8.so.0 \
/lib/x86_64-linux-gnu/libdl.so.2 \
/lib64/ld-linux-x86-64.so.2 \
/lib/x86_64-linux-gnu/libpthread.so.0 \
/lib/x86_64-linux-gnu/libtinfo.so.6 \
/lib/x86_64-linux-gnu/libdl.so.2"

mkdir -p lofsdisk/lib/x86_64-linux-gnu
mkdir -p lofsdisk/usr/lib/x86_64-linux-gnu
mkdir -p lofsdisk/lib64

for lib in $libs; do
	cp $lib lofsdisk$lib
done

echo "lofsdisk content:"
sudo chroot lofsdisk/ /bin/ls /

echo 
echo
echo "Running ex2 in lofsdisk"
cp ex2.out lofsdisk/ex2.out
sudo chroot lofsdisk /ex2.out

echo
echo
echo "Running ex2 in real root"
sudo ./ex2.out