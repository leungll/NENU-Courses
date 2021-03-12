/*
 * @Description: 
 * @version: 
 * @Author: LL Leung
 * @Date: 2019-12-22 14:16:20
 * @LastEditors  : LL Leung
 * @LastEditTime : 2019-12-22 14:21:21
 */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000;

int main(){
    char str[19];
    scanf("%s", str);
    string k(str);
    int n;
    scanf("%d", &n);

    vector<vector<long long>> dp(2, vector<long long>(maxn, 0));
    int flag = 0;
    dp[flag][0] = 1;

    for (int i = 0; i < k.size(); i++){
        for (int j = 0; j < n; j++){
            if (k[i] != 'X'){
                dp[!flag][(j * 10 + k[i] - '0') % n] += dp[flag][j];
            }
            else{
                for (int d = 0; d <= 9; d++){
                    dp[!flag][(j * 10 + d) % n] += dp[flag][j];
                }
            }
        }
        fill(dp[flag].begin(), dp[flag].end(), 0);
        flag = !flag;
    }
    printf("%lld\n", dp[flag][0]);
    // system("pause");
    return 0;
}