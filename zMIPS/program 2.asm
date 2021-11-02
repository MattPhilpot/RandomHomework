#mips Program 2

#Matthew Philpot

#turn the following into mips:
#
# f = f+f+i;
# f - g+(j+2);

#registers used:
#
#	t0	-f = 10
#	t1	-i = 7
#	t2	-j = 3
#	t3	-g = 4

.data
	output: .asciiz "\nF = "

.text

main:
	li $t0, 10		#initialize t0 to 10
	li $t1, 7		#initialize t1 to 7
	li $t2, 3		#initialize t2 to 3
	li $t3, 4		#initialize t3 to 4
	add $t0, $t0, $t1
	
	li $v0, 4
	la $a0, output
	syscall
	li $v0, 1		#printing out t0
	move $a0, $t0
	syscall

	add $t2, $t2, 2
	add $t0, $t2, $t3
	
	li $v0, 4
	la $a0, output
	syscall
	li $v0, 1		#printing out t0
	move $a0, $t0
	syscall	