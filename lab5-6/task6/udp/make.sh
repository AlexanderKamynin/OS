#!/bin/bash
IP=192.168.43.200
PORT=8000

for i in {1..100}
do
    echo -e "client $i start" | ./client $IP $PORT &
done