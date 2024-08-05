.global sum_diff
sum_diff:
  movl (%rdi), %eax     # sum %eax = *a
  addl (%rsi), %eax     # sum %eax = *a + *b
  movl (%rdi), %ebx     # diff %ebx = *a
  subl (%rsi), %ebx     # diff %ebx = *a - *b
  movb $0, (%rdx)     # (%rdx) is char* psum, setting to 0
  movb $0, (%rcx)     # (%rcx) is char* pdiff, setting to 0
  cmpl (%rdi), %eax     # flags set to sum - *a
  jae .L1     # jump if sum - *a >= 0
  movb $1, (%rdx) # if sum - *a < 0, we set (%rdx)=*psum to 1
  .L1:
  cmpl (%rdi), %ebx     # flags set to diff - *a
  jbe .L2     # jump if diff - *a <= 0
  movb $1, (%rcx)    #  if diff - *a > 0, we set (%rcx)=*pdiff to 1
  .L2:
  movl %eax, (%rdi)
  movl %ebx, (%rsi)
  ret
  
# void sum_diff(unsigned *a, unsigned *b, char *psum, char *pdiff){
#     unsigned sum = a + b;
#     unsigned diff = a - b;
#     *psum = 0;
#     *pdiff = 0;
#     if(sum < a)
#        *psum = 1;
#     if(diff > a)
#        *pdiff = 1;
#     *a = sum;
#     *b = diff;
# }

    