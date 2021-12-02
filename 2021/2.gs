n%{" "%}%:i                 # Split input by lines, then split each line by spaces
{0:h:d:a;}:v~               # Initialize variables, h, d, and a to zero (horizontal dist, depth, and aim)
['f''d''u']:x;              # Set two variables, x and y, that work together to map the commands
['h+:h;''d+:d;''d\-:d;']:y; # to each function, x contains the first letter of each command and in the
                            # corresponding index, y contains the function to run
{~~\1<x?y\=~}:f/            # push the pair of values to the stack (command word and number),
                            # convert the number from a string to an int, find the index of x that corresponds
                            # to the command word using just the first letter, then get the corresponding
                            # function from y and run it, providing the number from the pair as input
h d*p                       # multiply h and d then print the value

i                                   # push the input to the stack
v                                   # re-initialize variables h, d, and a to zero
['.h+:h;a*d+:d;''a+:a;''a\-:a;']:y; # change y to the new functions for part 2
{f}/                                # run f on each pair of values again, now that y has been changed
h d*                                # multiply h and d
