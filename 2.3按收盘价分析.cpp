#pragma once
#include <iostream>
#include "libxl.h"
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
#include <iomanip>
#include <time.h>
#include <conio.h>
#include "顺序表读入.cpp"
using namespace libxl;
using namespace std;

#define N 200
#define M 1000

typedef struct Stock60II
{
	int PointII;
	string Name60II;
	string Number60II;
	double ScoreII;
	double EndPriceII;
};

typedef struct StockV//定义结构体
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

typedef struct LNodeIII
{
	StockV* data;
	string StockClassI;
	string userDate;
	string userChangeRate;
	string StockNumber;
	string StockName;
	int dataLength;
	struct LNodeIII* next;
}LNodeIII, * linklistIII;


//inline wchar_t* StringToWchar(const string& pKey)
//{
//	const char* pCStrKey = pKey.c_str();
//	//第一次调用返回转换后的字符串长度，用于确认为wchar_t*开辟多大的内存空间
//	int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
//	wchar_t* pWCStrKey = new wchar_t[pSize];
//	//第二次调用将单字节字符串转换成双字节字符串
//	MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, pWCStrKey, pSize);
//	return pWCStrKey;
//}

inline void Excel(Stock60II* gp60)
{


	Book* book = xlCreateXMLBook();//创建一个XLSX的实例,在使用前必须先调用这个函数创建操作excel的对象

	book->setKey(L"TommoT", L"windows-2421220b07c2e10a6eb96768a2p7r6gc");//设置相应的key激活相关功能(购买)，否则创建book无法成功

	if (book->load(L"60支股票信息.xlsx"))//文件放入工程目录里
	{
		Sheet* sheetread = book->getSheet(1);//选取第一个表

		if (sheetread)
		{
			for (int row = sheetread->firstRow() + 1; row < sheetread->lastRow(); ++row)//行遍历
			{
				for (int col = sheetread->firstCol(); col < sheetread->lastCol(); ++col)//列遍历
				{
					CellType celltype = sheetread->cellType(row, col);//读取某行某列的单元格的类型。有字符串型，数值型，空值。

					Format* format = sheetread->cellFormat(row, col);

					if (celltype == CELLTYPE_STRING)//如果每个单元格内容为字符串类型
					{
						const wchar_t* t = sheetread->readStr(row, col);//从单元格中读取字符串及其格式

						char* pcstr = (char*)malloc(sizeof(char) * (2 * wcslen(t) + 1));//定义空间大小来存放读出的内容，wcslen()函数返回输入参数t的长度

						memset(pcstr, 0, 2 * wcslen(t) + 1);//初始化清零操作，开辟两倍+1的空间

						w2c(pcstr, t, 2 * wcslen(t) + 1); //pcstr的内容读出来后要进行中文编码的转换，这个为转换函数

						if (col == 1)
						{
							//cout << pcstr << endl;//输出
							gp60[row - 1].Name60II = pcstr;
						}
						if (col == 2)
						{
							gp60[row - 1].Number60II = pcstr;
						}

						free(pcstr);

					}
					else if (celltype == CELLTYPE_NUMBER)//如果每个单元格内容为数值类型
					{
						double result = sheetread->readNum(row, col);

						//cout << result << endl;
						if (col == 0)
						{
							gp60[row - 1].PointII = (int)result;
						}
						if (col == 3)
						{
							gp60[row - 1].ScoreII = result;
						}
					}
					//else if (celltype == CELLTYPE_BLANK)//如果每个单元格内容为空：无值但存在单元格样式
					//{
					//	cout << "\t\t" << endl;
					//}
					//else if (celltype == CELLTYPE_EMPTY)//不存在单元格样式
					//{
					//	cout << "\t\t" << endl;
					//}
				}
				//cout << endl;//每行内容换行分割输出
			}
		}
		////保存excel
		book->save(L"60支股票信息.xlsx");

		book->release();
	}
	/*for (int i = 0; i < 60; i++)
	{
		cout << gp60[i].PointI << "\t" << gp60[i].ScoreI << "\t" << gp60[i].Name60I << "\t" << gp60[i].Number60I << endl;
	}*/
	//system("pause");
	//return 0;
}

inline void SelectSort_score(Stock60II* gp60)
{
	for (int i = 0; i < 59; i++)
	{
		int k = i;
		for (int j = i + 1; j < 60; j++)
		{
			if (gp60[j].ScoreII > gp60[k].ScoreII)
			{
				k = j;
			}
		}
		if (k != i)
		{
			swap(gp60[i], gp60[k]);
		}
	}
}

inline void SelectSort_endprice(Stock60II* gp60)
{
	for (int i = 0; i < 59; i++)
	{
		int k = i;
		for (int j = i + 1; j < 60; j++)
		{
			if (gp60[j].EndPriceII > gp60[k].EndPriceII)
			{
				k = j;
			}
		}
		if (k != i)
		{
			swap(gp60[i], gp60[k]);
		}
	}
}

inline void SelectSort()
{
	Stock60II* gp60 = new Stock60II[60];
	Excel(gp60);
	SelectSort_score(gp60);
	Book* book = xlCreateXMLBook();//创建一个XLSX的实例,在使用前必须先调用这个函数创建操作excel的对象

	book->setKey(L"TommoT", L"windows-2421220b07c2e10a6eb96768a2p7r6gc");//设置用户注册信息，是否正版就在这里验证，否则第一行无法操作

	if (book)
	{

		Sheet* sheetwrite = book->addSheet(L"sheet1");;//生成第一个表

		if (sheetwrite)
		{
			int m, n;
			m = 61;
			n = 4;
			string label[4];
			label[0] = "序号";
			label[1] = "股票代码";
			label[2] = "股票名称";
			label[3] = "评分";
			for (int col = 0; col < n; ++col)
			{
				int row = 0;
				wchar_t* wchar = StringToWchar(label[col]);

				sheetwrite->writeStr(row, col, wchar);

				delete[]wchar;
			}
			for (int row = 1; row < m; ++row)
			{
				int col = 0;
				sheetwrite->writeNum(row, col, row);
			}
			for (int row = 1; row < m ; ++row)
			{
				for (int col = 1; col < n; ++col)
				{
					if (col == 1 || col == 2)
					{
						string str;
						if (col == 1)
						{
							str = gp60[row - 1].Number60II;
						}
						else
						{
							str = gp60[row - 1].Name60II;
						}
						//cout << str;
						wchar_t* wchar = StringToWchar(str);

						sheetwrite->writeStr(row, col, wchar);

						delete[]wchar;
					}
					else
					{
						sheetwrite->writeNum(row, col, gp60[row-1].ScoreII);
					}
				}
			}
		}
		//string str = ".xlsx";
		if (book->save(L"2-3评分排序.xlsx"))
		{
			//::ShellExecute(NULL, "open", "example.xls", NULL, NULL, SW_SHOW);
			cout << "2-3评分排序已生成！" << endl;
		}
		else
		{
			std::cout << book->errorMessage() << std::endl;
		}
	}
	book->release();

	int i, j;
	struct Enterprise* B;
	B = list();
	linklistIII L, L2;
	L = new LNodeIII;
	L->next = NULL;
	linklistIII q = L;
	for (j = 0; j < 200; j++)
	{
		int n = 0;
		string number;
		StockV* list = new StockV[M];
		number = B[j].Number;
		number.append(".txt");
		FILE* fs = NULL, * fp = NULL;
		fs = fopen(number.c_str(), "r");
		if (fs == NULL)
		{
			printf("程序出现错误！\n");
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
			fclose(fs);
			//cout << list[1].Date << endl << list[1].StartPrice << endl << list[1].EndPrice << endl << list[1].HighPrice << endl << list[1].LowPrice << endl << list[1].BargainNum << endl << list[1].BargainTotalPrice << endl << list[1].ExchangeRate << endl << list[1].ChangeAmount << endl << list[1].ChangeRate << endl;
			//cout << "输入1继续查询，输入0退出：";
		}
		linklistIII p = new LNodeIII;
		p->data = list;
		//strcpy(p->StockName.c_str(), B[j].BriefName.c_str());
		p->StockName = B[j].BriefName;
		p->StockNumber = B[j].Number;
		p->StockClassI = B[j].ClassI;
		p->dataLength = n - 1;
		p->next = NULL;
		q->next = p;
		q = q->next;
		//cout << q->data[1].Date << endl << q->StockName << endl << q->StockNumber << endl << endl;
	}
	for (i = 0; i < 60; i++)
	{
		q = L->next;
		for (j = 0; j < 200; j++)
		{
			if (!strcmp(gp60[i].Number60II.c_str(), q->StockNumber.c_str()))
			{
				gp60[i].EndPriceII = atof(q->data[0].EndPrice);
				break;
			}
			q = q->next;
		}
	}
	SelectSort_endprice(gp60);
	/*for (int i = 0; i < 60; i++)
	{
		cout << gp60[i].PointII << "\t" << gp60[i].ScoreII << "\t" << gp60[i].Name60II << "\t" << gp60[i].Number60II << "\t" << gp60[i].EndPriceII << endl;
	}*/
	Book* book1 = xlCreateXMLBook();//创建一个XLSX的实例,在使用前必须先调用这个函数创建操作excel的对象

	book1->setKey(L"TommoT", L"windows-2421220b07c2e10a6eb96768a2p7r6gc");//设置用户注册信息，是否正版就在这里验证，否则第一行无法操作

	if (book1)
	{

		Sheet* sheetwrite = book1->addSheet(L"sheet1");;//生成第一个表

		if (sheetwrite)
		{
			int m, n;
			m = 61;
			n = 4;
			string label[4];
			label[0] = "序号";
			label[1] = "股票代码";
			label[2] = "股票名称";
			label[3] = "收盘价";
			for (int col = 0; col < n; ++col)
			{
				int row = 0;
				wchar_t* wchar = StringToWchar(label[col]);

				sheetwrite->writeStr(row, col, wchar);

				delete[]wchar;
			}
			for (int row = 1; row < m; ++row)
			{
				int col = 0;
				sheetwrite->writeNum(row, col, row);
			}
			for (int row = 1; row < m; ++row)
			{
				for (int col = 1; col < n; ++col)
				{
					if (col == 1 || col == 2)
					{
						string str;
						if (col == 1)
						{
							str = gp60[row - 1].Number60II;
						}
						else
						{
							str = gp60[row - 1].Name60II;
						}
						//cout << str;
						wchar_t* wchar = StringToWchar(str);

						sheetwrite->writeStr(row, col, wchar);

						delete[]wchar;
					}
					else
					{
						sheetwrite->writeNum(row, col, gp60[row - 1].EndPriceII);
					}
				}
			}
		}
		//string str = ".xlsx";
		if (book1->save(L"2-3收盘价排序.xlsx"))
		{
			//::ShellExecute(NULL, "open", "example.xls", NULL, NULL, SW_SHOW);
			cout << "2-3收盘价排序已生成！" << endl;
		}
		else
		{
			std::cout << book1->errorMessage() << std::endl;
		}
	}
	book1->release();

	system("pause");
	//return 0;
}