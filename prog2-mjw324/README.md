# CSE202-Assembly-SU2022
Assembly: A programming exercise to write, compile, and link assembly code

## Learning Objectives
1) Write different functions in `X86-64 ISA` assembly code 
2) Compile assembly (.S) source files using the GNU AS(as) assembler
3) Write C program that uses functions compiled from assembly into object files
4) Link compiled assembly object files with the main C program
5) View the values in registers and the stack frame using gdb

## Instructions
Use the C program named `prog2.c` to call externally defined functions that you will write in assembly. You do NOT need (nor should you) edit the `prog2.c` code. In `prog2.c`, you will see six function prototypes that are defined in separate assembly source code files: `abs.S`, `sum_diff.S`, `gcd.S`, `sum_squares.S`, `max.S`, and `sort.S`. They are named based on the operation they perform. For example, `abs` returns the absolute value of its argument and max returns the maximum value in a list of integers.

Your task is to implement each function in X86-64 assembly. Because of this requirement, it is highly recommended you do your development work on the sunlab machines.

The abs function has already been implemented, so you have an example of what you are to do. Additionally, function shells have already been written in sum_diff.S, gcd.S, sum_squares.S, max.S, and sort.S. Here's a listing of the purpose of the functions. The C code is provided as comments at the end of each .S file. 

- `abs`: receives one integer as a parameter and returns its absolute value
- `sum_diff`: receives four parameters: two pointers to type unsigned integer and two pointers to type char. The function computes the sum and the difference of the two unsigned integers. The function sets the first char to 1 if the sum of the two unsigned integers overflows, 0 otherwise. The function sets the second char to 1 if the difference of the two unsigned integers overflows, 0 otherwise. The function also stores the sum in the first unsigned integer and the difference in the second unsigned integer.
- `gcd`: recursive function that receives two integers and returns their greatest common divisor.
- `sum_squares`: receives three doubles and returns the sum of their squares.
- `max`: receives a pointer to an array of integers and the number of elements in the array. The function returns the largest value in the array.
- `sort`: receives a pointer to an array of strings and the number of elements in the array. The function uses bubble sort to sort the array.

Before you modify anything, you should test what you have downloaded. To do this, simply type "`bash runTests.sh`". This Bash script compiles the program and runs a suite of tests. It compares the output of your program with the reference output of the program (`tests.reference`). You do NOT need (nor should you) edit `runTests.sh`, `makefile`, `tests.reference`, or `prog2.c`.

In addition to submitting your code in the various assembly `.S` files, you need to upload a JPEG file. The JPEG you are to create while you are developing/debugging your code for the sort function. While running "`gdb -tui --args ./prog2 sort bla blo obl abl lab bol bal lob`", step into your sort function and type the gdb command "`info registers`" to display all the register values. Know that you can use the shortcut "`i r`" to do the same thing, and you can type "`i r edi`" to just print the value in the `%edi` register, for example. Save a screenshot of the output into a "`registers.jpg`" file and push this to GitHub. You don't have to use the arguments I listed, those are just examples.

## Recommended Approach
1) Leverage the textbook.
2) Work on this assignment a little every day.

## Important Notes
1) Add comments to your code; it will help you and the graders!
2) Do NOT modify the files prog2.c, runTests.sh, makefile, tests.reference; only modify the .S files.
3) Push your code often!!! This will give you a backup, enable you to retrieve earlier versions, and demonstrate you actually wrote the code over time. If you only perform one push of your final code, your submission will be THOROUGHLY evaluated to ensure it is original. 
4) Refer to the Grading Rubric to maximize your score.
5) To submit your code for grading, simply perform a "git push"; which will upload your changes to GitHub Classroom and run the auto-grader. You may continue to push changes until you are informed "All tests passed" or the deadline published on Coursesite has passed.
6) Post any questions on Piazza.

