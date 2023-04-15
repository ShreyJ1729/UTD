Shrey Joshi
SXJ 210081

1.

42

11 28

8 13 61 18

2.

[42, 11, 28, 8, 13, 61, 18]

3.

1)  Swap the last node (11) with the root node (3)
2)  Move the new root (11) to its proper position:

    - Compare 11 to children (6 and 10)
    - Swap 11 with the smaller child (6)
    - compare 11 with new children (15 and 8)
    - swap 11 with smaller child (8)

           6

      / \
       8 10
      / \ / \
      15 25 19 21

4.

1)  Swap the last node (52) with the root node (12)
2)  Move the new root (52) to its position:

    - Compare 52 to children (18 and 16)
    - Swap 52 with smaller child (16)
    - Compare 52 to new children (21 and 24)
    - Swap 52 with smaller child (21)
    - compare 52 to its new children (42 and 54)
    - swap 52 with smaller child (42)

          	16
             /    \
            18    21
           / \   /  \
          25 32 54  24
          /\  / \
          49 46 58 50
                  / \
                 59 57

1.

Step 1:

    	        h1
    	         4
    	        / \
    	      10   50

    	        h2
    	         8
    	        / \
    	      12   19
    	     /  \
    	   30   14

Result

    		         4
    		        / \
    		      10   50
    		     / | \
    		   13 16 12
    		  /    |
    		20    19
    		     /  |
    		   30  14

Step 2:

    	        h1
    	         13
    	        /  \
    	      16   12

    	        h2
    	         19
    	        /  \
    	      30   14

Result

    			    13
    		        /  \
    		      16   19
    		     / |   / \
    		   20 50 30  14
    		         |
    		        12

Step 3:

    	        h1
    	         50

    	        h2
    	         30
    	        /  \
    	      14   19

Result

    	         14
    	        /  \
    	      19   30
    	          /  \
    	         50   -

6.

Step 1:
h1
5
/ \
 10 19
/ | / \
 13 20 54 -
/ | \
 16 18 25

    	        h2
    	         7
    	        / \
    	      12   40
    	     / |   / \
    	   30 14  50  -
    	       / \
    	      61 65

Result

    	         5
    	        / \
    	      10    7
    	     / |   / | \
    	   13 20 12 14 40
    	  / | \   / \
    	16 18 25 30 61
    	             |
    	            65

Step 2:

        h1
         16
        /  \
      18   25

    		        h2
    		         30
    		        /  \
    		      14   40
    		     / |   / \
    		   61 65 50  -

Result

    	         16
    	        /  \
    	      18   30
    	     / |   / | \
    	   25 20 14 40 50
    	             / \
    	            61 65

Step 3:

        h1
         18
        /  \
      25   20

        h2
         14
        /   \
      61    65

Result

    	         14
    	        /  \
    	      18   25
    	     / |   / \
    	   20 61 65  x

7.

Step 1:
h1
19
/ \
 54 39
/\ / \
 61 65 68 x
h2
11
/ \
 23 31
/\ / \
 55 87 92 x

Result

    	        11
    	       /  \
    	     19   31
    	     /\   / \
    	    54 23 39 92
    	   /|\
    	 61 65 68 55 87

Step 2:

    	        h1
    	        54
    	       /  \
    	     61   65
    	     /\   / \
    	    92 87 68 x

    	        h2
    	        23
    	       /  \
    	     19   31
    	     /\   / \
    	    55 39 11  x

Result
23
/ \
 54 31
/\ / \
 61 65 39 11
/. |\ |
92 87 68 55

Step 3:

    	        h1
    	        61
    	       /  \
    	     92   68
    	     /\    |
    	    87 65  55

    	        h2
    	        39
    	       /  \
    	     23   31
    	     /\   / \
    	    55 54 11  -

Result

    	        39
    	       /  \
    	     61   31
    	     /\   / \
    	    92 65 54 11
    	   /|\
    	 87 68 55

8.

Step 1:

        h1              h2
        8               6
        |               |
        12              15
        |               |
        17              9
       / | \            |
     14 20 21          19
                       |
                       11
                        \
                        16
                         \
                         23

Result
6
/ \
 8 9
/ \
 12 15
| / \
 17 19 11
/|\ |
14 20 16
|
23

Step 2:

        h1              h2
        17              11
       / | \            / \
     14 20 21         19  16
                       |   |
                       15  23
                      /
                     12
                      \
                       9
                       |
                       8
                       |
                       6

Result

        11
       / | \
     14 20 19
        |   | \
       17 15 16 23
       |\
      21 12
       |
       9
       |
       8
       |
       6

Step 3:

        h1              h2
        21              16
        |               / \
        20             15  23
       / | \           |
     14 17 19         19
                     / \
                   11  18
                   |   / \
                   12 13  14

        Result
        16
       / | \
     14 17 15
        |   | \
       21 19 23 18
           / \
         20 11 13
             |
             12
             |
             14

9.

Step 1:

        h1              h2
        13              6
       /   \            |
     17    22          15
     | \   | \        /  \
    20 21 40 26      19  16
         \   |\     /    |
         28 50 30 32     23
                     /   \
                    39   11

Result

    	        6
    	       / \
    	     13  15
    	     |   / \
    	    17 19  16
    	   /|\    / \
    	 20 21  22  23
    	      \/   / \
    	     28   39 11
    	           |
    	           30
    	           |
    	           32
    	           |
    	           50
    	           |
    	           40

Step 2:

        h1              h2
        17              11
       /   \            / \
     20    22         15  16
     |     | \       /    |
    28    40 26    19    23
          /   \   / \   / \
         39   50 32 30  31 18
                    /\   |
                   13 14 12

Result

    	        11
    	       /   \
    	     15    16
    	    /  \   / \
    	  17  19  23  18
    	  |\   |\  |
    	 20 22 28 31
    	  |   /   / \
    	 39 50  30 32
    	       |\  |
    	      13 14
    	       |
    	      12

Step 3:

        h1              h2
        28              18
       /   \            / \
     17    22         15  16
     |     | \       /    |
    20    40 26    19    23
          /   \   / \   / \
         39   50 32 30  31 11
                    /\   | \
                   13 14 12 21

Result

    	        18
    	       /   \
    	     15    16
    	    /  \   / \
    	  28  19  23  21
    	  |   |   |   |
    	 17  20  40  31
    	  |   /   / \  \
    	 39 50  30 32  11
    	       |\  |
    	      13 14
    	       |
    	      12

10.

a) []

b) assuming p is index of the parent node.

- Left index = `3p + 1`
- Midle index = `3p + 2`
- Right index =`3p + 3`

c) `floor((i - 1) / 3)` where `i` is the index of the child node.
