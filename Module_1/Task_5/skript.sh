#!/bin/bash

STR='[A-Za-z0-9]' 
for pid in $(ps -e -o pid=); do
    # Проверяем, соответствует ли процесс заданному выражению
    if [[ $(ps -p $pid -o comm=) =~ $STR ]]; then
        kill "$pid"
    fi
done
