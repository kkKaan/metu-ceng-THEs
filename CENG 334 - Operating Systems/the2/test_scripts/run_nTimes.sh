#!/bin/bash

for i in {1..10}
do
    make clean
    make all
    ./hw2 < input1.txt
done
