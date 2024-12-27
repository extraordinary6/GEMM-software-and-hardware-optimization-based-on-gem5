# GEMM-software-and-hardware-optimization-based-on-gem5

## 文件结构
1. **gemm 文件夹**  
   包含 GEMM 的软件实现与优化。

2. **tutorial 文件夹**  
   包含 CPU 架构的实现与优化。

3. **m5out 文件夹**  
   包括各种情况的统计信息。

4. **replacement_policies 文件夹**  
   包括缓存替换策略，涵盖 gem5 内建的一系列策略以及自定义的 Gen、 Hawkeye 等策略。
   
5. **matlab 文件夹**  
   包括给“软件优化”和“缓存参数调整”优化做数据可视化分析的相关MATLAB代码。
   
6. **xlsx 文件**  
   从m5out文件夹下总结出的一些有价值的信息用来分析。
   
7. **report.pdf 文件**   
   报告，含教程。

## Baseline 硬件架构

本实验的 **baseline** 是如下图所示基于X86的硬件架构，GEMM 采用多重循环的简单实现。

其中，CPU为基于顺序执行的X86TimingSimpleCPU，l1 dcache的大小设为4kB，l2 cache的大小设为16kB。
![image](https://github.com/user-attachments/assets/9069fb79-53e0-4020-8355-898450be8177)

