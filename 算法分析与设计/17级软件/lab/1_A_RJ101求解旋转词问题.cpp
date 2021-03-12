#include <bits/stdc++.h>
using namespace std;

bool is_in(string s1, string s2){
    bool flag = false;
    int i = 0, j = 0;
    int len1 = s1.length();
    int len2 = s2.length();
    while( i < len1 && j < len2 ){
        if(s1[i] == s2[j]){
            i++;
            j++;
        }else{
            i = i - j + 1;
            j = 0;
        }
        if(j == len2){
            flag = true;
            break;
        }
    }
    return flag;
}

int main(){
    int n;
    string s, s1, s2;

    cin >> n;
    while(n--){
    // while((cin >> s1) && (cin >> s2)){
        cin >> s1;
        cin >> s2;
        s = s1 + s1;
        if(is_in(s, s2)){
            printf("Yes\n");
        }else{
            printf("No\n");
        }
    }
    return 0;
}
