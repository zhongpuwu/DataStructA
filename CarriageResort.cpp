//==============================================
// 车厢重排
//----------------------------------------------
// 作者：王立波
// 修订：2017年2月
//==============================================

#include <iostream>
using namespace std;

typedef int QElemType;
#include "Realign.h"

//利用k个缓冲轨，对n节车厢重排
bool RealignCTrackStation(CTrackStation &TS, int *A, int &n)
{
    int k, nowOut = 1, i = 0;
    while (nowOut <= n)
    {
        if (HoldOut(TS, nowOut, k))
        {
            cout << nowOut << " 号车厢从 " << k << "号缓冲轨出队" << endl;
            nowOut++;
            continue;
        }
        if (i >= n || !HoldIn(TS, A[i], k))
            return false;
        cout << A[i] << " 号车厢进入 " << k << " 号缓冲轨" << endl;
        i++;
    }
    return true;
}

int main()
{
    int i, m, k;
    cout << "请输入需重排的车厢数:";
    cin >> m;
    int car, A[m];
    cout << "请依次输入需重排的车厢序列编号:";
    for (i = 0; i < m; i++)
        cin >> A[i];
    cout << "请输入缓冲轨（队列）的数目：";
    cin >> k;
    cout << endl;
    CTrackStation trackStation; //构建缓冲轨站
    bool ok = false;
    do
    {
        InitCTrackStation(trackStation, k);
        if (RealignCTrackStation(trackStation, A, m))
        { //利用缓冲轨站重排车厢
            ok = true;
            cout << endl
                 << "车厢已重排！" << endl;
        }
        else
        {
            DestroyCTrackStation(trackStation);
            cout << "缓冲轨的数目为" << k << "时，因车厢无法重排，请重输缓冲轨的数目:";
            cin >> k;
            cout << endl;
        }
    } while (!ok);
    DestroyCTrackStation(trackStation);

    system("pause");
    return 0;
}
