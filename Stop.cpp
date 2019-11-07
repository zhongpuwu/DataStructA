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
    cout << endl;
    cout << "跳转成功!\n"
         << endl;
    return true;
}
bool Come(Street &St, Stop &Sp, int n, int &t)
{
    TheCar c;
    int time;
Label1:
    // 用于重新输入 不想写循环
    cout << "请依次输入车牌 到达时间" << endl;
    cin >> c.id >> time;
    cout << endl;
    if (Search(Sp, St, n, c.id))
    {
        cout << "车牌已被占用，请换一个！\n"
             << endl;
        goto Label1;
    }
    else if (time < t)
    {
        cout << "入站时间不能小于当前时间，请换一个！\n"
             << endl;
        goto Label1;
    }
    else
    {

        c.in = time;
        t = time;
        In(St, Sp, c, n, t);
        return true;
    }
}
bool Quit(Street &St, Stop &Sp, int n, int t)
{
    int id, time;
Label2:
    // 用于重新输入 不想写循环
    cout << "请依次输入车牌 出站时间" << endl;
    cin >> id >> time;
    cout << endl;
    if (!Search_write(Sp, St, n, id, time))
    {
        cout << "查无此车\n"
             << endl;
        goto Label2;
    }
    else if (time < t)
    {
        cout << "出站时间不能小于当前时间，请换一个！\n"
             << endl;
        goto Label2;
    }
    else
    {
        cout << "出站意愿已经写入！" << endl;
        return true;
    }
}

// 假设便道无限长
// 规定车辆在停车场中和便道上的移动都是瞬时的
// 进停车场可以改变时间 出只会记录时间

int main()
{
    int t = 0;
    char com = ' ';
    int n; // 停车场长度，车辆个数；
    Stop Sp;
    Street St;
    InitStreet(St);  // 构造便道
    InitStop(Sp, n); // 构造停车场

    cout << "请输入停车场的长度";
    cin >> n;
    while (1)
    {
        cout << endl;
        cout << "当前时间: " << t << ":00" << endl;
        Print(Sp, St, n); // 打印停车场当前状态
        cout << endl;
        if (com != 'Q')
        {
            cout << "请输入需要进行的操作:A/D/Q/J ";
            cout << "PS:(A代表入站/D代表出站/Q代表结束输入/J代表跳转时间)" << endl;
            cin >> com;
            cout << endl;
            switch (com)
            {
            case 'J':
                Jump(t);
                break;
            case 'A':
                Come(St, Sp, n, t);
                break;
            case 'D':
                if (!StopEmpty(Sp))
                    Quit(St, Sp, n, t);
                else
                {
                    cout << "停车场为空时不能出站" << endl;
                    continue;
                }
                break;
            case 'Q':
                goto Label3;
                // 直接判断停车场是否为空
            default:
                cout << "指令不存在，请重新输入" << endl;
                continue;
            }
        }
        else
        {
        Label3:
            // 如果输入了Q就进行判断 判断成功才能结束程序
            if (StreetEmpty(St) && StopEmpty(Sp))
            {
                cout << "停车场已空!程序结束!" << endl;
                break;
            }
            else if (!StopEmpty(Sp))
            {
                cout << "停车场还有车辆未使出，请重新输入指令" << endl;
                com = ' ';
                continue;
            }
        }

        if (!StopEmpty(Sp))
        {
            OutStop(Sp, n, t);
        }

        if (!StreetEmpty(St) && !Stopfull(Sp, n))
        {
            Fill(Sp, St, n, t);
        }
    }

    DestroyStreet(St);
    DestroyStop(Sp);

    system("pause");
    return 0;
}
