#!/bin/sh
# Disassemble a .bin file using ndisasm
while [ $# -gt 0 ]
do
	ndisasm -b 64 -k 0,900 "$1" > "$1".dis
shift
done

