#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    for(int i = 0;i < n;i++){
        int a, b, cnt = 0;
        cin >> a >> b;
        for(int j = a;j <= b;j++){
            int sum = 0;
            for(int r = 1;r < j;r++){
                if(j % r == 0){
                    sum += r;
                }
            }
            if(sum == j){
                cnt++;
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}
