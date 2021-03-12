Rem echo off
echo Compiling the kernel...
if "%1" == "-16" goto ThumbCompile
armcc -c -g -O1 kernel.c
goto Link
:ThumbCompile
tcc -c -g -O1 kernel.c

:Link
armlink -o kernel.axf -ro-base 0x8000 -rw-base 0x40000 kernel.o -symdefs kernel.sym -map -symbols -list kernel.map

:makebin
fromelf kernel.axf -bin -o kernel.bin
echo "Made kernel.bin"
