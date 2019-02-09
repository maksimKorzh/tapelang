var user_input (#0)
var first(#1)
var second(#2)
set second(@1)

var next(#3)
var count(#4)

var user_prompt(#5)
set user_prompt($Enter the number of terms&: @0)

goto user_prompt(#5)
print(%)

var new_line(#6)
set new_line(@10)

goto end_of_user_prompt(#27)

loop(+)
[
    goto user_input(#0)
    getchar(,)
    putchar(.)
    goto end_of_user_prompt(#27)
    set end_of_user_prompt(@0)
]

goto new_line(#6)
putchar(.)

goto user_input(#0)
substract(-48)

loop
[
    goto count(#4)
    
    if(count &= 0)
    {0
        goto next(#3)
        set next(=#4)
        print(.%)
        goto new_line(#6)
        putchar(.)
    }

    {1
        goto next(#3)
        set next(=#4)
        print(.%)
        goto new_line(#6)
        putchar(.)
    }
                                      
    goto next(#3)
    set next(=#1)
    add next(+#2)
    print(.%)
    goto new_line(#6)
    putchar(.)

    goto first(#1)
    set first(=#2)
    goto second(#2)
    set second(=#3)
    goto count(#4)
    inc(+)

    goto user_input(#0)
    dec(-)
]
