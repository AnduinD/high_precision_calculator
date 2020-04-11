#include<cmath>
#include"List.h"
#include<iostream>

#if LINKED_LIST
void list::insertHead(List& L, int data)
{
    using namespace list;
    if (IsEmpty(L))     //表L为空表的情形
    {
        Node* temp = (Node*)malloc(sizeof(Node));
        temp->data = data;
        L.head = temp;
        temp->next = temp;
        temp->prior = temp;
    }
    else//表非空的时候
    {
        Node* temp = (Node*)malloc(sizeof(Node));
        temp->data = data;
        temp->next = L.head;
        temp->prior = L.head->prior;
        L.head->prior->next = temp;
        L.head->prior = temp;
        L.head = temp;
    }
}
void list::append(List& L, int data)
{//这个和insertHead基本一样，写两遍是想调用的时候清晰些
    using namespace list;
    if (IsEmpty(L))
    {//向空表中加入第一个元素的情况
        Node* temp = (Node*)malloc(sizeof(Node));
        temp->data = data;
        temp->next = temp;//把唯一结点的后继和前驱都引向自己
        temp->prior = temp;
        L.head = temp;//把指向首元的指针引过来
    }
    else
    {//向非空表中加入元素的情况
        Node* temp = (Node*)malloc(sizeof(Node));
        temp->data = data;
        temp->next = L.head;//把新末尾结点的后继引到首元这里来
        temp->prior = L.head->prior;//把其前驱引到原末尾结点来
        L.head->prior->next = temp;//把原末尾结点的后继引导新结点
        L.head->prior = temp;//把首元的前驱引到新结点
    }
}
void list::delElem(List& L, int order)
{
    if (L.head->next == L.head) //只剩一个结点的时候
    {
        L.head->next = L.head->prior = NULL;
        free(L.head);
        L.head = NULL;
    }
    else//表里不只有一个结点的时候
    {
        Node* cur = L.head;

        //把cur移动到待删除元素的头上
        if (order >= 0)
            for (int i = 1; i <= order; i++)
                cur = cur->next;
        else
            for (int i = -1; i >= order; i--)
                cur = cur->prior;

        L.head = cur->next;//把表头接过来先

        ///进行删除时的指针域调整
        cur->prior->next = cur->next;
        cur->next->prior = cur->prior;
        cur->next = NULL;
        cur->prior = NULL;

        free(cur);
        cur = NULL;
    }
}
void list::clear(List& L)
{//清空一个表
    while (!list::IsEmpty(L))
        delElem(L, 1);
}
void list::add(List& a, List& b, List& ans)
{//对表求和的函数
    using namespace list;//引用命名空间list

    //如果传入的是空表，先赋个零元
    if (IsEmpty(a)) insertHead(a, 0);
    if (IsEmpty(b)) insertHead(b, 0);

    if (a.sign == b.sign)
    {//a、b同号时的按加处理
        Node* cur_a = a.head->prior, * cur_b = b.head->prior;//把当前位指针初始引到两表个位的位置
        bool flag_Overflow = false;//是否要进位的标志
        do {
            int temp_int = cur_a->data + cur_b->data + flag_Overflow;//对表格元素进行加法运算
            flag_Overflow = temp_int / (int)pow(BASE_10, DIGIT_PER_NODE) ? true : false;//进位判断
            temp_int %= (int)pow(BASE_10, DIGIT_PER_NODE);//把temp_int高过四位的地方舍去

            insertHead(ans, temp_int);//把元素相加的结果填到ans表里去
            cur_a = cur_a->prior;//往前迭代
            cur_b = cur_b->prior;//往前迭代
        } while (cur_a != a.head->prior && cur_b != b.head->prior);//当其中一个加数被加完时，退出循环

        if (cur_a != a.head->prior || cur_b != b.head->prior)//两边位数不一样高的时候
        {
            Node* surpass = (cur_a == a.head->prior) ? cur_b : cur_a;
            //定义一个surpass指针指向未被加完的加数的剩余位
            do {
                int temp_int = surpass->data + flag_Overflow;
                flag_Overflow = temp_int / (int)pow(BASE_10, DIGIT_PER_NODE) ? true : false;//进位判断
                temp_int %= (int)pow(BASE_10, DIGIT_PER_NODE);
                insertHead(ans, temp_int);//把高位的数往ans表里填
                surpass = surpass->prior;
            } while (surpass != a.head->prior && surpass != b.head->prior);
        }
        else if (flag_Overflow)//两边位数一样高的时候，记得考虑一下，会不会最后有一次进位，像这种情况：9999+0001=1 0000
            insertHead(ans, flag_Overflow);

        if (a.sign == negative) negativeMark(ans);//最后给答案表填上符号
    }//a、b同号时的按加处理结束
    else
    {//a、b异号按减处理

        //先根据绝对值把两个数的大小调个序（绝对值大的在前）
        if (compare(a, b) == -1) swap(a, b);

        Node* cur_a = a.head->prior, * cur_b = b.head->prior;//把当前位指针初始引到两表个位的位置
        ans.sign = a.sign;//根据绝对值大者的符号，把ans的符号定下来

        //竖式减法的具体过程从这里开始
        bool flag_needBorrow = false;//是否需要借位的标志
        do {
            //对表格元素进行减法运算
            int temp_int = cur_a->data - cur_b->data - flag_needBorrow;
            if (temp_int < 0)
            {
                temp_int += (int)pow(BASE_10, DIGIT_PER_NODE);//借位处理
                flag_needBorrow = true;
            }
            else flag_needBorrow = false;//无需借位时，记得把标志复原

            insertHead(ans, temp_int);//把元素相减的结果填到ans表里去
            cur_a = cur_a->prior;//往前迭代
            cur_b = cur_b->prior;//往前迭代
        } while (cur_b != b.head->prior && cur_b != a.head->prior);//当减数被加完时，退出循环

        if (cur_a != a.head->prior)//被减数的位数更高的时候
        {
            Node* surpass = cur_a;
            //定义一个surpass指针指向被减数的剩余位
            do {
                int temp_int = surpass->data - flag_needBorrow;
                if (temp_int < 0)
                {
                    temp_int += (int)pow(BASE_10, DIGIT_PER_NODE);//借位处理
                    flag_needBorrow = true;
                }
                else flag_needBorrow = false;//无需借位时，记得把标志复原
                insertHead(ans, temp_int);//把高位的数往ans表里填
                surpass = surpass->prior;
            } while (surpass != a.head->prior);
        }
    }//a、b异号按减处理结束
}
void list::subtract(List& a, List& b, List& ans)
{
    signReverse(b);//减去一个数变为加上其相反数；
    add(a, b, ans);//进行高精度加运算
}

void list::multiply(List& a, List& b, List& ans)
{
    using namespace list;

    //如果传入的是空表，先赋个零元
    if (IsEmpty(a)) insertHead(a, 0);
    if (IsEmpty(b)) insertHead(b, 0);

    Node* cur_a = a.head->prior;//把第一个乘数指到个位
    Node* cur_b = b.head;//把第二个乘数指到最高位
    bool flag_Overflow = false;//在乘完之后，进行加法运算的时候，进位判断的标志
    do {
        List subAns;//用来存第一个乘数和第二个乘数的一位相乘所得的结果
        int amountCarry = 0;//需要进到下一位的数值
        do {
            int temp_int = cur_a->data * cur_b->data + amountCarry;//对表格元素进行乘法运算
            amountCarry = temp_int / (int)pow(BASE_10, DIGIT_PER_NODE);//carry量的记录
            temp_int %= (int)pow(BASE_10, DIGIT_PER_NODE);//把temp_int高过四位的地方舍去

            insertHead(subAns, temp_int);//把元素相加的结果填到ans表里去
            cur_a = cur_a->prior;//把第一个乘数往高位迭代
        } while (cur_a != a.head->prior);
        if (amountCarry != 0) insertHead(subAns, amountCarry);//最后如果高一位就直接填上去

        List tempAns;//搞一个空的tempAns出来
        add(ans, subAns, tempAns);//把之前加的结果暂存到tempAns中
        ans.head = tempAns.head;//再把要返回的ans指到tempAns这里来
        append(ans, 0);//给低位补零，记得乘法竖式的时候，加法部分每个数是要错开的这里就是起错开的作用
        //因为自己写的这个add()函数需要第三个传入参数为空表才可，所以才需要以上三行怪怪的操作

        cur_b = cur_b->next;//把第二个乘数往低位迭代
    } while (cur_b != b.head);

    delElem(ans, -1);//把最后一次的低位补零去掉
    ans.sign = a.sign == b.sign ? positive : negative;//最后给答案添上符号
}

/*
void list::divide(List& a, List& b, List& ans)
{
    ans.sign = (a.sign == b.sign) ? positive : negative;//先把符号定下来
    switch (compare(a, b))
    {
    case -1:insertHead(ans, 0); return;//a<b的时候
    case 0: insertHead(ans, 1); return;//a==b的时候
    default:break;//剩下的就是a>b的时候
    }

    //Node* cur_a = a.head, * cur_b = b.head;//把两个都先指到最高位
    for (int i = getLength(b); i < getLength(a); i++) append(b, 0);//先把b补到和a一样高
    do {
    } while (1);
}
*/




#endif /*LINKED_LIST*/