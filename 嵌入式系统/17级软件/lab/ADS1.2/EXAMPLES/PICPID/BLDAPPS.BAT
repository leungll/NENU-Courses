echo off
if "%1%" == "-16" goto Thumb
set CC=armcc
goto DoIt
:Thumb
set CC=tcc

:DoIt
echo "Note: The linker warnings: "Image does not have an entry point" may be safely ignored in this example."
%CC% -c -g -O1 nullapp.c
armlink -o nullapp.axf nullapp.o
fromelf nullapp.axf -bin -o nullapp.bin
echo "Built nullapp.bin"

echo "Building the application header and veneers..."
armasm %1 -g -apcs /ropi apphdr.s
armasm %1 -g -apcs /ropi kveneer.s

%CC% -c -g -O1 -apcs /ropi/rwpi app1.c
armlink -o app1.axf -ropi -rwpi -rw-base 0 -map -symbols -list app1.map kernel.sym kveneer.o app1.o apphdr.o
fromelf app1.axf -bin -o app1.bin
echo "Built app1.bin"

%CC% -c -g -O1 -apcs /ropi/rwpi app2.c
armlink -o app2.axf -ropi -rwpi -rw-base 0 -map -symbols -list app2.map kernel.sym kveneer.o app2.o apphdr.o
fromelf app2.axf -bin -o app2.bin
echo "Built app2.bin"

