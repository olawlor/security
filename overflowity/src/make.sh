#!/bin/sh
out=../problems
mkdir -p "$out"
rm "$out"/*
for f in `echo *.cpp`
do
	echo "$f"
	base=`echo "$f" | sed -e 's/.cpp//g'`
	g++ -Wall -no-pie "$f" -o "$out"/"$base" || exit 1
done
echo "Done"

