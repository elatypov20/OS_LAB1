#!/bin/bash

gcc ex2.c -o ex2

run_test(){
	./ex2&
	for (( i = 0; i < 8; i++ )); do
		echo "pstree #$i"
		sleep 3
		pstree
		echo 
		echo
	done
}

# you can use `./ex2.sh | grep ex2` to see beautiful result  
run_test > ex2.txt