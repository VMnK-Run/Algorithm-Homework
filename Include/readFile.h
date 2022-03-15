/*
 * @Author: VMnK_Run
 * @Description: 这个文件用于读入数据集中的数据
 * @FilePath: \Include\readFile.h
 */
#ifndef __READFILE_H__
#define __READFILE_H__
#include <fstream>
#include <iostream>
#include <string>
#include "variable.h"

/**
 * @brief 读取单个文件到数组
 * @param 读进的数组
 * @param 文件名
 * @return 数据个数
 */
int readSingleFile(int *arr, std::string filename){
    int data_len = 0;
    std::ifstream file("../Data/" + filename);
    if(filename == "p01_c.txt") file >> arr[0];
    else while(!file.eof()) file >> arr[++data_len];
    file.close();
    return data_len;
}

/**
 * @brief 将数据集中的数据读入数组,并利用其中一个文件得到此数据集中物品个数
 */
void readIn(){
    readSingleFile(&c, "p01_c.txt");
    n = readSingleFile(weight, "p01_w.txt");
    readSingleFile(price, "p01_p.txt");
}
#endif