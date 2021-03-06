// C++四单元作业.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using namespace std;
class matrix
{
public:
	matrix();
	friend matrix operator + (matrix, matrix);
	friend ostream & operator <<(ostream &, matrix &);
	friend istream & operator >>(istream &, matrix &);
private:
	int t[2][3];
};
matrix::matrix()
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 3; j++)
			t[i][j] = 0;
}
matrix operator +(matrix a, matrix b)
{
	matrix c;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 3; j++)
			c.t[i][j] = a.t[i][j] + b.t[i][j];
	return c;
}
ostream & operator << (ostream &output, matrix &a)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
			output << a.t[i][j] << "   ";
		output << endl;
	}
	return output;
}
istream & operator >>(istream &input, matrix &a)
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 3; j++)
			input >> a.t[i][j];
	return input;
}
int main()
{
	matrix a, b,c;
	cout << "Please input matrix a." << endl;
	cin >> a;
	cout << "Please input matrix b." << endl;
	cin >> b;
	cout << "a:" << endl << a;
	cout << "b:" << endl << b;
	c = a + b;
	cout << "c:" << endl << c;
	system("pause");
	return 0;
}
