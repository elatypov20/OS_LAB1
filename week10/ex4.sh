#!/bin/bash

rm -rf tmp
mkdir -p tmp

touch tmp/{file1,file2}

ln tmp/file1 tmp/link1

gcc ex4.c -o ex4
./ex4 tmp > ex4.txt