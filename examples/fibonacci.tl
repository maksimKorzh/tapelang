#0                                      variable 'user input' &= 0
#1                                      variable 'first' &= 0
#2 @1                                   variable 'second' &= 1
#3                                      variable 'next' &= 0
#4                                      variable 'count' &= 0

#5 $Enter the number of terms&: @0      string to prompt user
#5 %                                    print string

#6 @10                                  new line

#100 $true >@10>@0

#27 +[#0,.#27@0]                        get user input and store it at cell 0
#6.
#0 -48                                  convert char to int at cell 0

[
    #4                                  go to cell 4 (count variable)
        
        {0 #3 =#4 .% #6. #0-}           if count &= 0 next &= count
        {1 #3 =#4 .% #6. #0-}           if count &= 1 next &= count
                                        
        #3 =#1 +#2 .% #6.               print next &= first &+ second
        #1 =#2                          first &= second
        #2 =#3                          second &= next
        
        #4+                             increment count

    #0                                  go to cell 0
    -                                   decrements loop
]
