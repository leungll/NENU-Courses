/*
 * @Description: 
 * @version: 
 * @Author: LL Leung
 * @Date: 2019-12-08 15:43:40
 * @LastEditors  : LL Leung
 * @LastEditTime : 2019-12-22 10:13:23
 */
#include <bits/stdc++.h>
using namespace std;

const long mod = 1000000007L;

struct NodeType{
    long x;
    int num;
};

int bfs(long x0){
    NodeType e, el;
    if(x0 < 1 || x0 > 1000000006L){
        return -1;
    }
    x0 %= mod;
    queue <NodeType> qu;
    e.x= x0;
    e.num = 0;
    qu.push(e);
    while(!qu.empty()){
        e = qu.front(); 
        qu.pop();
        if (e.x == 0){
            return e.num;
        }
        if(e.num <= 100000){
            long x1 = (4 * e.x + 3) % mod;
            el.x = x1;
            el.num = e.num + 1;
            qu.push(el);
            long x2 = (8 * e.x + 7) % mod;
            el.x= x2;
            el.num = e.num + 1;
            qu.push(el);
        }
    }
    return -1;
}

int main(){
    long x0;
    while(cin >> x0){
        cout << bfs(x0) << endl;
    }
    
    // system("pause");
    return 0;
}

