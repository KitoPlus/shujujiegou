/***
读取excel指定内容并输出在控制台，注意请在关闭.xlsx文件条件下运行
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
//const wchar_t*   是一个指向宽字符类型的指针，这个指针指向的内容是个常量，不能改变

struct Enterprise
{
    string Number;//股票代码
    string BriefName;//股票简称
    string Code;//行业代码
    string ClassI;//一级行业
    string ClassII;//二级行业
    string House;//交易所
    string FullName;//股票全称
    string Date;//上市日期
    string Province;//省份
    string City;//城市
    string Corporation;//法人
    string Location;//地址
    string Website;//网址
    string Email;//邮箱
    string Tel;//电话
    string Major;//主营
    string Operation;//经营范围
};

inline char* w2c(char* pcstr, const wchar_t* pwstr, size_t len)//此函数支持中文读取和显示，需加入否则中文内容乱码
{
    int nlength = wcslen(pwstr);//获取转换后的长度

    int nbytes = WideCharToMultiByte(0, 0, pwstr, nlength, NULL, 0, NULL, NULL); //映射一个unicode字符串到一个多字节字符串

    if (nbytes > len)   nbytes = len;
    // 通过以上得到的结果，转换unicode 字符为ascii 字符
    WideCharToMultiByte(0, 0, pwstr, nlength, pcstr, nbytes, NULL, NULL);

    return pcstr;
}

inline wchar_t* StringToWchar(const string& pKey)
{
    const char* pCStrKey = pKey.c_str();
    //第一次调用返回转换后的字符串长度，用于确认为wchar_t*开辟多大的内存空间
    int pSize = MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, NULL, 0);
    wchar_t* pWCStrKey = new wchar_t[pSize];
    //第二次调用将单字节字符串转换成双字节字符串
    MultiByteToWideChar(CP_OEMCP, 0, pCStrKey, strlen(pCStrKey) + 1, pWCStrKey, pSize);
    return pWCStrKey;
}



inline Enterprise* list()
{
    Enterprise *A = new Enterprise[200];
    string Company[201][20];
    stringstream temp;

    Book* book = xlCreateXMLBook();//创建一个XLSX的实例,在使用前必须先调用这个函数创建操作excel的对象

    book->setKey(L"TommoT", L"windows-2421220b07c2e10a6eb96768a2p7r6gc");//设置相应的key激活相关功能(购买)，否则创建book无法成功

    if (book->load(L"introduction.xlsx"))//文件放入工程目录里
    {
        Sheet* sheetread = book->getSheet(0);//选取第一个表

        if (sheetread)
        {
            for (int row = sheetread->firstRow()+1; row < sheetread->lastRow(); ++row)//行遍历
            {
                for (int col = sheetread->firstCol(); col < sheetread->lastCol(); ++col)//列遍历
                {
                    CellType celltype = sheetread->cellType(row, col);//读取某行某列的单元格的类型。有字符串型，数值型，空值。

                    Format* format = sheetread->cellFormat(row, col);

                    if (celltype == CELLTYPE_STRING)//如果每个单元格内容为字符串类型
                    {
                        const wchar_t* t = sheetread->readStr(row, col);//从单元格中读取字符串及其格式

                        char* pcstr = (char*)malloc(sizeof(char) * (2 * wcslen(t) + 1));//定义空间大小来存放读出的内容，wcslen()函数返回输入参数t的长度

                        memset(pcstr, 0, 2 * wcslen(t) + 1);//初始化清零操作，开辟两倍+1的空间

                        w2c(pcstr, t, 2 * wcslen(t) + 1); //pcstr的内容读出来后要进行中文编码的转换，这个为转换函数

                        //cout << pcstr << endl;//输出
                        Company[row-1][col] = pcstr;

                        free(pcstr);

                    }
                    else if (celltype == CELLTYPE_NUMBER)//如果每个单元格内容为数值类型
                    {
                        double result = sheetread->readNum(row, col);

                        //cout << result << endl;
                        temp << result;
                        temp >> Company[row - 1][col];
                    }
                    else if (celltype == CELLTYPE_BLANK)//如果每个单元格内容为空：无值但存在单元格样式
                    {
                        //cout << "\t\t" << endl;
                        Company[row - 1][col] = " ";
                    }
                    else if (celltype == CELLTYPE_EMPTY)//不存在单元格样式
                    {
                        //cout << "\t\t" << endl;
                        Company[row - 1][col] = " ";
                    }
                }
                //cout << endl;//每行内容换行分割输出
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
        ////保存excel
        book->save(L"test.xlsx");

        book->release();
    }
    //system("pause");

    return A;
}
