#mips "Hello World"
#Matthew Philpot

.data
	the_string:   .asciiz "Hello World!\n"  #.asciiz - specifies a string terminated in null
.text

main:
	la $a0, the_string   	#la - load address, which in this case is a string
        li $v0, 4		#li - loads the last immediate
        syscall			#syscall - calls the last kernal
        
        li $v0, 10		#li - return
        syscall