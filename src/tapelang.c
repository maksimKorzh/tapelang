/*********************************************************************************\
;---------------------------------------------------------------------------------;
;                                                                                 ;
;                                  Tapelang v0.0.3                                ;
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

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>

#define VERSION "v0.0.3"
#define MEMORY_SIZE 65536
#define SOURCE_SIZE 25600

char memory[MEMORY_SIZE];
char source[SOURCE_SIZE];

char *src = source;
char *mem = memory;
int loop;

int src_flag;
char *source_ptr;

void execute()
{
    while(*src)
    {
        switch(*src)
        {
            case '!':   // execute brainfuck source from memory
            {
                if(!src_flag)
                {
                    source_ptr = src;
                    src = mem;
                    //printw("\nwe are now in memory at '%s'\n", mem);
                }

                else
                {
                    src = source_ptr;
                    //printw("we are now at source at '%s'", src);
                }

                src_flag ^= 1;
                break;
            }

            case '&':   // escape character
                *src++;
                break;

            case '?':   // print debug info
                printw("\n cell #%d: %d\n", mem - memory, *mem);
                //refresh();
                break;

            case '$':   // set current cell to ascii value of next char
                *src++;

                while((*src >= 'a' && *src <= 'z') || (*src >= 'A' && *src <= 'Z') || *src == ' ' || *src == '&')
                {
                    if(*src == '&') *src++;

                    if((mem - memory + 1) > 65535)
                    {
                        printw("\n ERROR: string is out of bounds!\n");
                        break;
                    }

                    *mem++ = *src++;
                }

                break;

            case '#':   // set current cell id to value of following integer
            {
                *src++;

                if(*src == '@')
                {
                    mem = memory + *mem;
                    break;
                }

                int num = atoi(src);

                if(num < 0 || num > 65535)
                {
                    printw("\n ERROR: cell #%d is out of ID bounds!", num);
                    printw("\n        cell #id bounds are from '0' to '65535'\n");
                    break;
                }

                mem = memory + num;
                break;
            }

            case '@':   // set constant value to current cell
                *src++;

                if(*src == '#')
                {
                    *mem = mem - memory;
                    break;
                }

                int num = atoi(src);

                if(num < -128 || num > 127)
                {
                    printw("\n ERROR: cell #%d value '%d' is out of value bounds!", mem - memory, num);
                    printw("\n        cell value bounds are from '-128' to '127'\n");
                    break;
                }

                *mem = num;
                break;

            case '%':   // print string at given cell
                printw("%s", mem);
                break;

            case ';': // store user input string at given cell
                echo();
                getstr(mem);
                noecho();
                break;

            case '/':   // write to file "out.txt"
            {
                FILE *out = fopen("out.txt" , "w");
                fwrite(mem, 1, strlen(mem),out);
                fclose(out);
                break;
            }

            case '\\':    // read from file "out.txt"
            {
                FILE *in = fopen("out.txt", "r");

                if(in == NULL)
                {
                    printw("\n ERROR: couldn't open file 'out.txt', no such file!\n");
                    break;
                }

                fread(mem + 1, 1, SOURCE_SIZE, in);
                fclose(in);
            }

            case '*':
            {
                *src++;
                int num = atoi(src);

                if((*mem * num) < -128 || (*mem * num) > 127)
                {
                    printw("\n ERROR: cell #%d value '%d' is out of value bounds!", mem - memory, *mem * num);
                    printw("\n        cell value bounds are from '-128' to '127'\n");
                    break;
                }

                *mem *= num;
                break;
            }

            case ':':
            {
                *src++;
                int num = atoi(src);

                if(num == (int)NULL)
                {
                    printw("\n FATAL ERROR: zero division!\n");
                    break;
                }

                *mem /= num;
                break;
            }

            case '{':
            {
                *src++;
                int num = atoi(src);

                if(*mem != num)
                {
                    loop = 1;
                    while(loop)
                    {
                        *src++;

                        if(*src == '{') loop++;
                        if(*src == '}') loop--;
                    }
                }

                break;
            }

            case '=':
            {
                *src++;

                if(*src == '#') *src++;
                else break;

                int num = atoi(src);

                if(num < 0 || num > 65535)
                {
                    printw("\n ERROR: cell #%d is out of ID bounds!", num);
                    printw("\n        cell #id bounds are from '0' to '65535'\n");
                    break;
                }

                *mem = *(memory + num);
                break;
            }

            case '>':
            {
                if(isdigit(*(src + 1)))
                {
                    *src++;
                    int num = atoi(src);

                    if(((mem - memory) + num) > 65535)
                    {
                        printw("\n ERROR: cell #%d is out of value bounds!", mem - memory + num);
                        printw("\n        cell #ID bounds are from '0' to '65535'\n");
                        break;
                    }

                    mem += num;
                    break;
                }

                else
                {
                    if((mem - memory) == 65535)
                    {
                        printw("\n WARNING: cell #%d is out of right bound!", mem - memory + 1);
                        mem = memory - 1;
                        printw("\n          setting cell #id to '%d'\n", mem - memory + 1);
                    }

                    *mem++;
                    break;
                }
            }

            case '<':
            {
                if(isdigit(*(src + 1)))
                {
                    *src++;
                    int num = atoi(src);

                    if(((mem - memory) - num) < 0)
                    {
                        printw("\n ERROR: cell #%d is out of value bounds!", mem - memory - num);
                        printw("\n        cell #ID bounds are from '0' to '65535'\n");
                        break;
                    }

                    mem -= num;
                    break;
                }

                else
                {
                    if(!(mem - memory))
                    {
                        printw("\n WARNING: cell #%d is out of left bound!", mem - memory - 1);
                        mem = memory + MEMORY_SIZE;
                        printw("\n          setting cell #id to '%d'\n", mem - memory - 1);
                    }

                    *mem--;
                    break;
                }
            }
            case '+':
            {
                if(isdigit(*(src + 1)))
                {
                    *src++;
                    int num = atoi(src);

                    if((*mem + num) < -128 || (*mem + num) > 127)
                    {
                        printw("\n ERROR: cell #%d value '%d' is out of value bounds!", mem - memory, *mem + num);
                        printw("\n        cell value bounds are from '-128' to '127'\n");
                        break;
                    }

                    *mem += num;
                    break;
                }

                else if(*(src + 1) == '#')
                {
                    src += 2;
                    int num = atoi(src);

                    if((*mem + num) < -128 || (*mem + num) > 127)
                    {
                        printw("\n ERROR: cell #%d value '%d' is out of value bounds!", mem - memory, *mem + num);
                        printw("\n        cell value bounds are from '-128' to '127'\n");
                        break;
                    }

                    *mem += *(memory + num);
                    break;

                }

                else
                {
                    if(*mem == 127)
                    {
                        printw("\n WARNING: cell #%d: value '%d' is out of positive bound!", mem - memory, *mem + 1);
                        *mem = -128;
                        printw("\n          setting cell #%d value to '%d'\n", mem - memory, *mem);
                        break;
                    }

                    ++*mem;
                    break;
                }
            }

            case '-':
            {
                if(isdigit(*(src + 1)))
                {
                    *src++;
                    int num = atoi(src);

                    if((*mem - num) < -128 || (*mem - num) > 127)
                    {
                        printw("\n ERROR: cell #%d value '%d' is out of value bounds!", mem - memory, *mem - num);
                        printw("\n        cell value bounds are from '-128' to '127'\n");
                        break;
                    }

                    *mem -= num;
                    break;
                }

                else if(*(src + 1) == '#')
                {
                    src += 2;
                    int num = atoi(src);

                    if((*mem + num) < -128 || (*mem + num) > 127)
                    {
                        printw("\n ERROR: cell #%d value '%d' is out of value bounds!", mem - memory, *mem + num);
                        printw("\n        cell value bounds are from '-128' to '127'\n");
                        break;
                    }

                    *mem -= *(memory + num);
                    break;

                }


                else
                {
                    if(*mem == -128)
                    {
                        printw("\n WARNING: cell #%d: value '%d' is out of negative bound!", mem - memory, *mem - 1);
                        *mem = 127;
                        printw("\n          setting cell #%d value to '%d'\n", mem - memory, *mem);
                        break;
                    }

                    --*mem;
                    break;
                }
            }

            case '.':
                if(*(src + 1) == '%')
                {
                    *src++;
                    printw("%d", *mem);
                    break;
                }

                addch(*mem);
                break;
            case ',': *mem = getch(); break;

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

        refresh();
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
            printf("\n   ERROR: file '%s' doesn't exist!\n\n", argv[1]);
            return 0;
        }

        fread(source, 1, SOURCE_SIZE, file);
        fclose(file);
        initscr();
        scrollok(stdscr,TRUE);
        noecho();
        execute();
    }

    addstr("\n\n Press any key to exit...\n");
    getch();
    endwin();
    return 0;
}
