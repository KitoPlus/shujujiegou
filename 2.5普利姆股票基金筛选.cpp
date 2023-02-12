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

extern bool visit[61];
extern int dist[61];
extern int smalltree[61][61];

inline void Floyd1(MatGraph MG, int SM[][61])
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

inline void Prim(MatGraph g, int cur)//ѡ�㷨����С������
{
    int index = cur;
    int sum = 0;
    int i = 0;
    int j = 0;
    //cout << index << " ";
    memset(visit, false, sizeof(visit));
    visit[cur] = true;
    //cout << cur;
    for (i = 1; i < 61; i++)
    {
        dist[i] = 5000;
        //cout << g.ShortestMap[cur][i] << endl;
    }
    for (i = 1; i < 61; i++)
    {
        for (j = 1; j < 61; j++)
        {
            dist[j] = g.ShortestMap[index][j];//��ʼ����ÿ����a�ڽӵĵ�ľ������dist
            //cout << dist[i] << endl;
        }
        int ks = index;
        int minor = 5000;
        for (j = 1; j < 61; j++)
        {
            if (!visit[j] && dist[j] < minor)          //�ҵ�δ���ʵĵ��У����뵱ǰ��С������������С�ĵ�
            {
                minor = dist[j];
                index = j;
            }
        }
        visit[index] = true;
        //cout << index << " ";
        smalltree[ks][index] = minor;
        sum += minor;
        //cout << sum << endl;
        for (j = 1; j < 61; j++)
        {
            if (!visit[j] && dist[j] > g.ShortestMap[index][j+1])      //ִ�и��£��������뵱ǰ��ľ���������͸���dist
            {
                dist[j] = g.ShortestMap[index][j+1];
            }
        }
    }
    //cout << endl;
    sum -= 5000;
    //return sum;               //������С����������·��ֵ
}

inline void PrimFundation()
{
	int i, j;
    RelationI* PrimMap = new RelationI[59];
	MatGraph PrimGraph;

    Stock60III* gp60 = new Stock60III[60];
    RelationI* Map83 = new RelationI[83];
    Excel1(gp60);//�����ֵ��Ϣ
    Excel2(Map83);//����·����Ϣ
    //MatGraph FloydList;
    PrimGraph.n = 60;
    PrimGraph.e = 83;
    for (i = 1; i <= 60; i++)//��ʼ���ڽӾ���
    {
        for (j = 1; j <= 60; j++)
        {
            PrimGraph.adjMat[i][j] = N;
        }
        PrimGraph.ver[i] = gp60[i - 1];
    }
    for (i = 0; i < 83; i++)//����Ȩֵ
    {
        PrimGraph.adjMat[Map83[i].Point1][Map83[i].Point2] = Map83[i].Weight;
        //cout << Map83[i].Point1 << " " << Map83[i].Point2 << " " << Map83[i].Weight << " " << FloydList.adjMat[Map83[i].Point1][Map83[i].Point2] << endl;
    }
    for (i = 1; i < 61; i++)//����ͼת����ͼ
    {
        for (j = 1; j < 61; j++)
        {
            if (PrimGraph.adjMat[i][j] == 5000)
            {
                PrimGraph.adjMat[i][j] = PrimGraph.adjMat[j][i];
            }
        }
    }
    int f;
    for (i = 1; i < 61; i++)//��ʼ��
    {
        for (j = 1; j < 61; j++)
        {
            PrimGraph.ShortestMap[i][j] = 0;
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
    Floyd1(PrimGraph, PrimGraph.ShortestMap);

    Prim(PrimGraph, 1);
    int fff = 0;
    for (i = 1; i < 61; i++)
    {
        for (j = 1; j < 61; j++)
        {
            if (smalltree[i][j] != 5000)
            {
                PrimMap[fff].Point1 = i;
                PrimMap[fff].Point2 = j;
                PrimMap[fff].Weight = smalltree[i][j];
                fff++;
                //cout << smalltree[i][j] << endl;
            }
        }
    }
    /*for (i = 0; i < 59; i++)
    {
        cout << PrimMap[i].Weight << endl;
    }*/
    for (i = 0; i < 59; i++)
    {
        for (j = 0; j < 59; j++)
        {
            if (PrimMap[j].Weight > PrimMap[i].Weight)
            {
                swap(PrimMap[j], PrimMap[i]);
            }
        }
    }
    for (int k = 1; k < 12; k++)
    {
        for (i = 1; i < 11; i++)
        {//��������Ϊ��������
            double p1, p2;//��ʱ�����������������Ϣ
            for (j = 1; j < 61; j++)
            {
                if (PrimMap[i].Point1 == PrimGraph.ver[j].PointIII)
                {
                    p1 = PrimGraph.ver[j].ScoreIII;
                }
                if (PrimMap[i + 1].Point1 == PrimGraph.ver[j].PointIII)
                {
                    p2 = PrimGraph.ver[j].ScoreIII;
                }
            }
            if (p1 < p2)
            {
                swap(PrimMap[i], PrimMap[i + 1]);
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
        cout << "��ض�" << i+1 << "��" << PrimMap[i].Weight << "\t" << "��Ʊ1��" << PrimGraph.ver[PrimMap[i].Point1].Name60III << "\t\t" << "��Ʊ2��" << PrimGraph.ver[PrimMap[i].Point2].Name60III << endl;
        if (i > 0)
        {
            if ((PrimGraph.ver[PrimMap[i].Point1].Name60III != PrimGraph.ver[PrimMap[i - 1].Point1].Name60III) && (PrimGraph.ver[PrimMap[i].Point1].Name60III != PrimGraph.ver[PrimMap[i - 1].Point2].Name60III))
            {
                cnt++;
            }
            if ((PrimGraph.ver[PrimMap[i].Point2].Name60III != PrimGraph.ver[PrimMap[i - 1].Point1].Name60III) && (PrimGraph.ver[PrimMap[i].Point2].Name60III != PrimGraph.ver[PrimMap[i - 1].Point2].Name60III))
            {
                cnt++;
            }
        }
    }
    cout << endl << "��������������ο�����Ʊǧ������������һ����Ͷ�ʲ����ǣ����������ᡣף������˳����" << endl;
    

	system("pause");
    //return 0;
}