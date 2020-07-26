#!/bin/bash
echo "algo,serie,set_type,taille,temps" > ./results.csv
ex_folder="exemplaires"
for algo in {"quick","counting","quickSeuil","quickRandomSeuil"}; do
    for testset_folder in $(ls $ex_folder); do
        for ex in $(ls ${ex_folder}/${testset_folder}); do
            taille=$(echo $ex | cut -d_ -f2)
            set_type=$(echo $testset_folder | cut -d_ -f3 | cut -d. -f1)
            if [[ "$algo" == "quickRandomSeuil" ]]; then
                for i in {1..10}; do
                    t=$(./tp.sh -e ./${ex_folder}/${testset_folder}/${ex} -a $algo -t)
                    echo $algo,$testset_folder,$set_type,$taille,$t
                done
            else
                t=$(./tp.sh -e ./${ex_folder}/${testset_folder}/${ex} -a $algo -t)
                echo $algo,$testset_folder,$set_type,$taille,$t
            fi
        done
    done
done >> results.csv