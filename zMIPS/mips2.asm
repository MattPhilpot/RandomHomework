#Program 1 - Takes a string and reverses the string
#
# 
# Cosc 300

.data

prompt: .asciiz " Given String is =   "
 
str: .asciiz " aaaaBBBBccccDDDD "

ans: .asciiz " The String reversed is= " 

.text
.globl main

main:

la $a0, prompt
li $v0, 4
syscall


la $a0, str
li $v0, 4
syscall


la $a0, ans
li $v0, 4
syscall

la $t1, str
li $t2, 0




Loop:

lb $t0, 0($t1)
beqz $t0, next

addi $sp, $sp, -4
sw $t0, 0($sp)

j Loop




next: 

lw $t0, 0($sp)
beqz $t0, End

addi $sp, $sp, 4

li $v0, 4
move $a0, $t0
syscall

j next


End:

li $v0, 10
syscall