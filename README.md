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
easy to implement such a functionallity with a simple atoi() function for parsing numeric constants. Numerous commands
for making brainfuck programming easier has arrived in addition as well...
