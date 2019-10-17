#ifndef _Realign_H_
#define _Realign_H_

struct TheCar
{
    bool able = true; // 记录数据有效性
    int id = 0;       // 记录车牌
    int times = 0;    // 记录有效时长
    int in = 0;       // 记录进场时刻
    int out = 0;      // 记录意愿出场时刻
};

typedef TheCar SElemType;
typedef TheCar QElemType;

#include "SqStack.h"
#include "LinkQueue.h"

typedef LinkQueue Street;
typedef SqStack Stop;

void InitStreet(LinkQueue &St)
{
    InitQueue(St);
}

void InitStop(SqStack &Sp, int n)
{
    InitSqStack(Sp, n);
}

void DestroyStreet(LinkQueue &St)
{
    DestroyQueue(St);
}

void DestroyStop(SqStack &Sp)
{
    DestroySqStack(Sp);
}

bool Stopfull(SqStack &St, int n)
{
    if (SqStackLength(St) >= n)
        return true;
    else
        return false;
}

bool StreetEmpty(LinkQueue &St)
{
    return QueueEmpty(St);
}

bool StopEmpty(SqStack &Sp)
{
    return SqStackEmpty(Sp);
}

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
                cout << t << ":00 汽车" << c.id << "离开便道，有效停车时间为" << c.times << ",比意愿时间晚了" << t - c.out << "时刻" << endl;
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

#endif