#include<cmath>
#include"List.h"
#include<iostream>

#if LINKED_LIST
void list::insertHead(List& L, int data)
{
    using namespace list;
    if (IsEmpty(L))     //��LΪ�ձ������
    {
        Node* temp = (Node*)malloc(sizeof(Node));
        temp->data = data;
        L.head = temp;
        temp->next = temp;
        temp->prior = temp;
    }
    else//��ǿյ�ʱ��
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
{//�����insertHead����һ����д����������õ�ʱ������Щ
    using namespace list;
    if (IsEmpty(L))
    {//��ձ��м����һ��Ԫ�ص����
        Node* temp = (Node*)malloc(sizeof(Node));
        temp->data = data;
        temp->next = temp;//��Ψһ���ĺ�̺�ǰ���������Լ�
        temp->prior = temp;
        L.head = temp;//��ָ����Ԫ��ָ��������
    }
    else
    {//��ǿձ��м���Ԫ�ص����
        Node* temp = (Node*)malloc(sizeof(Node));
        temp->data = data;
        temp->next = L.head;//����ĩβ���ĺ��������Ԫ������
        temp->prior = L.head->prior;//����ǰ������ԭĩβ�����
        L.head->prior->next = temp;//��ԭĩβ���ĺ�������½��
        L.head->prior = temp;//����Ԫ��ǰ�������½��
    }
}
void list::delElem(List& L, int order)
{
    if (L.head->next == L.head) //ֻʣһ������ʱ��
    {
        L.head->next = L.head->prior = NULL;
        free(L.head);
        L.head = NULL;
    }
    else//���ﲻֻ��һ������ʱ��
    {
        Node* cur = L.head;

        //��cur�ƶ�����ɾ��Ԫ�ص�ͷ��
        if (order >= 0)
            for (int i = 1; i <= order; i++)
                cur = cur->next;
        else
            for (int i = -1; i >= order; i--)
                cur = cur->prior;

        L.head = cur->next;//�ѱ�ͷ�ӹ�����

        ///����ɾ��ʱ��ָ�������
        cur->prior->next = cur->next;
        cur->next->prior = cur->prior;
        cur->next = NULL;
        cur->prior = NULL;

        free(cur);
        cur = NULL;
    }
}
void list::clear(List& L)
{//���һ����
    while (!list::IsEmpty(L))
        delElem(L, 1);
}
void list::add(List& a, List& b, List& ans)
{//�Ա���͵ĺ���
    using namespace list;//���������ռ�list

    //���������ǿձ��ȸ�����Ԫ
    if (IsEmpty(a)) insertHead(a, 0);
    if (IsEmpty(b)) insertHead(b, 0);

    if (a.sign == b.sign)
    {//a��bͬ��ʱ�İ��Ӵ���
        Node* cur_a = a.head->prior, * cur_b = b.head->prior;//�ѵ�ǰλָ���ʼ���������λ��λ��
        bool flag_Overflow = false;//�Ƿ�Ҫ��λ�ı�־
        do {
            int temp_int = cur_a->data + cur_b->data + flag_Overflow;//�Ա��Ԫ�ؽ��мӷ�����
            flag_Overflow = temp_int / (int)pow(BASE_10, DIGIT_PER_NODE) ? true : false;//��λ�ж�
            temp_int %= (int)pow(BASE_10, DIGIT_PER_NODE);//��temp_int�߹���λ�ĵط���ȥ

            insertHead(ans, temp_int);//��Ԫ����ӵĽ���ans����ȥ
            cur_a = cur_a->prior;//��ǰ����
            cur_b = cur_b->prior;//��ǰ����
        } while (cur_a != a.head->prior && cur_b != b.head->prior);//������һ������������ʱ���˳�ѭ��

        if (cur_a != a.head->prior || cur_b != b.head->prior)//����λ����һ���ߵ�ʱ��
        {
            Node* surpass = (cur_a == a.head->prior) ? cur_b : cur_a;
            //����һ��surpassָ��ָ��δ������ļ�����ʣ��λ
            do {
                int temp_int = surpass->data + flag_Overflow;
                flag_Overflow = temp_int / (int)pow(BASE_10, DIGIT_PER_NODE) ? true : false;//��λ�ж�
                temp_int %= (int)pow(BASE_10, DIGIT_PER_NODE);
                insertHead(ans, temp_int);//�Ѹ�λ������ans������
                surpass = surpass->prior;
            } while (surpass != a.head->prior && surpass != b.head->prior);
        }
        else if (flag_Overflow)//����λ��һ���ߵ�ʱ�򣬼ǵÿ���һ�£��᲻�������һ�ν�λ�������������9999+0001=1 0000
            insertHead(ans, flag_Overflow);

        if (a.sign == negative) negativeMark(ans);//�����𰸱����Ϸ���
    }//a��bͬ��ʱ�İ��Ӵ������
    else
    {//a��b��Ű�������

        //�ȸ��ݾ���ֵ���������Ĵ�С�����򣨾���ֵ�����ǰ��
        if (compare(a, b) == -1) swap(a, b);

        Node* cur_a = a.head->prior, * cur_b = b.head->prior;//�ѵ�ǰλָ���ʼ���������λ��λ��
        ans.sign = a.sign;//���ݾ���ֵ���ߵķ��ţ���ans�ķ��Ŷ�����

        //��ʽ�����ľ�����̴����￪ʼ
        bool flag_needBorrow = false;//�Ƿ���Ҫ��λ�ı�־
        do {
            //�Ա��Ԫ�ؽ��м�������
            int temp_int = cur_a->data - cur_b->data - flag_needBorrow;
            if (temp_int < 0)
            {
                temp_int += (int)pow(BASE_10, DIGIT_PER_NODE);//��λ����
                flag_needBorrow = true;
            }
            else flag_needBorrow = false;//�����λʱ���ǵðѱ�־��ԭ

            insertHead(ans, temp_int);//��Ԫ������Ľ���ans����ȥ
            cur_a = cur_a->prior;//��ǰ����
            cur_b = cur_b->prior;//��ǰ����
        } while (cur_b != b.head->prior && cur_b != a.head->prior);//������������ʱ���˳�ѭ��

        if (cur_a != a.head->prior)//��������λ�����ߵ�ʱ��
        {
            Node* surpass = cur_a;
            //����һ��surpassָ��ָ�򱻼�����ʣ��λ
            do {
                int temp_int = surpass->data - flag_needBorrow;
                if (temp_int < 0)
                {
                    temp_int += (int)pow(BASE_10, DIGIT_PER_NODE);//��λ����
                    flag_needBorrow = true;
                }
                else flag_needBorrow = false;//�����λʱ���ǵðѱ�־��ԭ
                insertHead(ans, temp_int);//�Ѹ�λ������ans������
                surpass = surpass->prior;
            } while (surpass != a.head->prior);
        }
    }//a��b��Ű����������
}
void list::subtract(List& a, List& b, List& ans)
{
    signReverse(b);//��ȥһ������Ϊ�������෴����
    add(a, b, ans);//���и߾��ȼ�����
}

void list::multiply(List& a, List& b, List& ans)
{
    using namespace list;

    //���������ǿձ��ȸ�����Ԫ
    if (IsEmpty(a)) insertHead(a, 0);
    if (IsEmpty(b)) insertHead(b, 0);

    Node* cur_a = a.head->prior;//�ѵ�һ������ָ����λ
    Node* cur_b = b.head;//�ѵڶ�������ָ�����λ
    bool flag_Overflow = false;//�ڳ���֮�󣬽��мӷ������ʱ�򣬽�λ�жϵı�־
    do {
        List subAns;//�������һ�������͵ڶ���������һλ������õĽ��
        int amountCarry = 0;//��Ҫ������һλ����ֵ
        do {
            int temp_int = cur_a->data * cur_b->data + amountCarry;//�Ա��Ԫ�ؽ��г˷�����
            amountCarry = temp_int / (int)pow(BASE_10, DIGIT_PER_NODE);//carry���ļ�¼
            temp_int %= (int)pow(BASE_10, DIGIT_PER_NODE);//��temp_int�߹���λ�ĵط���ȥ

            insertHead(subAns, temp_int);//��Ԫ����ӵĽ���ans����ȥ
            cur_a = cur_a->prior;//�ѵ�һ����������λ����
        } while (cur_a != a.head->prior);
        if (amountCarry != 0) insertHead(subAns, amountCarry);//��������һλ��ֱ������ȥ

        List tempAns;//��һ���յ�tempAns����
        add(ans, subAns, tempAns);//��֮ǰ�ӵĽ���ݴ浽tempAns��
        ans.head = tempAns.head;//�ٰ�Ҫ���ص�ansָ��tempAns������
        append(ans, 0);//����λ���㣬�ǵó˷���ʽ��ʱ�򣬼ӷ�����ÿ������Ҫ��������������������
        //��Ϊ�Լ�д�����add()������Ҫ�������������Ϊ�ձ�ſɣ����Բ���Ҫ�������йֵֹĲ���

        cur_b = cur_b->next;//�ѵڶ�����������λ����
    } while (cur_b != b.head);

    delElem(ans, -1);//�����һ�εĵ�λ����ȥ��
    ans.sign = a.sign == b.sign ? positive : negative;//���������Ϸ���
}

/*
void list::divide(List& a, List& b, List& ans)
{
    ans.sign = (a.sign == b.sign) ? positive : negative;//�Ȱѷ��Ŷ�����
    switch (compare(a, b))
    {
    case -1:insertHead(ans, 0); return;//a<b��ʱ��
    case 0: insertHead(ans, 1); return;//a==b��ʱ��
    default:break;//ʣ�µľ���a>b��ʱ��
    }

    //Node* cur_a = a.head, * cur_b = b.head;//����������ָ�����λ
    for (int i = getLength(b); i < getLength(a); i++) append(b, 0);//�Ȱ�b������aһ����
    do {
    } while (1);
}
*/




#endif /*LINKED_LIST*/