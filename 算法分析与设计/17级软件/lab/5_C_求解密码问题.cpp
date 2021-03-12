#include <bits/stdc++.h>
using namespace std;

const int maxn = 30;
char str[maxn], x[5];
int len, n;
bool flag;

void swap(char &a, char &b){
    char tmp = a;
    a = b;
    b = tmp;
}

int fn(char a, int n){
    if(n == 1){
        return a - 'A' + 1;
    }
    return (a - 'A' + 1) * fn(a, n - 1);
}

void dfs (int i){
    if(i == 5){
        if(fn(x[0], 1) - fn(x[1], 2) + fn(x[2], 3) - fn(x[3], 4) + fn(x[4], 5) == n){
            flag = true;
            for(int j = 0;j < 5;j++){
                cout << x[j];
            }
            puts("");
        }
        return;
    }
    if(flag == true){
        return;
    }
    for(int j = i;j < len;j++){
        swap(str[i], str[j]);
        x[i] = str[i];
        dfs(i + 1);
        swap(str[i], str[j]);
    }
}

int main(){
	while (true){
		cin >> n;
		if (n == 0){
			break;
		}
		cin >> str;
		len = strlen(str);
		sort(str, str + len, greater<char>());
		flag = false;
		dfs(0);
		if (!flag){
			printf("no solution\n");
		}
	}
    return 0;
}