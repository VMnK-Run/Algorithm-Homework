/*
 * @Author: VMnK_Run
 * @Description: 动态规划解决01背包问题，并实现了一种用一维数组表示状态空间方程的解法
 * @FilePath: \Src\DP.cpp
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
using std::max;
using std::string;

int dp[N][N];//状态数组
int dp_re[N];//优化后的一维状态数组
int res[N];//结果

void DP();//动态规划解法，使用二维数组
void DP_re();//优化解法，使用一维数组
void traceBack();//回溯求解

/**
 * @brief 动态规划解法，使用二维数组
 */
void DP(){
    LARGE_INTEGER t1,t2,tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);

    for(int j = 1; j <= c; j++){
        if(j >= weight[1]) dp[1][j] = price[1];//初始化
    }
    for(int i = 2; i <= n; i++){//依次更改i到n个物品
        for(int j = 1; j <= c; j++){//逐步试探着扩大容量的过程
            dp[i][j] = dp[i - 1][j];//从i-1转移过来
            if(j >= weight[i])//能放下当前物品
                dp[i][j] = max(dp[i][j], dp[i - 1][j - weight[i]] + price[i]);//进行比较判断是否放入
        }
    }
    QueryPerformanceCounter(&t2);
    cout <<(double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart <<endl;
}

/**
 * @brief 动态规划解法，使用一维数组
 */
void DP_re(){
    LARGE_INTEGER t1,t2,tc;
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&t1);
    for(int i = 1; i <= n; i++){//n次更新，对n个物品进行尝试
        for(int j = c; j >= 1; j--){//状态转移的过程，必须采用从c减为1
            if(j >= weight[i])
                dp_re[j] = max(dp_re[j], dp_re[j - weight[i]] + price[i]);//保证是从i-1转移而来
        }
    }
    QueryPerformanceCounter(&t2);
    cout <<(double)(t2.QuadPart-t1.QuadPart)/(double)tc.QuadPart <<endl;
}

/**
 * @brief 回溯求解
 */
void traceBack(){
    int remain = c;
    for(int i = n; i > 1; i--){
        if(dp[i][remain] == dp[i - 1][remain]) res[i] = 0;
        else{
            res[i] = 1;
            remain -= weight[i];
        }
    }
    if(dp[1][remain]) res[1] = 1;
}

int main()
{
    memset(price, 0, sizeof(price));
    memset(weight, 0, sizeof(weight));
    memset(dp, 0, sizeof(dp));
    memset(dp_re, 0, sizeof(dp_re));

    readIn();
    DP();
    DP_re();
    traceBack();

    cout << "The best value: " << dp[n][c] << endl;
    cout << "The best value by the refined solution: " << dp_re[c]<<endl;
    cout << "The best solution: ";
    for(int i = 1; i <= n; i++) cout << res[i] << " ";
    return 0;
}