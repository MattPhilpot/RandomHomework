#Matthew Philpot
#2610
#Program 6

.data
the_int:
	.word 4 #making room in memory for an integer with the address the_int

input:
	.asciiz "Enter a Number: \n" #asking for number


main:
	addi $t3, $zero, 1
	la $a0, input
	li $v0, 4
	syscall
	
	la $a0, the_int
	la $a1, the_int
	li $v0, 5
	syscall
	
	move $s0, $a0
	beq $s0, 1, end_loop
	addi $s0, $zero, $zero
 end_loop: 
	addi $s0, $t3, $zero
	
	move $a0, $s0
	li $v0, 1
	syscall
	
	li $v0, 10
	syscall