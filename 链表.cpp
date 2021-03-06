#include "stdafx.h"
#include <iostream>
#include <cstdlib>
using namespace std;

template <class T>
	class LNode
	{
	public:
		T data;
		LNode* next;
		LNode(LNode<T> *ptr = NULL) { next = ptr; }
		LNode(const T &item, LNode<T> *ptr = NULL)
		{
			next = ptr;
			data = item;
		}
	};

template <class T>
class LinkedList:public LNode<T>
{
private:
	
	LNode<T> *head;
	LNode<T> *tail;
	LNode<T> *cur;
	int size;
public:
	LinkedList();
	LinkedList(const T &item) { head = new LNode<T>(item); }
	LinkedList(const LinkedList<T> &a);
	~LinkedList();
	void Clear();
	LNode<T>* Locate(int pos);
	void LinkInsert(const T &a, int pos);
	void LinkDelete(int pos);
	void Linkchange(const T &a, int pos);
	LinkedList<T> &operator =(const LinkedList<T> &a);
	void Linkdisplay();
};

template <class T>
LinkedList<T>::LinkedList()
{
	head = NULL;
	tail = NULL;
	cur = NULL;
	size = 0;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &a)
{
	int n = a.size;
	size = n;
	head = new LNode<T>(a.head->data);
	LNode<T> *temp1 = head;
	LNode<T> *temp2 = a.head;
	for(int i=0;i<n;i++)
	{
		temp2 = temp2->next;
		LinkInsert(temp2->data, i);
		
	}
}

template <class T>
void LinkedList<T>::Clear()
{
	LNode<T>* temp = head;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
	head = NULL;
	tail = NULL;
	cur = NULL;
	size = 0;
}

template <class T>
LinkedList<T>::~LinkedList()
{
	Clear();
}

template <class T>

LNode<T>* LinkedList<T>::Locate(int pos)
{
	int i = 0;
	LNode<T>* temp = head;
	if (pos < 0)
		return NULL;
	while (temp != NULL && i < pos)
	{
		temp = temp->next;
		i++;
	}
	return temp;
}

template <class T>
void LinkedList<T>::LinkInsert(const T &a,int pos)
{
	LNode<T> *p = Locate(pos);
	if (p == NULL)
	{
		if (p == head)
		{
			head = new LNode<T>;
			head->data = a;
		}
			
		else return;

	}
	else
	{
		LNode<T> *temp = new LNode<T>(a);
		temp->next = p->next;
		p->next = temp;
		size++;
	}
}

template <class T>
void LinkedList<T>::LinkDelete(int pos)
{
	LNode<T> *p = Locate(pos);
	LNode<T> *temp = head;
	while (temp->next != p)
	{
		temp = temp->next;
	}
	temp->next = p->next;
	delete p;
	size--;
}

template <class T>
void LinkedList<T>::Linkchange(const T &a, int pos)
{
	LNode<T> *p = Locate(pos);
	p->data = a;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator =(const LinkedList<T> &a)
{
	int n = a.size;
	Clear();
	head = new LNode<T>(a.head->data);
	LNode<T> *temp1 = head;
	LNode<T> *temp2 = a.head;
	for (int i = 0; i<n; i++)
	{
		temp2 = temp2->next;
		LinkInsert(temp2->data, i);

	}
	return *this;
}

template <class T>
void LinkedList<T>::Linkdisplay()
{
	LNode<T>* temp = head;
	while (temp != NULL)
	{
		cout << temp->data << " ";
		temp = temp->next;
	}
}

int main()
{
	//默认构造函数和插入
	LinkedList<int> l1;
	for (int i = 0; i < 15; i++)
	{
		l1.LinkInsert(rand(), 0);
	}
	l1.Linkdisplay();
	cout << endl;

	//拷贝构造函数
	LinkedList<int> l2(l1);
	l2.Linkdisplay();
	cout << endl;

	//重载=
	LinkedList<int> l3;
	for (int i = 0; i < 15; i++)
	{
		l3.LinkInsert(rand(), 0);
	}
	l3.Linkdisplay();
	cout << endl;
	l3 = l1;
	l3.Linkdisplay();
	cout << endl;

	//删除节点
	l1.LinkDelete(3);
	l1.Linkdisplay();
	cout << endl;

	//访问和修改节点
	l1.Linkchange(555, 5);
	l1.Linkdisplay();
	cout << endl;

	cin.get();
	return 0;
}