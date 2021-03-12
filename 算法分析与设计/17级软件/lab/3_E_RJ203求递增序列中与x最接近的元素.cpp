#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e8 + 5;
int arr[maxn];

int main(){
    int n, m;
    cin >> n;
    for(int i = 0;i < n;i++){
        cin >> arr[i];
    }
    cin >> m;
    for(int i = 0; i < m; i++) {
        int k;
        cin >> k;
        int low = 0, high = n - 1;
        while(high - low > 1){
            int mid = (low +high) >> 1;
            if(arr[mid] > k){
                high = mid;
            }else{
                low = mid;
            }
        }
        int ans = abs(arr[low] - k) > abs(arr[high] - k) ? high : low;
        printf("%d\n", arr[ans]);
    }
    return 0;
}
