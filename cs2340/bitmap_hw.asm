# -----------------------------------------------
# DESCRIPTION
# -----------------------------------------------

# Name: Shrey Joshi
# Class: CS 2340 - Computer Architecture
# Assignment: Bitmap Project

# Super Mario Bros in MIPS Assembly

# -----------------------------------------------
# REGISTER & MEMORY USAGE
# -----------------------------------------------

# $v0 is strictly used for system calls
# $v1 is used for return values
# $a0 - $a3 are used for passing arguments to macros
# $t0 - $t9 are used for temporary values
# $s0 - $s7 are used for persistent variables (X, Y, color, etc.)

# $s0 is player X coordinate
# $s1 is player Y coordinate
# $s2 is reserved for color

# For all loops, 
# 	$t0 = start
# 	$t1 = end
# 	$t2 = step size (if applicable)
# 	$t3 = iterator


# -----------------------------------------------
# LONG GRAPHICS MACROS (CTR-F END_LONG_GRAPHICS_MACROS to find the end)
# -----------------------------------------------
# 	%regX = register containing X coordinate
# 	%regY = register containing Y coordinate

# ------------------------------------------------
# END OF LONG GRAPHICS MACROS
# ------------------------------------------------




#  -----------------------------------------------
# CONSTANTS
# ------------------------------------------------

# WIDTH = 1024 / 2 = 256
.eqv WIDTH, 512

# HEIGHT = 512 / 2 = 128
.eqv HEIGHT, 256

#  colors (first 2 bytes are alpha)
.eqv	RED 	0x00FF0000
.eqv	GREEN	0x0000FF00
.eqv	BLUE	0x000000FF

.eqv	WHITE	0x00FFFFFF
.eqv	BLACK	0x00000000


.eqv INPUT_AVAILABLE, 0xffff0000
.eqv INPUT_VALUE, 0xffff0004

.eqv PLAYER_HEIGHT, 50
.eqv PLAYER_WIDTH, 40

.eqv CLEAR_THRESHOLD, 10

# ------------------------------------------------
# DATA
# ------------------------------------------------

.data

	PLAYER_X_VELOCITY:	.word 10
	PLAYER_JUMP_VELOCITY:	.word 4

	GROUND_Y: 	.word 200

	VELOCITY_DAMPENING:	.float 0.99
	GRAVITY_ACCEL:	.float 0.1

	newline:	.asciiz "\n"
	marker: 	.asciiz "XXXXXXXXXXXXX"
	xVel:		.asciiz "X Speed: "
	xVelFloat:	.asciiz "X Speed (float): "
	yVel:		.asciiz "Y Speed: "
	yVelFloat:	.asciiz "Y Speed (float): "
	xPos:		.asciiz "X Pos: "
	xPosFloat:	.asciiz "X Pos (float): "
	yPos:		.asciiz "Y Pos: "
	yPosFloat:	.asciiz "Y Pos (float): "
	distanceFromGround: .asciiz "Distance from ground: "

# ------------------------------------------------
# MISC HELPER MACROS
# ------------------------------------------------

# ----- FOR LOOP -----
# 	%regIterator = register to use as iterator
# 	%from = starting value
# 	%to = ending value (inclusive)
# 	%bodyMacroName = name of macro to call in loop body
.macro for (%regIterator, %from, %to, %bodyMacroName, %arg1, %arg2, %arg3)
	add %regIterator, $zero, %from
	Loop:
	%bodyMacroName (%arg1, %arg2, %arg3)
	add %regIterator, %regIterator, 1
	ble %regIterator, %to, Loop

.end_macro

# ----- FOR LOOP REVERSE -----
# 	%regIterator = register to use as iterator
# 	%from = starting value
# 	%to = ending value (inclusive)
# 	%bodyMacroName = name of macro to call in loop body
.macro for_reverse (%regIterator, %from, %to, %bodyMacroName, %arg1, %arg2, %arg3)
	add %regIterator, $zero, %from
	Loop:
	%bodyMacroName (%arg1, %arg2, %arg3)
	sub %regIterator, %regIterator, 1
	bge %regIterator, %to, Loop

.end_macro

# ----- FOR LOOP WITH STEP -----
# 	%regIterator = register to use as iterator
# 	%from = starting value
# 	%to = ending value
# 	%step = step size
# 	%bodyMacroName = name of macro to call in loop body
.macro for_step (%regIterator, %from, %to, %step, %bodyMacroName, %arg1, %arg2, %arg3)
	add %regIterator, $zero, %from
	Loop:
	%bodyMacroName (%arg1, %arg2, %arg3)
	add %regIterator, %regIterator, %step
	ble %regIterator, %to, Loop

.end_macro

# ----- FOR LOOP WITH STEP REVERSE -----
# 	%regIterator = register to use as iterator
# 	%from = starting value
# 	%to = ending value
# 	%step = step size
# 	%bodyMacroName = name of macro to call in loop body
.macro for_step_reverse (%regIterator, %from, %to, %step, %bodyMacroName, %arg1, %arg2, %arg3)
	add %regIterator, $zero, %from
	Loop:
	%bodyMacroName (%arg1, %arg2, %arg3)
	sub %regIterator, %regIterator, %step
	bge %regIterator, %to, Loop

.end_macro

# ----- SET VALUE IMMEDIATE -----
# 	%reg = register to set
# 	%value = value to set
.macro set_value_immediate (%reg, %value)
	li %reg, %value

.end_macro

# ----- SET VALUE FROM REGISTER -----
# 	%reg = register to set
# 	%value = value to se
.macro set_value_register (%reg, %value)
	add %reg, $zero, %value
.end_macro

# ----- SET VALUE FLOAT IMMEDIATE -----
# 	%reg = register to set
# 	%value = value to set
.macro set_value_float_immediate (%freg, %value)
	set_value_immediate $t9, %value
	set_float_from_int %freg, $t9

.end_macro

# ----- DIVIDE FLOAT IMMEDIATE -----
# 	%reg = register to set
# 	%value = value to divide by
.macro divide_float_immediate (%reg, %value)
	set_value_float_immediate $f31, %value
	div.s %reg, %reg, $f31

.end_macro

# ----- SET INT FROM FLOAT -----
# 	%float = register to move from
# 	%reg = register to move to
.macro set_int_from_float (%reg, %float)
	mov.s $f0, %float
	cvt.w.s $f0, $f0
	mfc1 %reg, $f0

.end_macro

# ----- SET FLOAT FROM INT -----
# 	%float = register to move to
# 	%reg = register to move from
.macro set_float_from_int (%float, %reg)
	mtc1 %reg, %float
	cvt.s.w %float, %float

.end_macro

# ----- FLIP SIGN FLOAT -----
# 	%reg = register to flip
.macro flip_sign_float (%reg)
	neg.s %reg, %reg
.end_macro

# ----- FLIP SIGN INT -----
# 	%reg = register to flip
.macro flip_sign_int (%reg)
	neg %reg, %reg
.end_macro

# ----- SHIFT LEFT & SHIFT RIGHT -----
# 	%reg = register to shift
# 	%shift = number of bits to shift left
.macro shift_left (%reg, %shift)
	sll %reg, %reg, %shift
.end_macro

.macro shift_right (%reg, %shift)
	srl %reg, %reg, %shift
.end_macro

# ----- PRINT NEWLINE -----
.macro print_newline ()
	li $v0, 4
	la $a0, newline
	syscall
.end_macro

# ----- PRINT INTEGER WITH NEWLINE -----
# 	%reg = register to print
.macro print_integer_with_newline (%reg)
	li $v0, 1
	move $a0, %reg
	syscall
	li $v0, 4
	la $a0, newline
	syscall
.end_macro

# ----- PRINT FLOAT WITH NEWLINE -----
# 	%reg = register to print
.macro print_float_with_newline (%reg)
	li $v0, 2
	mov.s $f12, %reg
	syscall
	li $v0, 4
	la $a0, newline
	syscall
.end_macro

# ----- PRINT STRING WITH NEWLINE -----
# 	%string = string to print
.macro print_string_with_newline (%string)
	li $v0, 4
	la $a0, %string
	syscall
	li $v0, 4
	la $a0, newline
	syscall

.end_macro

# ----- PRINT STRING -----
# 	%string = string to print
.macro print_string (%string)
	li $v0, 4
	la $a0, %string
	syscall

.end_macro

# ----- WIDTH TIMES -----
# 	%factor = number of times to multiply by width
.macro width_times_constant (%factor)
	li 	$v1, %factor
	mul	$v1, $v1, WIDTH
.end_macro

# ----- HEIGHT TIMES -----
# 	%factor = number of times to multiply by height
.macro height_times_constant (%factor)
	li 	$v1, %factor
	mul	$v1, $v1, HEIGHT
.end_macro

# ----- sleep -----
# 	%time = time in milliseconds
.macro sleep (%time)
	li $v0, 32
	li $a0, %time
	syscall
.end_macro

# ----- exit -----
.macro exit ()
	li $v0, 10
	syscall
.end_macro

# ----- LOG DATA -----
.macro log_data()
	print_string_with_newline (marker)

	print_string (xPos)
	print_integer_with_newline ($s0)
	print_string(xPosFloat)
	print_float_with_newline ($f20)

	print_string (yPos)
	print_integer_with_newline ($s1)
	print_string(yPosFloat)
	print_float_with_newline ($f21)

	print_string(xVelFloat)
	print_float_with_newline ($f22)

	print_string(yVelFloat)
	print_float_with_newline ($f23)

	print_string(distanceFromGround)
	player_distance_from_ground()
	print_integer_with_newline ($v1)

	print_string_with_newline (marker)
.end_macro

# ----- PLAYER DISTANCE FROM GROUND -----
.macro player_distance_from_ground ()
	lw $t9, GROUND_Y # ground y coordinate
	set_int_from_float $t8, $f21 # player y coordinate
	
	sub $t9, $t9, $t8 # ground y - player y
	# will be negative if player is below ground
	move $v1, $t9
.end_macro

# ------------------------------------------------
# GRAPHICS MACROS
# ------------------------------------------------

# ----- DRAW PIXEL -----
# 	%x = x coordinate
# 	%y = y coordinate
# 	%color = color to draw
.macro draw_pixel (%x, %y, %color)
	# address = $gp + 4*(x + y*width)
	get_pixel_coordinate (%x, %y)

	sw	%color, ($v1)	  # store color at memory location

.end_macro

# ----- DRAW PIXEL WITH COLOR -----
# 	%x = x coordinate
# 	%y = y coordinate
# 	%color = color to draw (immediate)
.macro draw_pixel_with_color_immediate (%x, %y, %color)
	# address = $gp + 4*(x + y*width)
	get_pixel_coordinate (%x, %y)

	li	$t9, %color
	sw	$t9, ($v1)	  # store color at memory location

.end_macro

# ----- DRAW PIXEL WITH COLOR AND OFFSET -----
# 	%x = x offset from player x (immediate)
# 	%y = y offset from player y (immediate)
# 	%color = color to draw (immediate)
.macro draw_pixel_with_color_and_offset_immediate (%x, %y, %color)
	# address = $gp + 4*(x + y*width)
	addi $t9, $s0, %x
	addi $t8, $s1, %y
	get_pixel_coordinate (%x, %y)

	li	$t9, %color
	sw	$t9, ($v1)	  # store color at memory location

# ----- DRAW PIXEL RAW -----
# 	%address = address to draw pixel
# 	%color = color to draw
.macro draw_pixel_raw (%address, %color, %ignore)
	sw	%color, (%address)	  # store color at memory location

.end_macro

# ----- GET PIXEL COORDINATE -----
# 	%x = x coordinate
# 	%y = y coordinate
.macro get_pixel_coordinate (%x, %y)
	# address = $gp + 4*(x + y*width)
	mul	$v1, %y, WIDTH   # y * WIDTH
	add	$v1, $v1, %x	  # add X
	mul	$v1, $v1, 4	  # multiply by 4 to get word offset
	add	$v1, $v1, $gp	  # add to base address
.end_macro

# ----- CLEAR SCREEN -----
# 	%color = color to clear screen with
.macro clear_screen (%color)
	# start at pixel 0
	get_pixel_coordinate ($zero, $zero)
	set_value_register ($t0, $v1)

	# go until last pixel
	set_value_immediate ($t1, WIDTH)
	set_value_immediate ($t2, HEIGHT)
	get_pixel_coordinate($t1, $t2)
	subi $t1, $v1, 4

	# step size = 4
	set_value_immediate ($t2, 4)

	# set up iterator
	get_pixel_coordinate ($zero, $zero)
	set_value_register ($t3, $v1)

	# set color to register
	set_value_register ($t4, %color)

	# loop through all pixels
	for_step ($t3, $t0, $t1, $t2, draw_pixel_raw, $t3, $t4, $zero)

.end_macro


# ----- CLEAR OLD PLAYER -----
.macro clear_old_player ()
	# delete old player drawing by drawing a black rectangle over player
	clear_mario($s0, $s1)

	set_value_immediate ($s2, BLACK)

.end_macro

# ----- DRAW NEW PLAYER -----
.macro draw_new_player ()
	# draw new player drawing
	set_value_immediate ($s2, RED)
	jal	draw_player

.end_macro

# ------------------------------------------------
# PLAYER MACROS
# ------------------------------------------------

# ----- INCREMENT PLAYER VELOCITY X -----
.macro increment_player_velocity_x (%value)
	lw $t9, %value
	set_float_from_int($f0, $t9)
	divide_float_immediate ($f0, 10)
	add.s $f22, $f22, $f0

.end_macro

# ----- DECREMENT PLAYER VELOCITY X -----
.macro decrement_player_velocity_x (%value)
	lw $t9, %value
	set_float_from_int($f1, $t9)
	divide_float_immediate ($f1, 10)
	sub.s $f22, $f22, $f1

.end_macro

# ----- INCREMENT PLAYER VELOCITY Y -----
.macro increment_player_velocity_y (%value)
	lw $t9, %value
	set_float_from_int($f1, $t9)
	add.s $f23, $f23, $f1

.end_macro

# ----- DECREMENT PLAYER VELOCITY Y -----
.macro decrement_player_velocity_y (%value)
	lw $t9, %value
	set_float_from_int($f0, $t9)
	sub.s $f23, $f23, $f0

.end_macro

# ----- INCREMENT PLAYER X pos -----
.macro increment_player_x_pos (%value)
	lw $t9, %value
	set_float_from_int($f0, $t9)
	divide_float_immediate ($f0, 10)
	add.s $f20, $f20, $f0
	set_int_from_float ($s0, $f20)

.end_macro

# ----- DECREMENT PLAYER Y pos -----
.macro decrement_player_y_pos (%value)
	lw $t9, %value
	set_float_from_int($f0, $t9)
	sub.s $f21, $f21, $f0
	set_int_from_float ($s1, $f21)

.end_macro

# ------------------------------------------------
# MAIN
# ------------------------------------------------

.text
main:
	# set up variables

	# f20 = X position float = WIDTH/2
	set_value_float_immediate	($f20, WIDTH)
	divide_float_immediate	($f20, 2)

	# f21 = Y position float = HEIGHT/2
	set_value_float_immediate	($f21, HEIGHT)
	divide_float_immediate	($f21, 2)

	# set s0 and s1 (ints for graphics) based on f20 and f21
	set_int_from_float	($s0, $f20)
	set_int_from_float	($s1, $f21)

	# set initial velocities to 0
	# f22 = velocity x
	# f23 = velocity y
	set_value_float_immediate	($f22, 0)
	set_value_float_immediate	($f23, 0)

	# load color into s2
	set_value_immediate		($s2 , RED)

	# draw initial player
	jal draw_player

# ------------------------------------------------
# MAIN LOOP
# ------------------------------------------------

main_loop:
	# 60 fps = 17 ms / frame
	sleep(17)
	log_data

	# check if input available. if not, skip the processing and goto update player
	lw 	$t9, INPUT_AVAILABLE
	beq	$t9, $zero, update_player

	# processes input if one of wasd/space --> this updates player velocity based on input
	lw 	$t9, INPUT_VALUE
	beq	$t9, 32, exit	# space
	beq	$t9, 119, jump	# w
	beq $t9, 97, left	# a
	beq	$t9, 115, down_smash	# s
	beq	$t9, 100, right	# d


	j main_loop


update_player:
	# update player position based on velocity
	# pos = pos + velocity
	add.s $f20, $f20, $f22 # x
	add.s $f21, $f21, $f23 # y

	# if player is under ground now, set velocity y to 0 and snap player to ground
	player_distance_from_ground
	
	# blt $v1, 0, snap_player_to_ground

	# if player is close to ground and velocity >=0, don't update velocity. in other cases, update velocity
	# velocity y = velocity y + gravity
	bgt $v1, 0, do_gravity # if player is not on ground, apply gravity
	blt $s3, 0, do_gravity # if player is on ground and velocity y is negative, apply gravity
	
	skip_gravity:
		# set velocity y to 0
		set_value_float_immediate	($f23, 0)
		j after_gravity

	do_gravity:
		# update velocity y
		
		l.s $f0, GRAVITY_ACCEL
		add.s $f23, $f23, $f0 # y update velocity
	
	after_gravity:

	# dampen velocity x
	l.s $f0, VELOCITY_DAMPENING
	mul.s $f22, $f22, $f0

	# if abs velocity x is less than 0.1, set it to 0
	abs.s $f0, $f22
	set_value_float_immediate	($f1, 2)
	divide_float_immediate	($f1, 10)
	c.lt.s $f0, $f1
	bc1t set_velx_zero
	j skip_set_velx_zero

	set_velx_zero:
		set_value_float_immediate	($f22, 0)
	skip_set_velx_zero:

	# store new positions in temp
	set_int_from_float	($t8, $f20)
	set_int_from_float	($t9, $f21)

	# if new positions are same as the last frame's positions, don't re-draw character (this saves time)
	# just go back to main loop
	bne	$t8, $s0, clear_and_redraw_player
	bne	$t9, $s1, clear_and_redraw_player
	j main_loop

# snap_player_to_ground:
# 	# set player y position to ground
# 	lw $t9, GROUND_Y
# 	set_float_from_int($f21, $t9)
# 	set_value_register($s1, $t9)

# 	# set velocity y to 0
# 	set_value_float_immediate	($f23, 0)
# 	set_value_immediate		($s3, 0)

# 	j main_loop

clear_and_redraw_player:
	clear_old_player
		
	# save new values in s0 and s1
	set_int_from_float	($s0, $f20)
	set_int_from_float	($s1, $f21)
		
	draw_new_player

	j main_loop



jump:
	# check if player is on ground
	player_distance_from_ground
	# if not on ground, don't jump, just update player's physics and go back to main loop
	bne $v1, -2, update_player

	decrement_player_velocity_y(PLAYER_JUMP_VELOCITY)
	# set_player_velocity_y(PLAYER_JUMP_VELOCITY)
	j update_player
	
down_smash:
	# increment_player_velocity_y(PLAYER_DOWN_VELOCITY)
	j update_player

left:
	decrement_player_velocity_x(PLAYER_X_VELOCITY)
	j update_player
	
right:
	increment_player_velocity_x(PLAYER_X_VELOCITY)
	j update_player
		
exit:	li	$v0, 10
	syscall

# ------------------------------------------------
draw_player:

	draw_mario($s0, $s1)

	# # ----- LEFT SIDE
	# # set start to Y
	# set_value_register	($t0, $s1)
	# # set end as Y - PLAYER_HEIGHT
	# subi 	$t1, $t0, PLAYER_HEIGHT
	# # set x-coordinate to X
	# set_value_register	($t9, $s0)
	# # loop (reverse since we decrement)

	# for_reverse	($t3, $t0, $t1, draw_pixel, $t9, $t3, $s2)

	# # ----- TOP SIDE
	# # set start to X
	# set_value_register	($t0, $s0)
	# # set end as X + PLAYER_WIDTH
	# addi 	$t1, $t0, PLAYER_WIDTH
	# # set y-coordinate to Y - PLAYER_HEIGHT
	# subi 	$t9, $s1, PLAYER_HEIGHT
	# # loop
	# for	($t3, $t0, $t1, draw_pixel, $t3, $t9, $s2)

	# # ----- RIGHT SIDE
	# # set start to Y - PLAYER_HEIGHT
	# subi 	$t0, $s1, PLAYER_HEIGHT
	# # set end as Y
	# set_value_register	($t1, $s1)
	# # set x-coordinate to X + PLAYER_WIDTH
	# addi 	$t9, $s0, PLAYER_WIDTH
	# # loop
	# for	($t3, $t0, $t1, draw_pixel, $t9, $t3, $s2)

	# # ----- BOTTOM SIDE
	# # set start to X + PLAYER_WIDTH
	# addi 	$t0, $s0, PLAYER_WIDTH
	# # set end as X
	# set_value_register	($t1, $s0)
	# # set y-coordinate to PLAYER_HEIGHT
	# set_value_register	($t9, $s1)
	# # loop
	# for_reverse	($t3, $t0, $t1, draw_pixel, $t3, $t9, $s2)

	jr 	$ra