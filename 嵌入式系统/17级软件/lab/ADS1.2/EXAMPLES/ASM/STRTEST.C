#include <stdio.h>

extern void strcopy(char *d, const char *s);

int main()
{       const char *srcstr = "First string - source";
        char dststr[] = "Second string - destination";
        /* dststr is an array since we're going to change it */
 
        printf("Before copying:\n");
        printf("  '%s'\n  '%s'\n",srcstr,dststr);
        strcopy(dststr,srcstr);
        printf("After copying:\n");
        printf("  '%s'\n  '%s'\n",srcstr,dststr);
        return 0;
}
