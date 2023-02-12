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

typedef struct StockIV//����ṹ��
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
	//string Number;//��Ʊ����
	//string BriefName;//��Ʊ���
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
��ȡexcelָ�����ݲ�����ڿ���̨��ע�����ڹر�.xlsx�ļ�����������
***/

//const wchar_t*   ��һ��ָ����ַ����͵�ָ�룬���ָ��ָ��������Ǹ����������ܸı�

//char* w2c(char* pcstr, const wchar_t* pwstr, size_t len)//�˺���֧�����Ķ�ȡ����ʾ����������������������
//{
//	int nlength = wcslen(pwstr);//��ȡת����ĳ���
//
//	int nbytes = WideCharToMultiByte(0, 0, pwstr, nlength, NULL, 0, NULL, NULL); //ӳ��һ��unicode�ַ�����һ�����ֽ��ַ���
//
//	if (nbytes > len)   nbytes = len;
//	// ͨ�����ϵõ��Ľ����ת��unicode �ַ�Ϊascii �ַ�
//	WideCharToMultiByte(0, 0, pwstr, nlength, pcstr, nbytes, NULL, NULL);
//
//	return pcstr;
//}

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

inline void Excel(Stock60I* gp60)
{
	

	Book* book = xlCreateXMLBook();//����һ��XLSX��ʵ��,��ʹ��ǰ�����ȵ������������������excel�Ķ���

	book->setKey(L"TommoT", L"windows-2421220b07c2e10a6eb96768a2p7r6gc");//������Ӧ��key������ع���(����)�����򴴽�book�޷��ɹ�

	if (book->load(L"60֧��Ʊ��Ϣ.xlsx"))//�ļ����빤��Ŀ¼��
	{
		Sheet* sheetread = book->getSheet(1);//ѡȡ��һ����

		if (sheetread)
		{
			for (int row = sheetread->firstRow()+1; row < sheetread->lastRow(); ++row)//�б���
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
							gp60[row-1].Name60I = pcstr;
						}
						if (col == 2)
						{
							gp60[row - 1].Number60I = pcstr;
						}

						free(pcstr);

					}
					else if (celltype == CELLTYPE_NUMBER)//���ÿ����Ԫ������Ϊ��ֵ����
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

	//����׼temp�����Լ���λ�ã�����i��λ�ã�
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
			//cout << list[1].Date << endl << list[1].StartPrice << endl << list[1].EndPrice << endl << list[1].HighPrice << endl << list[1].LowPrice << endl << list[1].BargainNum << endl << list[1].BargainTotalPrice << endl << list[1].ExchangeRate << endl << list[1].ChangeAmount << endl << list[1].ChangeRate << endl;
			//cout << "����1������ѯ������0�˳���";
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
	cout << "�������ѯ��ҵ��";
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
	

	Book* book = xlCreateXMLBook();//����һ��XLSX��ʵ��,��ʹ��ǰ�����ȵ������������������excel�Ķ���

	book->setKey(L"TommoT", L"windows-2421220b07c2e10a6eb96768a2p7r6gc");//�����û�ע����Ϣ���Ƿ��������������֤�������һ���޷�����

	if (book)
	{

		Sheet* sheetwrite = book->addSheet(L"sheet1");;//���ɵ�һ����

		if (sheetwrite)
		{
			int m, n;
			m = nnnn;
			n = 5;
			string label[5];
			label[0] = "���";
			label[1] = "��Ʊ����";
			label[2] = "��Ʊ����";
			label[3] = "�ǵ���";
			label[4] = "����";
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
		if (book->save(L"һ����ҵ���ǵ�������.xlsx"))
		{
			//::ShellExecute(NULL, "open", "example.xls", NULL, NULL, SW_SHOW);
			cout << "һ����ҵ���ǵ������������ɣ�" << endl;
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