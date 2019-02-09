# Tapelang
Tapelang is a successor of brainfuck programming language which involves extra command set.

# Idea
I believe everybody who had ever tried to follow Urban Muller's challenge to write something useful in brainfuck
found it extremely difficult to implement the very basic things you can easily do in "real" programming languages.
Originally I was trying to implement something similar to C's readline() function equivalent. Probably many of you
has seen such a program in brainfuck: +[,.] - a "text editor". The problem in this particular app is that you're in
the infinite loop and can't naturally escape the execution. So if user want's say quit on pressing Enter key, the
program would change to: +[,.----------], but what if you want to escape on pressing Esc? You'll need 27 times type
"-"... So that's how the idea was born - why not to write +[,.-27] ? That's where I've started. It turned out really
easy to implement such a functionality with a simple atoi() function for parsing numeric constants. Numerous commands
for making brainfuck programming easier has arrived in addition as well.

# Disclaimer
I don't claim myself to be the inventor of something new for the ideas descibed above has been implemented many times
before. There are some "languaes" on esolangs.org with somewhat similar functionality. So I'm doing this just because
I like the idea behind brainfuck, especially it's extreme minimalism, and simply want slightly extend them on my own.

# Command set

    !              execute commands at the data pointer until encountered "!" to switch back to source file
    ?              print debug info in format "cell#ID: Value"
    &              skip character next to "&" (needed to store command symbols as strings)
    
    #[Number]      set data pointer at cell of a given number
    >              increment the data pointer (to point to the next cell to the right)
    
    >[Number]      add number to the data pointer

    <	             decrement the data pointer (to point to the next cell to the left)
    <[Number]      subtract number from the data pointer
    
    @[Number]      set byte at the data pointer to a given number
    
    #@             set data pointer at the value of a byte at given cell
    @#             set the byte at the data pointer to the value of data pointer
    
    +              increment (increase by one) the byte at the data pointer
    +[Number]      add number to the byte at the data pointer
    +#[Number]     add value of byte at cell#[Number] to the current cell's byte
    
    -	           decrement (decrease by one) the byte at the data pointer
    -[Number]      substract number from the byte at the data pointer
    -#[Number]     substract value of byte at cell#[Number] from the current cell's byte

    =#[Number]     assign value of byte at cell#[Number] to the current cell's byte
    
    *[Number]      multiply the byte at the data pointer by the number
    :[Number]      divide the byte at the data pointer by the number

    {[Number]}     execute {code} only if number equals the byte at the data pointer
    
    $[String]      write string starting at the data pointer (until zero cell is encountered)
    
    .              output ascii character of the byte at the data pointer
    .%             output decimal value of the byte at the data pointer
    ,	             accept one byte of input, storing its value in the byte at the data pointer
    
    %              output string at the data pointer (until zero cell is encountered)
    ;              accept bytes of input until '\n' is encountered and store them starting
                   at the data pointer
    
    /              write file "out.txt" containing string stored at the data pointer
                   (until zero cell is encountered)
                   
    \              read file "out.txt" and store it at the data pointer
    
    [	           if the byte at the data pointer is zero, then instead of moving
                   the instruction pointer forward to the next command, jump it forward
                   to the command after the matching "]" command
                   
    ]	           if the byte at the data pointer is nonzero, then instead of moving
                   the instruction pointer forward to the next command, jump it back
                   to the command after the matching [ command

# Example programs

  Hello, world!

    $Hello&, world&! >@10
    #0 %

  Fibonacci with casual styled comments

    #0                                      variable 'user input' &= 0
    #1                                      variable 'first' &= 0
    #2 @1                                   variable 'second' &= 1
    #3                                      variable 'next' &= 0
    #4                                      variable 'count' &= 0
    
    #5 $Enter the number of terms&: @0      string to prompt user
    #5 %                                    print string
    
    #6 @10                                  new line

    #27 +[#0,.#27@0]                        get user input and store it at cell 0
    #6.
    #0 -48                                  convert char to int at cell 0
    
    [
        #4                                  go to cell 4 (count variable)
            
            {0 #3 =#4 .% #6. }             if count &= 0 next &= count
            {1 #3 =#4 .% #6. }             if count &= 1 next &= count
                                            
            #3 =#1 +#2 .% #6.               print next &= first &+ second
            #1 =#2                          first &= second
            #2 =#3                          second &= next
            
            #4+                             increment count
    
        #0                                  go to cell 0
        -                                   decrements loop
    ]

  Fibonacci with pseudo code styled comments

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
    
        esle if(count &= 1)
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

# Build & Run

    sudo apt-get install libncurses5-dev libncursesw5-dev      to install ncurses library
    gcc tapelang.c -o tl -lncurses                             to compile with GCC
    tl hello.tl                                                to run a given file
