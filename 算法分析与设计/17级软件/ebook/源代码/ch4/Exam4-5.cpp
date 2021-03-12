#include <stdio.h>
#include <string>
using namespace std;
int Count(string s,string t)	//字符串匹配
{
	int num=0;				//累计出现次数
	int i=0,j=0;
	while (i<s.length() && j<t.length())
	{
		if (s[i]==t[j])		//比较的两个字符相同时
		{
			i++; j++;
		}
		else				//比较的两个字符不相同时
		{
			i=i-j+1;		//i回退
			j=0;			//j从0开始
		}
		if(j==t.length())
		{
			num++;			//出现次数增1
			j=0;			//j从0开始继续
		}
	}
	return num;
}
void main()
{
	string s="abababa";
	string t="aba";
	printf("t在s中出现次数: %d\n",Count(s,t));
}

