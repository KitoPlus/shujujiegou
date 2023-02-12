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
#include "1.1��Ʊ������Ϣ.cpp"
#include "1.2��Ʊ��ַ��Ϣ.cpp"
#include "1.3��Ʊ��ϸ��Ϣ.cpp"
#include "1.4��Ʊ�۸���Ϣ.cpp"
#include "2.1��ʱ�����.cpp"
#include "2.2����ҵ����.cpp"
#include "2.3�����̼۷���.cpp"
#include "2.4��Ʊ����Է���.cpp"
#include "2.5����ķ��Ʊ����ɸѡ.cpp"
#include "2.6����ͼ��Ʊ����ɸѡ.cpp"
#include "2.5.2������Ʊ����ɸѡ.cpp"
#include "1.3.2��Ʊ������Ϣ��ɾ��.cpp"
using namespace std;

bool visit[61];
int dist[61];
int smalltree[61][61];
int color[11];//Ⱦɫ��־���飬δȾɫΪ0����ɫΪ1����ɫΪ2��1~10��

// wchar_t* StringToWchar(const string& pKey)
//{
//	const char* pCStrKey = pKey.c_str();
//	//��һ�ε��÷���ת������ַ������ȣ�����ȷ��Ϊwchar_t*���ٶ����ڴ�ռ�
//	int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
//	wchar_t* pWCStrKey = new wchar_t[pSize];
//	//�ڶ��ε��ý����ֽ��ַ���ת����˫�ֽ��ַ���
//	MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, pWCStrKey, pSize);
//	return pWCStrKey;
//}

int main()
{
	int cntnu;
	while(1)
	{
		int choice;
		system("cls");
		system("color F0");
		printf("******************************************************************************\n");
		printf("******                    ��ӭʹ�ù�Ʊ��ѯ�����ϵͳ                    ******\n");
		printf("******************************************************************************\n");
		printf("******                        ��ϵͳ�߱����¹��ܣ�                      ******\n");
		printf("******                           1.��ѯϵͳ ��                          ******\n");
		printf("******                           2.����ϵͳ ��                          ******\n");
		printf("******                           3.�˳�ϵͳ ��                          ******\n");
		printf("******************************************************************************\n");
		cout << endl;
		cout << "��������ѡ��Ĺ��ܣ�";
		fflush(stdin);
		cin >> choice;
		if (choice == 1)
		{
			system("cls");
			system("color E0");
			choice = 0;
			printf("------------------------------------------------------------------------------\n");
			printf("------                         ��ӭʹ�ò�ѯ����                         ------\n");
			printf("------------------------------------------------------------------------------\n");
			printf("------                      ������ѡ�����²���֮һ��                    ------\n");
			printf("------                  1.��Ʊ������Ϣ��ѯ�����ڹ�ϣ����              ------\n");
			printf("------                  2.��Ʊ��ַ��Ϣ��ѯ������KMP����                 ------\n");
			printf("------                  3.��Ʊ��ϸ��Ϣ��ѯ�����ڶ�������������          ------\n");
			printf("------                  4.��Ʊ�۸���Ϣ��ѯ�����ڵ�������              ------\n");
			printf("------                  5.��Ʊ������Ϣɾ�������ڶ�������������          ------\n");
			printf("------                  0.������һ����                                  ------\n");
			printf("------------------------------------------------------------------------------\n");
			cout << endl;
			cout << "��ѡ������Ҫ���еĲ�����";
			cin >> choice;
			system("cls");
			switch (choice)
			{
			case 1: hashSearch(); break;
			case 2: web(); break;
			case 3: basic(); break;
			case 4: baseOnDate(); break;
			case 5: DeleteOne(); break;
			case 0: break;
			default: cout << "��������" << endl; break;
			}
		}
		else if (choice == 2)
		{
			system("cls");
			system("color B0");
			choice = 0;
			printf("------------------------------------------------------------------------------\n");
			printf("------                         ��ӭʹ�÷�������                         ------\n");
			printf("------------------------------------------------------------------------------\n");
			printf("------                      ������ѡ�����²���֮һ��                    ------\n");
			printf("------                    1.��ʱ�������ֱ�Ӳ������򣩣�                ------\n");
			printf("------                    2.����ҵ�������������򣩣�                    ------\n");
			printf("------                    3.�����̼۷�������ѡ�����򣩣�              ------\n");
			printf("------                    4.��Ʊ����Է�����Floyd���·������           ------\n");
			printf("------                    5.����ķ��Ʊ����ɸѡ��Prim��С����������      ------\n");
			printf("------                    6.����ͼ��Ʊ����ɸѡ������ͼ��Ⱦɫ������      ------\n");
			printf("------                    7.������Ʊ����ɸѡ��Kruskal��С����������     ------\n");
			printf("------                    0.������һ����                                ------\n");
			printf("------------------------------------------------------------------------------\n");
			cout << endl;
			cout << "��ѡ������Ҫ���еĲ�����";
			cin >> choice;
			system("cls");
			switch (choice)
			{
			case 1: InsertSort(); break;
			case 2: FastSort(); break;
			case 3: SelectSort(); break;
			case 4: Relate(); break;
			case 5: PrimFundation(); break;
			case 6: BipartFundation(); break;
			case 7: KrukalFundation(); break;
			case 0: break;
			default: cout << "��������" << endl; break;
			}
		}
		else if (choice == 3)
		{
			system("cls");
			cout << "��л����ʹ�ã�ף������˳����" << endl;
			break;
		}
	}
	

	system("pause");
	return 0;
}
