#ifndef _Realign_H_
#define _Realign_H_
#define NULL 0

struct TheCar
{
    bool able = true;
    int id = 0;
    int times = 0;       // 记录有效时长
    // bool instop = false; // 记录车的位置信息true意味着在停车场false意味着在便道
    int in = 0;
    int out = 0;
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

#endif