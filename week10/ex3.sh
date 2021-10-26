#!/bin/bash

rm -f _ex3.txt
echo Emil >_ex3.txt

echo "Removing executable permisions:" >ex3.txt
chmod a-x _ex3.txt >>ex3.txt
ls -l _ex3.txt	>>ex3.txt

echo >>ex3.txt
echo "Granting all permissions to owner and others:" >>ex3.txt
chmod u+rwx,o+rwx _ex3.txt >>ex3.txt
ls -l _ex3.txt	>>ex3.txt

echo >>ex3.txt
echo "Making group permissions same as user permissions:" >>ex3.txt
chmod g=u _ex3.txt >>ex3.txt
ls -l _ex3.txt	>>ex3.txt

echo >>ex3.txt
echo "chmod 660 will give only read and write permissions to user and group \
 and remove all permissions for other users" >>ex3.txt


echo >>ex3.txt
echo "chmod 775 will give all permissions to all users except \
writing for other users" >>ex3.txt

echo >>ex3.txt
echo "chmod 777 will give all permissions to all users" >>ex3.txt

