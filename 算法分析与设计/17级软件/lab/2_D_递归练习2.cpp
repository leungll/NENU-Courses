#include <bits/stdc++.h>
using namespace std;

int zuheshu(int m, int n){
    if(m < 0 || n < 0|| m < n){
        return 0;
    }
    if(m == n){
        return 1;
    }else{
        return zuheshu(m - 1, n) + zuheshu(m - 1, n - 1);
    }
}

int main(){
    int num = 0, x, y;
    cin >> num;
    while(num--){
        cin >> x >> y;
        printf("%d\n", zuheshu(x, y));
    }
    return 0;
}
