#include <bits/stdc++.h>
using namespace std;

const int maxn = 100;
int a[maxn], b[maxn];

int main() {
    int t;
    while(scanf("%d", &t) != EOF && t){
        a[0] = 1, b[0] = 0;
        for(int i = 1; i <= t; i++) {
            a[i] = b[i - 1];
            b[i] = 3 * a[i - 1] + 2 * b[i - 1];
        }
        printf("%d %d\n", a[t], b[t]);
    }
    return 0;
}   
