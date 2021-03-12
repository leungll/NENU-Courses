#include <stdio.h>
#include <string>
using namespace std;
int BF(string s,string t)	//字符串匹配
{
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
	}
	if (j==t.length())		//t的字符比较完毕
		return i-j;			//t是s的子串,返回位置
	else					//t不是s的子串
		return -1;			//返回-1
}

void main()
{
	string s="aababcabcde";
	string t="abcd";
	printf("index=%d\n",BF(s,t));
}

