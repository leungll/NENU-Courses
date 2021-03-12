                            MMUgen readme.txt
                            =================

MMUgen Release 1.0, 20th Sept 2000
==================================

MMUgen is a utility designed to generate MMU pagetable data from a text file
describing the virtual to physical address translation required. This text file
is known as a rules file, example of which are provided. 


Conditions of Use
-----------------

MMUgen has been adapted by ARM from an original design developed by Peter
Maloy of CodeSprite, www.codesprite.com

No support will be provided by ARM relating to the use of this product.


Files 
-----

mmugen.c                -MMUgen source code
MMUgen.pdf              -User Guide
readme.txt              -This file
Example(n).rules        -Various example rules files for MMUgen


Using MMUgen with ARM tools
---------------------------

An image file can be built from the command line using ARM tools as follows: 

armcc mmugen.c -o mmugen.axf

The code can then be executed from the command line under ARMulator as follows: 

armsd -exec mmugen.axf rulesfile outputfile

where rulesfile is an MMUgen text rules file, and outputfile is binary file containing 
level1 and (optionally) level2 page table data.


MMUgen: known limitations
-------------------------

MMUgen cannot currently be used to build fine level2 page tables.

MMUgen cannot be used to generate level2 pagetables with different sub page access 
permissions.

Domains are alway set to 0.

MMUgen does not report all errors and/or ommisions contained in rulesfiles, this
can result in incorrect pagetables being generated.


 