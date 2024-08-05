#!/bin/bash
	echo -e "Degree\tPOLY\t\tPOLY_2_1\tPOLY_4_1\tPOLY_2_1a\tPOLY_4_1a\tPOLY_4_2a\tPOLY_4_4\n"
	for n in {100000..500000..100000}; do
		gcc -g -O0 -std=c99 -DDEGREE=$n -oprog3 prog3.c
		./prog3
	done
