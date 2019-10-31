#ifndef _Realign_H_
#define _Realign_H_

struct TheCar
{
    int id = 0;    // 记录车牌
    int times = 0; // 记录有效时长
    int in = 0;    // 记录进场时刻
    int out = 10000;  // 记录意愿出场时刻
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

// 车辆驶入动作
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

// 停车场车辆驶出
bool OutStop(Stop &Sp, int n, int t)
{
    TheCar c;
    Stop Spf;
    InitStop(Spf, n);
    while (PopSqStack(Sp, c))
    {
        PushSqStack(Spf, c);
    }
    while (PopSqStack(Spf, c))
    {
        if (c.out <= t)
        {
            cout << t << ":00 汽车" << c.id << "离开停车场，有效停车时间为" << c.times << endl;
        }
        else
        {
            c.times++;
            PushSqStack(Sp, c);
        }
    }
    DestroyStop(Spf);
    return true;
}

// 填充停车场，清理出场车辆
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

// 打印出停车场当前状态
bool Print(Stop &Sp, Street &St, int n)
{
    Street Stf;
    Stop Spf;
    TheCar c;
    InitStop(Spf, n);
    InitStreet(Stf);
    while (PopSqStack(Sp, c))
    {
        PushSqStack(Spf, c);
    }
    cout << "停车场:";
    while (PopSqStack(Spf, c))
    {
        cout << c.id << " ";
        PushSqStack(Sp, c);
    }
    cout << endl;
    cout << "便道:";
    while (DeQueue(St, c))
    {
        cout << c.id << " ";
        EnQueue(Stf, c);
    }
    DestroyStreet(St);
    DestroyStop(Spf);
    St = Stf;
    cout << endl;
    return true;
}

// 查找车牌号 返回查找结果
bool Search(Stop &Sp, Street &St, int n, int id)
{
    Street Stf;
    Stop Spf;
    TheCar c;
    int flag = 0;
    InitStop(Spf, n);
    InitStreet(Stf);
    while (PopSqStack(Sp, c))
    {
        PushSqStack(Spf, c);
    }
    while (PopSqStack(Spf, c))
    {
        if (c.id == id)
            flag = 1;
        PushSqStack(Sp, c);
    }
    if (flag)
        return true;
    while (DeQueue(St, c))
    {
        if (c.id == id)
            flag = 1;
        EnQueue(Stf, c);
    }
    DestroyStreet(St);
    DestroyStop(Spf);
    if (flag)
        return true;
    else
        return false;
}
bool Search_write(Stop &Sp, Street &St, int n, int id, int out)
{
    Street Stf;
    Stop Spf;
    TheCar c;
    int flag = 0;
    InitStop(Spf, n);
    InitStreet(Stf);
    while (PopSqStack(Sp, c))
    {
        PushSqStack(Spf, c);
    }
    while (PopSqStack(Spf, c))
    {
        if (c.id == id)
        {
            flag = 1;
            c.out = out;
        }
        PushSqStack(Sp, c);
    }
    if (flag)
        return true;
    while (DeQueue(St, c))
    {
        if (c.id == id)
        {
            flag = 1;
            c.out = out;
        }
        EnQueue(Stf, c);
    }
    DestroyStreet(St);
    DestroyStop(Spf);
    if (flag)
        return true;
    else
        return false;
}

#endif