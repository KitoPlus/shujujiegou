#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include "˳������.cpp"
using namespace std;

inline vector<int> get_next(string b)	//��vector�������Ӵ�b��next����
{
	vector<int> result;		//������()����ȷ����С����ʵ�����Ԫ�ز���Ĭ�ϸ�ֵΪ0�ˣ�����һ���յ�������OK��
	int i, j;
	i = 0;
	j = -1;
	result.push_back(-1);	//��������Ԫ�ظ�ֵ����Ϊ��ʶʹ��
	while (i < b.size() - 1)
	{
		if (j == -1 || b[i] == b[j])	//b[i]��ʾ��׺�ĵ����ַ�
										//b[j]��ʾǰ׺�ĵ����ַ�
		{
			++i;
			++j;
			//�������ʵ���Ż��ظ����ַ�
			//����ֱ����result.push_back(j);����������ж����
			if (b[i] != b[j])
				result.push_back(j);
			else if (i == 1)
				result.push_back(j);
			else
				result.push_back(result[j]);
		}
		else
			j = result[j];		//���ַ���ͬ��ǰ׺�ַ�����
	}
	return result;
}
inline int KMP(string a, string b)
{
	vector<int> next = get_next(b);	//����get_text����
	int i = 0;
	int j = 0;
	//ע��size�������ص�������string::size_type���޷�����
	//��i<�����ĳ�����j<�Ӵ��ĳ���ʱ��ѭ������
	while (i < (int)a.size() && j < (int)b.size())//����ѭ������
	{
		if (j == -1 || a[i] == b[j])	//����ĸ��������������������㷨������
		{
			++i;
			++j;
		}
		else {
			j = next[j];	//������ȣ�j�˻غ��ʵ�λ��
		}
	}
	if (j == b.size()) {
		return i - j;		//���ﷵ�ص���ƥ���ַ���ʼ���±�λ
	}
	else {
		return -1;
	}
}


inline void web()
{
	struct Enterprise* B;
	string user;
	int i, flag, n;
	B = list();
	while (1)
	{
		cout << "��������ַ�ؼ��֣�";
		cin >> user;
		for (i = 0; i < 200; i++)//ѭ����������KMPƥ�䣬�ɹ���ֹͣ
		{
			flag = KMP(B[i].Website, user);
			if (flag != -1)
			{
				break;
			}
		}
		if (flag == -1)
		{
			cout << "δ��ѯ���й���Ϣ��" << endl;
		}
		else
		{
			cout << B[i].BriefName << " " << B[i].Number << endl;
		}
		cout << "��������������1������������0��";
		cin >> n;
		cout << endl << endl;
		if (!n)
		{
			break;
		}
	}
	cout << "��л����ʹ�ã�" << endl;
	system("pause");

	//return 0;
}