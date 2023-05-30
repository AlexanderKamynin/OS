#!/usr/bin/env bash

types='- c d l s b p'
for i in $types
do
    echo $i
    file_search=`ls -lRd /*/* | grep ^$i | head -1`
    if [[ -z $file_search ]]
    then
        echo "i can't find file with this type"
    else
        file_name=`ls -lRd /*/* | grep ^$i | head -1`
        #echo "$file_search"
        echo "$file_name"
    fi
done

