#!/bin/bash

FILENAME="ex2_1.txt"

echo 0 > "$FILENAME"

TIMER_FINISH=$(($SECONDS+10))

while [[ $SECONDS -lt $TIMER_FINISH ]]
do
	NUM="$(tail -n 1 $FILENAME)"
	INC=$(($NUM+1))
	echo "$INC" >> "$FILENAME"
	echo "$INC"
done
