/*
 *  CSE202: Data types and Binary Arithmetic Program
 *  Full name: Houria Oudghiri
 *  Full Lehigh Email Address: hoo219@lehigh.edu
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

extern int abs(int);
extern void sum_diff(unsigned*, unsigned*, unsigned char*, unsigned char*);
extern int gcd(int, int);
extern double sum_squares(double, double, double);
extern int max(int*, int);
extern void sort(char**, int);

int main(int argc, char **argv) {
  int i, val1, val2;
  unsigned char sum, diff;
  double v1, v2, v3;
  if (argc >= 3 && argc <= 10) {
    switch (argc) {
      case 3: // abs
        if(strcmp(argv[1], "abs") == 0){
          i = atoi(argv[2]);
          int j = abs(i);
          fprintf(stdout, "abs(%d) = %d\n", i, j);
        }
        else{
          fprintf(stderr, "Error: invalid operation\n");
          return 1;
        }
        break;
      case 4://gcd or sum_diff
        val1 = atoi(argv[2]);
        val2 = atoi(argv[3]);
        if(strcmp(argv[1], "gcd") == 0){
          fprintf(stdout, "gcd(%d, %d) = %d\n",
                val1, val2, gcd(val1, val2));
        }
        else if(strcmp(argv[1], "sum_diff") == 0){
          unsigned value1=atoi(argv[2]), value2=atoi(argv[3]);
          unsigned v1_old = value1;
          unsigned v2_old = value2;
          sum_diff(&value1, &value2, &sum, &diff);
          fprintf(stdout, "sum(%u, %u) = %u overflow? %x, diff(%u, %u) = %u overflows? %x\n", v1_old, v2_old, value1,
                          (sum==1), v1_old, v2_old, value2, (diff==1));
        }
        else{
          fprintf(stderr, "Error: invalid operation\n");
          return 1;
        }
        break;
      case 5: //sum_squares
        if(strcmp(argv[1], "sum_squares") == 0){
          v1 = (double) atof(argv[2]);
          v2 = (double) atof(argv[3]);
          v3 = (double) atof(argv[4]);
          double m = sum_squares(v1, v2, v3);
          fprintf(stdout, "sum_squares(%.2f, %.2f, %.2f) = %.2f\n", v1, v2, v3, m);
        }
        else{
          fprintf(stderr, "Error: invalid operation\n");
          return 1;
        }
        break;
      case 8://max
        if(strcmp(argv[1], "max") == 0){
          int arr[6];
          for(i=0; i<6; i++){
            arr[i] = atoi(argv[i+2]);
          }
          fprintf(stdout, "max{%d, %d, %d, %d, %d, %d} = %d\n",
                arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], max(arr, 6));
        }
        else{
          fprintf(stderr, "Error: invalid operation\n");
          return 1;
        }
        break;
      case 10://sort
        if(strcmp(argv[1], "sort") == 0){
          sort(argv+2, argc-2);
          fprintf(stdout, "sorted list = {%s, %s, %s, %s, %s, %s, %s, %s}\n",
                argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9]);
        }
        else{
          fprintf(stderr, "Error: invalid operation\n");
          return 1;
        }
        break;
      default:
          fprintf(stderr, "Wrong number of arguments on the command-line\n");
          return 1;
        break;
    }
  } else {
    fprintf(stderr, "Wrong number of arguments on the command-line\n");
    return 1;
  }
  return 0;
}
