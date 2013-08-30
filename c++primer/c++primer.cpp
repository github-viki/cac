// c++primer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
 ostream & operator << (ostream &os,const Sale_item& sa)
{
//	os<<this->getIsdn()<<'\t'<<this->getName()<<'\t'<<this->getSales()<<endl;
	os<<sa.getIsdn()<<'\t'<<sa.getName()<<'\t'<<sa.getSales()<<endl;
	return os;
}
int  Sale_item::sum=0;
int _tmain(int argc, _TCHAR* argv[])
{
	
	Sale_item a;
	//a.test=0;
	cout<<a;
	Sale_item b(1,"a","n");
	cout<<b;
	cout<<"haha"<<endl;
	//cout<<Sale_item::test<<endl;
	return 0;
}

