/*
 * newtst.cpp: Test code for new and delete.
 * Uses only the C library and the "new.h" functions from the cpplib.
 */

#include <stdio.h>
#include "new"

class A {
    static int nextidx;
  public:
    A() {printf("Constructed A #%d at %p\n", idx = ++nextidx, this);};
    ~A(){printf("Destroyed A #%d at %p\n", idx, this);};
    int idx;
};

int A::nextidx = 0;

int main()
{   A *a[5];
    int j;

    for (j = 0;  j < sizeof(a)/sizeof(A*);  ++j)
        a[j] = new A;

    for (j = sizeof(a)/sizeof(A*);  j > 0;  )
        --j, delete a[j];
    return 0;
}

