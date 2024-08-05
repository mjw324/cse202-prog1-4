.global sort
sort: # **list is %rdi, int n is %esi
    #    int sorted=0, i=1, j;
    #    char *temp;
    movl $0, %eax # let int sorted be %eax
    movl $1, %ecx # let int i be %ecx, j will be %edx, *temp will be (%rbx)
    oloop:
    cmpl %esi, %ecx # i - n
    jge oend # jump to end if i - n >= 0
    testl %eax, %eax # testing sorted - is 0 if not sorted
    jne oend # jump to end if sorted does not equal 0
    movl $0, %edx # j = 0
    movl $1, %eax # sorted = 1
        iloop:
        movl %esi, %r15d # move n to %r15d
        subl %ecx, %r15d # %r15d = n - i
        cmpl %r15d, %edx # j - (n - i) < 0
        jge iend # jmp if >=0
        # otherwise call cmp and save to register
            movq %rdi, %rbp # save list
            movq %rdx, %rbx
            movq %rcx, %r12
            movq %rsi, %r13
            movq %rdi, %rax
            movq (%rax, %rdx, 8), %rdi # First cmp argument is  list + j*8
            movq 8(%rax, %rdx, 8), %rsi # Second cmp argument is list + j * 8 + 8
            call comp
            movq %rbp, %rdi # list back to %rdi 
            movq %rbx, %rdx
            movq %r12, %rcx
            movq %r13, %rsi
            cmpl $0, %eax
            jle endif # jump to endif if %eax - 0 <= 0
            movl %ecx, %r15d
            addl $1, %r15d # j + 1 is %r15d
            movq (%rdi, %rdx, 8), %r9 # list[j] pointer is temporarily stored in %r9
            movq (%rdi, %r15, 8), %r8 # list[j+1] pointer is stored in %r8
            movq %r9, (%rdi, %r15, 8) # move the list[j] pointer to list[j + 1]
            movq %r8, (%rdi, %rdx, 8) # move the list[j + 1] pointer to list[j]
            movl $0, %eax
        endif:
        inc %edx # j++
        jmp iloop # restart inner loop
        iend:
        inc %ecx # i++
        jmp oloop # restart outer loop
    oend:
    retq

comp: # *str1 is (%rdi), *str2 is (%rsi)
    loop:
    movb (%rdi), %cl # move *str1 to char size register
    movb (%rsi), %dl # move *str2 to char size register
    cmpb $0, %cl  # null is 0, 0-*str1
    je end # if null we go to end
    cmpb %cl, %dl # *str2 - *str1
    jne end # if there is a difference in the chars, we jump to end
    inc %rdi # move to next char address
    inc %rsi # move to next char address
    jmp loop
    end:
    movzbl %cl, %eax   # return val = *str1
    movzbl %dl, %r9d
    subl %r9d, %eax # ret = *str1 - *str2
ret


# void sort(char **list, int n){
#    int sorted=0, i=1, j;
#    char *temp;
#    while(i < n && !sorted){
#         j=0;
#         sorted = 1;
#         while(j<n-i){
#             if(cmp(list[j], list[j+1]) > 0){
#                 temp = list[j];
#                 list[j] = list[j+1];
#                 list[j+1] = temp;
#                 sorted = 0;
#             }
#             j++;
#         }
#         i++;
#     }
# }
# int cmp(char *str1, char *str2){ // returns 0 if match
#     while(*str1 && (*str1 == *str2)){
#         str1++;
#         str2++;
#     }
#     return *str1 - *str2;
# }

    
