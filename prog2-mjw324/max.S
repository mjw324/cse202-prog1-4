.global max
max:
  movl $0, %edx # let i be %edx, set to 0
  movl (%rdi), %eax # let max be %eax, list[0] is (%rdi) (beginning of A[n])
  loop:
    cmpl %esi, %edx # i - n < 0?
    jge end # jumps to end if i - n >= 0
    cmpl %eax, (%rdi, %rdx, 4) # list[i] - max > 0? list[i] is equivalent to Mem_Address[%rdi + 4 * %edx]
    jle .L1 # jumps to .L1 if list[i] - max <= 0
    movl (%rdi, %rdx, 4), %eax # max = list[i] if list[i] > max
    .L1:
    inc %edx # i++
    jmp loop # jumps to beginning of while (test then action)
  end:
  ret


# *list in %rdi, n in %esi
# int max(int *list, int n){
#     int i = 0;
#     int max = list[i];
#     while (i < n){
#         if(list[i] > max)
#             max = list[i];
#         i++;
#     }
#     return max;
# }

