#!/bin/bash

echo -e "\nRunning make clean"
make -f makefile clean
echo -e "\nRunning make prog1"
make
rc=$?
total=0
if [[ $rc == 0 ]]; then
  tests=( "m 1 BF400000"
          "d 1 BF400000"  
          "m 1 80000000"
          "d 1 80000000"
          "m 1 7fffffff"
          "d 1 7fffffff"
          "m 3 7fffffff"
          "d 3 7fffffff"
          "m 1 FFFFFFFF"
          "d 1 ffffffff"
          "m 1 FF000000"
          "d 1 ff000000"
          "m 16 00000bcd"
          "d 16 00000bcd"
          "m 1 7F800000"
          "d 1 7F800000"
          "m 3 FE780000"
          "d 3 fe780000"
          "m 4 0200fe00"
          "d 4 0200FE00"
          "m 1 ff800000"
          "d 1 FF800000"
          "m 32 FFFFFFFF"
          "d -5 ffffffff"
          "m 10 ABCDEFG1"
          "p 10 ffffffff"
        )

  for test in "${tests[@]}"; do
    total=$((total + 1))
    echo -e "\nTest $total with args: $test"
    ./prog1 $test | tee -a tests.out
  done
paste -d '|' tests.out tests.reference | grep -Po '^(.*)\|+\K\1$' > out
count=0
input="./out"
while IFS= read -r line
do
  count=$((count + 1))
done < "$input"

if [[ $count == 70 ]]; then
   echo -e "\nAll tests passed"
   echo -e "Score: 70/70\n"
   exit 0
else
   echo -e "\n$count out of 70 passed"
   echo -e "Score: $count/70\n"
   exit 1
fi
fi
