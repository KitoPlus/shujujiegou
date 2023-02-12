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

typedef struct StockIV//定义结构体
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
	//string Number;//股票代码
	//string BriefName;//股票简称
};

typedef struct LNodeII
{
	StockIV* data;
	string StockClassI;
	string userDate;
	string userChangeRate;
	string StockNumber;
	string StockName;
	int dataLength;
	struct LNodeII* next;
}LNodeII, * linklistII;

typedef struct Stock60I
{
	int PointI;
	string Name60I;
	string Number60I;
	double ScoreI;
};

typedef struct Purpose
{
	int No;
	string PPSnumber;
	string PPSname;
	string PPSchangerate;
	string PPSdate;
	double changeratenum;
};

/***
读取excel指定内容并输出在控制台，注意请在关闭.xlsx文件条件下运行
***/

//const wchar_t*   是一个指向宽字符类型的指针，这个指针指向的内容是个常量，不能改变

//char* w2c(char* pcstr, const wchar_t* pwstr, size_t len)//此函数支持中文读取和显示，需加入否则中文内容乱码
//{
//	int nlength = wcslen(pwstr);//获取转换后的长度
//
//	int nbytes = WideCharToMultiByte(0, 0, pwstr, nlength, NULL, 0, NULL, NULL); //映射一个unicode字符串到一个多字节字符串
//
//	if (nbytes > len)   nbytes = len;
//	// 通过以上得到的结果，转换unicode 字符为ascii 字符
//	WideCharToMultiByte(0, 0, pwstr, nlength, pcstr, nbytes, NULL, NULL);
//
//	return pcstr;
//}

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

inline void Excel(Stock60I* gp60)
{
	

	Book* book = xlCreateXMLBook();//创建一个XLSX的实例,在使用前必须先调用这个函数创建操作excel的对象

	book->setKey(L"TommoT", L"windows-2421220b07c2e10a6eb96768a2p7r6gc");//设置相应的key激活相关功能(购买)，否则创建book无法成功

	if (book->load(L"60支股票信息.xlsx"))//文件放入工程目录里
	{
		Sheet* sheetread = book->getSheet(1);//选取第一个表

		if (sheetread)
		{
			for (int row = sheetread->firstRow()+1; row < sheetread->lastRow(); ++row)//行遍历
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
							gp60[row-1].Name60I = pcstr;
						}
						if (col == 2)
						{
							gp60[row - 1].Number60I = pcstr;
						}

						free(pcstr);

					}
					else if (celltype == CELLTYPE_NUMBER)//如果每个单元格内容为数值类型
					{
						double result = sheetread->readNum(row, col);

						//cout << result << endl;
						if (col == 0)
						{
							gp60[row - 1].PointI = (int)result;
						}
						if (col == 3)
						{
							gp60[row - 1].ScoreI = result;
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

inline void QuickSort(Purpose* array, int low, int high) 
{
	int i = low;
	int j = high;
	if (i >= j) 
	{
		return;
	}
	Purpose temp = array[low];
	while (i != j) {
		while (array[j].changeratenum <= temp.changeratenum && i < j) 
		{
			j--;
		}
		while (array[i].changeratenum >= temp.changeratenum && i < j) 
		{
			i++;
		}
		if (i < j) 
		{
			swap(array[i], array[j]);
		}
	}

	//将基准temp放于自己的位置，（第i个位置）
	swap(array[low], array[i]);
	QuickSort(array, low, i - 1);
	QuickSort(array, i + 1, high);
}

inline void FastSort()
{
	int i, j;
	struct Enterprise* B;
	Stock60I* gp60 = new Stock60I[60];
	Excel(gp60);
	/*for (int i = 0; i < 60; i++)
	{
		cout << gp60[i].PointI << "\t" << gp60[i].ScoreI << "\t" << gp60[i].Name60I << "\t" << gp60[i].Number60I << endl;
	}*/
	B = list();
	linklistII L, L2;
	L = new LNodeII;
	L->next = NULL;
	linklistII q = L;
	for (j = 0; j < 200; j++)
	{
		int n = 0;
		string number;
		StockIV* list = new StockIV[M];
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
			//cout << list[1].Date << endl << list[1].StartPrice << endl << list[1].EndPrice << endl << list[1].HighPrice << endl << list[1].LowPrice << endl << list[1].BargainNum << endl << list[1].BargainTotalPrice << endl << list[1].ExchangeRate << endl << list[1].ChangeAmount << endl << list[1].ChangeRate << endl;
			//cout << "输入1继续查询，输入0退出：";
		}
		linklistII p = new LNodeII;
		p->data = list;
		//strcpy(p->StockName.c_str(), B[j].BriefName.c_str());
		p->StockName = B[j].BriefName;
		p->StockNumber = B[j].Number;
		p->StockClassI = B[j].ClassI;
		p->dataLength = n-1;
		p->next = NULL;
		q->next = p;
		q = q->next;
		//cout << q->data[1].Date << endl << q->StockName << endl << q->StockNumber << endl << endl;
	}
	/*q = L->next;
	while (q)
	{
		cout << q->dataLength << endl;
		q = q->next;
	}*/

	q = L->next;
	while (q)
	{
		double fflag;
		int ffflag = 0;
		char temp1[10];
		for (i = 0; q->data[0].ChangeRate[i] != '%'; i++)
		{
			temp1[i] = q->data[0].ChangeRate[i];
		}
		temp1[i] = '\0';
		fflag = atof(temp1);
		//cout << temp1 << endl;
		for (i = 1; i < q->dataLength; i++)
		{
			//cout << q->data[i].Date<< endl;
			//cout << i << endl;
			memset(temp1, 0, sizeof(temp1));
			for (j = 0; q->data[i].ChangeRate[j] != '%'; j++)
			{
				temp1[j] = q->data[i].ChangeRate[j];
			}
			temp1[j] = '\0';
			if (atof(temp1) > fflag)
			{
				fflag = atof(temp1);
				ffflag = i;
			}
		}
		q->userChangeRate = q->data[ffflag].ChangeRate;
		q->userDate = q->data[ffflag].Date;
		q = q->next;
		//cout << endl << endl;
	}
	/*q = L->next;
	while (q)
	{
		cout << q->userChangeRate << " " << q->userDate << endl;
		q = q->next;
	}*/

	L2 = new LNodeII;
	L2->next = NULL;
	linklistII r = L2;
	for (i = 0; i < 60; i++)
	{
		q = L->next;
		for (j = 0; j < 200; j++)
		{
			if (!strcmp(gp60[i].Number60I.c_str(), q->StockNumber.c_str()))
			{
				linklistII p = new LNodeII;
				p->StockClassI = q->StockClassI;
				p->StockName = q->StockName;
				p->StockNumber = q->StockNumber;
				p->userChangeRate = q->userChangeRate;
				p->userDate = q->userDate;
				p->next = NULL;
				r->next = p;
				r = p;
				break;
			}
			q = q->next;
		}
	}
	/*r = L2->next;
	int nnnn = 0;
	while (r)
	{
		cout << r->StockClassI << "\t" << r->StockName << "\t" << r->StockNumber << "\t" << r->userChangeRate << "\t" << r->userDate << endl;
		r = r->next;
		nnnn++;
	}
	cout << nnnn;*/

	string userclass;
	cout << "请输入查询行业：";
	cin >> userclass;
	struct Purpose* pps = new Purpose[60];
	int nnnn = 1;
	q = L2->next;
	for (i = 0; i < 60; i++)
	{
		if (!strcmp(userclass.c_str(), q->StockClassI.c_str()))
		{
			pps[nnnn].PPSnumber = q->StockNumber;
			pps[nnnn].PPSname = q->StockName;
			pps[nnnn].PPSchangerate = q->userChangeRate;
			pps[nnnn].PPSdate = q->userDate;
			//cout << pps[nnnn].PPSname << " " << nnnn;
			nnnn++;
		}
		q = q->next;
	}
	//cout << nnnn;
	for (i = 1; i < nnnn; i++)
	{
		char temp1[10];
		for (j = 0; pps[i].PPSchangerate[j] != '%'; j++)
		{
			temp1[j] = pps[i].PPSchangerate[j];
		}
		temp1[j] = '\0';
		pps[i].changeratenum = atof(temp1);
	}
	
	QuickSort(pps, 1, nnnn);
	for (i = 2; i < nnnn+1; i++)
	{
		pps[i].No = i-1;
		//cout << pps[i].PPSnumber << "\t" << pps[i].PPSname << "\t" << pps[i].PPSchangerate << "\t" << pps[i].PPSdate << endl;
	}
	

	Book* book = xlCreateXMLBook();//创建一个XLSX的实例,在使用前必须先调用这个函数创建操作excel的对象

	book->setKey(L"TommoT", L"windows-2421220b07c2e10a6eb96768a2p7r6gc");//设置用户注册信息，是否正版就在这里验证，否则第一行无法操作

	if (book)
	{

		Sheet* sheetwrite = book->addSheet(L"sheet1");;//生成第一个表

		if (sheetwrite)
		{
			int m, n;
			m = nnnn;
			n = 5;
			string label[5];
			label[0] = "序号";
			label[1] = "股票代码";
			label[2] = "股票名称";
			label[3] = "涨跌幅";
			label[4] = "日期";
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
			for (int row = 2; row < m+1; ++row)
			{
				for (int col = 1; col < n; ++col)
				{
					string str;
					switch (col)
					{
					case 1: str = pps[row-1].PPSnumber; break;
					case 2: str = pps[row-1].PPSname; break;
					case 3: str = pps[row-1].PPSchangerate; break;
					case 4: str = pps[row-1].PPSdate; break;
					}
					//cout << str;
					wchar_t* wchar = StringToWchar(str);

					sheetwrite->writeStr(row-1, col, wchar);

					delete[]wchar;
				}
			}
		}
		//string str = ".xlsx";
		//userclass.append(".xlsx");
		if (book->save(L"一级行业按涨跌幅排序.xlsx"))
		{
			//::ShellExecute(NULL, "open", "example.xls", NULL, NULL, SW_SHOW);
			cout << "一级行业按涨跌幅排序已生成！" << endl;
		}
		else
		{
			std::cout << book->errorMessage() << std::endl;
		}
	}
	book->release();

		//cout << nnnn;

	system("pause");
	//return 0;
}