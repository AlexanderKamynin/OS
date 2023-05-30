#!/bin/bash

# task 2
i_node=$(ls -lRi $@ | cut -d ' ' -f 1)

echo "$i_node" - i_node for file with name "$@"
echo "The hard links on the file below:"

ls -lRi | grep -E "^(\ *$i_node)"