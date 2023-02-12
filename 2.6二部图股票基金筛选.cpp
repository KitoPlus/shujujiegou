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
#include <iomanip>
#include <time.h>
#include <conio.h>
#include "顺序表读入.cpp"
#include "2.4股票相关性分析.cpp"
using namespace libxl;
using namespace std;

extern int color[11];//染色标志数组，未染色为0，红色为1，蓝色为2（1~10）

inline void Floyd3(MatGraph MG, int SM[][61])
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
	for (i = 1; i <= MG.n; i++)
	{
		for (j = 1; j <= MG.n; j++)
		{
			*(SM[i] + j) = A[i][j];
		}
	}
}

inline bool dfs(int node[][11], int v, int c)
{
	color[v] = c;					//为当前顶点上色
	for (int i = 1; i < 11; ++i)
	{
		//遍历所有与之连接的顶点，即相邻顶点
		if (node[v][i])				//如果相邻的顶点同色，就返回false
		{
			if (color[i] == c)
			{
				return false;
			}
			else if (color[i] == 0)//如果相邻顶点未染色，就将其染为相反颜色即3-c，并继续dfs
			{
				color[i] = 3 - c;
				if (!dfs(node, i, color[i]))
				{
					return false;		//返回false
				}
			}
		}
	}
	return true;		//直到所有顶点都被染色，且没出现相邻同色顶点，就返回true
}

inline void BipartFundation()
{
	int i, j;
	MatGraph BiGraph;
	
	Stock60III* gp60 = new Stock60III[60];
	RelationI* Map83 = new RelationI[83];
	Excel1(gp60);//读入点值信息
	Excel2(Map83);//读入路径信息
	//MatGraph FloydList;
	BiGraph.n = 60;
	BiGraph.e = 83;
	for (i = 1; i <= 60; i++)//初始化邻接矩阵
	{
		for (j = 1; j <= 60; j++)
		{
			BiGraph.adjMat[i][j] = N;
		}
		BiGraph.ver[i] = gp60[i - 1];
	}
	for (i = 0; i < 83; i++)//读入权值
	{
		BiGraph.adjMat[Map83[i].Point1][Map83[i].Point2] = Map83[i].Weight;
		//cout << Map83[i].Point1 << " " << Map83[i].Point2 << " " << Map83[i].Weight << " " << FloydList.adjMat[Map83[i].Point1][Map83[i].Point2] << endl;
	}
	for (i = 1; i < 61; i++)//有向图转无向图
	{
		for (j = 1; j < 61; j++)
		{
			if (BiGraph.adjMat[i][j] == 5000)
			{
				BiGraph.adjMat[i][j] = BiGraph.adjMat[j][i];
			}
		}
	}
	int f;
	for (i = 1; i < 61; i++)
	{
		for (j = 1; j < 61; j++)
		{
			BiGraph.ShortestMap[i][j] = 0;
		}
	}
	//for (i = 1; i <= 60; i++)
	//{
	//	for (j = 1; j <= 60; j++)
	//	{
	//		if (PrimGraph.ShortestMap[i][j] != 5000)
	//		{
	//			cout << i << "：" << PrimGraph.ShortestMap[i][j] << endl;
	//		}
	//	}
	//	//cout << endl;
	//}
	/*for (i = 1; i < 61; i++)
	{
		int min = 5000;
		for (j = 1; j < 61; j++)
		{
			if (PrimGraph.ShortestMap[i][j] < min)
			{
				min = PrimGraph.ShortestMap[i][j];
			}
		}
		cout << i << "：" << min << endl;
	}*/
	/*for (i = 1; i < 61; i++)
	{
		for (j = 1; j < 61; j++)
		{
			smalltree[i][j] = 5000;
		}
	}*/
	Floyd3(BiGraph, BiGraph.ShortestMap);

	int user[11][11];
	for (i = 0; i < 11; i++)//初始化待判断数组和染色标志数组
	{
		for (j = 0; j < 11; j++)
		{
			user[i][j] = 0;
		}
		color[i] = 0;
	}
	while (1)
	{
		int flag = 1;
		system("cls");
		cout << "请输入十个点，点的范围是1~60，中间用回车隔开：" << endl;
		for (i = 1; i < 11; i++)
		{
			cin >> user[0][i];
			user[i][0] = user[0][i];
			if (user[0][i] > 60 || user[0][i] < 1)
			{
				flag = 0;
			}
		}
		if (flag)
		{
			for (i = 1; i < 11; i++)//建立关联矩阵
			{
				for (j = 1; j < 11; j++)
				{
					if (BiGraph.adjMat[user[0][i]][user[j][0]] != 5000)
					{
						user[i][j] = 1;
						user[j][i] = 1;
						//cout << user[i][j] << endl;
					}
				}
			}
			//system("pause");
			/*for (i = 0; i < 11; i++)
			{
				for (j = 0; j < 11; j++)
				{
					cout << user[i][j] << "\t";
				}
				cout << endl;
			}*/
			system("cls");
			if (dfs(user, 1, 1))
			{
				for (i = 1; i < 11; i++)
				{
					if (color[i] == 0)
					{
						color[i] = 1;
					}
				}
				cout << "可以构成二部图！" << endl;
				cout << endl<< "第一组节点信息如下：" << endl;
				for (i = 1; i < 11; i++)
				{
					if (color[i] == 1)
					{
						cout << user[0][i] << "：" << "\t" << BiGraph.ver[user[0][i]].Name60III << endl;
					}
					//cout << color[i] << endl;
				}
				cout << endl<< "第二组节点信息如下：" << endl;
				for (i = 1; i < 11; i++)
				{
					if (color[i] == 2)
					{
						cout << user[0][i] << "：" << "\t" << BiGraph.ver[user[0][i]].Name60III << endl;
					}
				}
			}
			else
			{
				cout << "不能构成二部图！" << endl;
			}
		}
		else
		{
			cout << endl << "您输入了有误点！" << endl;
		}
		cout << endl << "继续查询请输入1，退出请输入0：";
		cin >> flag;
		if (!flag)
		{
			break;
		}
	}
	cout << endl << "感谢您的使用！" << endl;

	system("pause");
}