## CSE 202 Prog1: Data Representation and Arithmetic

### Content of the repository:
1. The file prog1.c contains:
  * the union `value`, 
  * the enumerated type STATUS, 
  * the prototypes of the six functions to be implemented
  * an empty main function you have to complete
  * two functions `float_multiply_by_2` and `float_divide_by_2` contain the steps to multiply/divide a float number by 2 using the binary representation. 

2. The file makefile buildd the executable `prog1` from `prog1.c`
3. The file `tests.reference` contains the target output of the program for all the test cases listed in the assignment decsription [https://docs.google.com/document/d/1yieAPcdTVao2daGsWZW6nQg-JW_7I3MvrKI6hlzpDOc/edit?usp=share_link]
4. The file `run_tests.sh` is a bash file that performs the following:
  * builds the executable `prog1` using `makefile`
  * runs `prog1` for all the testcases and collect your program outputs in the file `tests.out`
  * compares your program output `tests.out` to `tests.reference`
  * counts the different lines between the files `tests.out` and `tests.reference`
  * displays the score of your program out of the 70 possible outputs
  
### How to test your code
1. run `bash run_tests.sh` locally on sunlab or
2. use the autograder on Github. When you push an updated prog1.c, the autograder will run `run_tests.sh` and display your score. As long as your program fails to pass all the test cases, the autograder will send you a report of the failure.

