//==============================================
// 教学计划编制问题
//----------------------------------------------
// 作者：武重甫
// 学号：17032430
// 修订：2017年11月
//==============================================
#include <iostream>
#include <iomanip>

using namespace std;

#include <String.h>
#include "Graph.h"

void InsertValue(OLGraph &G)
{
    cout << "请输入每门课的名称（三位字符）和学分例如c1 4（输入qt停止）：" << endl;
    VertexType id, v1, v2;
    int credit;
    while (true)
    {
        cin >> id;
        if (strcmp(id, "qt") == 0)
        {
            cout << "顶点输入完成！" << endl;
            break;
        }
        cin >> credit;
        if (!isdigit(credit) && credit < 0)
        {
            cout << "学号有误，请重新输入这个顶点" << endl;
            continue;
        }
        else
        {
            if (!InsertVex(G, id, credit))
                break;
        }
    }
    if (G.vexnum >= 1)
    {
        cout << endl
             << "下面是已插入的顶点:" << endl
             << setw(3) << "id"
             << ":"
             << "credit"
             << endl;
        for (int i = 0; i < G.vexnum; i++)
        {
            cout << setw(5) << G.xlist[i].id << ":" << G.xlist[i].credit << endl;
        }
    }
    cout << "请输入每一条弧的信息，例如c1 c4（输入qt停止）：" << endl;
    while (true)
    {
        cin >> v1;
        if (strcmp(v1, "qt") == 0)
        {
            cout << "弧输入完成！" << endl;
            break;
        }
        cin >> v2;
        InsertArc(G, v1, v2);
    }
    cout << "数据输入完成！" << endl;
}

int main(int argc, char const *argv[])
{
    OLGraph G;
    int choice;
    int credits[] = {4, 3, 4, 3, 2, 5, 3, 4, 5, 5, 5, 1};
    VertexType ids[] = {"c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8", "c9", "c10", "c11", "c12"};
    int Sq[][12] = {
        {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    cout << "请选择采用哪一种的实例" << endl
         << "1.教材案例，存在正解" << endl
         << "2.修改后的教材案例，图中有环，无解" << endl
         << "3.手动输入数据，无法判断是否存在环" << endl
         << "请选择1/2/3：" << endl;
    cin >> choice;
    switch (choice)
    {
    case 1:
        // 将教材的测试数据录入十字链表
        ResolveSq(credits, ids, Sq, G);
        // 打印测试数据十字链表形式
        PrintList(G);
        break;
    case 2:
        // 加入了一个成环的弧
        Sq[7][10] = 1;
        // 将教材的测试数据录入十字链表
        ResolveSq(credits, ids, Sq, G);
        // 打印测试数据十字链表形式
        PrintList(G);
        break;
    case 3:
        InsertValue(G);
        // 打印测试数据十字链表形式
        if (G.vexnum >= 2 && G.arcnum >= 1)
            PrintList(G);
        break;
    default:
        // 将教材的测试数据录入十字链表
        ResolveSq(credits, ids, Sq, G);
        // 打印测试数据十字链表形式
        PrintList(G);
        break;
    }
    // 初始化结果集
    Course Co;
    Co.CT = new CourseTag[G.vexnum];


    if (G.vexnum >= 2 && G.arcnum >= 1)
    {
        if (ToplogicalSort(G, Co))
        {
            // 打印出拓扑排序的结果
            PrintCourse(Co);
        }
    }
    else
    {
        cout << "数据不完整，无法排序！" << endl;
    }

    


    // 回收动态分配的结果集空间
    delete[] Co.CT;

    system("pause");
    return 0;
}