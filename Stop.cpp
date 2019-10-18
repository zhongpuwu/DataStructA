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

bool Jump(int &t)
{
    cout << "请输入您要跳转的时间:";
    cin >> t;
    cout << "跳转成功!" << endl;
    return true;
}
bool Come(Street &St, Stop &Sp, int t)
{
    cout << "";
    return true;
}
bool Quit()
{
    return true;
}

// 假设便道无限长
// 规定车辆在停车场中和便道上的移动都是瞬时的

int main()
{
    int t = 0;
    char com;
    int n; // 停车场长度，车辆个数；
    Stop Sp;
    Street St;
    InitStreet(St);  // 构造便道
    InitStop(Sp, n); // 构造停车场

    cout << "请输入停车场的长度";
    cin >> n;
    while (1)
    {
        cout << "当前时间: " << t << ":00" << endl;
        Print(Sp, St, n);
        if (com != 'Q')
        {
            cout << "请输入需要进行的操作:A/D/Q/J" << endl;
            cout << "A代表入站/D代表出站/Q代表结束输入/J代表跳转时间" << endl;
            cin >> com;
            switch (com)
            {
            case 'J':
                Jump(t);
                break;
            case 'A':
                Come(St, Sp, t);
                break;
            case 'D':
                Quit();
                break;
            }
        }
        // TheCar c;
        // while (PopSqStack(Sp, c))
        // {
        //     PushSqStack(Spf, c);
        // }
        // while (!StopEmpty(Spf))
        // {
        //     PopSqStack(Spf, c);
        //     if (c.out == t)
        //     {
        //         OutStop(c, t);
        //     }
        //     else
        //     {
        //         c.times++;
        //         PushSqStack(Sp, c);
        //     }
        // }
        // 借助辅助栈统计停车场车辆 和出停车场的操作

        if (!StreetEmpty(St) && !Stopfull(Sp, n))
        {
            Fill(Sp, St, n, t);
        }
        // 填充停车场，清理出场车辆
        if (!StopEmpty(Sp))
            break;
    }

    DestroyStreet(St);
    DestroyStop(Sp);

    system("pause");
    return 0;
}
