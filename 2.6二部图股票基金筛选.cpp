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

extern int color[11];//Ⱦɫ��־���飬δȾɫΪ0����ɫΪ1����ɫΪ2��1~10��

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

inline bool dfs(int node[][11], int v, int c)
{
	color[v] = c;					//Ϊ��ǰ������ɫ
	for (int i = 1; i < 11; ++i)
	{
		//����������֮���ӵĶ��㣬�����ڶ���
		if (node[v][i])				//������ڵĶ���ͬɫ���ͷ���false
		{
			if (color[i] == c)
			{
				return false;
			}
			else if (color[i] == 0)//������ڶ���δȾɫ���ͽ���ȾΪ�෴��ɫ��3-c��������dfs
			{
				color[i] = 3 - c;
				if (!dfs(node, i, color[i]))
				{
					return false;		//����false
				}
			}
		}
	}
	return true;		//ֱ�����ж��㶼��Ⱦɫ����û��������ͬɫ���㣬�ͷ���true
}

inline void BipartFundation()
{
	int i, j;
	MatGraph BiGraph;
	
	Stock60III* gp60 = new Stock60III[60];
	RelationI* Map83 = new RelationI[83];
	Excel1(gp60);//�����ֵ��Ϣ
	Excel2(Map83);//����·����Ϣ
	//MatGraph FloydList;
	BiGraph.n = 60;
	BiGraph.e = 83;
	for (i = 1; i <= 60; i++)//��ʼ���ڽӾ���
	{
		for (j = 1; j <= 60; j++)
		{
			BiGraph.adjMat[i][j] = N;
		}
		BiGraph.ver[i] = gp60[i - 1];
	}
	for (i = 0; i < 83; i++)//����Ȩֵ
	{
		BiGraph.adjMat[Map83[i].Point1][Map83[i].Point2] = Map83[i].Weight;
		//cout << Map83[i].Point1 << " " << Map83[i].Point2 << " " << Map83[i].Weight << " " << FloydList.adjMat[Map83[i].Point1][Map83[i].Point2] << endl;
	}
	for (i = 1; i < 61; i++)//����ͼת����ͼ
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
	/*for (i = 1; i < 61; i++)
	{
		for (j = 1; j < 61; j++)
		{
			smalltree[i][j] = 5000;
		}
	}*/
	Floyd3(BiGraph, BiGraph.ShortestMap);

	int user[11][11];
	for (i = 0; i < 11; i++)//��ʼ�����ж������Ⱦɫ��־����
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
		cout << "������ʮ���㣬��ķ�Χ��1~60���м��ûس�������" << endl;
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
			for (i = 1; i < 11; i++)//������������
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
				cout << "���Թ��ɶ���ͼ��" << endl;
				cout << endl<< "��һ��ڵ���Ϣ���£�" << endl;
				for (i = 1; i < 11; i++)
				{
					if (color[i] == 1)
					{
						cout << user[0][i] << "��" << "\t" << BiGraph.ver[user[0][i]].Name60III << endl;
					}
					//cout << color[i] << endl;
				}
				cout << endl<< "�ڶ���ڵ���Ϣ���£�" << endl;
				for (i = 1; i < 11; i++)
				{
					if (color[i] == 2)
					{
						cout << user[0][i] << "��" << "\t" << BiGraph.ver[user[0][i]].Name60III << endl;
					}
				}
			}
			else
			{
				cout << "���ܹ��ɶ���ͼ��" << endl;
			}
		}
		else
		{
			cout << endl << "������������㣡" << endl;
		}
		cout << endl << "������ѯ������1���˳�������0��";
		cin >> flag;
		if (!flag)
		{
			break;
		}
	}
	cout << endl << "��л����ʹ�ã�" << endl;

	system("pause");
}