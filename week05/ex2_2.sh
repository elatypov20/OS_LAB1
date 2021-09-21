#!/bin/bash

FILENAME="ex2_2.txt"

echo 0 > "$FILENAME"

TIMER_FINISH=$(($SECONDS+10))

while [[ $SECONDS -lt $TIMER_FINISH ]]
do
	if ln "$FILENAME" "$FILENAME.lock" >/dev/null 2>&1; then
		NUM="$(tail -n 1 $FILENAME)"
		INC=$(($NUM+1))
		echo "$INC" >> "$FILENAME"
		echo "$INC from $1"

		rm "$FILENAME.lock"
	fi
done
