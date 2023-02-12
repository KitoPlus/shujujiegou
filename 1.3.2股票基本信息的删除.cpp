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
#include "股票代码二叉排序树.cpp"
using namespace std;

inline int Delete(BiTree* p, int& l, int& r)
{
	/* 从二叉排序树中删除节点p， 并重接它的左或右子树 */
	BiTree q, s;
	int a = 0;
	if (!(*p)->llink && !(*p)->rlink)	/* p为叶子节点 */
		*p = NULL;
	else if (!(*p)->llink)	/* 左子树为空，重接右子树 */
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
	else if (!(*p)->rlink)	/* 右子树为空，重接左子树 */
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
	else						/* 左右子树均不为空 */
	{
		q = *p;
		s = (*p)->llink;
		while (s->rlink)		/* 转左，然后向右走到尽头*/
		{
			q = s;
			s = s->rlink;
		}
		(*p)->data = s->data;
		if (q != *p)				/* 判断是否执行过上述while循环 */
			q->rlink = s->llink;	/* 执行上述while循环，重接右子树 */
		else
			q->llink = s->llink;	/* 未执行上述while循环，重接左子树 */
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
	/* 若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素节点 */
	/* 并返回TRUE；否则返回FALSE */
	if (!(*T))
		return b;	/* 不存在关键字等于key的数据元素 */
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
		cout << "请输入要删除的股票代码：";
		cin >> hhh;
		if (strlen(hhh.c_str()) != 9 || hhh[0] != 'c' || hhh[1] != 'n' || hhh[2] != '_')//鲁棒性
		{
			cout << "输入的代码有误！";
		}
		else//代码转成整形
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
			if (flag == -1)//没找到
			{
				cout << "您输入的关键字不存在。" << endl;
			}
			else if (flag == 0)//叶节点
			{
				cout << "所需删除的股票位于叶节点，无需替补。" << endl;
			}
			else//删掉了
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
				cout << "新节点信息：" << "\t";
				for (i = 0; i < 200; i++)
				{
					if (!strcmp(B[i].Number.c_str(), newer.c_str()))//只输出了替代点，还没输出左右孩子
					{
						cout << B[i].BriefName << "\t" << B[i].Number << endl;
						break;
					}
				}
				if (!l)//判断有无左孩子，有则输出
				{
					cout << "该点没有左孩子。" << endl;
				}
				else
				{
					cout << "左孩子信息：" << "\t";
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
						if (!strcmp(B[i].Number.c_str(), newerl.c_str()))//只输出了替代点，还没输出左右孩子
						{
							cout << B[i].BriefName << "\t" << B[i].Number << endl;
							break;
						}
					}
				}
				if (!r)//判断有无右孩子，有则输出
				{
					cout << "该点没有右孩子。" << endl;
				}
				else
				{
					cout << "右孩子信息：" << "\t";
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
		cout << endl << "继续删除请输入1，退出输入0：";
		cin >> jixu;
		if (jixu == 0)
		{
			break;
		}
	}
	cout << endl << endl << "感谢您的使用！" << endl;
	

	system("pause");
}