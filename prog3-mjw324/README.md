[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-8d59dc4de5201274e310e4c54b9627a8934c3b88527886e3b421487c677d23eb.svg)](https://classroom.github.com/a/zNA3k58U)
# prog3: Program Optimization
## Programming Assignment  Learning Outcomes:
By completing the programming assignment, students will demonstrate the following skills:
- Apply different low-level optimization techniques to improve the performance of a program
- Evaluate the effect of the different optimization techniques on the program performance
- Test the correctness of the optimized code against the original code
- Discuss and compare the results of the different optimization techniques

## Specification

The following function poly evaluates the value of a polynomial, of degree N, for a given value of  variable x using the expression below:
     a0 + a1x + a2x^2 + . . . + anx^n 
     
```

    double poly(double a[], double x, long N){

        long i; 
    
        double result = a[0]; 
    
        double xpwr = x; 
    
        for(i=1; i<=N; i++){
    
            result += a[i] * xpwr; 
       
            xpwr = x * xpwr;   
       
        }
    
        return result;  
    
    }
    
```

In this assignment, you are asked to :
- apply different loop unrolling optimization techniques to the function poly. You must write at least five (5) different functions with different loop unrolling factors and a mix of multiple accumulators and/or reassociation.
- evaluate the effect of each optimized function by determining its execution time in clock cycles
- check the correctness of each optimized function against the original code
- discuss the results obtained by comparing the different functions and the limitations if any. 
 
You are provided with the program `prog3.c` that includes the following:
- The implementation of the function `poly` in C.
- The function `poly_2_1` that implements poly using loop unrolling 2x1.
- The main function calls `poly` and `poly_2_1` 100 times, measures the execution time of each function and displays the results in clock cycles. The main function contains an optional code that is executed only if the macro TEST is defined. The optional code checks the correctness of poly_2_1 by comparing its return value to the result of the original function poly. 

You are also provided with a makefile that has the following targets:
- `run` : runs the script file `runTests.sh`. The script compiles `prog3.c` and runs the program `prog3` for different values of the polynomial degree (macro `DEGREE` in `prog3.c`).
- `test`: compiles `prog3.c` and runs the program `prog3` with the macro `DEGREE` defined to be equal to 100,000 and the macro `TEST` set in order to check the correctness of the function `poly_2_1`.

You should modify `prog3.c` to complete the following:

- Add the definitions of five other functions for different loop unrolling techniques with a mix of multiple accumulators and/or reassociation.
- Call the added functions in the main function and measure their execution time by following the way it was done for `poly` and `poly_2_1`. Store the return value of the added functions in the array `results` to be used by the optional code. Update the names of the five functions in the array `cases`. 
  Make sure all your functions pass the correctness test before submitting your code.
- Display the execution time of the added functions.

Your submission should consist of the updated `prog3.c` and a write up of two pages max that includes an explanation of  the types of loop unrolling used, a description of the performance obtained, and a discussion of the results. There is no autograding for this assignment because you have the choice for the type of optimized functions you would opt for. 

Here is a sample output of the program for `poly` and `poly_2_1`.

```

   saturn:% make run

   bash runTests.sh

   Degree  POLY    POLY_2_1

   100000  20241   18218   0       0       0       0       0

   200000  39885   35724   0       0       0       0       0

   300000  59171   53373   0       0       0       0       0

   400000  78644   70467   0       0       0       0       0

   500000  98366   88178   0       0       0       0       0

   saturn:% make test

   gcc -g -O0 -DDEGREE=100000 -DTEST -oprog3 prog3.c

   ./prog3

   100000  20243   18190   0       0       0       0       0

   Testing for correctness

   POLY 2x1 passed the correctness test

   POLY V2 failed the correctness test

   POLY V3 failed the correctness test

   POLY V4 failed the correctness test

   POLY V5 failed the correctness test

   POLY V6 failed the correctness test
 
 ```
