armasm -g vectors.s
armasm -g stack.s
armasm -g -PD "ROM_RAM_REMAP SETL {TRUE}" init.s
armasm -g heap.s
armcc -c -g -O1 main.c -I..\include
armcc -c -g -O1 int_handler.c -I..\include
armcc -c -g -O1 retarget.c
armlink vectors.o init.o main.o int_handler.o retarget.o stack.o heap.o -scatter scat.scf -o ledflash.axf -entry 0x24000000 -info totals -info unused
fromelf ledflash.axf -bin -o ledflash.bin
fromelf ledflash.axf -m32 -o ledflash.m32

