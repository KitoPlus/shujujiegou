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
#include "��Ʊ�������������.cpp"
using namespace std;

#define N 200
#define M 1000

struct StockII//����ṹ��
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

inline void basic()
{
	int i, n = 0;
	while (1)
	{
		string number;
		StockII* list = new StockII[M];
		int flag = 1, n = 0;
		cout << "�������Ʊ���룺";
		cin >> number;
		if (strlen(number.c_str()) != 9 || number[0] != 'c' || number[1] != 'n' || number[2] != '_')
		{
			cout << "����Ĵ�������";
		}
		else
		{
			BiTreeASL(number);
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
				cout << "���̼ۣ�" << list[0].StartPrice << endl << "���̼ۣ�" << list[0].EndPrice << endl << "�ǵ�����" << list[0].ChangeRate << endl;
			}
			cout << "����1������ѯ������0�˳���";
			cin >> flag;
			cout << endl << endl;
			if (!flag)
			{
				break;
			}
		}
		
	}
	cout << "��л����ʹ�ã�" << endl;
	
	system("pause");
	//return 0;
}