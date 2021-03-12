/* Explanation of byte-reversing in ARM assembler

This program uses ANSI control codes, so should work on most terminal types 
under UNIX.  For a PC, you will need an ANSI driver installed, e.g. ANSI.SYS.
On HP-UX, use an XTERM terminal emulator (not HPTERM).
*/

#include <stdio.h>

static void cls(void)
{
  printf("\033[2J");
}

static void up(int n)
{
  while (n > 0)
  { printf("\033[1A");  --n;
  }
}

static void pause(void)
{
  fprintf(stderr, "Please press <Return> to proceed ");
  while( fgetc(stdin) != '\n' );
}

static void prologue(void)
{
    printf("\
        AMAZING FACTS ABOUT THE ARM - Reversing the bytes in a word\n\
\n\
This function reverses the bytes in a word. The method was discovered in\n\
1986 following a competition between ARM programmers; it requires just 4\n\
instructions and 1 work register. A method using only 3 instructions per\n\
word reversed was also found, but it has some set-up overhead and uses a\n\
2nd register. Can you re-discover this method?\n\
\n\
Later, the C compiler was 'taught' to generate exactly the instructions\n\
needed, from C source. Check this claim using armcc -S -DREV byterev.c\n\
and examining the assembly code file produced.\n\
\n\
unsigned long reverse(unsigned long v)\n\
{   unsigned long t;\n\
    t = v ^ ((v << 16) | (v >> 16));   /*  EOR r1,r0,r0,ROR #16  */\n\
    t &= ~0xff0000;                    /*  BIC r1,r1,#&ff0000    */\n\
    v = (v << 24) | (v >> 8);          /*  MOV r0,r0,ROR #8      */\n\
    return v ^ (t >> 8);               /*  EOR r0,r0,r1,LSR #8   */\n\
}\n\
\n\
To see the method in action, press <Return>. Each time you press <Return>\n\
one step of the reversal process will be executed. The values displayed\n\
are symbolic, starting with the input word D C B A.\n\
\n");
}

static void prelude(void)
{
    printf("\
        AMAZING FACTS ABOUT THE ARM - Reversing the bytes in a word\n\
\n\
unsigned long reverse(unsigned long v)\n\
{   unsigned long t;\n\
    t = v ^ ((v << 16) | (v >> 16));   /*  EOR r1,r0,r0,ROR #16  */\n\
    t &= ~0xff0000;                    /*  BIC r1,r1,#&ff0000    */\n\
    v = (v << 24) | (v >> 8);          /*  MOV r0,r0,ROR #8      */\n\
    return v ^ (t >> 8);               /*  EOR r0,r0,r1,LSR #8   */\n\
}\n\
\n");
}

static void show_state_1(void)
{
    printf("\
        v / r0                 t / r1         original input in v/r0\n\
\n\
  +---+---+---+---+      +---+---+---+---+\n\
  | D | C | B | A |      | x | x | x | x |\n\
  +---+---+---+---+      +---+---+---+---+\n\
\n\n\n\n\n\n\n");
}

static void show_state_2(void)
{
    printf("\
        v / r0                 t / r1         state after executing \n\
\n\
  +---+---+---+---+      +---+---+---+---+    t = v ^ ((v<<16) | (v>>16));\n\
  | D | C | B | A |      |D^B|C^A|B^D|A^C|\n\
  +---+---+---+---+      +---+---+---+---+    EOR r1,r0,r0,ROR #16\n\
\n\n\n\n\n\n\n");
}

static void show_state_3(void)
{
    printf("\
  +---+---+---+---+      +---+---+---+---+    t &= ~0xff0000;             \n\
  | D | C | B | A |      |D^B| 0 |B^D|A^C|\n\
  +---+---+---+---+      +---+---+---+---+    BIC r1,r1,#&ff0000  \n\
\n\n\n\n\n\n\n");
}

static void show_state_4(void)
{
    printf("\
  +---+---+---+---+      +---+---+---+---+    v = (v << 24) | (v >> 8);\n\
  | A | D | C | B |      |D^B| 0 |B^D|A^C|\n\
  +---+---+---+---+      +---+---+---+---+    MOV r0,r0,ROR #8  \n\
\n\n\n\n\n\n\n");
}

static void show_state_5(void)
{
    printf("\
  +---+---+---+---+      +---+---+---+---+    v = v ^ (t >> 8);        \n\
\n\
  +---+-^-+-^-+-^-+---+  +---+---+---+---+    EOR r0,r0,r1,LSR #8\n\
      |D^B| 0 |B^D|A^C|\n\
      +---+---+---+---+\n\
\n\
  +---+---+---+---+\n\
  | A | B | C | D |      (original input was: D C B A)\n\
  +---+---+---+---+\n\
\n");
}

int main()
{
    cls();
    prologue();
    pause();
    cls();
    prelude();
    show_state_1();
    pause();
    up(13);
    show_state_2();
    pause();
    up(11);
    show_state_3();
    pause();
    up(11);
    show_state_4();
    pause();
    up(11);
    show_state_5();
    pause();
    fputc('\n', stdout);
    return( 0 );
}

