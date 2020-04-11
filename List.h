#pragma once
#define BASE_10 10 //定义运算的进制数
#define DIGIT_PER_NODE 4//定义表的每一元素存储的十进制位数

#define LINKED_LIST 1

#define positive  true
#define negative false

#include<cstdlib>

#if LINKED_LIST 
class Node {//链表结点的封装
public:
	int data;//一个结点所存的位数（存四位的十进制数，包含前导0）
	Node* next, * prior;

	Node() {//初始化
		data = 0;
		next = NULL;
		prior = NULL;
	}
};
class List {//链表的封装
public:
	Node* head;//头结点
	bool sign;//这个数的符号，true为正，false为负

	List() {//初始化
		head = NULL;
		sign = positive;
	}
};
#endif /*Linked List*/

namespace list {
	inline bool IsEmpty(List& L)//判断表是否为空
	{
		return L.head == NULL;
	}
	inline bool IsPositive(List& L)//判断这个数的符号，true为正，false为负
	{
		return L.sign;
	}
	inline void negativeMark(List& L)//给表L标记负号
	{
		L.sign = negative;
	}
	inline void signReverse(List& L)//把表L的符号反转一次
	{
		L.sign = !L.sign;
	}
	inline int getLength(List& L)//取表长
	{
		if (IsEmpty(L)) return 0;//空表
		else
		{
			Node* p = L.head;
			int Length = 1;//先把首元算上
			while (p->next != L.head)
			{
				p = p->next;
				Length++;
			}
			return Length;
		}
	}
	inline void swap(List& x, List& y)//交换两表内容
	{
		List temp;
		temp.head = x.head        , temp.sign = x.sign;
		x.head = y.head              , x.sign = y.sign;
		y.head = temp.head        , y.sign = temp.sign;
	}
	void insertHead(List& L, int data);//在表的最头端插入值为data的元素
	void append(List& L, int data);//在表L的尾部附加值为data的元素
	void delElem(List& L, int order);//从表中把第order位的元素删除
	void clear(List& L);//清空一个表

	inline int compare(List& a, List& b)//比较a和b的大小，返回-1(a<b)、0(a==b)、1(a>b)
	{
		if (getLength(a) < getLength(b)) return -1;//a长度小于b的时候，a<b
		else if (getLength(a) == getLength(b))////a和b同长的时候
		{//从最高位一直比到a、b不等的位
		 //若该位上的a<b则整个的a<b
			Node* temp_a = a.head, * temp_b = b.head;
			if (temp_a->data == temp_b->data)
				do 	temp_a = temp_a->next, temp_b->next;
			while (temp_a->data == temp_b->data && temp_a != a.head && temp_b != b.head);
			if (temp_a->data < temp_b->data) return -1;//a比b的数值小的时候
			else if (temp_a->data == temp_b->data) return 0;//a和b完全相等的时候
		}
		return 1;//其他时候，就只剩a>b了
	}
	void add(List& a, List& b, List& ans);//对表求和的函数
	void subtract(List& a, List& b, List& ans);//对表求差的函数（就把add()函数封装了一下）
	void multiply(List& a, List& b, List& ans);//对表求积的函数
	//void divide(List& a, List& b, List& ans);//对表求商的函数
}