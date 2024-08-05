.global sum_squares
# a is %xmm0, b is %xmm1, %c is %xmm2
sum_squares:
  mulsd %xmm0, %xmm0
  mulsd %xmm1, %xmm1
  mulsd %xmm2, %xmm2
  addsd %xmm1, %xmm0
  addsd %xmm2, %xmm0
  retq

# double sum_squares(double a, double b, double c){
#     double s = (a * a + b * b + c * c);
#     return s;
# }
