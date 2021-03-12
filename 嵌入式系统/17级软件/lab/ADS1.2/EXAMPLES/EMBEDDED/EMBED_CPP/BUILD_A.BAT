armcpp -c -g -O1 triangle.cpp
armcpp -c -g -O1 tri.cpp
armlink tri.o triangle.o -o embed.axf -info totals

