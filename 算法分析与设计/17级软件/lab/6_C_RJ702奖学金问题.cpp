#include <bits/stdc++.h>
using namespace std;

const int maxn = 201;
#define min(x, y) ( (x) < (y) ? (x) : (y))

int n;
struct NodeType{
    int a, b;
    bool operator < (const NodeType &s){
        return b < s.b;
    }
};

NodeType A[maxn];
double avg;
int r, effort = 0;

void solve(){
    int Sums = (int)n * avg, sum = 0;
    for(int i = 0;i < n;i++){
        sum += A[i].a;
    }
    sort(A, A + n);
    for(int j = 0;j < n;j++){
        if(sum >= Sums){
            break;
        }
        effort += A[j].b * min(Sums - sum, r - A[j].a);
        sum += min(Sums - sum, r - A[j].a);
    }
}

int main(){
    while(1){
        cin >> n;
        if(n == 0){
            break;
        }
        for(int i = 0;i < n;i++){
            cin >> A[i].a >> A[i].b;
        }
        cin >> r >> avg;
        solve();
        cout << effort << endl;
    }
    // system("pause");
    return 0;
}