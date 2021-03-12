/* Example 4-4 */

long long smull(int x, int y)
{
    return (long long) x * (long long) y;
}

/* Example 5-5 */

long long smull(int x, int y)
{
    long long res;
    __asm { SMULL ((int*)&res)[0], ((int*)&res)[1], x, y }
    return res;
}


