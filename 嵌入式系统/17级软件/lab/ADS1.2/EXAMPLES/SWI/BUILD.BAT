armasm -g ahandle.s
armcc -c -g -O1 main.c
armcc -c -g -O1 chandle.c
armlink ahandle.o main.o chandle.o -o swi.axf

