.data 
# name string input, 100 characters max
input_string: .space 100

# numbers
num_chars: .word 0
num_words: .word 0

# output strings
prompt: .asciiz "Enter your input string: "
exit_string: .asciiz "Goodbye!"
empty_string: .asciiz ""
space_char: .asciiz " "
word_count: .asciiz "Words: "
char_count: .asciiz "Characters: "
newlines: .asciiz "\n\n"

.text
main:
	# prompt dialog for input
	li $v0, 54
	la $a0, prompt
	la $a1, input_string
	li $a2, 100
	syscall
	
	# if cancel button pressed or input null or can't be parsed, exit (a1=0 means OK status)
	bne $a1, 0, exit
	
	# print inputted string
	li $v0, 4
	la $a0, input_string
	syscall
	
count:
	# count number of characters in string + load to $v0
	# $a1 is the address of input string
	# $s1 is the current char
	# $t1 is the number of characters, initializing as -1 since nullchar appears after last char
	# $t2 is the number of spaces

	# save $s1 to stack
	addi $sp, $sp, -1
	sb $s1, 0($sp)
	
	# initalize
	la $a1, input_string
	li $s1, 0
	li $t1, -1
	li $t2, 0

	jal count_loop

	# restore $s1 from stack
	lb $s1, 0($sp)
	addi $sp, $sp, 1

	j print
	
count_loop:
	# load current char onto $s1
	lb $s1, ($a1)
	
	# if char is null, terminate
	beq $s1, $zero, count_loop_done
	
	# increment length and increment char address
	addi $t1, $t1, 1
	addi $a1, $a1, 1
	la $v0, ($t1)

	# if char is space, increment space counter
	beq $s1, 32, count_space

	# loop
	j count_loop

count_space:
	# increment space counter
	addi $t2, $t2, 1
	la $v1, ($t2)

	# loop
	j count_loop

count_loop_done:
	jr $ra

print:
	# read from $v0 which contains number of chars, save to memory
	sw $v0, num_chars

	# read from $v1 which contains number of spaces, save to memory
	# first substract to get number of words
	add $v1, $v1, 1
	sw $v1, num_words
	
	# print char count
	li $v0, 4
	la $a0, char_count
	syscall
	
	li $v0, 1
	lw $a0, num_chars
	syscall

	# space
	li $v0, 4
	la $a0, space_char
	syscall

	# print word count
	li $v0, 4
	la $a0, word_count
	syscall

	li $v0, 1
	lw $a0, num_words
	syscall

exit:
	# show goodbye dialog and exit
	li $v0, 59
	la $a0, exit_string
	la $a1, empty_string
	syscall
	
	li $v0, 10
	syscall
