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
    InitStop(Spf, n); // 构造一个出停车场的辅助栈

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
