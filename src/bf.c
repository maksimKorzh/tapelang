/*********************************************************************************\
;---------------------------------------------------------------------------------;
;                                                                                 ;
;                                Brainfuck v0.0.1                                 ;
;                                                                                 ;
;---------------------------------------------------------------------------------;
;---------------------------------------------------------------------------------;
;                                                                                 ;
;                    Brainfuck programming language interpreter                   ;
;                                                                                 ;
;---------------------------------------------------------------------------------;
;---------------------------------------------------------------------------------;
;                                                                                 ;
;                                by Maksim Korzh                                  ;
;                                                                                 ;
;---------------------------------------------------------------------------------;
;*********************************************************************************;
;---------------------------------------------------------------------------------;
;                                                                                 ;
;       THIS PROGRAM IS FREE SOFTWARE. IT COMES WITHOUT ANY WARRANTY, TO          ;
;        THE EXTENT PERMITTED BY APPLICABLE LAW. YOU CAN REDISTRIBUTE IT          ;
;       AND/OR MODIFY IT UNDER THE TERMS OF THE DO WHAT THE FUCK YOU WANT         ;
;          TO PUBLIC LICENCE, VERSION 2, AS PUBLISHED BY SAM HOCEVAR.             ;
;                SEE http://www.wtfpl.net/ FOR MORE DETAILS.                      ;
;                                                                                 ;
;---------------------------------------------------------------------------------;
;*********************************************************************************;
;---------------------------------------------------------------------------------;
;                                                                                 ;
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
;                                                                                 ;
;---------------------------------------------------------------------------------;
;---------------------------------------------------------------------------------;
;            please let me know if you find this code/project useful              ;
;---------------------------------------------------------------------------------;
;*********************************************************************************;
;---------------------------------------------------------------------------------;
;                                                                                 ;
;         Copyright © 2019  Maksim Korzh  <freesoft.for.people@gmail.com>         ;
;                                                                                 ;
;---------------------------------------------------------------------------------;
\*********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define VERSION "v0.0.2"
#define MEMORY_SIZE 65536
#define SOURCE_SIZE 25600

char memory[MEMORY_SIZE];
char source[SOURCE_SIZE];
char *src = source;
char *mem = memory;
int loop;

void execute()
{
    while(*src)
    {
        switch(*src)
        {
            case '#':
                printf("\n cell #%d: %d\n", mem - memory, *mem);
                break;
        
            case '>':

                if((mem - memory) == 65535)
                {
                    printf("\n WARNING: cell #%d is out of right bound!", mem - memory + 1);
                    mem = memory - 1;
                    printf("\n          setting cell #id to '%d'\n", mem - memory + 1);
                }

                *mem++;
                break;

            case '<':

                if(!(mem - memory))
                {
                    printf("\n WARNING: cell #%d is out of left bound!", mem - memory - 1);
                    mem = memory + MEMORY_SIZE;
                    printf("\n          setting cell #id to '%d'\n", mem - memory - 1);
                }
                
                *mem--;
                break;

            case '+':

                if(*mem == 127)
                {
                    printf("\n WARNING: cell #%d: value '%d' is out of positive bound!", mem - memory, *mem + 1);
                    *mem = -128;
                    printf("\n          setting cell #%d value to '%d'\n", mem - memory, *mem);
                    break;
                }

                ++*mem;
                break;
                
            case '-':

                if(*mem == -128)
                {
                    printf("\n WARNING: cell #%d: value '%d' is out of negative bound!", mem - memory, *mem - 1);
                    *mem = 127;
                    printf("\n          setting cell #%d value to '%d'\n", mem - memory, *mem);
                    break;
                }

                --*mem;
                break;
                
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
                   
                    if(*src == '[') loop--;
                    if(*src == ']') loop++;
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
        printf("\n   FATAL ERROR: no input file!\n USAGE EXAMPLE: bf filename.bf\n\n");
        exit(1);
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
