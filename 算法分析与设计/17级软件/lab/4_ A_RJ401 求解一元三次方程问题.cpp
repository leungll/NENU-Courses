#include <bits/stdc++.h>
using namespace std;

int main(){
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int cnt = 0;
    double x;
    for(int i = -10000;i <= 10000;i++){
        x = i / 100.0;
        double fx = a * x * x * x + b * x * x + c * x + d;
        if(fx > -0.0001 && fx < 0.0001){
            cnt++;
            if(cnt < 3){
                printf("%0.2f ", x);
            }else{
                printf("%0.2f", x);
            }
        }
    }
    return 0;
}
