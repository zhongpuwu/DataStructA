#ifndef _Realign_H_
#define _Realign_H_

#include "LinkQueue.h"

struct CTrackStation
{
    LinkQueue *pTracks; //各缓冲轨(队列)
    int trackCount;     //缓冲轨数量
};

//初始化k个轨道
void InitCTrackStation(CTrackStation &TS, int &k)
{
    TS.trackCount = k;
    TS.pTracks = new LinkQueue[k];
    for (int i = 0; i < k; i++)
        InitQueue(TS.pTracks[i]);
}

//销毁k个轨道
void DestroyCTrackStation(CTrackStation &TS)
{
    for (int i = 0; i < TS.trackCount; i++)
        DestroyQueue(TS.pTracks[i]);
    delete[] TS.pTracks;
    TS.trackCount = 0;
}

//将车厢car移到其中一个可用缓冲轨，成功返回true。
bool HoldIn(CTrackStation &TS, int &car, int &k)
{
    int bestTrack = -1; //目前最优的缓冲轨
    int bestLast = -1;  //最优缓冲轨中的最后一节车厢
    int i;
    for (i = 0; i < TS.trackCount; i++)
    { //查找最优缓冲轨
        if (!QueueEmpty(TS.pTracks[i]))
        {
            int last; //车厢编号
            last = GetLast(TS.pTracks[i]);
            if (car > last && last > bestLast)
            { //缓冲轨i尾部的车厢号较大
                bestLast = last;
                bestTrack = i;
            }
        }
    }
    if (bestTrack == -1)
    { //未找到合适缓冲轨，查找空闲缓冲轨
        for (i = 0; i < TS.trackCount; i++)
            if (QueueEmpty(TS.pTracks[i]))
            {
                bestTrack = i;
                break;
            }
    }
    if (bestTrack == -1)
        return false; //没有可用的缓冲轨
    EnQueue(TS.pTracks[bestTrack], car);
    k = bestTrack; //将车厢ca移入k号缓冲轨
    return true;
}

//将缓冲轨中车厢car移出，成功返回true。
bool HoldOut(CTrackStation &TS, int &car, int &k)
{
    int i;
    for (i = 0; i < TS.trackCount; i++)
    {
        if (!QueueEmpty(TS.pTracks[i]))
        {
            int headCar; //车厢编号
            headCar = GetHead(TS.pTracks[i]);
            if (headCar == car)
            {
                DeQueue(TS.pTracks[i], headCar);
                k = i; //将缓冲轨中车厢car从k号轨移出
                return true;
            }
        }
    }
    return false;
}

#endif
