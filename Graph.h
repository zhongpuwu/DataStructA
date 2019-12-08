#ifndef _Graph_H_
#define _Graph_H_

// 这个文件里将会解决拓扑排序以及数据插入的问题

typedef int QElemType;

#include "OrthogonalList.h"
#include "LinkQueue.h"

struct CourseTag
{
    int level;     // “拓扑排序”的结果，对课程的优先级进行标记，首先删除的优先级最高为0
    int credit;    // 相应课程的学分
    VertexType id; // 课程名称
};
struct Course
{
    CourseTag *CT; // 存放课程信息的数组
    int Conum = 0; // 存入的课程数量，最大值等于G.vexnum
};

// 解析邻接矩阵并录入样例数据
bool ResolveSq(int credits[], VertexType ids[], int Sq[][12], OLGraph &G)
{
    for (int i = 0; i < 12; i++)
    {
        InsertVex(G, ids[i], credits[i]);
    }

    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if (Sq[i][j])
            {
                InsertArc(G, ids[i], ids[j]);
            }
        }
    }
    return true;
}

bool ToplogicalSort(OLGraph &G, Course &Co)
{
    LinkQueue LQ;
    InitQueue(LQ);
    int head, level = 0;
    bool ring_flag = false;     // 判断图中是否有环
    bool indegree_flag = false; // 判断一次循环中是否发现了入度为0的点
    bool flag = false;          // 判断一次循环中是否发现了able为true的点
    while (true)
    {
        indegree_flag = false;
        flag = false;
        for (int i = 0; i < G.vexnum; i++)
        {
            if (G.xlist[i].able)
            {
                flag = true;
                if (G.xlist[i].indegree <= 0)
                {
                    indegree_flag = true;
                    EnQueue(LQ, i);
                }
            }
        }
        while (DeQueue(LQ, head))
        {
            strcpy(Co.CT[Co.Conum].id, G.xlist[head].id);
            Co.CT[Co.Conum].credit = G.xlist[head].credit;
            Co.CT[Co.Conum].level = level;
            DeleteVex(G, G.xlist[head].id);
            Co.Conum++;
        }
        level++;
        if (flag && !indegree_flag)
        {
            ring_flag = true;
            break;
        }
        // 认定图中有环的条件
        // 1.一次循环中没有发现入度为0的顶点
        // 2.这次循环中发现了able为true的顶点
        if (!indegree_flag)
            break; // 退出循环的条件是一次循环中找不到入度为0的点
    }
    if (ring_flag)
    {
        cout << "图中有环，无法进行拓扑排序!" << endl;
        return false;
    }
    else
    {
        return true;
    }
}
bool PrintCourse(Course Co)
{
    if (Co.Conum == 0)
    {
        cout << "结果为空集！" << endl;
        return false;
    }
    else
    {
        cout << setw(3) << "id"
             << ":" << right
             << "level" << endl;
        for (int i = 0; i < Co.Conum; i++)
        {
            cout << setw(3) << Co.CT[i].id << ":" << Co.CT[i].level << endl;
        }
    }
    return true;
}

#endif