#include <bits/stdc++.h>
using namespace std;

const int maxn = 55;
int fishSize[maxn];

int main() {
    int n, minSize, maxSize;
    while(cin >> minSize >> maxSize >> n) {
        int cnt = 0;
        for(int i = 0; i < n; i++) {
            cin >> fishSize[i];
        }
        for(int i = minSize; i <= maxSize; i++) {
            bool flag = true;
            for(int j = 0; j < n; j++) {
                if( (i >= fishSize[j] * 2 && i <= fishSize[j] * 10) || (fishSize[j] >= i * 2 && fishSize[j] <= i * 10) ) {
                    flag = false;
                    break;
                }
            }
            if(flag) {
                cnt++;
            }
        }
        printf("%d\n", cnt);
        memset(fishSize, 0, sizeof(fishSize));
    }
    return 0;
}
