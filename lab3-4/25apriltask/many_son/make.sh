#!/bin/bash

for (( i=1; i <= 18; i++ ))
do
gcc son$i.c -o son$i -lm
done

gcc father_fifo.c -o father_fifo
gcc father_rr.c -o father_rr

