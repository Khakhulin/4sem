#!/bin/bash
    for i in 1 2 4 8
    do
        echo "$i thread\n" 
        /usr/bin/time  -p ./paral $i
    done
