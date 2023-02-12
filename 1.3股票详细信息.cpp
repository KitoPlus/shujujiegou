#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include "股票代码二叉排序树.cpp"
using namespace std;

#define N 200
#define M 1000

struct StockII//定义结构体
{
	char Date[9];//日期
	char StartPrice[10];//开盘价
	char EndPrice[10];//收盘价
	char HighPrice[10];//最高价
	char LowPrice[10];//最低价
	char BargainNum[15];//成交量
	char BargainTotalPrice[10];//成交额
	char ExchangeRate[10];//换手率
	char ChangeAmount[10];//涨跌额
	char ChangeRate[10];//涨跌幅
};

inline void basic()
{
	int i, n = 0;
	while (1)
	{
		string number;
		StockII* list = new StockII[M];
		int flag = 1, n = 0;
		cout << "请输入股票代码：";
		cin >> number;
		if (strlen(number.c_str()) != 9 || number[0] != 'c' || number[1] != 'n' || number[2] != '_')
		{
			cout << "输入的代码有误！";
		}
		else
		{
			BiTreeASL(number);
			number.append(".txt");
			FILE* fs = NULL, * fp = NULL;
			fs = fopen(number.c_str(), "r");
			if (fs == NULL)
			{
				printf("暂无该股票信息！\n");
				//return 0;
			}
			else
			{
				fseek(fs, 88, SEEK_SET);//调整指针位置
				for (i = 0; i < M; i++)//文件读取 
				{
					fscanf(fs, "%s", list[i].Date);
					fscanf(fs, "%s", list[i].StartPrice);
					fscanf(fs, "%s", list[i].EndPrice);
					fscanf(fs, "%s", list[i].HighPrice);
					fscanf(fs, "%s", list[i].LowPrice);
					fscanf(fs, "%s", list[i].BargainNum);
					fscanf(fs, "%s", list[i].BargainTotalPrice);
					fscanf(fs, "%s", list[i].ExchangeRate);
					fscanf(fs, "%s", list[i].ChangeAmount);
					fscanf(fs, "%s", list[i].ChangeRate);
					n++;
					if (feof(fs) != 0)	break;//判断是否读取完毕 
				}
				cout << "开盘价：" << list[0].StartPrice << endl << "收盘价：" << list[0].EndPrice << endl << "涨跌幅：" << list[0].ChangeRate << endl;
			}
			cout << "输入1继续查询，输入0退出：";
			cin >> flag;
			cout << endl << endl;
			if (!flag)
			{
				break;
			}
		}
		
	}
	cout << "感谢您的使用！" << endl;
	
	system("pause");
	//return 0;
}