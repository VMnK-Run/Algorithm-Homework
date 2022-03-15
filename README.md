# Algorithm-Homework

[Homework]A stupid algorithmic homework by me.


现在看来其实这份作业做的相当的愚蠢，或许可以尝试使用makefile，或许可以自动读取多份文本文件

#### 目录结构描述

├─Data						//存放数据集的文件夹
│      p01_c.txt			 //第一个数据集的背包容量
│      p01_p.txt			//第一个数据集的物品价值
│      p01_s.txt			//第一个数据集的最优解
│      p01_w.txt		   //第一个数据集的物品重量
│      p07_c.txt			//
│      p07_p.txt		   //
│      p07_s.txt		   //
│      p07_w.txt		 //
│
├─Include
│      readFile.h		//从txt文件读入到数组中的函数
│      variable.h		//三个算法都会使用到的变量
│
└─Src
        BranchBound.cpp		 //分支限界做法
        DP.cpp							//回溯做法
        TraceBack.cpp			   //动态规划做法

#### 文件描述

+ 这份代码通过动态规划、回溯、分支限界三种算法解决01背包问题并进行性能分析
+ 从Data里读入数据
+ Include存放需要用到的读入函数和全局变量
+ 算法验证在Src文件夹内进行，每个算法由一个cpp文件进行管理，编译运行相应的文件即可
+ 为方便进行实时管理，运行结果直接显示在控制台上
+ 若要添加新的数据集，只需将数据集下载到Data文件夹，并更改 ` Include/readFile.h` 中相应的文件名称即可
+ 同理，更换数据集只需更改 ` Include/readFile.h` 中相应的文件名称即可
+ 输出时将输出该数据集对应的01背包最优值和最优解
  + 最优解说明：1表示该物品装入背包，0表示不装入，顺序与数据集初始顺序相同
