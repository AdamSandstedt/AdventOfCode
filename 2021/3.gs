n%{1/{~}%}%:i   # Split input by line, then split each string into individual chars then convert them to ints
.,:h;           # Get the number of lines and store in var, h
{zip{{+}*}%}:w~ # Zip the lists together, so the nth list has all of the nth bits, then sum those list to get
                # the # of 1s in each bit place
{2*h>}%         # Check if each bit is a majority of 1s or 0s
.{!}%           # Copy the previous list of bits and invert them
{2base}:z~\z*p  # Convert both lists of bits into ints and multiply them

0:j;i
{{..w j=2*\,<}:x~!{:d;{j=d=},j):j;.,1>}:y~}do
~z
0:j;i
{x y}do
~z*
