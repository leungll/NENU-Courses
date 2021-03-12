#include <bits/stdc++.h>
using namespace std;

const int maxn = 50;
int arr[maxn];

int main()
{
    int n, c;
    int cont = 0;
    cin >> n >> c;
    for(int i = 0;i < n;i++){
        cin >> arr[i];
    }
    for(int i = 0;i < n;i++){
        for(int j = i;j < n;j++){
            if(arr[i] - arr[j] == c || arr[i] - arr[j] == -c) {
                cont++;
            }
        }
    }
    cout << cont;
    return 0;
}

