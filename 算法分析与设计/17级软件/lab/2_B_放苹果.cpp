#include <bits/stdc++.h>
using namespace std;

int apple(int m, int n){
    if(m == 0 || n == 1){
        return 1;
    }
    if(n > m){
        return apple(m, m);
    }else{
        return apple(m - n, n) + apple(m, n - 1);
    }
}

int main(){
    int n = 0, x, y;
    cin >> n;
    while(n--){
        cin >> x >> y;
        printf("%d\n", apple(x, y));
    }
    return 0;
}
