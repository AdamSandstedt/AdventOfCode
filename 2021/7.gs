','%{~}%$     # Split the input by commas, convert to integers, and sort the resulting list
{.0=:x;.-1=:m;9.?:a;}:f~    # Initialize some vars, x is the min value, m is the max, and
                            # a will be the lowest cost, initialized to large number (9^9)
{{.{x-abs g}%{+}*.a<{:a}{}if;x):x m<}do}:l~ # loop incrementing x until it equals m
                                            # each loop it calculates the distances between the
                                            # input positions and x then sum them, and check
                                            # if the sum is less than a, updating if it is
a p           # print a
f             # re-inititalize vars
{.)*2/}:g;    # update g so that it finds the triange number of the distance
l             # run the loop again with the new g
;a            # print a
