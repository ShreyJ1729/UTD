See http://shreyjoshi.com/super-mario-mips

### Instructions

To run:

1. Load the "super-mario.asm" file into MARS (this may take 15-20 seconds for it to load)
2. Then hit "assemble" (again, will take 15-20 seconds)
3. Open the Bitmap Display with the following settings:
   1. unit pixel width = 2
   2. unit pixel height = 2
   3. width = 1024
   4. height = 512
   5. source = `$gp` (global pointer
4. Open the keyboard simulator and full-screen the Bitmap Display
5. Hit "Run" and then "connect to mips" on both the bitmap and keyboard display
6. Use the WASD keys to move the player around the screen. Walking off the screen wraps you around the start.

### Written Overview

I was very interested in creating animations in assembly, so I chose to create an animated mario character for my MIPS project. Due to time constraints, I stopped there and didn't create an actual playable game, but this code could easily be refactored and continued to represent a super mario level.

Since I knew before starting that the codebase for this project would become progressively messier and more difficult to debug, I decided to create macros for most small-but-annoying tasks in order to make later development more painless. This included single line drop-in replacements for

1. looping over a range and invoking another macro for each iteration step
   1. variants for reverse for loops and with step-sizes
2. loading in immediate values for registers and floats
3. converting between and doing arithmetic with int and float values
4. printing any int, float, string
5. bitshifting
6. sleep (delay)

I also had compound macros that invoked other macros, such as:

1. logging all player data
2. computing player distance from ground
3. drawing a single pixel at a certain x, y coordinate
   1. variants with different argument types (immediate vs register)
4. get memory address for a certain x, y location for a pixel in the bitmap
5. overlay black pixels on the old mario character for frame updates
6. increment/decrement player velocity x/y
7. increment/decrement player position x/y
8. processing input character
9. drawing mario run/idle frames 0-7

You can find a flowchart of the most high-level macros and how they're used in the flowchart diagram below.

Using macros was a critical part of development since it made debugging code significantly easier.

Now let's do a high-level walkthrough of the codebase and talk about some important design decisions.

#### Register and Memory Usage

- `$v0` is strictly used for system calls
- `$v1` is used for return values
- `$a0` - `$a3` are used for passing arguments to macros
- `$t0` - `$t9` are used for temporary values
- `$s0` - `$s7` are used for persistent variables (X, Y, color, etc.)

- `$s0` is player X coordinate
- `$s1` is player Y coordinate
- `$s2` is reserved for color
- `$s4` is reserved for direction --> -1 is left, 1 is right
- `$s7` is the frame counter for mario's animation

For all loops,

- `$t0` = start
- `$t1` = end
- `$t2` = step size (if applicable)
- `$t3` = iterator

### Flowchart

![[flowchart.png]]

See flowchart with zoomable interactive interface here:
https://mermaid.live/view#pako:eNqFVU1v2zAM_SuCzmmQrzqJB-zU607bafMgaDabCLUlQZLTuF3_-yjJju3UyU6RyUfykXyK3mmuCqApPRiuj-TH05dMZrLiRihmaskO4pk8PHwlz4ZXYJlTTIszlHaumw4mihLu4zI5YQ7wvhCXouJOKMkqnhtl_xcTqn4OyuS84I4H4F8hhRO8FG9g_5Jzw7RH3PGfoLzt18fGityyXEnruHRXxeYOzi6Y_KEl2nGKp2A8QqnBjExh9Jh6ZNQlb8CwSp2gAhkyx9A4ZmVYqZQeGQ2cwFhgk87OyF6FOzLr4H7sEDYClooXzIJjJ17WcJn7APGH45zQgfH9BAZ-bYR0Qh6mvaU6sLZ3P1vv7eYT_IXhr1EQg_gR4oDkIiBXyhRCcgefUXkJ3DCbGwB5w6nKoqXiAVcLibgjlwdgUToqF665kLoPRyWKa90OdCPkr4z6nzTLJA671ihP0gUNbW1dgR1mstdrvIckV7V0SJ_-jioU8lIgbLmtEs6-lLQlgCbrNal8PtxFq0MSduEr4MBCP-MC2K9ROVhLhNS1I06RWmMMtPEhGSqyJxJqBjYR2E4aGY2-Pav1ubt8LdZzCysiXBYoXa-JrlCsMMoxqhITDcpEg6_TMcYb-GxU5WeLVq512fg7esL14nfBKw3SO9nZ8zhC_kKgOOAwuEVqtwhETSFhFgn3Dd_wpJcuUYj9HEOzEl57S9gnGcz3RsLx7u_DxgyvWAUKUQBhUFNi-1z3zr_2NHj6WRi-Ttfe6X8IOqMVGGy8wHfuHedFMuqOKOOMpngsuHnJaCY_EMdrp743MqepMzXMWpE8CY77rzojFMIp8y2-m-H5nFHN5U-lLhD8pOk7PdP0cb5fPO42y2SfbDe7x91yRhuaLjfzxWa7W21W6-1inSyT7ceMvoUEi_l-v94nu_Vqsdkni90q-fgHbwzR7A

### Screenshots and Sample run video

Sample run: https://youtu.be/LhNIEds_Tz0

![[Pasted image 20230424154921.png]]

![[Pasted image 20230424155050.png]]

### Hints, Warnings, and Future Work

1. The code for animations consists of over 25,000 lines of calls to the draw_pixel macro with different coordinate and color arguments. This is obviously not the best way to do animations - a far more efficient way that I tried was converting the frame data into a different file format, then loading that into MIPS memory, but I kept running into memory errors so I ditched the approach for the easier way of just writing out all the function calls for every pixel for each frame.

2. Currently, when mario exits the screen, there is no code that puts his x position on the other side of the screen - instead what happens is that the x value is incremented beyond the max x value, so the y value effectively increases by 1 in the code that finds the memory address for the reference pixel.

3. The x velocity is dampened by 1% each frame if the player is on the ground, simulating friction, but this restriction does not apply when the player is in the air. Thus, it is possible to achieve infinite speed by repeatedly jumping and moving in one direction, since the screen wraps the player around whenever mario exits leaves the viewable area. This could be prevented by enforcing a maximum X velocity for ther player.
