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
    
    -	             decrement (decrease by one) the byte at the data pointer
    -[Number]      substract number from the byte at the data pointer
    
    *[Number]      multiply the byte at the data pointer by the number
    :[Number]      divide the byte at the data pointer by the number
    
    $[String]      write string starting at the data pointer (until zero cell is encountered)
    
    .              output the byte at the data pointer.
    ,	             accept one byte of input, storing its value in the byte at the data pointer.
    
    %              output string at the data pointer (until zero cell is encountered)
    ;              accept bytes of input until '\n' is encountered and store them starting at the data pointer
    
    /              write file "out.txt" containing string stored at the data pointer (until zero cell is encountered)
    \              read file "out.txt" and store it at the data pointer
    
    [	           if the byte at the data pointer is zero, then instead of moving the instruction pointer forward
                   to the next command, jump it forward to the command after the matching "]" command
                   
    ]	           if the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward
                   to the next command, jump it back to the command after the matching [ command

# Build & Run

    sudo apt-get install libncurses5-dev libncursesw5-dev      to install ncurses library
    gcc tapelang.c -o tl -lncurses                             to compile with GCC
    tl hello.tl                                                to run a given file
