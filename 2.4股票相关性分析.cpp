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
#include "˳������.cpp"
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
	int n;						//�������
	int e;						//���� 
	int adjMat[61][61];		//�ڽӾ�������			
	Stock60III ver[61];		//��Ŷ�����Ϣ 
	int ShortestMap[61][61];   //���·����
}MatGraph;						//������������ͼ�ڽӾ�������

//inline wchar_t* StringToWchar(const string& pKey)
//{
//	const char* pCStrKey = pKey.c_str();
//	//��һ�ε��÷���ת������ַ������ȣ�����ȷ��Ϊwchar_t*���ٶ����ڴ�ռ�
//	int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
//	wchar_t* pWCStrKey = new wchar_t[pSize];
//	//�ڶ��ε��ý����ֽ��ַ���ת����˫�ֽ��ַ���
//	MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, pWCStrKey, pSize);
//	return pWCStrKey;
//}

inline void Excel1(Stock60III* gp60)//�������ֺͱ����Ϣ
{


	Book* book = xlCreateXMLBook();//����һ��XLSX��ʵ��,��ʹ��ǰ�����ȵ������������������excel�Ķ���

	book->setKey(L"TommoT", L"windows-2421220b07c2e10a6eb96768a2p7r6gc");//������Ӧ��key������ع���(����)�����򴴽�book�޷��ɹ�

	if (book->load(L"60֧��Ʊ��Ϣ.xlsx"))//�ļ����빤��Ŀ¼��
	{
		Sheet* sheetread = book->getSheet(1);//ѡȡ��һ����

		if (sheetread)
		{
			for (int row = sheetread->firstRow() + 1; row < sheetread->lastRow(); ++row)//�б���
			{
				for (int col = sheetread->firstCol(); col < sheetread->lastCol(); ++col)//�б���
				{
					CellType celltype = sheetread->cellType(row, col);//��ȡĳ��ĳ�еĵ�Ԫ������͡����ַ����ͣ���ֵ�ͣ���ֵ��

					Format* format = sheetread->cellFormat(row, col);

					if (celltype == CELLTYPE_STRING)//���ÿ����Ԫ������Ϊ�ַ�������
					{
						const wchar_t* t = sheetread->readStr(row, col);//�ӵ�Ԫ���ж�ȡ�ַ��������ʽ

						char* pcstr = (char*)malloc(sizeof(char) * (2 * wcslen(t) + 1));//����ռ��С����Ŷ��������ݣ�wcslen()���������������t�ĳ���

						memset(pcstr, 0, 2 * wcslen(t) + 1);//��ʼ�������������������+1�Ŀռ�

						w2c(pcstr, t, 2 * wcslen(t) + 1); //pcstr�����ݶ�������Ҫ�������ı����ת�������Ϊת������

						if (col == 1)
						{
							//cout << pcstr << endl;//���
							gp60[row - 1].Name60III = pcstr;
						}
						if (col == 2)
						{
							gp60[row - 1].Number60III = pcstr;
						}

						free(pcstr);

					}
					else if (celltype == CELLTYPE_NUMBER)//���ÿ����Ԫ������Ϊ��ֵ����
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
					//else if (celltype == CELLTYPE_BLANK)//���ÿ����Ԫ������Ϊ�գ���ֵ�����ڵ�Ԫ����ʽ
					//{
					//	cout << "\t\t" << endl;
					//}
					//else if (celltype == CELLTYPE_EMPTY)//�����ڵ�Ԫ����ʽ
					//{
					//	cout << "\t\t" << endl;
					//}
				}
				//cout << endl;//ÿ�����ݻ��зָ����
			}
		}
		////����excel
		book->save(L"60֧��Ʊ��Ϣ.xlsx");

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


	Book* book = xlCreateXMLBook();//����һ��XLSX��ʵ��,��ʹ��ǰ�����ȵ������������������excel�Ķ���

	book->setKey(L"TommoT", L"windows-2421220b07c2e10a6eb96768a2p7r6gc");//������Ӧ��key������ع���(����)�����򴴽�book�޷��ɹ�

	if (book->load(L"60֧��Ʊ��Ϣ.xlsx"))//�ļ����빤��Ŀ¼��
	{
		Sheet* sheetread = book->getSheet(0);//ѡȡ��һ����

		if (sheetread)
		{
			for (int row = sheetread->firstRow() + 1; row < sheetread->lastRow(); ++row)//�б���
			{
				for (int col = sheetread->firstCol(); col < sheetread->lastCol(); ++col)//�б���
				{
					CellType celltype = sheetread->cellType(row, col);//��ȡĳ��ĳ�еĵ�Ԫ������͡����ַ����ͣ���ֵ�ͣ���ֵ��

					Format* format = sheetread->cellFormat(row, col);

					if (celltype == CELLTYPE_NUMBER)//���ÿ����Ԫ������Ϊ��ֵ����
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
				//cout << endl;//ÿ�����ݻ��зָ����
			}
		}
		////����excel
		book->save(L"60֧��Ʊ��Ϣ.xlsx");

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
	int aPath[61];										//���һ�����·��������
	int d;													//�������
	int flag = 0;
	for (i = 1; i < 61; i++)
	{
		for (j = 1; j < 61; j++)
		{
			if (A[a][b] != N)
			{//������ i �� ���� j ֮�����·��
				printf("�� %d �� %d �Ĺ�����ʽΪ��", a, b);
				k = path[a][b];
				d = 0;
				aPath[d] = b;								//·��������յ�
				while (k != -1 && k != a) {					//·��������м��
					d++;
					aPath[d] = k;
					k = path[a][k];
				}
				d++;
				aPath[d] = a;								//·����������
				printf("%d", aPath[d]);						//������
				for (s = d - 1; s >= 0; s--) {				//���·������������
					printf("->%d", aPath[s]);
				}
				printf("\t");
				printf("����Ʊ�����̶�Ϊ��%d\n\n", A[a][b]);
				flag = 1;
				return;
			}
		}
	}
	if (!flag)
	{
		cout << "��֧��Ʊ֮���޹����ԣ�" << endl << endl;
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
		cout << i << "��" << min << endl;
	}*/
	for (i = 1; i <= MG.n; i++)
	{
		for (j = 1; j <= MG.n; j++)
		{
			*(SM[i] + j) = A[i][j];
		}
	}
	displayPath(A, path, s, t);							//������·��
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
	Excel1(gp60);//�����ֵ��Ϣ
	Excel2(Map83);//����·����Ϣ
	MatGraph FloydList;
	FloydList.n = 60;
	FloydList.e = 83;
	for (i = 1; i <= 60; i++)//��ʼ���ڽӾ���
	{
		for (j = 1; j <= 60; j++)
		{
			FloydList.adjMat[i][j] = N;
		}
		FloydList.ver[i] = gp60[i - 1];
	}
	for (i = 0; i < 83; i++)//����Ȩֵ
	{
		FloydList.adjMat[Map83[i].Point1][Map83[i].Point2] = Map83[i].Weight;
		//cout << Map83[i].Point1 << " " << Map83[i].Point2 << " " << Map83[i].Weight << " " << FloydList.adjMat[Map83[i].Point1][Map83[i].Point2] << endl;
	}
	for (i = 1; i < 61; i++)//����ͼת����ͼ
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
		cout << "��������ֻ��Ʊ����ţ��м��ûس���������" << endl;
		cin >> temp1 >> temp2;
		/*temp1 = SearchPoint(gp60, str1);
		temp2 = SearchPoint(gp60, str2);*/
		if (temp1 == -1 || temp2 == -1)
		{
			cout << "��ϵͳ��ʱ�޷���������ֻ��Ʊ��" << endl << endl;
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
			cout << "����Ҫ��ѯ����ֻ��Ʊ��ŷֱ��ǣ�" << temp1 << " " << temp2 << endl;
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

		cout << "������ѯ������1������������0��";
		cin >> f;
		cout << endl << endl;
		if (!f)
		{
			break;
		}
	}
	cout << "��л����ʹ�ã�" << endl << endl;


	system("pause");
	return FloydList;
}