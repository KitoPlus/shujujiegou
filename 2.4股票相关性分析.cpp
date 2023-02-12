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

#define N 5000

typedef struct Stock60III
{
	int PointIII;
	string Name60III;
	string Number60III;
	double ScoreIII;
};

typedef struct RelationI
{
	int Point1;
	int Point2;
	int Weight;
};

typedef struct matrix {
	int n;						//顶点个数
	int e;						//边数 
	int adjMat[61][61];		//邻接矩阵数组			
	Stock60III ver[61];		//存放顶点信息 
	int ShortestMap[61][61];   //最短路矩阵
}MatGraph;						//别名，完整的图邻接矩阵类型

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

inline void Excel1(Stock60III* gp60)//读入评分和标号信息
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
							gp60[row - 1].Name60III = pcstr;
						}
						if (col == 2)
						{
							gp60[row - 1].Number60III = pcstr;
						}

						free(pcstr);

					}
					else if (celltype == CELLTYPE_NUMBER)//如果每个单元格内容为数值类型
					{
						double result = sheetread->readNum(row, col);

						//cout << result << endl;
						if (col == 0)
						{
							gp60[row - 1].PointIII = (int)result;
						}
						if (col == 3)
						{
							gp60[row - 1].ScoreIII = result;
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
		cout << gp60[i].PointIII << "\t" << gp60[i].ScoreIII << "\t" << gp60[i].Name60III << "\t" << gp60[i].Number60III << endl;
	}*/
	//system("pause");
	//return 0;
}

inline void Excel2(RelationI* Map83)
{


	Book* book = xlCreateXMLBook();//创建一个XLSX的实例,在使用前必须先调用这个函数创建操作excel的对象

	book->setKey(L"TommoT", L"windows-2421220b07c2e10a6eb96768a2p7r6gc");//设置相应的key激活相关功能(购买)，否则创建book无法成功

	if (book->load(L"60支股票信息.xlsx"))//文件放入工程目录里
	{
		Sheet* sheetread = book->getSheet(0);//选取第一个表

		if (sheetread)
		{
			for (int row = sheetread->firstRow() + 1; row < sheetread->lastRow(); ++row)//行遍历
			{
				for (int col = sheetread->firstCol(); col < sheetread->lastCol(); ++col)//列遍历
				{
					CellType celltype = sheetread->cellType(row, col);//读取某行某列的单元格的类型。有字符串型，数值型，空值。

					Format* format = sheetread->cellFormat(row, col);

					if (celltype == CELLTYPE_NUMBER)//如果每个单元格内容为数值类型
					{
						double result = sheetread->readNum(row, col);

						//cout << result << endl;
						if (col == 0)
						{
							Map83[row - 1].Point1 = (int)result;
						}
						if (col == 1)
						{
							Map83[row - 1].Point2 = (int)result;
						}
						if (col == 2)
						{
							Map83[row - 1].Weight = (int)result;
						}
					}
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
		cout << Map83[i].Point1 << "\t" << Map83[i].Point2 << "\t" << Map83[i].Weight << endl;
	}*/
	//system("pause");
	//return 0;
}

inline void displayPath(int A[61][61], int path[61][61], int a, int b) {
	int i, j, k;
	int s;
	int aPath[61];										//存放一条最短路径（逆向）
	int d;													//顶点个数
	int flag = 0;
	for (i = 1; i < 61; i++)
	{
		for (j = 1; j < 61; j++)
		{
			if (A[a][b] != N)
			{//若顶点 i 和 顶点 j 之间存在路径
				printf("从 %d 到 %d 的关联方式为：", a, b);
				k = path[a][b];
				d = 0;
				aPath[d] = b;								//路径上添加终点
				while (k != -1 && k != a) {					//路劲上添加中间点
					d++;
					aPath[d] = k;
					k = path[a][k];
				}
				d++;
				aPath[d] = a;								//路径上添加起点
				printf("%d", aPath[d]);						//输出起点
				for (s = d - 1; s >= 0; s--) {				//输出路径上其他顶点
					printf("->%d", aPath[s]);
				}
				printf("\t");
				printf("两股票关联程度为：%d\n\n", A[a][b]);
				flag = 1;
				return;
			}
		}
	}
	if (!flag)
	{
		cout << "两支股票之间无关联性！" << endl << endl;
	}
}

inline void Floyd(MatGraph MG, int s, int t, int SM[][61])
{
	int i, j, k;
	int A[61][61];
	int path[61][61];
	for (i = 1; i <= MG.n; i++)
	{
		for (j = 1; j <= MG.n; j++)
		{
			A[i][j] = MG.adjMat[i][j];
			if (i != j && MG.adjMat[i][j] < N)
			{
				path[i][j] = i;							//顶点 i 到顶点 j 有边时
			}
			else
			{
				path[i][j] = -1;						//顶点 i 到顶点 j 无边时
			}
		}
	}
	for (k = 1; k <= MG.n; k++)
	{						//一次考察所有顶点
		for (i = 1; i <= MG.n; i++)
		{
			for (j = 1; j <= MG.n; j++)
			{
				if (A[i][j] > A[i][k] + A[k][j])        //A是邻接矩阵
				{
					A[i][j] = A[i][k] + A[k][j];		//修改最短路径长度
					path[i][j] = path[k][j];			//修改最短路径
				}
			}
		}
	}
	/*for (i = 1; i < 61; i++)
	{
		int min = 5000;
		for (j = 1; j < 61; j++)
		{
			if (A[i][j] < min)
			{
				min = A[i][j];
			}
		}
		cout << i << "：" << min << endl;
	}*/
	for (i = 1; i <= MG.n; i++)
	{
		for (j = 1; j <= MG.n; j++)
		{
			*(SM[i] + j) = A[i][j];
		}
	}
	displayPath(A, path, s, t);							//输出最短路径
}

//inline int SearchPoint(Stock60III* gp60, string a)
//{
//	for (int i = 0; i < 60; i++)
//	{
//		if (!strcmp(a.c_str(), gp60[i].Name60III.c_str()))
//		{
//			return gp60[i].PointIII;
//		}
//	}
//	return -1;
//}


inline MatGraph Relate()
{
	int i, j;
	Stock60III* gp60 = new Stock60III[60];
	RelationI* Map83 = new RelationI[83];
	Excel1(gp60);//读入点值信息
	Excel2(Map83);//读入路径信息
	MatGraph FloydList;
	FloydList.n = 60;
	FloydList.e = 83;
	for (i = 1; i <= 60; i++)//初始化邻接矩阵
	{
		for (j = 1; j <= 60; j++)
		{
			FloydList.adjMat[i][j] = N;
		}
		FloydList.ver[i] = gp60[i - 1];
	}
	for (i = 0; i < 83; i++)//读入权值
	{
		FloydList.adjMat[Map83[i].Point1][Map83[i].Point2] = Map83[i].Weight;
		//cout << Map83[i].Point1 << " " << Map83[i].Point2 << " " << Map83[i].Weight << " " << FloydList.adjMat[Map83[i].Point1][Map83[i].Point2] << endl;
	}
	for (i = 1; i < 61; i++)//有向图转无向图
	{
		for (j = 1; j < 61; j++)
		{
			if (FloydList.adjMat[i][j] == 5000)
			{
				FloydList.adjMat[i][j] = FloydList.adjMat[j][i];
			}
		}
	}
	int f;
	for (i = 1; i < 61; i++)
	{
		for (j = 1; j < 61; j++)
		{
			FloydList.ShortestMap[i][j] = 0;
		}
	}
	while (1)
	{
		fflush(stdin);
		string str1, str2;
		int temp1, temp2;
		cout << "请输入两只股票的序号（中间用回车隔开）：" << endl;
		cin >> temp1 >> temp2;
		/*temp1 = SearchPoint(gp60, str1);
		temp2 = SearchPoint(gp60, str2);*/
		if (temp1 == -1 || temp2 == -1)
		{
			cout << "本系统暂时无法分析这两只股票！" << endl << endl;
		}
		else
		{
			for (int i = 0; i < 60; i++)
			{
				if (temp1==gp60[i].PointIII)
				{
					str1 = gp60[i].Name60III;
				}
			}
			for (int i = 0; i < 60; i++)
			{
				if (temp2 == gp60[i].PointIII)
				{
					str2 = gp60[i].Name60III;
				}
			}
			cout << "您将要查询的两只股票序号分别是：" << temp1 << " " << temp2 << endl;
			Floyd(FloydList, temp1, temp2, FloydList.ShortestMap);
		}
		/*for (i = 1; i <= 60; i++)
		{
			for (j = 1; j <= 60; j++)
			{
				if (FloydList.ShortestMap[i][j] != 5000)
				{
					cout << FloydList.ShortestMap[i][j] << "\t";
				}
			}
			cout << endl;
		}*/

		cout << "继续查询请输入1，否则请输入0：";
		cin >> f;
		cout << endl << endl;
		if (!f)
		{
			break;
		}
	}
	cout << "感谢您的使用！" << endl << endl;


	system("pause");
	return FloydList;
}