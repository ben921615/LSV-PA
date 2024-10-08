#!/bin/bash

A_RESULT_DIR="my_result/"
MY_RESULT="WSY_result_2/"

MAPPER="my_script/mapper.py"

BENCHMARKS='comp adder div int2float log2 mem_ctrl router sqrt square'

for case in ${BENCHMARKS}
do
    for i in {3..6}; do
        echo -e "\033[0;32m Compare ${case}, cut ${i}\033[0m"
        python3 ${MAPPER} ${A_RESULT_DIR}${case}${i}.out ${MY_RESULT}${case}${i}.out
        printf "\n\n"
    done
done
