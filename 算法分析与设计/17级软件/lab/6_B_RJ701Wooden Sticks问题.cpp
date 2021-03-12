#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e4 + 10;

int t, n;

struct NodeType{
    int l, w;
    friend bool operator < (NodeType a, NodeType b){
        if(a.l != b.l){
            return a.l < b.l;
        }
        return a.w < b.w;
    }
}s[maxn];

int ans;
bool flag[maxn];

void solve(){
    sort(s + 1,s + n + 1);
    memset(flag, 0, sizeof(flag));
    ans = 0;
    for(int j = 1;j <= n;j++){
        if (!flag[j]){
            flag[j] = true;
            int preend = j;
            for(int i = preend + 1;i <= n;i++){
                if(s[i].w >= s[preend].w && !flag[i]){
                    preend = i;
                    flag[i] = true;
                }
            }
            ans++;
        }
    }
}

int main(){
    cin >> t;
    while(t--){
        cin >> n;
        for(int i = 1;i <= n;i++){
            cin >> s[i].l >> s[i].w;
        }
        solve();
        cout << ans << endl;
    }

    // system("pause");
    return 0;
}
