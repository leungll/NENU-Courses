#include <stdio.h>

extern void thumb_function(void);

int main(void)
{
     printf("Hello from ARM\n"); 
     thumb_function(); 
     printf("And goodbye from ARM\n"); 
     return (0); 
}
