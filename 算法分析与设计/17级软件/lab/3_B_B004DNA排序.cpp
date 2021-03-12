#include <bits/stdc++.h>
using namespace std;

const int maxn = 1005;

struct po{
    char ch[maxn];
    int s;
}p[maxn];

bool cmp(struct po a, struct po b){
    return a.s < b.s;
}

int main(){
    int n, m;
    cin >> n >> m;
    char ch[maxn][maxn];
    for(int i = 0;i < m;i++){
        cin >> p[i].ch;
    }
    for(int i = 0;i < m;i++){
        int sum = 0;
        for(int j = 0;j < n;j++){
            for(int r = j + 1;r < n;r++){
                if(p[i].ch[j] > p[i].ch[r]){
                    sum++;
                }
            }
        }
        p[i].s = sum;
    }
    sort(p, p + m, cmp);
    for(int i = 0;i < m;i++){
        printf("%s\n", p[i].ch);
    }
}
