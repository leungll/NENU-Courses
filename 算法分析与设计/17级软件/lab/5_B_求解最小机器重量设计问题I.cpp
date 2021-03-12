#include <bits/stdc++.h>
using namespace std;

const int maxn = 105;
const int INF = 1e6;
int cost_money[maxn][maxn], weight[maxn][maxn], seller[maxn], seller_temp[maxn];
int n, m, cost, min_weight = INF, c = 0, w = 0;

void dfs(int i){
    if(i > n){
        if(w < min_weight){
            min_weight = w;
            for(int j = 1;j <= n;j++){
                seller[j] = seller_temp[j];
            }
        }
    }else{
        for(int j = 1;j <= m;j++){
            if(c + cost_money[i][j] <= cost && w + weight[i][j] < min_weight){
                seller_temp[i] = j;
                c += cost_money[i][j];
                w += weight[i][j];
                dfs(i + 1);
                c -= cost_money[i][j];
                w -= weight[i][j];
            }
        }
    }
}

int main(){
    cin >> n >> m >> cost;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            cin >> weight[i][j];
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            cin >> cost_money[i][j];
        }
    }
    dfs(1);
    for(int i = 1;i < n;i++){
        printf("%d ", seller[i]);
    }
    printf("%d\n", seller[n]);
    printf("%d\n", min_weight);
    return 0;
}