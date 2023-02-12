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

typedef struct StockV//����ṹ��
{
	char Date[9];//����
	char StartPrice[10];//���̼�
	char EndPrice[10];//���̼�
	char HighPrice[10];//��߼�
	char LowPrice[10];//��ͼ�
	char BargainNum[15];//�ɽ���
	char BargainTotalPrice[10];//�ɽ���
	char ExchangeRate[10];//������
	char ChangeAmount[10];//�ǵ���
	char ChangeRate[10];//�ǵ���
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
//	//��һ�ε��÷���ת������ַ������ȣ�����ȷ��Ϊwchar_t*���ٶ����ڴ�ռ�
//	int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
//	wchar_t* pWCStrKey = new wchar_t[pSize];
//	//�ڶ��ε��ý����ֽ��ַ���ת����˫�ֽ��ַ���
//	MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, pWCStrKey, pSize);
//	return pWCStrKey;
//}

inline void Excel(Stock60II* gp60)
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
							gp60[row - 1].Name60II = pcstr;
						}
						if (col == 2)
						{
							gp60[row - 1].Number60II = pcstr;
						}

						free(pcstr);

					}
					else if (celltype == CELLTYPE_NUMBER)//���ÿ����Ԫ������Ϊ��ֵ����
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
	Book* book = xlCreateXMLBook();//����һ��XLSX��ʵ��,��ʹ��ǰ�����ȵ������������������excel�Ķ���

	book->setKey(L"TommoT", L"windows-2421220b07c2e10a6eb96768a2p7r6gc");//�����û�ע����Ϣ���Ƿ��������������֤�������һ���޷�����

	if (book)
	{

		Sheet* sheetwrite = book->addSheet(L"sheet1");;//���ɵ�һ����

		if (sheetwrite)
		{
			int m, n;
			m = 61;
			n = 4;
			string label[4];
			label[0] = "���";
			label[1] = "��Ʊ����";
			label[2] = "��Ʊ����";
			label[3] = "����";
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
		if (book->save(L"2-3��������.xlsx"))
		{
			//::ShellExecute(NULL, "open", "example.xls", NULL, NULL, SW_SHOW);
			cout << "2-3�������������ɣ�" << endl;
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
			printf("������ִ���\n");
			//return 0;
		}
		else
		{
			fseek(fs, 88, SEEK_SET);//����ָ��λ��
			for (i = 0; i < M; i++)//�ļ���ȡ 
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
				if (feof(fs) != 0)	break;//�ж��Ƿ��ȡ��� 
			}
			fclose(fs);
			//cout << list[1].Date << endl << list[1].StartPrice << endl << list[1].EndPrice << endl << list[1].HighPrice << endl << list[1].LowPrice << endl << list[1].BargainNum << endl << list[1].BargainTotalPrice << endl << list[1].ExchangeRate << endl << list[1].ChangeAmount << endl << list[1].ChangeRate << endl;
			//cout << "����1������ѯ������0�˳���";
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
	Book* book1 = xlCreateXMLBook();//����һ��XLSX��ʵ��,��ʹ��ǰ�����ȵ������������������excel�Ķ���

	book1->setKey(L"TommoT", L"windows-2421220b07c2e10a6eb96768a2p7r6gc");//�����û�ע����Ϣ���Ƿ��������������֤�������һ���޷�����

	if (book1)
	{

		Sheet* sheetwrite = book1->addSheet(L"sheet1");;//���ɵ�һ����

		if (sheetwrite)
		{
			int m, n;
			m = 61;
			n = 4;
			string label[4];
			label[0] = "���";
			label[1] = "��Ʊ����";
			label[2] = "��Ʊ����";
			label[3] = "���̼�";
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
		if (book1->save(L"2-3���̼�����.xlsx"))
		{
			//::ShellExecute(NULL, "open", "example.xls", NULL, NULL, SW_SHOW);
			cout << "2-3���̼����������ɣ�" << endl;
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