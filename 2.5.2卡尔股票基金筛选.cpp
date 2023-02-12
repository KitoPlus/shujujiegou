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
#include "˳������.cpp"
#include "2.4��Ʊ����Է���.cpp"
using namespace libxl;
using namespace std;

extern int smalltree[61][61];

struct Node  //��Ϊ���ݽṹ�洢ͼ
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
				path[i][j] = i;							//���� i ������ j �б�ʱ
			}
			else
			{
				path[i][j] = -1;						//���� i ������ j �ޱ�ʱ
			}
		}
	}
	for (k = 1; k <= MG.n; k++)
	{						//һ�ο������ж���
		for (i = 1; i <= MG.n; i++)
		{
			for (j = 1; j <= MG.n; j++)
			{
				if (A[i][j] > A[i][k] + A[k][j])        //A���ڽӾ���
				{
					A[i][j] = A[i][k] + A[k][j];		//�޸����·������
					path[i][j] = path[k][j];			//�޸����·��
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
	cout << "��С������ȨֵΪ:";
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
	Excel1(gp60);//�����ֵ��Ϣ
	Excel2(Map83);//����·����Ϣ
	//MatGraph FloydList;
	KrusGraph.n = 60;
	KrusGraph.e = 83;
	for (i = 1; i <= 60; i++)//��ʼ���ڽӾ���
	{
		for (j = 1; j <= 60; j++)
		{
			KrusGraph.adjMat[i][j] = N;
		}
		KrusGraph.ver[i] = gp60[i - 1];
	}
	for (i = 0; i < 83; i++)//����Ȩֵ
	{
		KrusGraph.adjMat[Map83[i].Point1][Map83[i].Point2] = Map83[i].Weight;
		//cout << Map83[i].Point1 << " " << Map83[i].Point2 << " " << Map83[i].Weight << " " << FloydList.adjMat[Map83[i].Point1][Map83[i].Point2] << endl;
	}
	for (i = 1; i < 61; i++)//����ͼת����ͼ
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
	//			cout << i << "��" << PrimGraph.ShortestMap[i][j] << endl;
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
		cout << i << "��" << min << endl;
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
	//			cout << i << "��" << PrimGraph.ShortestMap[i][j] << endl;
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
		cout << i << "��" << min << endl;
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
	{//ֻ����ȨֵΪ2��
		for (i = 1; i < 11; i++)
		{//��������Ϊ��������
			double p1, p2;//��ʱ�����������������Ϣ
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
	cout << "����ϵͳ�������Ϊ���Ƽ����»����飺" << endl << endl;
	int cnt = 2;
	for (i = 0; i < 12; i++)
	{
		if (cnt == 6)
		{
			break;
		}
		cout << "��ض�" << i + 1 << "��" << KrusMap[i].Weight << "\t" << "��Ʊ1��" << KrusGraph.ver[KrusMap[i].Point1].Name60III << "\t\t" << "��Ʊ2��" << KrusGraph.ver[KrusMap[i].Point2].Name60III << endl;
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
	cout << endl << "��������������ο�����Ʊǧ������������һ����Ͷ�ʲ����ǣ����������ᡣף������˳����" << endl;

	system("pause");
}