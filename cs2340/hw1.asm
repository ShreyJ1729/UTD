.data 
# a b c integer inputs
a: .space 4
b: .space 4
c: .space 4

# answer result values
ans1: .word 0
ans2: .word 0
ans3: .word 0

# name string input
name: .space 20

# output strings
prompt_name: .asciiz "Enter your name: "
prompt_ints: .asciiz "Enter an integer from 1-100: "
result: .asciiz "Here's your answers: "
spacechar: .asciiz " "

.text
main:
	# prompt for name input
	li $v0, 4
	la $a0, prompt_name
	syscall
	
	# get name input
	li $v0, 8
	li $a1, 20
	la $a0, name
	syscall
	
	# get input a and store
	li $v0, 4
	la $a0, prompt_ints
	syscall
	li $v0, 5
	syscall
	sw $v0, a
	
	# get input b and store
	li $v0, 4
	la $a0, prompt_ints
	syscall
	li $v0, 5
	syscall
	sw $v0, b
	
	# get input c and store
	li $v0, 4
	la $a0, prompt_ints
	syscall
	li $v0, 5
	syscall
	sw $v0, c
	
	# calculate ans1 = 2a - c + 4
	lw $t1, a
	lw $t2, c
	li $t3, 0
	add $t3, $t1, $t1 # a+a
	sub $t3, $t3, $t2 # -c
	add $t3, $t3, 4 # +4
	sw $t3, ans1
	
	# calculate ans2 = b - c + (a - 2)
	lw $t1, a
	lw $t2, b
	lw $t3, c
	li $t4, 0
	sub $t4, $t2, $t3 # b-c
	add $t4, $t4, $t1 # +a
	sub $t4, $t4, 2 # -2
	sw $t4, ans2
	
	
	# calculate ans3 = (a + 3) - (b - 1) + (c + 3)
	# a - b + c + 7
	lw $t1, a
	lw $t2, b
	lw $t3, c
	li $t4, 0
	sub $t4, $t1, $t2
	add $t4, $t4, $t3
	add $t4, $t4, 7
	sw $t4, ans3
	
	# output name and output prompt
	li $v0, 4
	la $a0, name
	syscall
	li $v0, 4
	la $a0, result
	syscall
	
	# output answers, space separated
	li $v0, 1
	lw $a0, ans1
	syscall
	
	li $v0, 4
	la $a0, spacechar
	syscall
	
	li $v0, 1
	lw $a0, ans2
	syscall
	
	li $v0, 4
	la $a0, spacechar
	syscall
	
	li $v0, 1
	lw $a0, ans3
	syscall
	
exit:
	li $v0, 10
	syscall

# sample runs:
# a=1, b=2, c=3
# results were (3 -2 9)

# a=4 b=5 c=6
# results were (6, 1, 12)