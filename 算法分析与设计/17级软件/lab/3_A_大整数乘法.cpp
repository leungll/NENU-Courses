#include <bits/stdc++.h>
using namespace std;

const int maxn = 105;
int a[maxn], b[maxn], c[maxn];
//char a1[maxn], b1[maxn];

int main(){
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    memset(c, 0, sizeof(c));

    int result = 0, t = 1;
//    gets(a1);
//    gets(b1);
    char a1[] = "172";
    char b1[] = "147";
    int la = strlen(a1);
    int lb = strlen(b1);
    for(int i = 0;i < la;i++){
        a[la - i] = a1[i] - 48;
    }
    for(int i = 0;i < lb;i++){
        b[lb - i] = b1[i] - 48;
    }
    for(int i = 1;i <= lb;i++){
        int res = 0;
        for(int j = 1;j <= la;j++){
            t = i + j;
            result = a[j] * b[i] + res + c[t - 1];
            res = result / 10;
            c[t - 1] = result % 10;
        }
        while(res){
            c[t++] = res % 10;
            res /= 10;
        }
    }
    while(c[t] == 0){
        t--;
    }
    for(int i = t;i >= 1;i--){
        printf("%d", c[i]);
    }
    return 0;
}
