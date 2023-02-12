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

extern int smalltree[61][61];

struct Node  //作为数据结构存储图
{
	int start;
	int end;
	int length;
};

inline void Floyd2(MatGraph MG, int SM[][61])
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

inline int Kruskal(Node* arr, bool* visited)
{
	int a, b;
	a = 0;
	b = 166;
	int weight = 0;
	for (int i = 0; i < 166; i++)
	{
		if (!visited[arr[i].start] || !visited[arr[i].end])
		{
			weight += arr[i].length;
			visited[arr[i].start] = true;
			visited[arr[i].end] = true;
			smalltree[arr[i].start][arr[i].end] = arr[i].length;
			a++;
			//cout << a++;
		}
	}
	cout << "最小生成树权值为:";
	cout << weight << endl;
	return a;
}

inline void KrukalFundation()
{
	int i, j;
	int how;
	bool visited[61];
	RelationI* KrusMap = new RelationI[59];
	MatGraph KrusGraph;
	
	Stock60III* gp60 = new Stock60III[60];
	RelationI* Map83 = new RelationI[83];
	Excel1(gp60);//读入点值信息
	Excel2(Map83);//读入路径信息
	//MatGraph FloydList;
	KrusGraph.n = 60;
	KrusGraph.e = 83;
	for (i = 1; i <= 60; i++)//初始化邻接矩阵
	{
		for (j = 1; j <= 60; j++)
		{
			KrusGraph.adjMat[i][j] = N;
		}
		KrusGraph.ver[i] = gp60[i - 1];
	}
	for (i = 0; i < 83; i++)//读入权值
	{
		KrusGraph.adjMat[Map83[i].Point1][Map83[i].Point2] = Map83[i].Weight;
		//cout << Map83[i].Point1 << " " << Map83[i].Point2 << " " << Map83[i].Weight << " " << FloydList.adjMat[Map83[i].Point1][Map83[i].Point2] << endl;
	}
	for (i = 1; i < 61; i++)//有向图转无向图
	{
		for (j = 1; j < 61; j++)
		{
			if (KrusGraph.adjMat[i][j] == 5000)
			{
				KrusGraph.adjMat[i][j] = KrusGraph.adjMat[j][i];
			}
		}
	}
	int f;
	for (i = 1; i < 61; i++)
	{
		for (j = 1; j < 61; j++)
		{
			KrusGraph.ShortestMap[i][j] = 0;
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
	for (i = 1; i < 61; i++)
	{
		for (j = 1; j < 61; j++)
		{
			smalltree[i][j] = 5000;
		}
	}
	Floyd2(KrusGraph, KrusGraph.ShortestMap);

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
	int num = 0;
	for (i = 1; i < 61; i++)
	{
		for (j = 1; j < 61; j++)
		{
			smalltree[i][j] = 5000;
		}
		visited[i] = 0;
	}
	Node* edges = new Node[166];
	int n = 0;
	for (i = 1; i < 61; i++)
	{
		for (j = 1; j < 61; j++)
		{
			if (KrusGraph.adjMat[i][j] != 5000)
			{
				edges[n].start = i;
				edges[n].end = j;
				edges[n].length = KrusGraph.adjMat[i][j];
				n++;
			}
		}
	}
	//cout << n;
	for (i = 0; i < 166; i++)
	{
		for (j = 0; j < 166; j++)
		{
			if (edges[i].length < edges[j].length)
			{
				swap(edges[i], edges[j]);
			}
		}
	}
	/*for (i = 0; i < 3600; i++)
	{
		cout << edges[i].length << endl;
	}*/
	how = Kruskal(edges, visited);
	//cout << how;
	/*for (i = 1; i < 61; i++)
	{
		cout << visited[i];
	}*/
	int fff = 0;
	for (i = 1; i < 61; i++)
	{
		for (j = 1; j < 61; j++)
		{
			if (smalltree[i][j] != 5000)
			{
				KrusMap[fff].Point1 = i;
				KrusMap[fff].Point2 = j;
				KrusMap[fff].Weight = smalltree[i][j];
				fff++;
				//cout << smalltree[i][j] << endl;
			}
		}
	}
	//cout << fff;
	
	for (i = 0; i < how; i++)
	{
		for (j = 0; j < how; j++)
		{
			if (KrusMap[j].Weight > KrusMap[i].Weight)
			{
				swap(KrusMap[j], KrusMap[i]);
			}
		}
	}
	/*for (i = 0; i < how; i++)
	{
		cout << KrusMap[i].Weight << endl;
	}*/
	for (int k = 1; k < 12; k++)
	{//只排了权值为2的
		for (i = 1; i < 11; i++)
		{//以评分作为二级依据
			double p1, p2;//临时接收两个点的评分信息
			for (j = 1; j < 61; j++)
			{
				if (KrusMap[i].Point1 == KrusGraph.ver[j].PointIII)
				{
					p1 = KrusGraph.ver[j].ScoreIII;
				}
				if (KrusMap[i + 1].Point1 == KrusGraph.ver[j].PointIII)
				{
					p2 = KrusGraph.ver[j].ScoreIII;
				}
			}
			//cout << p1 << " " << p2 << endl;
			if (p1 < p2)
			{
				swap(KrusMap[i], KrusMap[i + 1]);
			}
		}
	}
	system("cls");
	cout << "根据系统分析结果为您推荐以下基金组：" << endl << endl;
	int cnt = 2;
	for (i = 0; i < 12; i++)
	{
		if (cnt == 6)
		{
			break;
		}
		cout << "相关度" << i + 1 << "：" << KrusMap[i].Weight << "\t" << "股票1：" << KrusGraph.ver[KrusMap[i].Point1].Name60III << "\t\t" << "股票2：" << KrusGraph.ver[KrusMap[i].Point2].Name60III << endl;
		if (i > 0)
		{
			if ((KrusGraph.ver[KrusMap[i].Point1].Name60III != KrusGraph.ver[KrusMap[i - 1].Point1].Name60III) && (KrusGraph.ver[KrusMap[i].Point1].Name60III != KrusGraph.ver[KrusMap[i - 1].Point2].Name60III))
			{
				cnt++;
			}
			if ((KrusGraph.ver[KrusMap[i].Point2].Name60III != KrusGraph.ver[KrusMap[i - 1].Point1].Name60III) && (KrusGraph.ver[KrusMap[i].Point2].Name60III != KrusGraph.ver[KrusMap[i - 1].Point2].Name60III))
			{
				cnt++;
			}
		}
	}
	cout << endl << "本分析结果仅供参考。股票千万条，谨慎第一条，投资不理智，亲人两行泪。祝您生意顺利！" << endl;

	system("pause");
}