//==============================================
// 停车场问题
//----------------------------------------------
// 作者：武重甫
// 学号：17032430
// 修订：2017年10月
//==============================================

#include <iostream>
using namespace std;

#include "Move.h"

TheCar *pCars;

// 假设便道无限长
// 规定车辆在停车场中和便道上的移动都是瞬时的
// 结束了所有输入后才可以进行停车场模拟
// 时间控制在20个时刻内

bool In(Street &St, Stop &Sp, TheCar &c, int n, int t)
{
    if (!Stopfull(Sp, n))
    {
        cout << "在" << t << "时刻，车牌为" << c.id << "的汽车驶入停车场，位置是" << SqStackLength(Sp) << endl;
        PushSqStack(Sp, c);
        return true;
    }
    else
    {
        cout << "在" << t << "时刻，车牌为" << c.id << "的汽车驶入便道，位置是" << QueueLength(St) << endl;
        EnQueue(St, c);
        return false;
    }
}

bool OutStreet(Street &St, LinkNode *pre, int t)
{
    LinkNode *p = pre->next;
    pre->next = p->next;
    cout << "在" << t << "时刻，车牌为" << p->data.id << "的汽车离开便道，有效停车时间为" << p->data.times << endl;
    p = NULL;
    return true;
}

bool OutStop(Stop &Sp, Street &St, int id, int t)
{
    TheCar c;
    do
    {
        PopSqStack(Sp, c);
    } while (c.id != id);
    EnQueue(St, c);
    cout << "在" << t << "时刻，车牌为" << c.id << "的汽车离开停车场，有效停车时间为" << c.times << endl;
    return true;
}

bool Fill(Stop &Sp, Street &St, int n)
{
    TheCar c;
    while (!Stopfull(Sp, n))
    {
        DeQueue(St, c);
        PushSqStack(Sp, c);
        if (StreetEmpty(St))
            break;
    }
    return true;
}

int main()
{
    int n, x; //停车场长度，车辆个数；

    cout << "请输入停车场的长度";
    cin >> n;
    cout << "请输入车辆的个数";
    cin >> x;
    cout << "请依次输入车辆信息：车牌 到达时间 离开时间\n";
    pCars = new TheCar[x];
    for (int i = 0; i < x; i++)
    {
        cin >> pCars[i].id >> pCars[i].in >> pCars[i].out;
        pCars[i].able = true;
    }
    Street St;
    Stop Sp;
    InitStreet(St);
    InitStop(Sp, n);

    for (int t = 0; t < 20; t++)
    {
        for (int j = 0; j < x; j++)
        {
            if (pCars[j].in == t && pCars[j].able == true)
            {
                In(St, Sp, pCars[j], n, t);
                pCars[j].able = false;
            }
        }
        for (int j = 0; j < SqStackLength(Sp); j++)
        {
            if ((Sp.base + j)->out == t)
                OutStop(Sp, St, (Sp.base + j)->id, t);
            else
                (Sp.base + j)->times++;
        }
        TheCar c;
        if (!StreetEmpty(St))
            if (St.front->data.out == t)
            {
                DeQueue(St, c);
                cout << "在" << t << "时刻，车牌为" << c.id << "的汽车离开便道，有效停车时间为" << c.times << endl;
            }
        if (St.front->next != NULL && St.front != NULL)
            for (LinkNode *p = St.front; p->next->next != NULL; p = p->next)
            {
                if (p->next->data.out == t)
                    OutStreet(St, p, t);
            }
        if (!StreetEmpty(St) && !Stopfull(Sp, n))
            Fill(Sp, St, n);
    }

    DestroyStreet(St);
    DestroyStop(Sp);
    delete[] pCars;

    system("pause");
    return 0;
}
