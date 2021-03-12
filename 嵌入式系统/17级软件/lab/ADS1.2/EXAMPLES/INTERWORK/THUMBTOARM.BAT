tcc   -c -g -O1 -apcs /interwork thumbmain.c
armcc -c -g -O1 -apcs /interwork armsub.c
armlink thumbmain.o armsub.o -o thumbtoarm.axf -info veneers

