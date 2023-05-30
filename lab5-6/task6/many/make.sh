#!/bin/bash

for i in {1..100}
do
    echo -e "client $i start\n" | ./client &
done