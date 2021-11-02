#mips Program 4

#Matthew Philpot

#turn the following into mips:
#
#int a[] = {1,2,3,4,5,6,7,8,9,10};
#int j;
#int test = 0;
#for(j=0; j<10; j++)
#	test += a[j];
#
#printf( "%d\n", test );
#

#registers used:
#	
#	t0	-used to store 'j'
#	t1	-used to store 'test'
#	t2	-used to store jump
#	s0	-used to store array


.data
	array: 		.space 10
.data
	string_print: 	.asciiz "\nTest = "
 
	
.text

main:
	li $t0, 1			#initialize j with 0
	li $t1, 0			#initialize test with 0
	li $t2, 4			#initialize offset with 4
	sw $t0, array($0)		#store int 1 into first spot in array

loop_one:				#first loop to fill up array
	add $t0, $t0, 1			#add 1 to t3
	sw $t0, array($t2)		#store t3 in array(offset t2)
	add $t2, $t2, 4			#increment offset by one spot
	bne $t0, 10, loop_one		#iff t2!=10, loop back to loop_one

	li $t2, 0			#reset offset to 0
	li $t0, 0			#reset j to 0			
	beq $0, 0, loop_two		#jumps to loop_two

jump_correct:
	li $t2, 4	

loop_two:				#loop two, this adds all the spots in array together into test
	add $t0, $t0, 1			#add 1 to j
	lw $s0, array($t2)		#load value from array(offset) into s0
	add $t1, $t1, $s0		#test += s0
	beq $t2, 0, jump_correct	#corrects the jump to have an offset of 4
	
	add $t2, $t2, 4			
	bne $t0, 10, loop_two

	li $v0, 1			
	move $a0, $t1
	syscall	

	li $v0, 10
	syscall