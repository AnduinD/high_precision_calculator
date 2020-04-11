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
#define DATA_AMOUNT 500//������Ҫ���Ե���������
#define LENGTH_LIMIT  1000000//�����������ĵ���󳤶�
#define FILENAME "debug_out_multiply.txt"//�ļ���
#endif/*RECORDING*/


//ѡ�������һ������
#define ADD 1
#define SUBTRACT 0
#define MULTIPLY 0

#if RECORDING
inline int randomize_longint(std::string& S)//�����ʼ��������˳�������ִ�����
{
    int n = (rand()*rand()) % LENGTH_LIMIT;//��Լ������������������ĳ���
    S = rand() % 2 ? "-" : "";
    for (int i = 0; i < n; i++)//����������ÿһλ�����ֵ������ǰ�������ڣ�
    {
        srand(i*time(NULL));
        S += rand() % 10 + '0';
    }
    return n;
}
#endif /*RECORDING*/
int main();

