#include "main.h"
#if DEBUG
using namespace std;

int main()
{
#if CONSOLE
    const string num1[] = { "0", "-23456789",         "-99999999",  "100010001",   "100010001", "-999999999999", "1000099999999"};
    const string num2[] = { "0", "-76543211", "1000000000000", "-100010001", "-100010000", "-999999999999",                         "1"};
    //应输出                       "0""-100000000"	  "999900000001"		            "0"	               "1" "-1999999999998"   "1000100000000"
    for (int z = 0; z < 7; z++)
    {
        string num_1 = num1[z], num_2 = num2[z]; //用这两个字符串接受读入的长整数
        string num_ans = "";           //用这个数作为返回的结果

        cout << num_1 << '\n' << num_2 << endl;
#elif RECORDING
    freopen(FILENAME, "w", stdout);
    for (int z = 1; z <= DATA_AMOUNT; z++)//循环测试z组数据
    {
        string num_1 = "", num_2 = ""; //用这两个字符串接受读入的长整数
        string num_ans = "";           //用这个数作为返回的结果

        //随机初始化大整数
        srand(z);//随机种子初始化
        int len_1 = randomize_longint(num_1);
        int len_2 = randomize_longint(num_2);
#endif /*debug mode:console or record*/

        LARGE_INTEGER startTick, endTick, Tick_Per_Sec;
        QueryPerformanceFrequency(&Tick_Per_Sec);//计时频率初始化

        //注：这里的时间记录把数据类型转换的时间也记录进来了
        QueryPerformanceCounter(&startTick);//计时开始
#if ADD
        hal::high_precision_add(num_1, num_2, num_ans);//实验运算
#endif/*ADD*/
#if SUBTRACT
        hal::high_precision_subtract(num_1, num_2, num_ans);//实验运算
#endif /*SUBTRACT*/
#if MULTIPLY
        hal::high_precision_multiply(num_1, num_2, num_ans);//实验运算
#endif/*MULTIPLY*/
        QueryPerformanceCounter(&endTick);//计时结束

#if CONSOLE
        cout << "ans= " << num_ans << endl;
        cout << "running time: " << (double)(endTick.QuadPart - startTick.QuadPart) / (double)Tick_Per_Sec.QuadPart << "s" << endl;
    }
        system("pause");
#elif RECORDING
         //把输入数据的规模（位数）和运算时间打成一张表
        cout << max(len_1, len_2) << "\t";
        cout << (double)(endTick.QuadPart - startTick.QuadPart) / Tick_Per_Sec.QuadPart << "\n";
    }
    fclose(stdout);
#endif /*debug mode:console or record*/

    return 0;
}
#endif /*DEBUG*/