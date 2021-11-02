#mips Program 3
#Matthew Philpot
#turn the following into mips:
#
#int n;
#
#if(n==0)
#	test=1;
#else
#	test=2;
#printf( "%d\n", test );
#

#registers used:
#	t0	-used to store 'n'
#	t1	-used to store 'test'
#	s0	-used to store pass number

.data
	String_one:	.asciiz "\nRunning first time with n=0\n"
	String_two:	.asciiz "\nRunning second time with n=11\n"
	Print_out:	.asciiz "Test = "
.text

main:

pass_one:			#first pass
	li $v0, 4		#load 4 into v0 for string printout
	la $a0, String_one
	syscall			#printing first string

	li $s0, 0
	li $t0, 0		#load 0 into $t0.
	beq $0, 0, continue

pass_two:			#second pass
	li $v0, 4		#load 4 into v0 for string printout
	la $a0, String_two
	syscall			#printing second string

	addi $s0, $s0, 1
	li $t0, 11		#loads 11 into $t0

continue:
	bne $t0, 0, Else
	li $t1, 1
	beq $0, 0, Next

Else:	
	li $t1, 2

Next:
	la $a0, Print_out
	syscall			#printing out Print_out
	li $v0, 1		#load 1 into v0 for integer printout
	move $a0, $t1		#load test to be printed 
	syscall			#printing out test

	beq $s0, 0, pass_two	#if we're on the first pass, will go back to pass_two to begin second part of program

	li $v0, 10		#end of program
	syscall