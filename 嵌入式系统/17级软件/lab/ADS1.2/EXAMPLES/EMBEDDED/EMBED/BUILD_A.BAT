armcc -c -g -O1 main.c
armlink main.o -o embed.axf -info totals

