/*
 * @Author: VMnK_Run
 * @Description: 分支限界解决01背包问题
 * @FilePath: \Src\BranchBound.cpp
 */
#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <Windows.h>
#include <functional>

#include "../Include/readFile.h"

using std::cin;
using std::cout;
using std::endl;

int cw = 0;//已选择物品的重量
int cv = 0;//已选择物品的价值
int bestv = 0;//目前最优价值
int bestx[N];//当前最优解

//结点信息
struct Node{
    Node(int w, int p, int l, int up, Node* par, bool f){//构造函数
        this->w = w;
        this->p = p;
        this->level = l;
        this->upbound = up;
        this->parent = par;
        this->flag = f;
    }
    int w;//已选择物品的总重量
    int p;//已选择物品的总价值
    Node *parent;//记录父节点，方便进行回溯求解
    int level;//层数,即待选物品编号
    bool flag;//表示结点是否选择
    int upbound;//结点价值上界
};

//优先级队列
std::priority_queue<Node*, std::vector<Node*>, std::function<bool(Node*, Node*)\
>> que([](Node*n1, Node*n2)->bool //默认是大根堆
{
	return n1->upbound < n2->upbound;//价值越高优先级越高
});

//价值上界，从i开始所有物品价值的和加上当前价值
int maxBound(int i){
    int bound = cv;
    for(int level = i; level <= n; level++) bound += price[level];
    return bound;
}

//添加结点至队列中
void addNode(int w, int v, int l, int up, Node* par, bool f){
    Node *node = new Node(w, v, l, up, par, f);
    que.push(node);
}

int main()
{
    memset(weight, 0 ,sizeof(weight));
    memset(price, 0, sizeof(price));

    readIn();
    int i = 1;

    //初始化结点，从第1个物品开始搜索
    Node *node = new Node(0, 0, 1, maxBound(1), nullptr, false);

    LARGE_INTEGER t1,t2,tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);

    while((i = node->level) <= n){//每次循环都选择当前结点所指向的物品
        cw = node->w;
        cv = node->p;

        if(cw + weight[i] <= c){//展开左子节点，可以放下当前物品
            if(cv + price[i] > bestv){//是否可以更新当前最优解
                bestv = cv + price[i];
            }
            //将当前物品放入，并将该状态加入优先级队列
            addNode(cw + weight[i], cv + price[i], i + 1, node->upbound, node, true);
        }

        //若不放该物品，需要修改限界函数
        if(maxBound(i + 1) >= bestv){//不放置的话要判断还能否得到更优解
            addNode(cw, cv, i + 1, maxBound(i + 1), node, false);
        }

        node = que.top();//获得下一个要展开的结点
        que.pop();//已扩展的结点出队

    }

    QueryPerformanceCounter(&t2);
    cout <<(double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart <<endl;

    cout << "The best value: " << bestv << endl;
    for(int i = n; i >= 1; i--){
        if(node->flag) bestx[i] = 1;
        else bestx[i] = 0;
        node = node->parent;
    }
    cout << "The best solution: ";
    for(int i = 1; i<= n; i++) cout << bestx[i] << " "; 
    return 0;
}
