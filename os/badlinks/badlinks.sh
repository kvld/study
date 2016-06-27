#!/usr/bin/env bash

for i in $(find -L $1 -type l -mtime +7); do
    if [ ! -e $i ]; then
        echo $i
    fi
done