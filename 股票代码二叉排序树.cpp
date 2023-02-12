#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "˳������.cpp"
using namespace std;



typedef struct BiTNode
{
	int data;
	int count;
	struct BiTNode* llink;
	struct BiTNode* rlink;
}BiTNode, * BiTree;


inline int BSTnodecnt(BiTree T)//���ܽڵ���
{
	int d = 0;
	if (!T)
		return 0;
	else
	{
		d = 1 + BSTnodecnt(T->llink) + BSTnodecnt(T->rlink);
	}
	return d;
}
inline int BSTasl(BiTree t, int d)//���ܲ���
{
	d++;
	int a = d;
	if (t->llink)
		d += BSTasl(t->llink, a);
	if (t->rlink)
		d += BSTasl(t->rlink, a);
	return d;
}
inline float BSTaslplus(BiTree T)//��ASL
{
	float a = BSTasl(T, 0) * 1.0 / BSTnodecnt(T);
	return a;
}


inline int SearchBST(BiTree& T, int key)
{
	int num = 0;
	BiTree s = new BiTNode;					//�����½��
	s->data = key;
	s->count = 0;
	s->llink = NULL;
	s->rlink = NULL;
	BiTree q = T, p = NULL;
	while (q)								//�Ӹ��ڵ㿪ʼ�Ƚϣ�ֱ�����Ϊ��
	{
		p = q;								//���û���ҵ�����p��㱣��q��㣬q���һ����NULL�����key�ĸ���㣨��qΪNULL��������ѭ����������p����q��NULL�Ľ�㣩
		if (q->data > key)						//���data����key����key�ٸ����ӽ��Ƚ�
		{
			q = q->llink;
			num++;
		}	
		else if (q->data < key) 								//���dataС��key����key�ٸ����ӽ��Ƚ�
		{
			q = q->rlink;
			num++;
		}
		else
		{
			num++;
			return num;
		}
	}
	return 0;
}


inline void BuildBST(BiTree& T, int key)
{
	BiTree s = new BiTNode;					//�����½��
	s->data = key;
	s->count = 0;
	s->llink = NULL;
	s->rlink = NULL;
	if (!T)									//��Ϊ����ý����Ǹ��ڵ�
	{
		T = s;
		return;
	}
	BiTree q = T, p = NULL;
	while (q)								//�Ӹ��ڵ㿪ʼ�Ƚϣ�ֱ�����Ϊ��
	{
		p = q;								//���û���ҵ�����p��㱣��q��㣬q���һ����NULL�����key�ĸ���㣨��qΪNULL��������ѭ����������p����q��NULL�Ľ�㣩
		if (q->data > key)						//���data����key����key�ٸ����ӽ��Ƚ�
			q = q->llink;
		else 								//���dataС��key����key�ٸ����ӽ��Ƚ�
			q = q->rlink;
	}
	if (p->data > key)							//p�Ǹ����
	{
		//N++;
		p->llink = s;
	}
	else
	{
		//N++;
		p->rlink = s;
	}
}
inline void BiTreeASL(string C)
{
	struct Enterprise* B;
	B = list();
	int i, j, sf;
	float ASL;
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
	//number = 0;				//��0��ʼ����
	//aInOrderTraverse(T, N);
	//int flag;
	/*cout << "������Ҫ��ѯ�Ĺ�Ʊ���룺";
	cin >> C;*/
	if (strlen(C.c_str()) != 9 || C[0] != 'c' || C[1] != 'n' || C[2] != '_')
	{
		cout << "����Ĵ�������";
	}
	else
	{
		for (i = 3; i < 9; i++)
		{
			temp[i - 3] = C[i];
		}
		int key = atoi(temp);
		sf = SearchBST(T, key);
		ASL = BSTaslplus(T);
		/*if (!ASL)
		{
			cout << "���޴˹�Ʊ��Ϣ��" << endl;
		}*/
		if(sf != 0)
		{
			cout << "ASL�� " << ASL << endl;
		}
	}
	/*cout << "������ѯ������1����������0��";
	cin >> flag;*/
		/*if (!flag)
		{
			break;
		}*/
	
	/*system("pause");
	return 0;*/
}
