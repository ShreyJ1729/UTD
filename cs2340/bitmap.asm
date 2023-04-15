.data
colors: .word 0xFFFF00FF  # yellow
        .word 0xFF00FFFF  # cyan
        .word 0xFFFF0000  # red
        .word 0xFF00FF00  # green

.text
.globl main

# bitmap display constants
SCREEN_WIDTH = 640
SCREEN_HEIGHT = 480
DISPLAY_BASE = 0x10008000

# color constants
YELLOW = 0
CYAN = 1
RED = 2
GREEN = 3

# function to write a pixel to the bitmap display
# $a0 = x-coordinate
# $a1 = y-coordinate
# $a2 = color index
write_pixel:
    sll $t0, $a1, 9          # multiply y-coordinate by 640 (2^9)
    sll $t1, $a0, 2          # multiply x-coordinate by 4 (2^2)
    add $t2, $t0, $t1        # add x and y offsets
    add $t3, $t2, $t2        # multiply offset by 2 (since each pixel is 2 bytes)
    add $t4, $t3, $t3        # multiply offset by 2 again
    add $t5, $t4, $t4        # multiply offset by 2 again
    add $t6, $t5, $t5        # multiply offset by 2 again
    add $t7, $t6, $t6        # multiply offset by 2 again
    add $t8, $t7, $t7        # multiply offset by 2 again
    add $t9, $t8, $t8        # multiply offset by 2 again
    add $t2, $t9, $t2        # add x and y offsets again
    add $t2, $t2, $t2        # multiply offset by 2 again
    li $t3, 0x10008000       # load display base address
    addu $t3, $t3, $t2       # add offset to display base address
    lw $t4, colors($a2)      # load color value from color array
    sw $t4, 0($t3)           # write color value to bitmap display
    jr $ra                   # return

# function to draw a box on the bitmap display
draw_box:
    addi $sp, $sp, -16       # allocate stack space
    sw $ra, 0($sp)           # save return address
    sw $s0, 4($sp)           # save s0
    
    li $s0, 150              # initial x-coordinate
    li $s1, 110              # initial y-coordinate
    
    # draw top of box
    li $t0, YELLOW           # yellow color
    li $t1, 7                # draw 7 pixels
    loop_top:
        beq $t1, $zero, exit_loop_top   # exit loop when done
        jal write_pixel       # write pixel
        addi $s0, $s0, 1      # increment x-coordinate
        addi $t1, $t1, -1     # decrement loop counter
        j loop_top
    exit_loop_top:
    
    #
