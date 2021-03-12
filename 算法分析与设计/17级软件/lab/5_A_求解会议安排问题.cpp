#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e4 + 5;
int n, ans = 0, tmp = 0, cnt;

struct room{
    int start;
    int end;
};

void dfs(room arr[], int i){
    cnt = 0;
    for (int j = 1; j <= n; j++){
        if (arr[j].start >= arr[i].end){
            int t = arr[j].end - arr[j].start;
            tmp += t;
            dfs(arr, j);
            tmp -= t;
            cnt++;
        }
    }
    if (cnt == 0){
        if (tmp > ans){
            ans = tmp;
        }
    }
}

int main(){
    while (cin >> n){
        room arr[maxn];
        arr[0].end = 0;
        for (int i = 1; i <= n; i++){
            cin >> arr[i].start >> arr[i].end;
        }
        dfs(arr, 0);
        cout << ans << endl;
    }
    return 0;
}