This directory contains files to perform initialization for cached cores.

The core-specific files, for example 940T.s, contain code to perform 
initialization required to enable the caches for the core. 

The operation of the caches are controlled though either a Memory Protection 
Unit (MPU) or a Memory Management Unit (MMU) - a description of the target 
memory is applied to the MPU/MMU, and in these examples the target memory map 
is that of the ARM Integrator board.

Please note that the example code to initialize MMUs is intentionally simplistic.

In addition to the cache initialization code, the file CMclocks.s can be used 
to set the core and bus clock frequency of an Integrator Core Module. 

Please note that no checks are made to ensure sensible values are chosen.

The functions provided are:
 Clock_Speed (in CMclocks.s)
 Cache_Init  (in the core-specific files e.g. 940T.s).


To call these functions from your assembler application add the lines:

    IMPORT Clock_Speed
    IMPORT Cache_Init

    BL Clock_Speed
    BL Cache_Init


To call these functions from your C application add the lines:

    extern void Clock_Speed(void);
    extern void Cache_Init(void);

    Clock_Speed();
    Cache_Init();


