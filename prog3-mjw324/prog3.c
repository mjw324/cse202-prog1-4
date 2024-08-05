#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// original poly
double poly(double a[], double x, long degree){
    long i;
    double result = a[0];
    double xpwr = x;
    for(i=1; i<= degree; i++){
        result += a[i] * xpwr;
        xpwr = x * xpwr;
    }
    return result;
}
// poly with loop unrolling 2x1
double poly_2_1(double a[], double x, long degree){
    long i;
    double result = a[0];
    double xpwr = x, x2 = x * x;
    long limit = degree-1;
    for(i=1; i<=limit; i+=2){
        result += a[i] * xpwr;
        result += a[i+1] * xpwr * x;
        xpwr =  xpwr * x2;
    }
    for(; i<=degree; i++){
        result += a[i] * xpwr;
        xpwr = x * xpwr;
    }
    return result;
}

// poly with loop unrolling 4x1
double poly_4_1(double a[], double x, long degree){
    long i;
    double result = a[0];
    double xpwr = x, x4 = x * x * x * x;
    long limit = degree-3;
    for(i=1; i<=limit; i+=4){
        result += a[i] * xpwr;
        result += a[i+1] * xpwr * x;
        result += a[i+2] * xpwr * x * x;
        result += a[i+3] * xpwr * x * x * x;
        xpwr =  xpwr * x4;
    }
    for(; i<=degree; i++){
        result += a[i] * xpwr;
        xpwr = x * xpwr;
    }
    return result;
}

// poly with loop unrolling 4x1a
double poly_4_1a(double a[], double x, long degree){
    long i;
    double result = a[0];
    double xpwr = x, x4 = x * x * x * x;
    long limit = degree-3;
    for(i=1; i<=limit; i+=4){
        result += (a[i] * xpwr) + (a[i+1] * xpwr * x) + (a[i+2] * xpwr * x * x) + (a[i+3] * xpwr * x * x * x);
        xpwr =  xpwr * x4;
    }
    for(; i<=degree; i++){
        result += a[i] * xpwr;
        xpwr = x * xpwr;
    }
    return result;
}

// poly with loop unrolling 2x1a
double poly_2_1a(double a[], double x, long degree){
    long i;
    double result = a[0];
    double xpwr = x, x2 = x * x;
    long limit = degree-1;
    for(i=1; i<=limit; i+=2){
        result += (a[i] * xpwr) + (a[i+1] * xpwr * x);
        xpwr =  xpwr * x2;
    }
    for(; i<=degree; i++){
        result += a[i] * xpwr;
        xpwr = x * xpwr;
    }
    return result;
}

// poly with loop unrolling 4x2a
double poly_4_2a(double a[], double x, long degree){
    long i;
    double result1 = a[0], result2 = 0;
    double xpwr = x, x4 = x * x * x * x;
    long limit = degree-3;
    for(i=1; i<=limit; i+=4){
        result1 += (a[i] * xpwr) + (a[i+2] * xpwr * x * x);
        result2 += (a[i+1] * xpwr * x) + (a[i+3] * xpwr * x * x * x);
        xpwr =  xpwr * x4;
    }
    for(; i<=degree; i++){
        result1 += a[i] * xpwr;
        xpwr = x * xpwr;
    }
    return result1 + result2;
}

// poly with loop unrolling 4x4
double poly_4_4(double a[], double x, long degree){
    long i;
    double result1 = a[0], result2 = 0, result3 = 0, result4 = 0;
    double xpwr = x, x4 = x * x * x * x;
    long limit = degree-3;
    for(i=1; i<=limit; i+=4){
        result1 += a[i] * xpwr;
        result2 += a[i+1] * xpwr * x;
        result3 += a[i+2] * xpwr * x * x;
        result4 += a[i+3] * xpwr * x * x * x;
        xpwr =  xpwr * x4;
    }
    for(; i<=degree; i++){
        result1 += a[i] * xpwr;
        xpwr = x * xpwr;
    }
    return result1 + result2 + result3 + result4;
}


int main(){
    double c[DEGREE+1];
    int i;
    clock_t start;
    clock_t times[7];
    double results[7];
    for(i=0; i<=DEGREE; i++){
        c[i] = rand() / 10000000000.0;
    }
    for(i=0; i<7; i++){
        times[i] = 0;
        results[i] = 0;
    }
    for(i=0; i<100; i++){
        start = clock();
        results[0] = poly(c, 2, DEGREE);
        times[0] +=  (clock()-start);
        start = clock();
        results[1] = poly_2_1(c, 2, DEGREE);
        times[1] += (clock()-start);
        start = clock();
        results[2] = poly_4_1(c, 2, DEGREE);
        times[2] += (clock()-start);
        start = clock();
        results[3] = poly_2_1a(c, 2, DEGREE);
        times[3] += (clock()-start);
        start = clock();
        results[4] = poly_4_1a(c, 2, DEGREE);
        times[4] += (clock()-start);
        start = clock();
        results[5] = poly_4_2a(c, 2, DEGREE);
        times[5] += (clock()-start);
        start = clock();
        results[6] = poly_4_4(c, 2, DEGREE);
        times[6] += (clock()-start);
    }
    printf("%-d\t%-ld\t\t%ld\t\t%ld\t\t%ld\t\t%ld\t\t%ld\t\t%-ld\n", DEGREE,
                times[0], times[1], times[2], times[3], times[4], times[5], times[6]);
    #ifdef TEST
        char *cases[] = {"POLY 2x1",
                        "POLY 4x1",
                        "POLY 2x1a",
                        "POLY 4x1a",
                        "POLY 4x2a",
                        "POLY 4x4"};
        printf("Testing for correctness\n");
        for(i=1; i<7; i++){
            if(results[i] != results[0]){
                printf("%s failed the correctness test\n", cases[i-1]);
            }
            else{
                printf("%s passed the correctness test\n", cases[i-1]);
            }
        }
    #endif
}
