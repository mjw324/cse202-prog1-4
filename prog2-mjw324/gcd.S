.global gcd        # gcd(int a, int b) 
#%edi=a %esi=b
gcd:
  cmpl %edi, %esi # b - a
  jle .L1 # if b - a <= 0, we jump to L1
  movl %esi, %edx # b value saved in %edx for swap
  movl %edi, %esi # b = a
  movl %edx, %edi # a = %edx which has b's value
  call gcd # calls gcd(b, a)
  ret # returns gcd(b, a)
  .L1:
  cmpl $0, %esi # b - 0
  jne .L2 # if b is not 0, we jump over returning a
  movl %edi, %eax # save a into return value
  ret # return a
  .L2:
  test $1, %edi  # a & 1
  jne .L3 # jumps if a & 1 does not equal 0
  test $1, %esi # b & 1
  jne .L3 # jumps if b & 1 does not equal 0
  # otherwise return 2 * gcd(a>>1, b>>1)
  sarl $1, %edi # a >> 1
  sarl $1, %esi # b >> 1
  call gcd # gcd(a>>1, b>>1)
  imul $2, %eax # 2 * return value
  ret
  .L3:
  test $1, %edi # a & 1
  jne .L4 # jumps if a & 1 does not equal 0
  test $1, %esi # b & 1
  je .L4 # jumps if b & 1 does equal 0
  # otherwise return gcd(a>>1, b)
  sarl $1, %edi # a >> 1
  call gcd # gcd(a>>1, b)
  ret
  .L4:
  test $1, %edi # a & 1
  je .L5 # jumps if a & 1 does equal 0
  test $1, %esi # b & 1
  jne .L5 # jumps if b & 1 does not equal 0
  # otherwise return gcd(a, b>>1)
  sarl $1, %esi # b >> 1
  call gcd # gcd(a, b>>1)
  ret
  .L5:
  movl %edi, %edx # a value is saved in edx
  sub %esi,%edx # %edx= a-b
  sarl $1, %edx # %edx >> 1 === edx / 2^1
  movl %edx, %edi # move value of edx (a-b)/2 into a
  call gcd
  ret


# int gcd(int a, int b){
#     if(b > a){
#         return gcd(b, a);
#     }
#     if(b==0){
#         return a;
#     }
#     if(((a&1)==0) && ((b&1)==0)){
#         return 2 * gcd(a>>1, b>>1);
#     }
#     if(((a&1)==0) && ((b&1)!=0)){
#         return gcd(a>>1, b);
#     }
#     if(((a&1)!=0) && ((b&1)==0)){
#         return gcd(a, b>>1);
#     }
#     return gcd((a-b)/2, b);
# }
