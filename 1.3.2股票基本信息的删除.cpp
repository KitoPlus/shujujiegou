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
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include "��Ʊ�������������.cpp"
using namespace std;

inline int Delete(BiTree* p, int& l, int& r)
{
	/* �Ӷ�����������ɾ���ڵ�p�� ���ؽ�������������� */
	BiTree q, s;
	int a = 0;
	if (!(*p)->llink && !(*p)->rlink)	/* pΪҶ�ӽڵ� */
		*p = NULL;
	else if (!(*p)->llink)	/* ������Ϊ�գ��ؽ������� */
	{
		q = *p;
		*p = (*p)->rlink;
		free(q);
		a = (*p)->data;
		if ((*p)->llink)
		{
			l = (*p)->llink->data;
		}
		if ((*p)->rlink)
		{
			r = (*p)->rlink->data;
		}
	}
	else if (!(*p)->rlink)	/* ������Ϊ�գ��ؽ������� */
	{
		q = *p;
		*p = (*p)->llink;
		free(q);
		a = (*p)->data;
		if ((*p)->llink)
		{
			l = (*p)->llink->data;
		}
		if ((*p)->rlink)
		{
			r = (*p)->rlink->data;
		}
	}
	else						/* ������������Ϊ�� */
	{
		q = *p;
		s = (*p)->llink;
		while (s->rlink)		/* ת��Ȼ�������ߵ���ͷ*/
		{
			q = s;
			s = s->rlink;
		}
		(*p)->data = s->data;
		if (q != *p)				/* �ж��Ƿ�ִ�й�����whileѭ�� */
			q->rlink = s->llink;	/* ִ������whileѭ�����ؽ������� */
		else
			q->llink = s->llink;	/* δִ������whileѭ�����ؽ������� */
		free(s);
		a = (*p)->data;
		if ((*p)->llink)
		{
			l = (*p)->llink->data;
		}
		if ((*p)->rlink)
		{
			r = (*p)->rlink->data;
		}
	}
	return a;
}

inline int DeleteBST(BiTree* T, int key, int& l, int& r)
{
	int b = -1;
	/* ������������T�д��ڹؼ��ֵ���key������Ԫ��ʱ����ɾ��������Ԫ�ؽڵ� */
	/* ������TRUE�����򷵻�FALSE */
	if (!(*T))
		return b;	/* �����ڹؼ��ֵ���key������Ԫ�� */
	else
	{
		if (key == (*T)->data)
			b=Delete(T, l, r);
		else if (key < (*T)->data)
			return DeleteBST(&(*T)->llink, key, l, r);
		else
			return DeleteBST(&(*T)->rlink, key, l, r);
	}
}

inline void DeleteOne()
{
	struct Enterprise* B;
	B = list();
	int i, j, ASL;
	int S[200];
	//string C;
	char temp[6];
	BiTree T = NULL;
	for (j = 0; j < 200; j++)
	{
		for (i = 3; i < 9; i++)
		{
			temp[i - 3] = B[j].Number[i];
		}
		S[j] = atoi(temp);
	}

	for (j = 0; j < 200; j++)
	{
		//cin >> S[j];
		BuildBST(T, S[j]);
	}
	while (1)
	{
		int jixu = 1;
		int key;
		key = 0;
		string hhh;
		system("cls");
		cout << "������Ҫɾ���Ĺ�Ʊ���룺";
		cin >> hhh;
		if (strlen(hhh.c_str()) != 9 || hhh[0] != 'c' || hhh[1] != 'n' || hhh[2] != '_')//³����
		{
			cout << "����Ĵ�������";
		}
		else//����ת������
		{
			for (i = 3; i < 9; i++)
			{
				temp[i - 3] = hhh[i];
			}
			key = atoi(temp);
			int l, r;
			l = 0;
			r = 0;
			int flag = DeleteBST(&T, key, l, r);
			//cout << flag;
			if (flag == -1)//û�ҵ�
			{
				cout << "������Ĺؼ��ֲ����ڡ�" << endl;
			}
			else if (flag == 0)//Ҷ�ڵ�
			{
				cout << "����ɾ���Ĺ�Ʊλ��Ҷ�ڵ㣬�����油��" << endl;
			}
			else//ɾ����
			{
				string temp1 = to_string(flag);
				string newer;
				switch (strlen(temp1.c_str()))
				{
				case 1: newer = "cn_00000"; break;
				case 2: newer = "cn_0000"; break;
				case 3: newer = "cn_000"; break;
				case 4: newer = "cn_00"; break;
				case 5: newer = "cn_0"; break;
				case 6: newer = "cn_"; break;
				}
				newer.append(temp1);
				cout << "�½ڵ���Ϣ��" << "\t";
				for (i = 0; i < 200; i++)
				{
					if (!strcmp(B[i].Number.c_str(), newer.c_str()))//ֻ���������㣬��û������Һ���
					{
						cout << B[i].BriefName << "\t" << B[i].Number << endl;
						break;
					}
				}
				if (!l)//�ж��������ӣ��������
				{
					cout << "�õ�û�����ӡ�" << endl;
				}
				else
				{
					cout << "������Ϣ��" << "\t";
					string temp2 = to_string(l);
					string newerl;
					switch (strlen(temp2.c_str()))
					{
					case 1: newerl = "cn_00000"; break;
					case 2: newerl = "cn_0000"; break;
					case 3: newerl = "cn_000"; break;
					case 4: newerl = "cn_00"; break;
					case 5: newerl = "cn_0"; break;
					case 6: newerl = "cn_"; break;
					}
					newerl.append(temp2);
					for (i = 0; i < 200; i++)
					{
						if (!strcmp(B[i].Number.c_str(), newerl.c_str()))//ֻ���������㣬��û������Һ���
						{
							cout << B[i].BriefName << "\t" << B[i].Number << endl;
							break;
						}
					}
				}
				if (!r)//�ж������Һ��ӣ��������
				{
					cout << "�õ�û���Һ��ӡ�" << endl;
				}
				else
				{
					cout << "�Һ�����Ϣ��" << "\t";
					string temp3 = to_string(r);
					string newerr;
					switch (strlen(temp3.c_str()))
					{
					case 1: newerr = "cn_00000"; break;
					case 2: newerr = "cn_0000"; break;
					case 3: newerr = "cn_000"; break;
					case 4: newerr = "cn_00"; break;
					case 5: newerr = "cn_0"; break;
					case 6: newerr = "cn_"; break;
					}
					newerr.append(temp3);
					for (i = 0; i < 200; i++)
					{
						if (!strcmp(B[i].Number.c_str(), newerr.c_str()))
						{
							cout << B[i].BriefName << "\t" << B[i].Number << endl;
							break;
						}
					}
				}
			}
		}
		cout << endl << "����ɾ��������1���˳�����0��";
		cin >> jixu;
		if (jixu == 0)
		{
			break;
		}
	}
	cout << endl << endl << "��л����ʹ�ã�" << endl;
	

	system("pause");
}