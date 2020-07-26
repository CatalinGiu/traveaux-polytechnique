#!/usr/bin/env bash

for file in "$1"/*
do
    echo "$file"
    timeout 3m ./lego "$file" >> out.txt
    python3 sol_check.py "$file" out.txt
done
