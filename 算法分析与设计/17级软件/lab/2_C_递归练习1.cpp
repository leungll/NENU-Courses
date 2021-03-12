#include <bits/stdc++.h>
using namespace std;

int getYear(int n){
    int year;
    if(n == 1){
        year = 10;
    }else{
        year = getYear(n - 1) + 2;
    }
    return year;
}

int main(){
    int n = 5;
    printf("%d", getYear(n));
    return 0;
}
