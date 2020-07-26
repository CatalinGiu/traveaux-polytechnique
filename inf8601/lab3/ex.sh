#!/usr/bin/bash

TIMEFORMAT=%R

for x in ordered blocking combined buffered async
do
    echo  "$x"
    for i in {1..20}; do 
        time `mpirun -np 4 ./src/exchng --lib $x --height 2078 --width 4096 &> /dev/null`
    done
    
done