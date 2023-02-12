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

typedef struct StockIII//����ṹ��
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
	string Number;//��Ʊ����
	string BriefName;//��Ʊ���
};

typedef struct LNodeI
{
	StockIII* data;
	double userStartPrice;
	double userEndPrice;
	string userChangeRate;
	string StockNumber;
	string StockName;
	int dataLength;
	struct LNodeI* next;
}LNodeI, * linklistI;

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

inline void SortList(linklistI H,int c)
{
	linklistI p, q, r, s;
	if (H == NULL)
	{
		return;
	}
	p = H->next;
	H->next = NULL;//�����ͷ������
	switch (c)
	{
	case 1:
	{
		while (p)//ѭ��ʣ�µı�
		{
			r = p->next;
			q = H->next;
			s = H;
			while (q && p->userStartPrice < q->userStartPrice)
			{
				s = q;
				q = q->next;
			}
			p->next = q;
			s->next = p;
			s = p;
			p = r;
		}
		break;
	}
	case 2:
	{
		while (p)//ѭ��ʣ�µı�
		{
			r = p->next;
			q = H->next;
			s = H;
			while (q && p->userEndPrice < q->userEndPrice)
			{
				s = q;
				q = q->next;
			}
			p->next = q;
			s->next = p;
			s = p;
			p = r;
		}
		break;
	}
	case 3:
	{
		int i;
		while (p)//ѭ��ʣ�µı�
		{
			r = p->next;
			q = H->next;
			s = H;
			char temp1[10], temp2[10];
			double t1, t2;
			for (i = 0; p->userChangeRate[i] != '%'; i++)
			{
				temp1[i] = p->userChangeRate[i];
			}
			temp1[i] = '\0';
			t1 = atof(temp1);
			//cout << "t1 = " << t1 << endl;
			if (q)
			{
				for (i = 0; q->userChangeRate[i] != '%'; i++)
				{
					temp2[i] = q->userChangeRate[i];
				}
				temp2[i] = '\0';
				t2 = atof(temp2);
				//cout << "t2 = " << t2 << endl;
			}
			while (q && t1 < t2)
			{
				s = q;
				q = q->next;
				if (q)
				{
					for (i = 0; q->userChangeRate[i] != '%'; i++)
					{
						temp2[i] = q->userChangeRate[i];
					}
					temp2[i] = '\0';
					t2 = atof(temp2);
					//cout << "t2 = " << t2 << endl;
				}
			}
			p->next = q;
			s->next = p;
			s = p;
			p = r;
		}
		break;
	}
	}
	
}

inline void InsertSort()
{
	int i, j;
	struct Enterprise* B;
	B = list();
	linklistI L;
	L = new LNodeI;
	L->next = NULL;
	linklistI q = L;
	for (j = 0; j < 200; j++)
	{
		int n = 0;
		string number;
		StockIII* list = new StockIII[M];
		number = B[j].Number;
		number.append(".txt");
		FILE* fs = NULL, * fp = NULL;
		fs = fopen(number.c_str(), "r");
		if (fs == NULL)
		{
			printf("%s������ִ���\n",number);
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
		linklistI p = new LNodeI;
		p->data = list;
		//strcpy(p->StockName.c_str(), B[j].BriefName.c_str());
		p->StockName = B[j].BriefName;
		p->StockNumber = B[j].Number;
		p->dataLength = n;
		p->next = NULL;
		q->next = p;
		q = q->next;
		//cout << q->data[0].Date << endl << q->StockName << endl << q->StockNumber << endl << endl;
	}
	while (1)
	{
		int flag;
		system("cls");
		string userdate;
		cout << "�������ѯ���ڣ�";
		cin >> userdate;
		int ffflag = 0;
		if (strlen(userdate.c_str()) != 8)
		{
			cout << "���ڸ�ʽ����" << endl;
		}
		else
		{
			q = L->next;
			while (q)//���������Ϣ
			{
				int fflag = 0;
				for (i = 0; i < q->dataLength; i++)
				{
					if (!strcmp(q->data[i].Date, userdate.c_str()))
					{
						q->userStartPrice = atof(q->data[i].StartPrice);
						q->userEndPrice = atof(q->data[i].EndPrice);
						q->userChangeRate = q->data[i].ChangeRate;
						fflag = 1;
						ffflag = 1;
						break;
					}
				}
				if (!fflag)
				{
					q->userStartPrice = NULL;
					q->userEndPrice = NULL;
					q->userChangeRate = " ";
				}
				q = q->next;
			}
			if (!ffflag)
			{
				cout << "���޸�����Ϣ��" << endl;
			}
			else
			{
				int paixu;
				cout << "�������������ݣ�1 ���̼ۣ�2 ���̼ۣ�3 �ǵ�����";
				fflush(stdin);
				cin >> paixu;
				if (paixu == 1)
				{
					SortList(L, 1);
					/*q = L->next;
					while (q)
					{
						cout << q->userStartPrice << endl;
						q = q->next;
					}*/

					Book* book = xlCreateXMLBook();//����һ��XLSX��ʵ��,��ʹ��ǰ�����ȵ������������������excel�Ķ���

					book->setKey(L"TommoT", L"windows-2421220b07c2e10a6eb96768a2p7r6gc");//�����û�ע����Ϣ���Ƿ��������������֤�������һ���޷�����

					if (book) {

						Sheet* sheetwrite = book->addSheet(L"sheet1");;//���ɵ�һ����

						if (sheetwrite)
						{
							int m, n;

							m = 201;
							n = 6;

							string label[6];
							label[0] = "���";
							label[1] = "��Ʊ����";
							label[2] = "��Ʊ����";
							label[3] = "���̼ۣ���Ԫ��";
							label[4] = "���̼ۣ���Ԫ��";
							label[5] = "�ǵ���";
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

							q = L->next;
							for (int row = 1; row < m; ++row)//���б���
							{
								for (int col = 1; col < n; ++col)//���б���
								{

									string str;

									//cin >> str;
									switch (col)
									{
									case 1: str = q->StockNumber; break;
									case 2: str = q->StockName; break;
									case 3: str = to_string(q->userStartPrice); break;
									case 4: str = to_string(q->userEndPrice); break;
									case 5: str = q->userChangeRate; break;
									}
									wchar_t* wchar = StringToWchar(str);

									sheetwrite->writeStr(row, col, wchar);

									delete[]wchar;

								}
								q = q->next;
							}
						}
						////����excel
						if (book->save(L"���̼�����.xlsx"))
						{
							//::ShellExecute(NULL, "open", "example.xls", NULL, NULL, SW_SHOW);
							cout << "���̼����������ɣ�" << endl;
						}
						else
						{
							std::cout << book->errorMessage() << std::endl;
						}
					}
					book->release();
				}
				else if (paixu == 2)
				{
					SortList(L, 2);
					/*q = L->next;
					while (q)
					{
						cout << q->userStartPrice << endl;
						q = q->next;
					}*/

					Book* book = xlCreateXMLBook();//����һ��XLSX��ʵ��,��ʹ��ǰ�����ȵ������������������excel�Ķ���

					book->setKey(L"TommoT", L"windows-2421220b07c2e10a6eb96768a2p7r6gc");//�����û�ע����Ϣ���Ƿ��������������֤�������һ���޷�����

					if (book) {

						Sheet* sheetwrite = book->addSheet(L"sheet1");;//���ɵ�һ����

						if (sheetwrite)
						{
							int m, n;

							m = 201;
							n = 6;

							string label[6];
							label[0] = "���";
							label[1] = "��Ʊ����";
							label[2] = "��Ʊ����";
							label[3] = "���̼ۣ���Ԫ��";
							label[4] = "���̼ۣ���Ԫ��";
							label[5] = "�ǵ���";
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

							q = L->next;
							for (int row = 1; row < m; ++row)//���б���
							{
								for (int col = 1; col < n; ++col)//���б���
								{

									string str;

									//cin >> str;
									switch (col)
									{
									case 1: str = q->StockNumber; break;
									case 2: str = q->StockName; break;
									case 3: str = to_string(q->userStartPrice); break;
									case 4: str = to_string(q->userEndPrice); break;
									case 5: str = q->userChangeRate; break;
									}
									wchar_t* wchar = StringToWchar(str);

									sheetwrite->writeStr(row, col, wchar);

									delete[]wchar;

								}
								q = q->next;
							}
						}
						////����excel
						if (book->save(L"���̼�����.xlsx"))
						{
							//::ShellExecute(NULL, "open", "example.xls", NULL, NULL, SW_SHOW);
							cout << "���̼����������ɣ�" << endl;
						}
						else
						{
							std::cout << book->errorMessage() << std::endl;
						}
					}
					book->release();
				}

				else if (paixu == 3)
				{
					SortList(L, 3);
					/*q = L->next;
					while (q)
					{
						cout << q->userChangeRate << endl;
						q = q->next;
					}*/

					Book* book = xlCreateXMLBook();//����һ��XLSX��ʵ��,��ʹ��ǰ�����ȵ������������������excel�Ķ���

					book->setKey(L"TommoT", L"windows-2421220b07c2e10a6eb96768a2p7r6gc");//�����û�ע����Ϣ���Ƿ��������������֤�������һ���޷�����

					if (book) {

						Sheet* sheetwrite = book->addSheet(L"sheet1");;//���ɵ�һ����

						if (sheetwrite)
						{
							int m, n;

							m = 201;
							n = 6;

							string label[6];
							label[0] = "���";
							label[1] = "��Ʊ����";
							label[2] = "��Ʊ����";
							label[3] = "���̼ۣ���Ԫ��";
							label[4] = "���̼ۣ���Ԫ��";
							label[5] = "�ǵ���";
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

							q = L->next;
							for (int row = 1; row < m; ++row)//���б���
							{
								for (int col = 1; col < n; ++col)//���б���
								{

									string str;

									//cin >> str;
									switch (col)
									{
									case 1: str = q->StockNumber; break;
									case 2: str = q->StockName; break;
									case 3: str = to_string(q->userStartPrice); break;
									case 4: str = to_string(q->userEndPrice); break;
									case 5: str = q->userChangeRate; break;
									}
									wchar_t* wchar = StringToWchar(str);

									sheetwrite->writeStr(row, col, wchar);

									delete[]wchar;

								}
								q = q->next;
							}
						}
						////����excel
						if (book->save(L"�ǵ�������.xlsx"))
						{
							//::ShellExecute(NULL, "open", "example.xls", NULL, NULL, SW_SHOW);
							cout << "�ǵ������������ɣ�" << endl;
						}
						else
						{
							std::cout << book->errorMessage() << std::endl;
						}
					}
					book->release();
				}
			}
		}
		
		cout << endl << "��������������1���˳�������0��";
		cin >> flag;
		if (!flag)
		{
			break;
		}
	}
	cout << endl << "��л����ʹ�ã�" << endl;
	system("pause");
	//return 0;
}