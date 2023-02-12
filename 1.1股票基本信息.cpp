/***************************************************
Ŀ�ģ���һ����������hash��
��ֵ��97
��ϣ�����Ĺ��췽��������������
ɢ�г�ͻ����������ַ��
***************************************************/
#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <Windows.h>
#include "˳������.cpp"
using namespace std;

#define N 97

//Enterprise A[200];
typedef struct node
{
    Enterprise data;
    struct node* next = NULL;
}listnode, * pLinklist;

inline int insert(pLinklist h, int K, Enterprise T)//������ϣ��
{
    int value = K % N; /*����������*/
    pLinklist p = &h[value]; /*pָ���ϣ����Ӧ���λ��,�൱��ָ������ͷ*/
    pLinklist q = NULL; /*q����Ҫ�������*/

    q = new listnode;
    q->data = T;
    q->next = NULL;
    /*��p->nextΪNULL������ͷָ��գ�����while, head-->q-->NULL
    ��p->next��ΪNULL����head-->q1-->NULL����q1>q������while,head-->q-->q1-->NULL
    ��p->next��ΪNULL����head-->q1-->NULL����q1<q����while,head-->q1-->q-->NULL ʹ���������Ǵ�С�����,���ﲻҪ�����򣬹�ûд*/
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
    /*��ϣ�� ������ַ�������ͻ ���ýڵ���Ϊ���ݽṹ �����нڵ��൱������ͷ����������*/
    listnode hash[N];
    /*Ҫ�����ϣ�������*/
    B=list();//����˳���
    for (i = 0; i < 200; i++)//ѭ����ÿһ����Ʊ������й�ϣ����
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
    while (1)//��ϣ����
    {
        cout << "�������Ʊ���룺";
        int judge = 0;//��־λ��¼�Ƿ��������
        cin >> key;
        //strcpy_s(temp, key);
        if (strlen(key) != 9)
        {
            cout << "�������ĸ�ʽ�������������룡";
            judge = 1;
        }
        else
        {
            K = 0;
            for (j = 0; j < 9; j++)//��������ת��
            {
                K = K + (int)key[j];
            }
            int f = K % N;//��λ��
            pLinklist p = hash[f].next;//��������
            int flag = 0;//��־λ��¼�Ƿ���ҵ�
            float ASL = 1;

            double sum = 0, len = 0;//sum��¼�ܲ�����len��¼�м���Ԫ�� 
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
            ASL = sum / len;//����ASL

            while (p)//��������
            {
                strcpy_s(temp, p->data.Number.c_str());
                if (!strcmp(key, temp))
                {
                    cout << p->data.BriefName << "\t" << p->data.Number << "\t" << p->data.ClassI << "\t" << p->data.ClassII << "\t" << p->data.Major << endl;
                    cout << "���β���ASL = " << ASL << endl;
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
                cout << "���޴˹�Ʊ��Ϣ��" << endl;
            }
            cout << "������ѯ������1����������0��";
            cin >> judge;
        }
        if (!judge)
        {
            break;
        }
        cout << endl << endl;
    }
    
    //delete B;
    cout << endl << endl << "��л����ʹ�ã�" << endl << endl;
    system("pause");
    
    //return 0;
}
