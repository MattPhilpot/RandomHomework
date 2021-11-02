.data
mystring: .space 100     #maximum of 100 character..well 99 & 1 space I guess.
newline: .asciiz "\n"
space: .asciiz " "

.text

main:
li $v0,8
la $a0, mystring
li $a1, 10              # I only read 9 character and a space even though the max is 100. 
                        #Prof. wanted that extra space in declaration. 
syscall
la $a0, newline
li $v0, 4               #print function
syscall

la $a0, mystring        
move $t0, $a0
li $t2,9

loop:         # loop to display the ascii decimal of the character

lb $a0, 0($t0)
li $v0, 1       #print an integer - the ascii decimal
syscall
la $a0, space
li $v0, 4       #print string - " "
syscall

addi $t2, $t2, -1
addi $t0, $t0, 1
bnez $t2, loop  #when $t2 != 0, branch to loop

la $a0, newline
syscall         #printing a new line

jal calcRev

la 	$a0, mystring #load string with offset given
move	$t1, $a0
Looper:
lb	$a0, 0($t1)
li 	$v0, 11
syscall
add	$t1, $t1, 1
ble	$t1, $t0, Looper

li $v0, 10
syscall

calcRev:
la      $a0, mystring   
move    $t1, $a0   #beginning addess of the string
li      $t2, 0        #leftmost index
addi    $t3, $a1, -1 #rightmost index

loopRev:        
add     $t4, $t1, $t2
lb      $t5, 0($t4) #load character beginning from left-end

add     $t6, $t1, $t3
lb      $t7, 0($t6) #load character beginning from right-end

sb      $t5, 0($t6) #store left-end byte to right-end
sb      $t7, 0($t4) #opposite of the above instruction
addi    $t2, $t2, 1
addi    $t3, $t3, -1
slt     $t7, $t3, $t2   #if $t3 < $t2, $t7 = 0. else $t7 = 1
beqz    $t7, loopRev

jr      $ra
