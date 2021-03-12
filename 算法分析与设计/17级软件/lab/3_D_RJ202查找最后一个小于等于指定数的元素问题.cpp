#include <bits/stdc++.h>
using namespace std;

const int maxn = 1005;
int arr[maxn];

int main(){
    int n, m;
    cin >> n >> m;
    for(int i = 0;i < n;i++){
        cin >> arr[i];
    }
    for(int i = 0; i < m; i++) {
        int x, flag = 0;
        cin >> x;
        for(int j = 0; j < n; j++) {
            if(flag == 0) {
                if(arr[j] > x) {
                    cout << arr[j - 1] << endl;
                    flag = 1;
                }
            }
        }
    }
    return 0;
}
