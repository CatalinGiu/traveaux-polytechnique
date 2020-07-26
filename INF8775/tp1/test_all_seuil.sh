#!/usr/bin/env bash

echo "taille,seuil,temps" > ./results_seuil.csv
ex_folder="exemplaires"
algo="quickSeuil"
for testset_folder in $(ls $ex_folder); do
    for ex in $(ls ${ex_folder}/${testset_folder}); do
        for i in {1..25}; do
            for j in {1..5}; do
                n_ex=$(echo $ex | cut -d_ -f3 | cut -d. -f1)
                taille=$(echo $ex | cut -d_ -f2)
                t=$(./run_seuil.sh -e ./${ex_folder}/${testset_folder}/${ex} -a $algo -t -s $i)
                echo $taille,$i,$t
            done
        done
    done
done >> results_seuil.csv

