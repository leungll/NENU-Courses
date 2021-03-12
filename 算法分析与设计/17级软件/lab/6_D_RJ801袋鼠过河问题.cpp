/*
 * @Description: 
 * @version: 
 * @Author: LL Leung
 * @Date: 2019-12-22 13:59:25
 * @LastEditors: LL Leung
 * @LastEditTime: 2019-12-22 14:08:12
 */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e4 + 1;
const int INF = 0x3f3f3f3f;
#define min(x, y) ( (x) < (y) ? (x) : (y))

int n;
int a[maxn], dp[maxn];

int solve(){
    for(int i = 1;i <= n;i++){
        dp[i] = INF;
    }
    dp[0] = 0;
    for(int i = 1;i <= n;i++){
        for(int j = 0;j < i;j++){
            if(a[j] + j >= i){
                dp[i] = min(dp[i], dp[j] + 1);
            }
        }
    }
    return dp[n] == INF ? -1 : dp[n];
}

int main(){
    while(cin >> n){
        for(int i = 0;i < n;i++){
            cin >> a[i];
        }
        cout << solve() << endl;
    }
    return 0;
}
