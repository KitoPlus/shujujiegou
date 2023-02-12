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

inline void Prim(MatGraph g, int cur)//选点法找最小生成树
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
            dist[j] = g.ShortestMap[index][j];//初始化，每个与a邻接的点的距离存入dist
            //cout << dist[i] << endl;
        }
        int ks = index;
        int minor = 5000;
        for (j = 1; j < 61; j++)
        {
            if (!visit[j] && dist[j] < minor)          //找到未访问的点中，距离当前最小生成树距离最小的点
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
            if (!visit[j] && dist[j] > g.ShortestMap[index][j+1])      //执行更新，如果点距离当前点的距离更近，就更新dist
            {
                dist[j] = g.ShortestMap[index][j+1];
            }
        }
    }
    //cout << endl;
    sum -= 5000;
    //return sum;               //返回最小生成树的总路径值
}

inline void PrimFundation()
{
	int i, j;
    RelationI* PrimMap = new RelationI[59];
	MatGraph PrimGraph;

    Stock60III* gp60 = new Stock60III[60];
    RelationI* Map83 = new RelationI[83];
    Excel1(gp60);//读入点值信息
    Excel2(Map83);//读入路径信息
    //MatGraph FloydList;
    PrimGraph.n = 60;
    PrimGraph.e = 83;
    for (i = 1; i <= 60; i++)//初始化邻接矩阵
    {
        for (j = 1; j <= 60; j++)
        {
            PrimGraph.adjMat[i][j] = N;
        }
        PrimGraph.ver[i] = gp60[i - 1];
    }
    for (i = 0; i < 83; i++)//读入权值
    {
        PrimGraph.adjMat[Map83[i].Point1][Map83[i].Point2] = Map83[i].Weight;
        //cout << Map83[i].Point1 << " " << Map83[i].Point2 << " " << Map83[i].Weight << " " << FloydList.adjMat[Map83[i].Point1][Map83[i].Point2] << endl;
    }
    for (i = 1; i < 61; i++)//有向图转无向图
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
    for (i = 1; i < 61; i++)//初始化
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
        {//以评分作为二级依据
            double p1, p2;//临时接收两个点的评分信息
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
    cout << "根据系统分析结果为您推荐以下基金组：" << endl << endl;
    int cnt = 2;
    for (i = 0; i < 12; i++)
    {
        if (cnt == 6)
        {
            break;
        }
        cout << "相关度" << i+1 << "：" << PrimMap[i].Weight << "\t" << "股票1：" << PrimGraph.ver[PrimMap[i].Point1].Name60III << "\t\t" << "股票2：" << PrimGraph.ver[PrimMap[i].Point2].Name60III << endl;
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
    cout << endl << "本分析结果仅供参考。股票千万条，谨慎第一条，投资不理智，亲人两行泪。祝您生意顺利！" << endl;
    

	system("pause");
    //return 0;
}