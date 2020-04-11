#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<iostream>
#include<string>
#include<ctime>
#include<algorithm>
#include<windows.h>
#include"HAL_high_precision.h"

#define DEBUG 1

#define CONSOLE 1
#define RECORDING 0

#if RECORDING
#define DATA_AMOUNT 500//调整需要测试的数据组数
#define LENGTH_LIMIT  1000000//调整长整数的的最大长度
#define FILENAME "debug_out_multiply.txt"//文件名
#endif/*RECORDING*/


//选择测试哪一种运算
#define ADD 1
#define SUBTRACT 0
#define MULTIPLY 0

#if RECORDING
inline int randomize_longint(std::string& S)//随机初始化函数，顺带返回字串长度
{
    int n = (rand()*rand()) % LENGTH_LIMIT;//在约定长度内随机大整数的长度
    S = rand() % 2 ? "-" : "";
    for (int i = 0; i < n; i++)//给大整数的每一位随机赋值（包括前导零在内）
    {
        srand(i*time(NULL));
        S += rand() % 10 + '0';
    }
    return n;
}
#endif /*RECORDING*/
int main();

