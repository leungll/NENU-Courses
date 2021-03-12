#include <stdio.h>

extern void arm_function(void);

int main(void)
{
     printf("Hello from Thumb\n"); 
     arm_function(); 
     printf("And goodbye from Thumb\n"); 
     return (0); 
}
