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
#include "˳������.cpp"
using namespace std;

#define N 200
#define M 1000

struct Stock//����ṹ��
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

typedef struct LNode
{
	Stock* data;
	string StockNumber;
	string StockName;
	int dataLength;
	struct LNode* next;
}LNode, *linklist;

//void InitList_L(linklist L)//�����ձ� 
//{
//	L = (LNode*)malloc(sizeof(LNode));
//	L->next = NULL;
//}

inline void baseOnDate()
{
	int i, j;
	struct Enterprise* B;
	B = list();
	linklist L;
	L = new LNode;
	L->next = NULL;
	linklist q = L;
	for (j = 0; j < 200; j++)
	{
		int n = 0;
		string number;
		Stock* list = new Stock[M];
		number = B[j].Number;
		number.append(".txt");
		FILE* fs = NULL, * fp = NULL;
		fs = fopen(number.c_str(), "r");
		if (fs == NULL)
		{
			printf("���޸ù�Ʊ��Ϣ��\n");
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
		linklist p = new LNode;
		p->data = list;
		p->StockName = B[j].BriefName;
		p->StockNumber = B[j].Number;
		p->dataLength = n;
		p->next = NULL;
		q->next = p;
		q = q->next;
		//cout << q->data[0].Date << endl << q->StockName << endl << q->StockNumber << endl << endl;
	}
	int flag = -1;
	while (1)
	{
		system("cls");
		string SearchDate;
		cout << "�������ѯ���ڣ�";
		cin >> SearchDate;
		if (strlen(SearchDate.c_str()) != 8)
		{
			cout << "���ڸ�ʽ����" << endl;
		}
		//cout << SearchDate;
		else
		{
			int num = 0;
			printf("��Ʊ����\t��Ʊ����\t���̼�\t���̼�\t�ǵ���\n");
			printf("-------------------------------------------------------\n");
			linklist t = L->next;
			while (t)
			{
				int fffflag = 0;
				for (i = 0; i < t->dataLength; i++)
				{
					if (!strcmp(SearchDate.c_str(), t->data[i].Date))
					{
						flag = 0;
						fffflag = 1;
						num++;
						cout << t->StockNumber << "\t" << t->StockName << "\t" << t->data[i].StartPrice << "\t" << t->data[i].EndPrice << "\t" << t->data[i].ChangeRate << endl;
						break;
					}
				}
				if (!fffflag)
				{
					cout << t->StockNumber << "\t" << t->StockName << "\t" << "���޸�����Ϣ" << endl;
				}
				t = t->next;
			}
			printf("-------------------------------------------------------\n");
			if (flag != 0)
			{
				cout << "���޸�����Ϣ��" << endl;
			}
			cout << "�������µĹ�Ʊ��Ϣ������" << "\t" << num << endl;
		}
		
		cout << "������ѯ������1���˳�������0��";
		cin >> flag;
		cout << endl << endl;
		if (!flag)
		{
			break;
		}
	}
	

	cout << "��л����ʹ�ã�" << endl;

	system("pause");
	//return 0;
}