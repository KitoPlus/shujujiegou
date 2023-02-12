/***************************************************
目的：将一堆整数存入hash表
键值：97
哈希函数的构造方法：除留余数法
散列冲突方法：链地址法
***************************************************/
#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <Windows.h>
#include "顺序表读入.cpp"
using namespace std;

#define N 97

//Enterprise A[200];
typedef struct node
{
    Enterprise data;
    struct node* next = NULL;
}listnode, * pLinklist;

inline int insert(pLinklist h, int K, Enterprise T)//建立哈希表
{
    int value = K % N; /*除留余数法*/
    pLinklist p = &h[value]; /*p指向哈希表中应存的位置,相当于指向链表头*/
    pLinklist q = NULL; /*q生成要存的数据*/

    q = new listnode;
    q->data = T;
    q->next = NULL;
    /*若p->next为NULL，链表头指向空，不走while, head-->q-->NULL
    若p->next不为NULL，如head-->q1-->NULL，若q1>q，不走while,head-->q-->q1-->NULL
    若p->next不为NULL，如head-->q1-->NULL，若q1<q，走while,head-->q1-->q-->NULL 使链表排列是从小到大的,这里不要求有序，故没写*/
    /*while (p->next && p->next->data < T)
    {
        p = p->next;
    }*/

    q->next = p->next;
    p->next = q;

    return 0;
}


inline void hashSearch()
{
    
    struct Enterprise *B;
    char temp[10];
    char key[10];
    int K, i,j;
    /*哈希表 用链地址法处理冲突 故用节点作为数据结构 数组中节点相当于链表头，不存数据*/
    listnode hash[N];
    /*要存入哈希表的数据*/
    B=list();//读入顺序表
    for (i = 0; i < 200; i++)//循环对每一个股票代码进行哈希表建立
    {
        strcpy_s(temp, B[i].Number.c_str());
        //cout << temp << endl;
        K = 0;
        for (j = 0; j < 9; j++)
        {
            K = K + (int)temp[j];
        }
        //cout << K << endl;
        insert(hash, K, B[i]);
    }

    /*for (i = 0; i < N; i++)
        show(hash[i].next);*/
    while (1)//哈希查找
    {
        cout << "请输入股票代码：";
        int judge = 0;//标志位记录是否继续查找
        cin >> key;
        //strcpy_s(temp, key);
        if (strlen(key) != 9)
        {
            cout << "输入代码的格式有误！请重新输入！";
            judge = 1;
        }
        else
        {
            K = 0;
            for (j = 0; j < 9; j++)//待查代码的转换
            {
                K = K + (int)key[j];
            }
            int f = K % N;//找位置
            pLinklist p = hash[f].next;//遍历链表
            int flag = 0;//标志位记录是否查找到
            float ASL = 1;

            double sum = 0, len = 0;//sum记录总步数，len记录有几个元素 
            for (i = 0; i < N; i++)
            {
                if (hash[i].next)
                {
                    int cnt = 1;
                    pLinklist t = hash[i].next;
                    while (t)
                    {
                        sum += cnt;
                        cnt++;
                        len++;
                        t = t->next;
                        //cout << sum;
                    }
                }
            }
            ASL = sum / len;//计算ASL

            while (p)//遍历链表
            {
                strcpy_s(temp, p->data.Number.c_str());
                if (!strcmp(key, temp))
                {
                    cout << p->data.BriefName << "\t" << p->data.Number << "\t" << p->data.ClassI << "\t" << p->data.ClassII << "\t" << p->data.Major << endl;
                    cout << "本次查找ASL = " << ASL << endl;
                    flag = 1;
                    break;
                }
                else
                {
                    p = p->next;
                }
            }
            if (!flag)
            {
                cout << "暂无此股票信息！" << endl;
            }
            cout << "继续查询请输入1，否则输入0：";
            cin >> judge;
        }
        if (!judge)
        {
            break;
        }
        cout << endl << endl;
    }
    
    //delete B;
    cout << endl << endl << "感谢您的使用！" << endl << endl;
    system("pause");
    
    //return 0;
}
