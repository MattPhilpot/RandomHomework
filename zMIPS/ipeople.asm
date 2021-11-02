#MIPS MAGIC

#Matthew Philpot

.data
	greeting:	.asciiz	"Please enter input file name: "
	fin:		.space 	80
	buffer: 	.space	16384
	open_err:	.asciiz	"Error opening file!"
	read_err:	.asciiz "Error reading file!"
	new_line:	.asciiz "\n"
.text


main:	
	li 	$v0, 4
	la	$a0, greeting
	syscall
	li	$v0, 8
	la	$a0, fin
	li	$a1, 80
	syscall
	
	la	$a0, fin
	add	$a0, $a0, 79
	
	jal fix_name
	jal file_read
	j end

fix_name:			#fixing your sloppy input... magically
	lb	$v0, 0($a0)
	bnez	$v0, fix_done
	sub	$a0, $a0, 1
	j 	fix_name

fix_done:			#I'm done bitches
	sb	$0, 0($a0)

file_read:
	li 	$v0, 13
	la	$a0, fin
    	li   	$a1, 0        
	li   	$a2, 0x100 	
	syscall
	beq	$v0, -1, oerr

	move 	$s0, $v0 	#saving file descriptor
	
	li 	$v0, 14
	move 	$a0, $s0
	la 	$a1, buffer
	li	$a2, 16384
	syscall
	beq	$v0, -1, rerr

	li	$v0, 30
	syscall
	move	$t7, $a1	#end time?

	li 	$v0, 4
	la 	$a0, buffer
	syscall

end:
   	li 	$v0, 10
    	syscall
	
oerr:				#called if error opening file
	li 	$v0, 4
	la 	$a0, open_err
	syscall
	j end

rerr:				#called if error reading file
	li 	$v0, 4
	la 	$a0, read_err
	syscall
	j end
