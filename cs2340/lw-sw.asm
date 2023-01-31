.data
a: .word 1
b: .word 2
c: .word 3
d: .word 4

.text
main:
	# load a and b into register from memory
	lw $t1, a
	lw $t2, b
	
	# store into c and d
	sw $t1, c
	sw $t2, d
	
	# output all to console
	li $v0, 1
	la $a0, a
	syscall
	
exit:
	li $v0, 10
	syscall