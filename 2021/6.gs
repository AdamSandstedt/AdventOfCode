','%{~}%:i;           # Splits input by commas, converts each to int, and assigns to var, i
10,1>{:x;i{x=},,}%    # Counts the number of occurances of 1 through 9, stores those in a
                      # list of length 9 (each postion tracks the number of fish on that day)
79{,{;(:x;6/~~[\x+\]x++}/}:f~ # Simulates 80 days. Each day, it shifts the first value to 
                              # the last postion and also adds that last amount to position 7
.{+}*p                # Adds up all the values in the list and prints
176f                  # Simulates for another 176 days to get to 256 days total
{+}*                  # Adds up all the values in the list
