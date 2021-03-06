// 第七次作业.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#define NUMBER 10000
#define TESTCOUNT 5
typedef struct
{
	int *array;
	int size;
	int number;
}Maxheap;
bool lt(const int &k, const int &e)
{
	return k < e;
}
void swap(int *h, int i, int j)
{
	int z = h[i];
	h[i] = h[j];
	h[j] = z;
}
void inssort(int A[], int n)
{
	int i, j;
	for (i = 0; i<n; i++)
		for (j = i; (j>0) && (lt(A[j], A[j - 1])); j--)
			swap(A, j, j - 1);
}
void inssort2(int A[], int n, int incr)
{
	int i, j;
	for (i = incr; i < n; i += incr)
		for (j = i; (j > incr) && (lt(A[j], A[j - incr])); j -= incr)
			swap(A, j, j - incr);
}
void shellsort(int A[], int n)
{
	int i, j;
	for (i = n / 2; i > 0; i /= 2)
		for (j = 0; j < i; j++)
			inssort2(&A[j], n - j, i);
	inssort2(A, n, 1);
}
int findpivot(int A[], int i, int j)
{
	return (i + j) / 2;
}
int partition(int A[], int l, int r, int &pivot)
{
	do
	{
		while (lt(A[++l], pivot));
		while ((r != 0) && lt(pivot, A[--r]));
		swap(A, l, r);
	} while (l < r);
	swap(A, l, r);
	return l;
}
void qsort(int A[], int i, int j)
{
	int pivotindex, k;
	if (j <= i) return;
	pivotindex = findpivot(A, i, j);
	swap(A, pivotindex, j);
	k = partition(A, i - 1, j, A[j]);
	swap(A, k, j);
	qsort(A, i, k - 1);
	qsort(A, k + 1, j);
}
void mergesort(int A[], int temp[], int left, int right)
{
	int i, j, k, mid;
	if ((right - left) <= 9)
	{
		inssort(&A[left], right - left + 1);
		return;
	}
	mid = (left + right) / 2;
	if (left == right)
		return;
	mergesort(A, temp, left, mid);
	mergesort(A, temp, mid + 1, right);
	for (i = mid; i >= left; i--)
		temp[i] = A[i];
	for (j = 1; j <= right - mid; j++)
		temp[right - j + 1] = A[j + mid];
	for (i = left, j = right, k = left; k <= right; k++)
		if (temp[i] < temp[j])
			A[k] = temp[i++];
		else
			A[k] = temp[j--];
}
void radix(int A[], int B[], int n, int k, int r, int cnt[])
{
	int i, j, rtok;
	for (i = 0, rtok = 1; i < k; i++, rtok *= r)
	{
		for (j = 0; j < r; j++)
			cnt[j] = 0;
		for (j = 0; j < n; j++)
			cnt[(A[j] / rtok) % r]++;
		for (j = 1; j < r; j++)
			cnt[j] = cnt[j - 1] + cnt[j];
		for (j = n - 1; j >= 0; j--)
			B[--cnt[(A[j] / rtok) % r]] = A[j];
		for (j = 0; j < n; j++)
			A[j] = B[j];
	}
}
int leftchild(int pos)
{
	return 2 * pos + 1;
}
int rightchild(int pos)
{
	return 2 * pos + 2;
}
bool isleaf(int number, int pos)
{
	return (pos >= number / 2) && (pos < number);
}
void maxheapSiftdown(Maxheap &heap, int pos)
{
	while (!isleaf(heap.number, pos))
	{
		int j = leftchild(pos);
		int rc = rightchild(pos);
		if ((rc < heap.number) && lt(heap.array[j], heap.array[rc]))
			j = rc;
		if (!lt(heap.array[pos], heap.array[j]))
			return;
		swap(heap.array, pos, j);
		pos = j;
	}
}
void maxheapBuildHeap(Maxheap &heap)
{
	int i;
	for (i = heap.number / 2 - 1; i >= 0; i--)
		maxheapSiftdown(heap, i);
}
bool maxheapCreate(Maxheap &heap, int *array, int num, int maxsize)
{
	heap.array = array;
	heap.number = num;
	heap.size = maxsize;
	maxheapBuildHeap(heap);
	return true;
}
bool maxheapRemovemax(Maxheap &heap, int &val)
{
	if (heap.number == 0)
		return false;
	swap(heap.array, 0, --heap.number);
	if (heap.number != 0)
		maxheapSiftdown(heap, 0);
	val = heap.array[heap.number];
	return true;
}
void heapsort(int A[], int n)
{
	int mval, i;
	Maxheap heap;
	maxheapCreate(heap, A, n, n);
	for (i = 0; i < n; i++)
		maxheapRemovemax(heap, mval);
}
int main()
{
	int data[NUMBER] = { 0 };
	int test[NUMBER] = { 0 };
	int i, j;
	double time, average;
	LARGE_INTEGER begin, end, freq;
	for (i = 0; i < NUMBER; i++)
	{
		data[i] = rand() % NUMBER;
	}
	QueryPerformanceFrequency(&freq);
	for (i = 0, average = 0.0; i < TESTCOUNT; i++)
	{
		for (j = 0; j < NUMBER; j++)
			test[j] = data[j];
		QueryPerformanceCounter(&begin);
		inssort(test, NUMBER);
		QueryPerformanceCounter(&end);
		time = (end.QuadPart - begin.QuadPart) / (double)freq.QuadPart;
		average += time;
		printf("%lf\n", time);
	}
	printf("Insssort's average time is:%lf\n", average / TESTCOUNT);
	for (i = 0, average = 0.0; i < TESTCOUNT; i++)
	{
		for (j = 0; j < NUMBER; j++)
			test[j] = data[j];
		QueryPerformanceCounter(&begin);
		shellsort(test, NUMBER);
		QueryPerformanceCounter(&end);
		time = (end.QuadPart - begin.QuadPart) / (double)freq.QuadPart;
		average += time;
		printf("%lf\n", time);
	}
	printf("Shellsort's average time is:%lf\n", average / TESTCOUNT);
	for (i = 0, average = 0.0; i < TESTCOUNT; i++)
	{
		for (j = 0; j < NUMBER; j++)
			test[j] = data[j];
		QueryPerformanceCounter(&begin);
		qsort(test, 0, NUMBER - 1);
		QueryPerformanceCounter(&end);
		time = (end.QuadPart - begin.QuadPart) / (double)freq.QuadPart;
		average += time;
		printf("%lf\n", time);
	}
	printf("Qsort's average time is:%lf\n", average / TESTCOUNT);
	for (i = 0, average = 0.0; i < TESTCOUNT; i++)
	{
		for (j = 0; j < NUMBER; j++)
			test[j] = data[j];
		QueryPerformanceCounter(&begin);
		heapsort(test, NUMBER);
		QueryPerformanceCounter(&end);
		time = (end.QuadPart - begin.QuadPart) / (double)freq.QuadPart;
		average += time;
		printf("%lf\n", time);
	}
		printf("Heapsort's average time is:%lf\n", average / TESTCOUNT);
	for (i = 0, average = 0.0; i < TESTCOUNT; i++)
	{
		for (j = 0; j < NUMBER; j++)
			test[j] = data[j];
		int *temp = new int[NUMBER];
		QueryPerformanceCounter(&begin);
		mergesort(test, temp, 0, NUMBER - 1);
		QueryPerformanceCounter(&end);
		time = (end.QuadPart - begin.QuadPart) / (double)freq.QuadPart;
		average += time;
		printf("%lf\n", time);
		delete[] temp;
	}
	printf("Mergesort's average time is:%lf\n", average / TESTCOUNT);
	for (i = 0, average = 0.0; i < TESTCOUNT; i++)
	{
		for (j = 0; j < NUMBER; j++)
			test[j] = data[j];
		int *temp = new int[NUMBER];
		int cnt[10] = { 0 };
		QueryPerformanceCounter(&begin);
		radix(test, temp, NUMBER, 5, 10, cnt);
		QueryPerformanceCounter(&end);
		time = (end.QuadPart - begin.QuadPart) / (double)freq.QuadPart;
		average += time;
		printf("%lf\n", time);
		delete[] temp;
	}
	printf("Radix's average time is:%lf\n", average / TESTCOUNT);	
	system("pause");
	return 0;
}