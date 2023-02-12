#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "顺序表读入.cpp"
using namespace std;



typedef struct BiTNode
{
	int data;
	int count;
	struct BiTNode* llink;
	struct BiTNode* rlink;
}BiTNode, * BiTree;


inline int BSTnodecnt(BiTree T)//求总节点数
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
inline int BSTasl(BiTree t, int d)//求总步数
{
	d++;
	int a = d;
	if (t->llink)
		d += BSTasl(t->llink, a);
	if (t->rlink)
		d += BSTasl(t->rlink, a);
	return d;
}
inline float BSTaslplus(BiTree T)//求ASL
{
	float a = BSTasl(T, 0) * 1.0 / BSTnodecnt(T);
	return a;
}


inline int SearchBST(BiTree& T, int key)
{
	int num = 0;
	BiTree s = new BiTNode;					//生成新结点
	s->data = key;
	s->count = 0;
	s->llink = NULL;
	s->rlink = NULL;
	BiTree q = T, p = NULL;
	while (q)								//从根节点开始比较，直到结点为空
	{
		p = q;								//如果没有找到，用p结点保留q结点，q最后一个非NULL结点是key的父结点（而q为NULL才能跳出循环，所以用p保留q非NULL的结点）
		if (q->data > key)						//结点data大于key，则key再跟左子结点比较
		{
			q = q->llink;
			num++;
		}	
		else if (q->data < key) 								//结点data小于key，则key再跟右子结点比较
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
	BiTree s = new BiTNode;					//生成新结点
	s->data = key;
	s->count = 0;
	s->llink = NULL;
	s->rlink = NULL;
	if (!T)									//树为空则该结点就是根节点
	{
		T = s;
		return;
	}
	BiTree q = T, p = NULL;
	while (q)								//从根节点开始比较，直到结点为空
	{
		p = q;								//如果没有找到，用p结点保留q结点，q最后一个非NULL结点是key的父结点（而q为NULL才能跳出循环，所以用p保留q非NULL的结点）
		if (q->data > key)						//结点data大于key，则key再跟左子结点比较
			q = q->llink;
		else 								//结点data小于key，则key再跟右子结点比较
			q = q->rlink;
	}
	if (p->data > key)							//p是父结点
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
	//number = 0;				//从0开始计数
	//aInOrderTraverse(T, N);
	//int flag;
	/*cout << "请输入要查询的股票代码：";
	cin >> C;*/
	if (strlen(C.c_str()) != 9 || C[0] != 'c' || C[1] != 'n' || C[2] != '_')
	{
		cout << "输入的代码有误！";
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
			cout << "暂无此股票信息！" << endl;
		}*/
		if(sf != 0)
		{
			cout << "ASL： " << ASL << endl;
		}
	}
	/*cout << "继续查询请输入1，否则输入0：";
	cin >> flag;*/
		/*if (!flag)
		{
			break;
		}*/
	
	/*system("pause");
	return 0;*/
}
