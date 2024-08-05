/*
 *  CSE202: Data types and Binary Arithmetic
 *  Full name: Micah Worth
 *  Full Lehigh Email Address: mjw324@lehigh.edu
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

// enumerated type STATUS
enum STATUS {NORMAL, OVERFLOW, DENORMALIZED_NORMALIZED, NORMALIZED_DENORMALIZED, INFINITY, NAN};

// Union to store unsigned integer, integer, and float numbers as 4 bytes
union value{
  unsigned char bytes[4];
  unsigned uvalue;
};

// Prototypes of the functions

// reads 8 hex characters from string input and stores it in the union v
// returns -1 if the hexadecimal number is invalid, 0 otherwise
int read_hex(union value *v, char *input);
// writes the 4 bytes in the union v to the console
void write_hex(union value v);


// functions to perform the multiplication by a power of 2 for the three data types
unsigned unsigned_multiply_power_2(int k, union value v, enum STATUS *status);
unsigned signed_multiply_power_2(int k, union value v, enum STATUS *status);
unsigned float_multiply_power_2(int k, union value v, enum STATUS *status);
// multiplies the float representation in v by 2, returns the bit representation of the result
// sets the status to DENORMALIZED-NORMALIZED, NORMAL, Infinity, or Nan depending on the result
unsigned float_multiply_by_2(unsigned v);

// functions to perform the division by a power of 2 for the three data types
unsigned unsigned_divide_power_2(int k, union value v, enum STATUS *status);
unsigned signed_divide_power_2(int k, union value v, enum STATUS *status);
unsigned float_divide_power_2(int k, union value v, enum STATUS *status);
// divides the float representation in v by 2, returns the bit representation of the result
// sets the status to NORMALIZED-DENORMALIZED, NORMAL, Infinity, or Nan depending on the result
unsigned float_divide_by_2(unsigned v);

// main method
int main(int argc, char* argv[]){
    if(argc != 4){
      printf("Three arguments are needed (op, k and 8 hex character string)\n");
      return 0;
    }
    /* complete the main function */
    return 0;
}

int read_hex(union value *v, char *input){
  for(int i = 0; i < 4; i++) { // 4 bytes
    unsigned char c1;
    unsigned char c2;
    if(input[i] == 'F' || input[i] == 'f') {
      c1 = 15;
    } else if (input[i] == 'E' || input[i] == 'e') {
      c1 = 14;
    } else if (input[i] == 'D' || input[i] == 'd') {
      c1 = 13;
    } else if (input[i] == 'C' || input[i] == 'c') {
      c1 = 12;
    } else if(input[i] == 'B' || input[i] == 'b') {
      c1 = 11;
    } else if(input[i] == 'A' || input[i] == 'a') {
      c1 = 10;
    } else if((input[i] - '0') >= 0 && (input[i] - '0') < 10) { // if char is 0-9
      c1 = input[i] - '0';
    } else {
      return -1;
    }
    if(input[i+1] == 'F' || input[i+1] == 'f') {
      c2 = 15;
    } else if (input[i+1] == 'E' || input[i+1] == 'e') {
      c2 = 14;
    } else if (input[i+1] == 'D' || input[i+1] == 'd') {
      c2 = 13;
    } else if (input[i+1] == 'C' || input[i+1] == 'c') {
      c2 = 12;
    } else if(input[i+1] == 'B' || input[i+1] == 'b') {
      c2 = 11;
    } else if(input[i+1] == 'A' || input[i+1] == 'a') {
      c2 = 10;
    } else if((input[i+1] - '0') >= 0 && (input[i+1] - '0') < 10) { // if char is 0-9
      c2 = input[i+1] - '0';
    } else {
      return -1;
    }
    v->bytes[i] = (c1 << 4) | c2;
  }
  for(int i = 0; i < 4; i++) {
    printf("%d ", v->bytes[i]);
  }
  return 0;
}

void write_hex(union value v){ 
}

unsigned unsigned_multiply_power_2(int k, union value v1, enum STATUS *status){
    unsigned result = v1.uvalue;
    return result;
}

unsigned unsigned_divide_power_2(int k, union value v1, enum STATUS *status){
    unsigned result = v1.uvalue;
    return result;
}

unsigned signed_multiply_power_2(int k, union value v1, enum STATUS *status){
    unsigned result = v1.uvalue;
    return result;
}

unsigned signed_divide_power_2(int k, union value v1, enum STATUS *status){
    unsigned result = v1.uvalue;
    return result;
}

unsigned float_multiply_power_2(int k, union value v1, enum STATUS *status){
    unsigned result = v1.uvalue;
    return result;
}

unsigned float_divide_power_2(int k, union value v1, enum STATUS *status){
    unsigned result = v1.uvalue;
    return result;
}

unsigned float_multiply_by_2(unsigned v){
    /* decompose the bit representation into parts */
    /* extract the sign bit */
    unsigned sign = v >> 31;    
    /* extract the 8 bits of the exponent */
    unsigned exponent; 
    /* extract the 23 bits of the fraction */
    unsigned fraction;
    if(exponent == 0){ // denormalized
      /* shift the fraction to the left 1 position*/
      if(fraction > 0x7FFFFF){ // need to normalize
        /* ignore the extra bit in the fraction */
        fraction = fraction & 0x7FFFFF; // remove the 25th bit
        /* increment the exponent */
        /* number is now normalized */
      }
    }
    else if(exponent < 0xFF){ // normalized
      /* increment the exponent */;
      /* check if the exponent reached 255 (special cases) */
    }
    else{ // special cases
      /* do nothing: Infinity * 2 = Infinity and Nan * 2 = Nan */
    }
    /* reassemble the bits */
    return (sign << 31) | (exponent << 23) | fraction;
}

unsigned float_divide_by_2(unsigned v){
    /* decompose the bit representation into parts */
    /* extract the sign bit */
    unsigned sign = v >> 31;    
    /* extract the 8 bits of the exponent */
    unsigned exponent;
    /* extract the 23 bits of the fraction */
    unsigned fraction;
    /* determine if roundup is needed  */
    /* (2 least significant bits of the fraction equal 0x3 */
    if(exponent == 0){// denormalized
       // shift the fraction to the right and add roundup
    }
    else if(exponent < 0xff){ // normalized
       // decrement the exponent
       // check if exponent reached 0 (number becomes denormalized)
       // if exponent == 0, 
       // shift the fraction to the right; add the roundup and 0x400000 
    }
    else{ // special cases
      // do nothing: Inf/2 = Inf and NaN/2 = NaN
    }

    /* Reassemble bits */
     return (sign << 31) | (exponent << 23) | fraction;
}


