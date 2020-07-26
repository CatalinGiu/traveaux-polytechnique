#!/bin/bash

OPTIONS=""
while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    -a)
    ALGO="$2"
    if [[ "glouton progdyn local" != *$ALGO* ]]; then
	echo "'$ALGO' is not a valid algorithm, please choose between glouton, progdyn or local."; exit
    fi
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
        echo "Argument inconnu: ${1}"; exit;;
esac
shift
done

./$ALGO $EX_PATH $OPTIONS
