#!/bin/bash

echo Emil >../week01/file.txt

INODE=$(ls -i ../week01/file.txt | head -n1 | awk '{print $1;}')

rm -f ex2.txt

link ../week01/file.txt _ex2.txt >>ex2.txt

find .. -inum $INODE >>ex2.txt

find .. -inum $INODE -exec rm {} \; >> ex2.txt