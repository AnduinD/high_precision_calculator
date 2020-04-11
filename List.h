#pragma once
#define BASE_10 10 //��������Ľ�����
#define DIGIT_PER_NODE 4//������ÿһԪ�ش洢��ʮ����λ��

#define LINKED_LIST 1

#define positive  true
#define negative false

#include<cstdlib>

#if LINKED_LIST 
class Node {//������ķ�װ
public:
	int data;//һ����������λ��������λ��ʮ������������ǰ��0��
	Node* next, * prior;

	Node() {//��ʼ��
		data = 0;
		next = NULL;
		prior = NULL;
	}
};
class List {//����ķ�װ
public:
	Node* head;//ͷ���
	bool sign;//������ķ��ţ�trueΪ����falseΪ��

	List() {//��ʼ��
		head = NULL;
		sign = positive;
	}
};
#endif /*Linked List*/

namespace list {
	inline bool IsEmpty(List& L)//�жϱ��Ƿ�Ϊ��
	{
		return L.head == NULL;
	}
	inline bool IsPositive(List& L)//�ж�������ķ��ţ�trueΪ����falseΪ��
	{
		return L.sign;
	}
	inline void negativeMark(List& L)//����L��Ǹ���
	{
		L.sign = negative;
	}
	inline void signReverse(List& L)//�ѱ�L�ķ��ŷ�תһ��
	{
		L.sign = !L.sign;
	}
	inline int getLength(List& L)//ȡ��
	{
		if (IsEmpty(L)) return 0;//�ձ�
		else
		{
			Node* p = L.head;
			int Length = 1;//�Ȱ���Ԫ����
			while (p->next != L.head)
			{
				p = p->next;
				Length++;
			}
			return Length;
		}
	}
	inline void swap(List& x, List& y)//������������
	{
		List temp;
		temp.head = x.head        , temp.sign = x.sign;
		x.head = y.head              , x.sign = y.sign;
		y.head = temp.head        , y.sign = temp.sign;
	}
	void insertHead(List& L, int data);//�ڱ����ͷ�˲���ֵΪdata��Ԫ��
	void append(List& L, int data);//�ڱ�L��β������ֵΪdata��Ԫ��
	void delElem(List& L, int order);//�ӱ��аѵ�orderλ��Ԫ��ɾ��
	void clear(List& L);//���һ����

	inline int compare(List& a, List& b)//�Ƚ�a��b�Ĵ�С������-1(a<b)��0(a==b)��1(a>b)
	{
		if (getLength(a) < getLength(b)) return -1;//a����С��b��ʱ��a<b
		else if (getLength(a) == getLength(b))////a��bͬ����ʱ��
		{//�����λһֱ�ȵ�a��b���ȵ�λ
		 //����λ�ϵ�a<b��������a<b
			Node* temp_a = a.head, * temp_b = b.head;
			if (temp_a->data == temp_b->data)
				do 	temp_a = temp_a->next, temp_b->next;
			while (temp_a->data == temp_b->data && temp_a != a.head && temp_b != b.head);
			if (temp_a->data < temp_b->data) return -1;//a��b����ֵС��ʱ��
			else if (temp_a->data == temp_b->data) return 0;//a��b��ȫ��ȵ�ʱ��
		}
		return 1;//����ʱ�򣬾�ֻʣa>b��
	}
	void add(List& a, List& b, List& ans);//�Ա���͵ĺ���
	void subtract(List& a, List& b, List& ans);//�Ա����ĺ������Ͱ�add()������װ��һ�£�
	void multiply(List& a, List& b, List& ans);//�Ա�����ĺ���
	//void divide(List& a, List& b, List& ans);//�Ա����̵ĺ���
}