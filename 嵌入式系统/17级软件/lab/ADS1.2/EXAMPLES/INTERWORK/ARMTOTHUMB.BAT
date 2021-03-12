armcc -c -g -O1 -apcs /interwork armmain.c
tcc   -c -g -O1 -apcs /interwork thumbsub.c
armlink armmain.o thumbsub.o -o armtothumb.axf -info veneers

