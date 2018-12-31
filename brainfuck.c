/*********************************************************************************\
;---------------------------------------------------------------------------------;
;                            Brainfuck interpreter v0.0.1                         ;
;---------------------------------------------------------------------------------;
\*********************************************************************************/

/*********************************************************************************\
;---------------------------------------------------------------------------------;
;       Copyright © 2019 Your Maksim Korzh  <freesoft.for.people@gmail.com>       ;
;---------------------------------------------------------------------------------;
'       THIS PROGRAM IS FREE SOFTWARE. IT COMES WITHOUT ANY WARRANTY, TO          ;
;        THE EXTENT PERMITTED BY APPLICABLE LAW. YOU CAN REDISTRIBUTE IT          ;
;       AND/OR MODIFY IT UNDER THE TERMS OF THE DO WHAT THE FUCK YOU WANT         ;
;          TO PUBLIC LICENCE, VERSION 2, AS PUBLISHED BY SAM HOCEVAR.             ;
;                SEE http://www.wtfpl.net/ FOR MORE DETAILS.                      ;
;---------------------------------------------------------------------------------;
\*********************************************************************************/

/*********************************************************************************\
;---------------------------------------------------------------------------------;
;                   DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE                   ;
;                           Version 2, December 2004                              ;
;                                                                                 ;
;        Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>                         ;
;                                                                                 ;
;        Everyone is permitted to copy and distribute verbatim or modified        ;
;        copies of this license document, and changing it is allowed as long      ;
;        as the name is changed.                                                  ;
;                                                                                 ;
;                   DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE                   ;
;          TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION        ;
;                                                                                 ;
;         0. You just DO WHAT THE FUCK YOU WANT TO.                               ;
;---------------------------------------------------------------------------------;
\*********************************************************************************/

#include <stdio.h>                        /* C standard library for handling I/O */
#include <errno.h>                /* C standard library for handling error codes */

#define VERSION "v0.0.1"                              /* current program version */
#define MEMORY_SIZE 30000                            /* "infinite tape" constant */
#define SOURCE_SIZE 10000                                /* max source file size */

int memory[MEMORY_SIZE];                             /* available program memory */
char source[SOURCE_SIZE];                                  /* source file buffer */
char *src = source;                                       /* instruction pointer */
int *mem = memory;                                         /* RAM memory pointer */
int loop;                                                /* nested loops counter */

void execute()                             /* brainfuck instructions interpreter */
{
    while(*src)
    {
        //while(*src == ' ' || *src == '\n') *src++;

        switch(*src)
        {
            case '>': *mem++;  break;    // increment memory pointer
            case '<': *mem--;  break;    // decrement memory pointer
            case '+': ++*mem;  break;    // increments memory reference
            case '-': --*mem;  break;    // decrements memory reference
            case '.': putc(*mem, stdout); break;
            case ',': *mem = getc(stdin); break;
                
            case '[':

                if(!*mem)
                {
                    loop = 1;
                    while(loop)
                    {
                        *src++;

                        if(*src == '[') loop++;
                        if(*src == ']') loop--;
                    }
                }

                break;

            case ']':

                loop = 1;
                while(loop)
                {
                    *src--;
                   
                    if(*src == '[') loop--;    //
                    if(*src == ']') loop++;    //
                }

                *src--;
                break;
        }
        
        *src++;
    }
}

int main(int argc,char *argv[])
{
    if(argc == 1)
    {
        printf("\n     Brainfuck interpreter %s by Maksim Korzh\n\n", VERSION);
        printf("  1. Type or paste in brainfuck source code\n");
        printf("  2. Use Ctrl-D for code execution(linux)\n");
        printf("  3. Use ./brainfuck [filename] to execute source file\n");
        printf("\n              Happy brainfucking!\n\n");
        
        fread(source, 1, SOURCE_SIZE - 1, stdin);
        execute();
    }

    else if(argc == 2)
    {
        FILE *file = fopen(argv[1], "r");

        if(errno)
        {
            printf("File '%s' doesn't exist!\n", argv[1]);
            return 0;
        }
        
        fread(source, 1, SOURCE_SIZE, file);
        fclose(file);
        execute();
    }
    
    return 0;
}