#include<algorithm>
#include<cmath>
#include"HAL_high_precision.h"

void hal::convert_str2num(string& S, List& L)
{
	if (S[0] == '-') list::negativeMark(L);//对负数符号的处理
	int top = list::IsPositive(L) ? 0 : 1;//标出数据串的数字头部
	int end = (int)S.size()-1 ;//把数据串数字部分长度取出来
	for (int i = end; i >= top; /*i -= DIGIT_PER_NODE*/)
	{
		int temp_int = 0;//用这个变量暂存四位整数
		for (int j = 0; j < DIGIT_PER_NODE; j++)
		{//内层循环每四位一读
			if (i >= top) //感觉这样处理不太好，本来就最后处理一手就行，这样搞得老是要判断
			{
				//temp_ch[j] = S[i + j];//取出字符串的一位	
				temp_int += int(S[i--] - '0')*(int)pow(BASE_10, j);//把读取的数加到暂存的四位数上去
			}
			else break;
		}
		list::insertHead(L, temp_int);//把这个四位数填到表的尾元位置
	}
}

void hal::convert_num2str(List& L, string& S)
{
	S = ((list::IsPositive(L) ? "" : "-"));//先把答案字串的符号定下来
	Node* cur = L.head;
	do {
		int temp_int = cur->data;//取出四位数
		char temp_ch[DIGIT_PER_NODE];
		//用这个数组当个栈，把数（<=4位）转换为四位的字符串
		for (int i = 0; i < DIGIT_PER_NODE; i++)
		{//四个一循环往答案字符串里加数字字符
			temp_ch[i] = (char)(temp_int % BASE_10) + '0';//取出最低位，转成字符
			temp_int /= 10;//把最低位除掉
		}
		for (int i = DIGIT_PER_NODE - 1; i >= 0; i--)
		{
			S += temp_ch[i];
		}
		cur = cur->next;//指针漫游到下一表项
	} while (cur != L.head);
}

void hal::format(string& S)
{
	int top = S[0] == '-' ? 1 : 0;
	while (S[top] == '0')
		S.erase(top, 1);//这里写去除前导零的操作
	top = S[0] == '-' ? 1 : 0;
	if (S== ""||S=="-") S = '0';//留下最后一个零，把-0改成0
}

void hal::high_precision_add(string& num_1, string& num_2, string& num_ans)//加法运算
{//注：这个函数更多的是对下层的一个调用，自身只是实现数据类型转换
	List longInteger_1, longInteger_2, longInteger_Ans;

	//把读入的两个长整数字符串转成四位十进制一组的整数表
	//注：由于用的表的结构，可以不逆向存储
	//（即不必把最低位存在最前面，最高位存在最后面）
	convert_str2num(num_1, longInteger_1);
	convert_str2num(num_2, longInteger_2);

	list::add(longInteger_1, longInteger_2, longInteger_Ans);//这里进行真正的高精度加运算

	convert_num2str(longInteger_Ans, num_ans);//把答案转回字符串类型
	format(num_ans);//把答案字符串格式化

	list::clear(longInteger_1);
	list::clear(longInteger_2);
	list::clear(longInteger_Ans);
}


void hal::high_precision_subtract(string& num_1, string& num_2, string& num_ans)//减法运算
{//注：这个函数更多的是对下层的一个调用，自身只是实现数据类型转换
	List longInteger_1, longInteger_2, longInteger_Ans;
	convert_str2num(num_1, longInteger_1);
	convert_str2num(num_2, longInteger_2);

	list::signReverse(longInteger_2);//减去一个数变为加上其相反数；
	list::add(longInteger_1, longInteger_2, longInteger_Ans);//进行高精度加运算

	convert_num2str(longInteger_Ans, num_ans);//把答案转回字符串类型
	format(num_ans);//把答案字符串格式化

	list::clear(longInteger_1);
	list::clear(longInteger_2);
	list::clear(longInteger_Ans);
}
void hal::high_precision_multiply(string& num_1, string& num_2, string& num_ans)//乘法运算
{
	List longInteger_1, longInteger_2, longInteger_Ans;
	convert_str2num(num_1, longInteger_1);
	convert_str2num(num_2, longInteger_2);

	list::multiply(longInteger_1, longInteger_2, longInteger_Ans);//这里进行真正的高精度加运算

	convert_num2str(longInteger_Ans, num_ans);//把答案转回字符串类型
	format(num_ans);//把答案字符串格式化

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

	list::divide(longInteger_1, longInteger_2, longInteger_Ans);//这里进行真正的高精度加运算

	convert_num2str(longInteger_Ans, num_ans);//把答案转回字符串类型
	format(num_ans);//把答案字符串格式化

	list::clear(longInteger_1);
	list::clear(longInteger_2);
	list::clear(longInteger_Ans);

}
*/

