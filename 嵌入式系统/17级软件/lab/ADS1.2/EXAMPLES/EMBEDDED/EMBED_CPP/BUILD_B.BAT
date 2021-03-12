armasm -g vectors.s
armasm -g init.s
armasm -g stack.s
armasm -g heap.s
armcpp -c -g -O1 tri.cpp
REM Use the following two lines to build without the serial port. 
armcpp -c -g -O1 triangle.cpp -DEMBEDDED
armcc -c -g -O1 retarget.c
REM Use the following two lines to build using the serial port. 
REM armcpp -c -g -O1 triangle.cpp -DEMBEDDED -DUSE_SERIAL_PORT
REM armcc -c -g -O1 retarget.c -DUSE_SERIAL_PORT
armcc -c -g -O1 uart.c -I..\include
armcc -c -g -O1 serial.c -I..\include
armlink vectors.o init.o tri.o triangle.o retarget.o uart.o serial.o stack.o heap.o -scatter scat_b.scf -o embed.axf -entry 0x0 -info totals -info unused
fromelf embed.axf -bin -o embed.bin
fromelf embed.axf -m32 -o embed.m32

