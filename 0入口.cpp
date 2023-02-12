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
#include "1.1股票基本信息.cpp"
#include "1.2股票网址信息.cpp"
#include "1.3股票详细信息.cpp"
#include "1.4股票价格信息.cpp"
#include "2.1按时间分析.cpp"
#include "2.2按行业分析.cpp"
#include "2.3按收盘价分析.cpp"
#include "2.4股票相关性分析.cpp"
#include "2.5普利姆股票基金筛选.cpp"
#include "2.6二部图股票基金筛选.cpp"
#include "2.5.2卡尔股票基金筛选.cpp"
#include "1.3.2股票基本信息的删除.cpp"
using namespace std;

bool visit[61];
int dist[61];
int smalltree[61][61];
int color[11];//染色标志数组，未染色为0，红色为1，蓝色为2（1~10）

// wchar_t* StringToWchar(const string& pKey)
//{
//	const char* pCStrKey = pKey.c_str();
//	//第一次调用返回转换后的字符串长度，用于确认为wchar_t*开辟多大的内存空间
//	int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
//	wchar_t* pWCStrKey = new wchar_t[pSize];
//	//第二次调用将单字节字符串转换成双字节字符串
//	MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, pWCStrKey, pSize);
//	return pWCStrKey;
//}

int main()
{
	int cntnu;
	while(1)
	{
		int choice;
		system("cls");
		system("color F0");
		printf("******************************************************************************\n");
		printf("******                    欢迎使用股票查询与分析系统                    ******\n");
		printf("******************************************************************************\n");
		printf("******                        本系统具备以下功能：                      ******\n");
		printf("******                           1.查询系统 ；                          ******\n");
		printf("******                           2.分析系统 ：                          ******\n");
		printf("******                           3.退出系统 ：                          ******\n");
		printf("******************************************************************************\n");
		cout << endl;
		cout << "请输入您选择的功能：";
		fflush(stdin);
		cin >> choice;
		if (choice == 1)
		{
			system("cls");
			system("color E0");
			choice = 0;
			printf("------------------------------------------------------------------------------\n");
			printf("------                         欢迎使用查询功能                         ------\n");
			printf("------------------------------------------------------------------------------\n");
			printf("------                      您可以选择以下操作之一：                    ------\n");
			printf("------                  1.股票基本信息查询（基于哈希表）；              ------\n");
			printf("------                  2.股票网址信息查询（基于KMP）；                 ------\n");
			printf("------                  3.股票详细信息查询（基于二叉排序树）；          ------\n");
			printf("------                  4.股票价格信息查询（基于单链表）；              ------\n");
			printf("------                  5.股票基本信息删除（基于二叉排序树）；          ------\n");
			printf("------                  0.返回上一级；                                  ------\n");
			printf("------------------------------------------------------------------------------\n");
			cout << endl;
			cout << "请选择您将要进行的操作：";
			cin >> choice;
			system("cls");
			switch (choice)
			{
			case 1: hashSearch(); break;
			case 2: web(); break;
			case 3: basic(); break;
			case 4: baseOnDate(); break;
			case 5: DeleteOne(); break;
			case 0: break;
			default: cout << "操作有误！" << endl; break;
			}
		}
		else if (choice == 2)
		{
			system("cls");
			system("color B0");
			choice = 0;
			printf("------------------------------------------------------------------------------\n");
			printf("------                         欢迎使用分析功能                         ------\n");
			printf("------------------------------------------------------------------------------\n");
			printf("------                      您可以选择以下操作之一：                    ------\n");
			printf("------                    1.按时间分析（直接插入排序）；                ------\n");
			printf("------                    2.按行业分析（快速排序）；                    ------\n");
			printf("------                    3.按收盘价分析（简单选择排序）；              ------\n");
			printf("------                    4.股票相关性分析（Floyd最短路径）；           ------\n");
			printf("------                    5.普利姆股票基金筛选（Prim最小生成树）；      ------\n");
			printf("------                    6.二部图股票基金筛选（二部图与染色法）；      ------\n");
			printf("------                    7.卡尔股票基金筛选（Kruskal最小生成树）；     ------\n");
			printf("------                    0.返回上一级；                                ------\n");
			printf("------------------------------------------------------------------------------\n");
			cout << endl;
			cout << "请选择您将要进行的操作：";
			cin >> choice;
			system("cls");
			switch (choice)
			{
			case 1: InsertSort(); break;
			case 2: FastSort(); break;
			case 3: SelectSort(); break;
			case 4: Relate(); break;
			case 5: PrimFundation(); break;
			case 6: BipartFundation(); break;
			case 7: KrukalFundation(); break;
			case 0: break;
			default: cout << "操作有误！" << endl; break;
			}
		}
		else if (choice == 3)
		{
			system("cls");
			cout << "感谢您的使用，祝您生意顺利！" << endl;
			break;
		}
	}
	

	system("pause");
	return 0;
}
