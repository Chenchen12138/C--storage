// C++第一次上机.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
int main()
{
	char b[3] = { 'd','e','f' };
	const char a = 'a';    //常量
	char* const p1=b;        //常指针
	const char *p2;        //指向常量的指针
	const char* const p3=&a;   //指向常量的常指针
}