#!/bin/bash
echo "algo,serie,taille,r,temps" > ./results.csv
ex_folder="exemplaires"
for algo in {"glouton","progdyn","local"}; do
    for ex in $(ls ${ex_folder}/); do
        length=$(echo $ex | cut -d- -f2)
        serie=$(echo $ex | cut -d- -f3)
        t=$(./tp.sh -e ./${ex_folder}/${ex} -a $algo -t)
        echo $algo,$serie,$length,$t
    done
done >> results.csv
