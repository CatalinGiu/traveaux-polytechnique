#!/bin/bash

OPTIONS=""
while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    -a)
    ALGO="$2"
    shift
    ;;
    -e)
    EX_PATH="$2"
    shift
    ;;
    -p|-t)
    OPTIONS="${OPTIONS}${1} "
    ;;
    *)
        echo "Argument inconnu: ${1}"
        exit
    ;;
esac
shift
done

case $ALGO in
	quick) COMMAND="./quick $EX_PATH 0 -1";;
	quickSeuil) COMMAND="./quick $EX_PATH 0 7";;
	quickRandomSeuil) COMMAND="./quick $EX_PATH 1 7";;
	counting) COMMAND="./counting $EX_PATH";;
	*) echo "'$ALGO' is not a valid algorithm, please choose between counting, quick, quickSeuil and quickRandomSeuil."; exit;;
esac

$COMMAND $OPTIONS
