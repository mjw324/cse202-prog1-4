#!/bin/bash 
	gcc -g -Wall -Wextra -Wwrite-strings -DP=4 -oprog4 prog4.c
	./prog4 2>&1 | tee output1

	./checkOutput.pl output1 3

	gcc -g -Wall -Wextra -Wwrite-strings -DP=8 -oprog4 prog4.c
	./prog4 2>&1 | tee output2

	./checkOutput.pl output2 7
