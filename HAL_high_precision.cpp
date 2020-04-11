#include<algorithm>
#include<cmath>
#include"HAL_high_precision.h"

void hal::convert_str2num(string& S, List& L)
{
	if (S[0] == '-') list::negativeMark(L);//�Ը������ŵĴ���
	int top = list::IsPositive(L) ? 0 : 1;//������ݴ�������ͷ��
	int end = (int)S.size()-1 ;//�����ݴ����ֲ��ֳ���ȡ����
	for (int i = end; i >= top; /*i -= DIGIT_PER_NODE*/)
	{
		int temp_int = 0;//����������ݴ���λ����
		for (int j = 0; j < DIGIT_PER_NODE; j++)
		{//�ڲ�ѭ��ÿ��λһ��
			if (i >= top) //�о���������̫�ã������������һ�־��У������������Ҫ�ж�
			{
				//temp_ch[j] = S[i + j];//ȡ���ַ�����һλ	
				temp_int += int(S[i--] - '0')*(int)pow(BASE_10, j);//�Ѷ�ȡ�����ӵ��ݴ����λ����ȥ
			}
			else break;
		}
		list::insertHead(L, temp_int);//�������λ������βԪλ��
	}
}

void hal::convert_num2str(List& L, string& S)
{
	S = ((list::IsPositive(L) ? "" : "-"));//�ȰѴ��ִ��ķ��Ŷ�����
	Node* cur = L.head;
	do {
		int temp_int = cur->data;//ȡ����λ��
		char temp_ch[DIGIT_PER_NODE];
		//��������鵱��ջ��������<=4λ��ת��Ϊ��λ���ַ���
		for (int i = 0; i < DIGIT_PER_NODE; i++)
		{//�ĸ�һѭ�������ַ�����������ַ�
			temp_ch[i] = (char)(temp_int % BASE_10) + '0';//ȡ�����λ��ת���ַ�
			temp_int /= 10;//�����λ����
		}
		for (int i = DIGIT_PER_NODE - 1; i >= 0; i--)
		{
			S += temp_ch[i];
		}
		cur = cur->next;//ָ�����ε���һ����
	} while (cur != L.head);
}

void hal::format(string& S)
{
	int top = S[0] == '-' ? 1 : 0;
	while (S[top] == '0')
		S.erase(top, 1);//����дȥ��ǰ����Ĳ���
	top = S[0] == '-' ? 1 : 0;
	if (S== ""||S=="-") S = '0';//�������һ���㣬��-0�ĳ�0
}

void hal::high_precision_add(string& num_1, string& num_2, string& num_ans)//�ӷ�����
{//ע���������������Ƕ��²��һ�����ã�����ֻ��ʵ����������ת��
	List longInteger_1, longInteger_2, longInteger_Ans;

	//�Ѷ���������������ַ���ת����λʮ����һ���������
	//ע�������õı�Ľṹ�����Բ�����洢
	//�������ذ����λ������ǰ�棬���λ��������棩
	convert_str2num(num_1, longInteger_1);
	convert_str2num(num_2, longInteger_2);

	list::add(longInteger_1, longInteger_2, longInteger_Ans);//������������ĸ߾��ȼ�����

	convert_num2str(longInteger_Ans, num_ans);//�Ѵ�ת���ַ�������
	format(num_ans);//�Ѵ��ַ�����ʽ��

	list::clear(longInteger_1);
	list::clear(longInteger_2);
	list::clear(longInteger_Ans);
}


void hal::high_precision_subtract(string& num_1, string& num_2, string& num_ans)//��������
{//ע���������������Ƕ��²��һ�����ã�����ֻ��ʵ����������ת��
	List longInteger_1, longInteger_2, longInteger_Ans;
	convert_str2num(num_1, longInteger_1);
	convert_str2num(num_2, longInteger_2);

	list::signReverse(longInteger_2);//��ȥһ������Ϊ�������෴����
	list::add(longInteger_1, longInteger_2, longInteger_Ans);//���и߾��ȼ�����

	convert_num2str(longInteger_Ans, num_ans);//�Ѵ�ת���ַ�������
	format(num_ans);//�Ѵ��ַ�����ʽ��

	list::clear(longInteger_1);
	list::clear(longInteger_2);
	list::clear(longInteger_Ans);
}
void hal::high_precision_multiply(string& num_1, string& num_2, string& num_ans)//�˷�����
{
	List longInteger_1, longInteger_2, longInteger_Ans;
	convert_str2num(num_1, longInteger_1);
	convert_str2num(num_2, longInteger_2);

	list::multiply(longInteger_1, longInteger_2, longInteger_Ans);//������������ĸ߾��ȼ�����

	convert_num2str(longInteger_Ans, num_ans);//�Ѵ�ת���ַ�������
	format(num_ans);//�Ѵ��ַ�����ʽ��

	list::clear(longInteger_1);
	list::clear(longInteger_2);
	list::clear(longInteger_Ans);
}

/*
void hal::high_precision_divide(string& num_1, string& num_2, string& num_ans)
{
	List longInteger_1, longInteger_2, longInteger_Ans;
	convert_str2num(num_1, longInteger_1);
	convert_str2num(num_2, longInteger_2);

	list::divide(longInteger_1, longInteger_2, longInteger_Ans);//������������ĸ߾��ȼ�����

	convert_num2str(longInteger_Ans, num_ans);//�Ѵ�ת���ַ�������
	format(num_ans);//�Ѵ��ַ�����ʽ��

	list::clear(longInteger_1);
	list::clear(longInteger_2);
	list::clear(longInteger_Ans);

}
*/

