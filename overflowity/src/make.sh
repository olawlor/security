#!/bin/sh
rm ../problems/*
for f in `echo *.cpp`
do
	echo "$f"
	base=`echo "$f" | sed -e 's/.cpp//g'`
	g++ -Wall -no-pie "$f" -o ../problems/"$base" || exit 1
done
echo "Done"

