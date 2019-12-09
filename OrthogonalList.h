#ifndef _OrthogonalList_H_
#define _OrthogonalList_H_

//有向图的十字链表存储表示

/*
十字链表（Orthogonal List）是有向图的一种链式存储结构，
可以看成是将有向图的邻接表和逆邻接表结合起来得到的一种链表。
在十字链表中，对应于有向图的每一条弧有一个结点，对于每一个顶点也有一个结点
*/

#define MAX_VERTEX_NUM 40          // 最大节点数量
#define MAX_NAME 6                 // 顶点名称的最大长度
typedef int InfoType;              // 定义弧相关信息的类型
typedef char VertexType[MAX_NAME]; // 定义顶点的名称类型

struct ArcBox // 弧结点，原来这玩意叫做弧?!
{
    int tailvex, headvex;                // 该弧的尾和头顶点的位置(就是下标而已)
    ArcBox *hlink = NULL, *tlink = NULL; // 分别为弧头相同和弧尾相同的弧的链域
    InfoType *info = NULL;               // 该弧相关信息的指针(可此题不需要)
};
struct VexNode // 顶点结点，不如说是顶点数组
{
    int credit;                               // 保存该顶点课程的学分
    int indegree = 0;                         // 保存顶点的入度，求拓扑排序时会用
    bool able = true;                         // 指示该顶点是否被删除，被删除的顶点不配拥有弧
    VertexType id;                            // 保存该顶点的课程代号
    ArcBox *firstin = NULL, *firstout = NULL; // 分别指向该顶点第一条入弧和出弧
};
struct OLGraph // 十字链表表示的有向图
{
    VexNode xlist[MAX_VERTEX_NUM]; // 表头向量(数组)
    int vexnum = 0;                // 有向图的当前顶点数和弧数
    int arcnum = 0;                // 注意一下vex指的是顶点arc指的是弧
};

// 函数原型
bool GraphFull(OLGraph &G);
bool GraphEmpty(OLGraph &G);
bool DeleteArc_head(OLGraph &G, int head);

// 以下为十字链表的基本操作的实现 -----------------------------------------------

// 查找顶点在顶点数组中的位置，也就是根据顶点名称求顶点下标
int LocateVex(OLGraph G, VertexType u)
{
    for (int i = 0; i < G.vexnum; i++)
        if (strcmp(G.xlist[i].id, u) == 0) // 字符串匹配查找指定名称顶点的下标
            return i;                      // 找到了就返回顶点的下标
    return -1;                             // 如果没有找到位置就返回-1，默认返回-1
}
// 向十字链表中添加一个顶点结点，如果超过了最大顶点数量，只能放弃输入
bool InsertVex(OLGraph &G, VertexType id, int credit)
{
    if (LocateVex(G, id) != -1)
    {
        cout << "此顶点已存在!" << endl;
        return true;
    }
    else if (!GraphFull(G))                // 在图有多余空间时插入
    {                                      // 如果空间已满则放弃插入
        G.xlist[G.vexnum].credit = credit; //
        strcpy(G.xlist[G.vexnum].id, id);
        cout << "顶点" << G.xlist[G.vexnum].id << "插入成功！" << endl;
        G.vexnum++;
        return true;
    }
    else
    {
        cout << "最大顶点数目已达到，无法继续插入" << endl;
        return false;
    }
}
// 向十字链表中添加一条弧，并且保证弧的连通性
// 需要保证插入新弧后仍然是简单图，否则将放弃这条弧
bool InsertArc(OLGraph &G, VertexType head, VertexType tail)
{
    bool outflag = true;              // true表示未找到相同的弧
    ArcBox *Boxp, *p = NULL;          // p用于遍历头链
    Boxp = new ArcBox;                // 开辟一个结点空间，这个空间在删除时将会被回收
    int headvex = LocateVex(G, head); // 找到头的位置
    int tailvex = LocateVex(G, tail); // 找到尾的位置，这里不使用Locate函数可能会减少时间复杂度
    if (headvex == -1 || tailvex == -1)
    {
        cout << "没有在图中找到有效结点，数据无效" << endl;
        delete Boxp;  // 释放无效的弧内存
        return false; // 头或尾顶点任一个在图中不存在则标志着输入无效
    }
    else // 为了保证生成的图是简单图，需要判断是否存在重复的弧，不存在才能插入
    {    // 这样做的目的是减少删除弧时的时间复杂度
        p = G.xlist[headvex].firstout;
        while (p != NULL)
        {
            if (p->tailvex == tailvex)
            {
                outflag = false; // 找到了相同的弧，需要放弃输入
                break;
            }
            p = p->hlink;
        }
        if (outflag)
        {
            Boxp->headvex = headvex;
            Boxp->tailvex = tailvex;
            Boxp->hlink = G.xlist[headvex].firstout;
            Boxp->tlink = G.xlist[tailvex].firstin;
            G.xlist[headvex].firstout = Boxp;
            G.xlist[tailvex].firstin = Boxp; // 向十字链表中插入了新的弧
            G.xlist[tailvex].indegree++;     // 记录入度的增加，方便进行拓扑排序
            G.arcnum++;                      // 弧总数增加
            cout << "弧" << head << "-->" << tail << "插入成功" << endl;
            return true;
        }
        else
        {
            cout << "输入了重复的弧，插入失败" << endl;
            delete Boxp;
            return false;
        }
    }
}
// 在图中删除指定结点，并且顺势删除与这个结点有联系的弧
// 删除顶点时，不会减少vexnum
// 删除弧的操作需要调用其他函数来完成
bool DeleteVex(OLGraph &G, VertexType id)
{
    int loc = LocateVex(G, id);
    G.xlist[loc].able = false;
    return DeleteArc_head(G, loc); // 其实只需要删除出弧，因为入弧为0，但需要同步修改入度
}
// 删除出弧，因为入度为0，所以不用考虑入弧
bool DeleteArc_head(OLGraph &G, int head)
{
    ArcBox *p = G.xlist[head].firstout, *rp; // 遍历头链
    while (p != NULL)
    {
        rp = p;
        G.xlist[rp->tailvex].indegree--; // 实时更新顶点的入度
        p = p->hlink;
        delete rp;
        rp = NULL;
    }
    return true;
}
// 判断顶点是否超出限制（40）
bool GraphFull(OLGraph &G)
{
    if (G.vexnum >= MAX_VERTEX_NUM)
        return true;
    else
        return false;
}
// 判断顶点是否为空
bool GraphEmpty(OLGraph &G)
{
    if (G.vexnum <= 0)
        return true;
    else
        return false;
}
// 邻接表和逆邻接表的格式打印出十字链表 只打印able==true的顶点信息
bool PrintList(OLGraph &G)
{
    cout << endl;
    ArcBox *p;
    if (GraphEmpty(G))
        cout << "图中没有顶点啊！" << endl;
    else
    {
        cout << "课程名称" << endl;
        for (int i = 0; i < G.vexnum; i++)
        {
            if (G.xlist[i].able)
            {
                cout << G.xlist[i].id << ":" << endl;
                cout << "邻接表";
                p = G.xlist[i].firstout;
                while (p != NULL)
                {
                    cout << "-->" << G.xlist[p->tailvex].id;
                    p = p->hlink;
                }
                cout << endl;
                cout << "逆邻接表";
                p = G.xlist[i].firstin;
                while (p != NULL)
                {
                    cout << "-->" << G.xlist[p->headvex].id;
                    p = p->tlink;
                }
                cout << endl;
                cout << endl;
            }
        }
    }
    return true;
}

#endif