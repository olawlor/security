#!/bin/bash
cd `dirname $0`
sudo killall node
echo "while [ true ]; do date >> log; node wurst.js >> log; sleep 2; done" | sudo su wurst_user  >> log  2>&1


