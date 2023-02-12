/***
��ȡexcelָ�����ݲ�����ڿ���̨��ע�����ڹر�.xlsx�ļ�����������
***/
#pragma once

#include <iostream>
#include "libxl.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <time.h>
#include <conio.h>
#include <Windows.h>
using namespace libxl;
using namespace std;
//const wchar_t*   ��һ��ָ����ַ����͵�ָ�룬���ָ��ָ��������Ǹ����������ܸı�

struct Enterprise
{
    string Number;//��Ʊ����
    string BriefName;//��Ʊ���
    string Code;//��ҵ����
    string ClassI;//һ����ҵ
    string ClassII;//������ҵ
    string House;//������
    string FullName;//��Ʊȫ��
    string Date;//��������
    string Province;//ʡ��
    string City;//����
    string Corporation;//����
    string Location;//��ַ
    string Website;//��ַ
    string Email;//����
    string Tel;//�绰
    string Major;//��Ӫ
    string Operation;//��Ӫ��Χ
};

inline char* w2c(char* pcstr, const wchar_t* pwstr, size_t len)//�˺���֧�����Ķ�ȡ����ʾ����������������������
{
    int nlength = wcslen(pwstr);//��ȡת����ĳ���

    int nbytes = WideCharToMultiByte(0, 0, pwstr, nlength, NULL, 0, NULL, NULL); //ӳ��һ��unicode�ַ�����һ�����ֽ��ַ���

    if (nbytes > len)   nbytes = len;
    // ͨ�����ϵõ��Ľ����ת��unicode �ַ�Ϊascii �ַ�
    WideCharToMultiByte(0, 0, pwstr, nlength, pcstr, nbytes, NULL, NULL);

    return pcstr;
}

inline wchar_t* StringToWchar(const string& pKey)
{
    const char* pCStrKey = pKey.c_str();
    //��һ�ε��÷���ת������ַ������ȣ�����ȷ��Ϊwchar_t*���ٶ����ڴ�ռ�
    int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
    wchar_t* pWCStrKey = new wchar_t[pSize];
    //�ڶ��ε��ý����ֽ��ַ���ת����˫�ֽ��ַ���
    MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, pWCStrKey, pSize);
    return pWCStrKey;
}



inline Enterprise* list()
{
    Enterprise *A = new Enterprise[200];
    string Company[201][20];
    stringstream temp;

    Book* book = xlCreateXMLBook();//����һ��XLSX��ʵ��,��ʹ��ǰ�����ȵ������������������excel�Ķ���

    book->setKey(L"TommoT", L"windows-2421220b07c2e10a6eb96768a2p7r6gc");//������Ӧ��key������ع���(����)�����򴴽�book�޷��ɹ�

    if (book->load(L"introduction.xlsx"))//�ļ����빤��Ŀ¼��
    {
        Sheet* sheetread = book->getSheet(0);//ѡȡ��һ����

        if (sheetread)
        {
            for (int row = sheetread->firstRow()+1; row < sheetread->lastRow(); ++row)//�б���
            {
                for (int col = sheetread->firstCol(); col < sheetread->lastCol(); ++col)//�б���
                {
                    CellType celltype = sheetread->cellType(row, col);//��ȡĳ��ĳ�еĵ�Ԫ������͡����ַ����ͣ���ֵ�ͣ���ֵ��

                    Format* format = sheetread->cellFormat(row, col);

                    if (celltype == CELLTYPE_STRING)//���ÿ����Ԫ������Ϊ�ַ�������
                    {
                        const wchar_t* t = sheetread->readStr(row, col);//�ӵ�Ԫ���ж�ȡ�ַ��������ʽ

                        char* pcstr = (char*)malloc(sizeof(char) * (2 * wcslen(t) + 1));//����ռ��С����Ŷ��������ݣ�wcslen()���������������t�ĳ���

                        memset(pcstr, 0, 2 * wcslen(t) + 1);//��ʼ�������������������+1�Ŀռ�

                        w2c(pcstr, t, 2 * wcslen(t) + 1); //pcstr�����ݶ�������Ҫ�������ı����ת�������Ϊת������

                        //cout << pcstr << endl;//���
                        Company[row-1][col] = pcstr;

                        free(pcstr);

                    }
                    else if (celltype == CELLTYPE_NUMBER)//���ÿ����Ԫ������Ϊ��ֵ����
                    {
                        double result = sheetread->readNum(row, col);

                        //cout << result << endl;
                        temp << result;
                        temp >> Company[row - 1][col];
                    }
                    else if (celltype == CELLTYPE_BLANK)//���ÿ����Ԫ������Ϊ�գ���ֵ�����ڵ�Ԫ����ʽ
                    {
                        //cout << "\t\t" << endl;
                        Company[row - 1][col] = " ";
                    }
                    else if (celltype == CELLTYPE_EMPTY)//�����ڵ�Ԫ����ʽ
                    {
                        //cout << "\t\t" << endl;
                        Company[row - 1][col] = " ";
                    }
                }
                //cout << endl;//ÿ�����ݻ��зָ����
            }
        }
        for (int i = 0; i < 200; i++)
        {
            for (int j = 0; j < 17; j++)
            {
                //cout << Company[i][j] << "\t";
                switch (j)
                {
                case 0: A[i].Number = Company[i][j]; break;
                case 1: A[i].BriefName = Company[i][j]; break;
                case 2: A[i].Code = Company[i][j]; break;
                case 3: A[i].ClassI = Company[i][j]; break;
                case 4: A[i].ClassII = Company[i][j]; break;
                case 5: A[i].House = Company[i][j]; break;
                case 6: A[i].FullName = Company[i][j]; break;
                case 7: A[i].Date = Company[i][j]; break;
                case 8: A[i].Province = Company[i][j]; break;
                case 9: A[i].City = Company[i][j]; break;
                case 10:A[i].Corporation = Company[i][j]; break;
                case 11:A[i].Location = Company[i][j]; break;
                case 12:A[i].Website = Company[i][j]; break;
                case 13:A[i].Email = Company[i][j]; break;
                case 14:A[i].Tel = Company[i][j]; break;
                case 15:A[i].Major = Company[i][j]; break;
                case 16:A[i].Operation = Company[i][j]; break;
                }
            }
            //printf("\n");
        }
        /*for (int i = 0; i < 200; i++)
        {
            cout << A[i].BriefName << endl;
        }*/
        ////����excel
        book->save(L"test.xlsx");

        book->release();
    }
    //system("pause");

    return A;
}
