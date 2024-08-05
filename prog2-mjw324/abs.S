.global abs
abs:
  movl %edi, %eax
  testl %eax, %eax
  jge .end
  negl %eax
.end:
  retq


# int abs(int a){
#    if(a < 0)
#        a = -a;
#    return a;
# }

