#pragma once
#include <string>
#include<cstdio>
#include<iostream>
#include"List.h"

namespace hal {
	using namespace std;
	void convert_str2num(string& s, List& head);//把读入的字符串类型转换为线性表存储的数
	void convert_num2str(List& head, string& S);//把读入的数从线性表存储转换为字符串类型
	void format(string& S);//把数据字符串格式化：去掉前导零，留下最后一个零
	void high_precision_add(string& num_1, string& num_2, string& num_ans);//加法运算
	void high_precision_subtract(string& num_1, string& num_2, string& num_ans);//减法运算
	void high_precision_multiply(string& num_1, string& num_2, string& num_ans);//乘法运算
	//void high_precision_divide(string& num_1, string& num_2, string& num_ans);//除法运算
}