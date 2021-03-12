#include <bits/stdc++.h>
using namespace std;

int chushu(int m, int n){
    int u = m, v = n;
    int r = u % v;
    if(r == 0){
        return v;
    }else{
        chushu(v, r);
    }
}

int main(){
    int num = 0, x, y;
    cin >> num;
    while(num--){
        cin >> x >> y;
        printf("%d\n", chushu(x, y));
    }
    return 0;
}
