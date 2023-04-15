# Calculating BMI in MIPS
# Shrey Joshi
# SXJ210081

.data
prompt1: .asciiz "What is your name? "
prompt2: .asciiz "Please enter your height in inches: "
prompt3: .asciiz "Please enter your weight in pounds: "
newline: .asciiz "\n"
output2: .asciiz "your bmi is: "
output4: .asciiz "This is a normal weight"
output3: .asciiz "This is considered underweight"
output5: .asciiz "This is considered overweight"
output6: .asciiz "This is considered obese"

bmi_constant: .float 703.0
bmi_under: .float 18.5
bmi_normal: .float 25.0
bmi_over: .float 30.0


# 20 character max name
name: .space 20

.text
  
input:
	# Ask for user name
	li $v0, 4
	la $a0, prompt1
	syscall
	
	# Read in user name
	li $v0, 8
	li $a1, 20
	la $a0, name
	syscall
	
	# Ask for user height
	li $v0, 4
	la $a0, prompt2
	syscall
	
	# Read in user height
	li $v0, 5
	syscall
	mtc1 $v0, $f0
	cvt.s.w $f0, $f0
	
	# Ask for user weight
	li $v0, 4
	la $a0, prompt3
	syscall
	
	# Read in user weight
	li $v0, 5
	syscall
	mtc1 $v0, $f2
	cvt.s.w $f2, $f2
	
	# print out user name
	li $v0, 4
	la $a0, name
	syscall
	

calculate:
	# calculate bmi from inputs, $f0 = height and $f2 = weight
	
	l.s  $f4, bmi_constant # load 703 to f4
	
	mul.s $f2, $f2, $f4 # weight *= 703
	mul.s $f0, $f0, $f0 # height *= height
	div.s $f12, $f2, $f0 # bmi = f12 = weight/height
	

output_bmi:
	# output prompt
	li $v0, 4
	la $a0, output2
	syscall
	
	# output bmi value, alread in $f12
	li $v0, 2
	syscall
	
	li $v0, 4
	la $a0, newline
	syscall
	

classify_bmi:
	# load comparison values into f0, f2, f4
	l.s $f0, bmi_under
	l.s $f2, bmi_normal
	l.s $f4, bmi_over
	
	# prepare for string print
	li $v0, 4
	
	# jump to appropriate section based on bmi value
	c.lt.s $f12, $f0
	bc1t underweight
	c.lt.s $f12, $f2
	bc1t normalweight
	c.lt.s $f12, $f4
	bc1t overweight
	j obese

underweight:
	la $a0, output3
	syscall
	j exit
	
normalweight:
	la $a0, output4
	syscall
	j exit
	
	
overweight:
	la $a0, output5
	syscall
	j exit
	
obese:
	la $a0, output6
	syscall
	
exit:
	li $v0, 10
	syscall