// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <cstdio>
#include <tchar.h>
#include <iostream>
#include <string>
//#include <>
using namespace std;
class Sale_item
{
private:
	int sales;
	string name;
	string isdn;
	
public:
	Sale_item():sales(0),isdn(),name(){};
	Sale_item(int sales,string name,string isdn):sales(sales),name(name),isdn(isdn){};
	string getName() const {return name;};
	string getIsdn() const{return isdn;};
	int getSales() const{return sales;};
	bool setName(string x){name=x;};
	bool setIsdn(string x){isdn=x;};
	bool setSales(int x){sales=x;};
	static int sum;
//////////////////////////////////////////////////////////////////////////װ������
public:
	
private:
	
};
//ostream & operator<< (ostream &os,Sale_item sa);
// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
