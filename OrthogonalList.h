#ifndef _OrthogonalList_H_
#define _OrthogonalList_H_

//有向图的十字链表存储表示
#define MAX_VERTEX_NUM 12          // 最大节点数量
#define MAX_NAME 4                 // 顶点字符串的最大长度
typedef int InfoType;              // 定义弧相关信息的类型
typedef char VertexType[MAX_NAME]; // 定义顶点的名称类型

struct ArcBox // 弧结点
{
    int tailvex, headvex;  // 该弧的尾和头顶点的位置
    ArcBox *hlink, *tlink; // 分别为弧头相同和弧尾相同的弧的链域
    InfoType *info;        // 该弧相关信息的指针(可无)
};
struct VexNode // 顶点结点
{
    int credit;                 // 学分
    VertexType id;              // 顶点的数据(课程代号)
    ArcBox *firstin, *firstout; // 分别指向该顶点第一条入弧和出弧
};
struct OLGraph
{
    VexNode xlist[MAX_VERTEX_NUM]; // 表头向量(数组)
    int vexnum, arcnum;            // 有向图的当前顶点数和弧数
};

// 以下为十字链表的基本操作的实现

//查找顶点在顶点数组中的位置
int LocateVex(OLGraph G, VertexType u)
{
    int i;
    for (i = 0; i < G.vexnum; i++)
        if (strcmp(u, G.xlist[i].id) == 0)
            return i;
    return -1;
}

Status TopologicalSort(OLGraph)

#endif