n%{~}%:i    # split input by newlines and convert each line into integer then assign to variable, i

'           # begin function for part 1
[.1>]zip-1< # copy i and remove first value, then zip the two lists together 
            # and remove the last list (the only list with a single value)
{~<}%       # map the "less than" function to the pair of values, this results in a list of 1s and 0s
{+}*        # fold the list using addition
':f~p       # this ends the part 1 function and applies it to i, then prints the value

i
[.1>.1>]zip-2<  # copy the input 2 times, each time removing the first value, then zip those 3 lists together
                # and remove the last 2 lists (they only contain 1 or 2 values, not 3)
{~++}%          # map an addition function to each of those lists, resulting in a list of sums
f~              # apply the part 1 function to the result
