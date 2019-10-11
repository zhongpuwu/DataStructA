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
        cout << t << ":00 汽车" << c.id << "驶入停车场，位置是" << SqStackLength(Sp) << endl;
        PushSqStack(Sp, c);
        return true;
    }
    else
    {
        cout << t << ":00 汽车" << c.id << "驶入便道，位置是" << QueueLength(St) << endl;
        EnQueue(St, c);
        return false;
    }
}

bool OutStop(TheCar &c, int t)
{
    cout << t << ":00 汽车" << c.id << "离开停车场，有效停车时间为" << c.times << endl;
    return true;
}

bool Fill(Stop &Sp, Street &St, int n, int t)
{
    TheCar c;
    while (!Stopfull(Sp, n))
    {
        if (!StreetEmpty(St))
        {
            DeQueue(St, c);
            if (c.out < t)
                cout << t << ":00 汽车" << c.id << "离开便道，有效停车时间为" << c.times << ",等待时间为" << t - c.out << endl;
            else if (c.out == t)
                cout << t << ":00 汽车" << c.id << "离开便道，有效停车时间为" << c.times << endl;
            else
            {
                cout << t << ":00 汽车" << c.id << "离开便道，进入停车场" << endl;
                c.times++;
                PushSqStack(Sp, c);
            }
        }
        else
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
    Stop Sp, Spf;
    InitStreet(St);
    InitStop(Sp, n);
    InitStop(Spf, n); // 构造一个出停车场时的辅助栈

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
        TheCar c;
        while (PopSqStack(Sp, c))
        {
            PushSqStack(Spf, c);
        }
        while (!StopEmpty(Spf))
        {
            PopSqStack(Spf, c);
            if (c.out == t)
            {
                OutStop(c, t);
            }
            else
            {
                c.times++;
                PushSqStack(Sp, c);
            }
        } // 使用辅助栈统计停车场车辆
        if (!StreetEmpty(St) && !Stopfull(Sp, n))
            Fill(Sp, St, n, t); // 填充停车场，清理出场车辆
    }

    DestroyStreet(St);
    DestroyStop(Sp);
    delete[] pCars;

    system("pause");
    return 0;
}
