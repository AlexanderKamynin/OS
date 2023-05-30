#!/bin/bash

# task 3
count=0

echo All symbol links on file "$1":

for file in $(find / -lname $1 2>/dev/null)
do
    echo $file
    count=$(( $count + 1 ))
done

echo Total count of links on file: "$count"

