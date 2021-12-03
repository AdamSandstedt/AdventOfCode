n%{1/{~}%}%:i   # Split input by line, then split each string into individual chars then convert them to ints
.,:h;           # Get the number of lines and store in var, h
{zip{{+}*}%}:w~ # Zip the lists together, so the nth list has all of the nth bits, then sum those list to get
                # the # of 1s in each bit place
{2*h>}%         # Check if each bit is a majority of 1s or 0s
.{!}%           # Copy the previous list of bits and invert them
{2base}:z~\z*p  # Convert both lists of bits into ints and multiply them

0:j;i           # Initilize j to 0 (used to index into the bits) and push the input to the stack
{{..w j=2*\,<}:x~!{:d;{j=d=},j):j;.,1>}:y~}do # Get the # of 1s in the jth bit and check if its a majority
                                              # by evaluating "(# of 1s)*2 >= (total # of bits)"
                                              # then filter out any lists that dont have that same jth bit
                                              # then reapeat this loop until the list only has 1 item left
~z          # Convert the resulting list of bits to an int
0:j;i       # Reset j to 0 and push i to the stack
{x y}do     # Almost the exact same as line 10, except it finds the minority bit instead of majority,
            # this is done by evaluating "(# of 1s)*2 < (total # of bits)"
~z*         # Convert the resulting list of bits to an int then multiply with the previous result
