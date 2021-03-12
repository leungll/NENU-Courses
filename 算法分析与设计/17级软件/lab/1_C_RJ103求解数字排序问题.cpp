#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;
const int maxn = 1004;

map<int, int> mp;
vector<PII> vec;

bool cmp(const PII &p1, const PII &p2){
    return p1.second > p2.second;
}

int main(){
    int n;
    cin >> n;
    while(n--){
        int x;
        cin >> x;
        if( mp.find(x) != mp.end() ){
            mp[x]++;
        }else{
            mp[x] = 1;
        }
    }
    map<int, int>:: iterator itor1 = mp.begin();
    for(;itor1 != mp.end();itor1++){
        vec.push_back( make_pair(itor1 -> first, itor1 -> second) );
    }
    sort(vec.begin(), vec.end(), cmp);
    vector<PII>:: iterator itor2 = vec.begin();
    for(;itor2 != vec.end();itor2++){
        cout << itor2 -> first << " ";
        cout << itor2 -> second << endl;
    }
    return 0;
}