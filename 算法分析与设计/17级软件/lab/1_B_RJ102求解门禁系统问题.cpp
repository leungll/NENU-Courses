#include <bits/stdc++.h>
using namespace std;

map<int, int> mp;
int main(){
    int n;
    cin >> n;
    for(int i = 0;i < n;i++){
        int x;
        cin >> x;
        if( mp.find(x) != mp.end() ){
            mp[x]++;
            if(i == 0){
                printf("%d", mp[x]);
            }else{
                printf(" %d", mp[x]);
            }
        }else{
            mp[x] = 1;
            if(i == 0){
                printf("1");
            }else{
                printf(" 1");
            }
        }
    }
    return 0;
}