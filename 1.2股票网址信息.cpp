#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include "顺序表读入.cpp"
using namespace std;

inline vector<int> get_next(string b)	//用vector来保存子串b的next数组
{
	vector<int> result;		//别想用()帮它确定大小，其实是添加元素并且默认赋值为0了，建立一个空的容器就OK了
	int i, j;
	i = 0;
	j = -1;
	result.push_back(-1);	//将容器首元素赋值，作为标识使用
	while (i < b.size() - 1)
	{
		if (j == -1 || b[i] == b[j])	//b[i]表示后缀的单个字符
										//b[j]表示前缀的单个字符
		{
			++i;
			++j;
			//这里的其实是优化重复的字符
			//可以直接用result.push_back(j);代替下面的判断语句
			if (b[i] != b[j])
				result.push_back(j);
			else if (i == 1)
				result.push_back(j);
			else
				result.push_back(result[j]);
		}
		else
			j = result[j];		//若字符不同，前缀字符回溯
	}
	return result;
}
inline int KMP(string a, string b)
{
	vector<int> next = get_next(b);	//调用get_text函数
	int i = 0;
	int j = 0;
	//注意size函数返回的类型是string::size_type是无符号数
	//若i<主串的长度且j<子串的长度时，循环继续
	while (i < (int)a.size() && j < (int)b.size())//控制循环次数
	{
		if (j == -1 || a[i] == b[j])	//两字母相等则继续，相对于朴素算法增加了
		{
			++i;
			++j;
		}
		else {
			j = next[j];	//若不相等，j退回合适的位置
		}
	}
	if (j == b.size()) {
		return i - j;		//这里返回的是匹配字符开始的下标位
	}
	else {
		return -1;
	}
}


inline void web()
{
	struct Enterprise* B;
	string user;
	int i, flag, n;
	B = list();
	while (1)
	{
		cout << "请输入网址关键字：";
		cin >> user;
		for (i = 0; i < 200; i++)//循环遍历进行KMP匹配，成功则停止
		{
			flag = KMP(B[i].Website, user);
			if (flag != -1)
			{
				break;
			}
		}
		if (flag == -1)
		{
			cout << "未查询到有关信息！" << endl;
		}
		else
		{
			cout << B[i].BriefName << " " << B[i].Number << endl;
		}
		cout << "继续查找请输入1，否则请输入0：";
		cin >> n;
		cout << endl << endl;
		if (!n)
		{
			break;
		}
	}
	cout << "感谢您的使用！" << endl;
	system("pause");

	//return 0;
}