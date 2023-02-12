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
#include "顺序表读入.cpp"
using namespace std;

#define N 200
#define M 1000

struct Stock//定义结构体
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
	string Number;//股票代码
	string BriefName;//股票简称
};

typedef struct LNode
{
	Stock* data;
	string StockNumber;
	string StockName;
	int dataLength;
	struct LNode* next;
}LNode, *linklist;

//void InitList_L(linklist L)//构建空表 
//{
//	L = (LNode*)malloc(sizeof(LNode));
//	L->next = NULL;
//}

inline void baseOnDate()
{
	int i, j;
	struct Enterprise* B;
	B = list();
	linklist L;
	L = new LNode;
	L->next = NULL;
	linklist q = L;
	for (j = 0; j < 200; j++)
	{
		int n = 0;
		string number;
		Stock* list = new Stock[M];
		number = B[j].Number;
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
			//cout << list[1].Date << endl << list[1].StartPrice << endl << list[1].EndPrice << endl << list[1].HighPrice << endl << list[1].LowPrice << endl << list[1].BargainNum << endl << list[1].BargainTotalPrice << endl << list[1].ExchangeRate << endl << list[1].ChangeAmount << endl << list[1].ChangeRate << endl;
			//cout << "输入1继续查询，输入0退出：";
		}
		linklist p = new LNode;
		p->data = list;
		p->StockName = B[j].BriefName;
		p->StockNumber = B[j].Number;
		p->dataLength = n;
		p->next = NULL;
		q->next = p;
		q = q->next;
		//cout << q->data[0].Date << endl << q->StockName << endl << q->StockNumber << endl << endl;
	}
	int flag = -1;
	while (1)
	{
		system("cls");
		string SearchDate;
		cout << "请输入查询日期：";
		cin >> SearchDate;
		if (strlen(SearchDate.c_str()) != 8)
		{
			cout << "日期格式有误！" << endl;
		}
		//cout << SearchDate;
		else
		{
			int num = 0;
			printf("股票代码\t股票名称\t开盘价\t收盘价\t涨跌幅\n");
			printf("-------------------------------------------------------\n");
			linklist t = L->next;
			while (t)
			{
				int fffflag = 0;
				for (i = 0; i < t->dataLength; i++)
				{
					if (!strcmp(SearchDate.c_str(), t->data[i].Date))
					{
						flag = 0;
						fffflag = 1;
						num++;
						cout << t->StockNumber << "\t" << t->StockName << "\t" << t->data[i].StartPrice << "\t" << t->data[i].EndPrice << "\t" << t->data[i].ChangeRate << endl;
						break;
					}
				}
				if (!fffflag)
				{
					cout << t->StockNumber << "\t" << t->StockName << "\t" << "暂无该日信息" << endl;
				}
				t = t->next;
			}
			printf("-------------------------------------------------------\n");
			if (flag != 0)
			{
				cout << "暂无该日信息！" << endl;
			}
			cout << "该日期下的股票信息条数：" << "\t" << num << endl;
		}
		
		cout << "继续查询请输入1，退出请输入0：";
		cin >> flag;
		cout << endl << endl;
		if (!flag)
		{
			break;
		}
	}
	

	cout << "感谢您的使用！" << endl;

	system("pause");
	//return 0;
}