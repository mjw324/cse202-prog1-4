
#!/bin/bash
rm -f tests.out 2>&1 >/dev/null
echo -e "\nRunning make clean"
make -f makefile clean
echo -e "\nRunning make prog2"
make
rc=$?
total=0
if [[ $rc == 0 ]]; then
  tests=( "abs 12"
          "abs -25"
          "sum_diff 25 12"
          "sum_diff 12 25"
          "sum_diff 3000000000 2000000000"
          "sum_diff 2000000000 3000000000"
          "gcd 25 12"
          "gcd 12 15"
          "gcd 18 6"
          "sum_squares 3.75 4.50 12.25"
          "sum_squares 4.0 4.0 4.0"
          "max 11 77 22 44 66 3"
          "max -11 -22 -33 -44 -66 -77"
          "sort bla blo obl abl lab bol bal lob"
          "sort 300 500 200 600 400 100 800 700"
          "sort kiwi strawberry apple orange banana peach blueberry mango"
        )

  for test in "${tests[@]}"; do
    total=$((total + 1))
    echo -e "\nTest $total with args: $test"
    ./prog2 $test | tee -a tests.out
  done
paste -d '|' tests.out tests.reference | grep -Po '^(.*)\|+\K\1$' > out
count=0
input="./out"
while IFS= read -r line
do
  count=$((count + 1))
done < "$input"

if [[ $count == 16 ]]; then
   echo -e "\nAll tests passed"
   echo -e "Score: 80/80\n"
   exit 0
else
   echo -e "\n$count out of 16 passed"
   count=$((count * 5))
   echo -e "Score: $count /80\n"
   exit 1
fi

fi
