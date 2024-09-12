#!/usr/bin/env bash

cat .pid | while read line
do
    if sudo kill $line
        then echo $line " killed";
    fi
done