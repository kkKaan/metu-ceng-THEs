#!/bin/bash

for i in {1..1000}
do
    make clean
    make all
    ./hw2 < input1.txt | tail -4 | diff - output1.txt > diff.txt
    if [ -s diff.txt ]
    then
        echo "Test $i: Failed"
        cat diff.txt | tail -4
    else
        echo "Test $i: Passed"
    fi
done

