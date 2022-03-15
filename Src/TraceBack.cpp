/*
 * @Author: VMnK_Run
 * @Description: 用回溯法进行01背包问题求解
 * @FilePath: \Src\TraceBack.cpp
 */
#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <Windows.h>
#include "../Include/readFile.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

int cw = 0;//当前物品重量
int cp = 0;//当前物品总价值
int x[N];//当前解
int bestp = 0;//当前最优解
int bestx[N];//当前最优解

//限界函数，剩余所有物品总价值
int bound(int k){
    int remain = 0;
    for(int i = k + 1; i <= n; i++) remain += price[i];
    return cp + remain;
}

void traceBack(int k){
    if(k > n){//遍历完n个物品
        if(cp > bestp){//发现更优解
            bestp = cp;
            for(int i = 1; i <= n; i++) bestx[i] = x[i];
        }
    }
    else{
        if(cw + weight[k] <= c){//还能放下当前物品
            x[k] = 1;
            cw += weight[k];
            cp += price[k];
            traceBack(k + 1);//去查看下一个物品
            cp -= price[k];//还原
            cw -= weight[k];
            x[k] = 0;
        }
        if(bound(k) > bestp){//剪枝条，是否还能获得最优解
            x[k] = 0;
            traceBack(k + 1);
        }
    }
}



int main()
{
    memset(weight, 0, sizeof(weight));
    memset(price, 0, sizeof(price));

    readIn();

    LARGE_INTEGER t1,t2,tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    
    traceBack(1);

    QueryPerformanceCounter(&t2);
    cout <<(double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart <<endl;

    cout << "The best value: " << bestp << endl;
    cout << "The best solution: ";
    for(int i = 1; i <= n; i++) cout << bestx[i] << " ";
    return 0;
}