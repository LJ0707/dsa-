#pragma once
#include<iostream>
#include<fstream>
#include"BigNumber.h"

/*初始化消息，得到消息的位数*/
void initMessage(std::fstream *file,std::fstream *);

/*函数返回消息的第i个分组*/
void getMessage(std::fstream*,int,uint32_t* );

/*利用sha算法得到文件的哈希值，返回160位消息*/
void shaMessage(std::fstream *file,uint32_t *);

/*利用sha算法计算大整数序列的hash值，返回值为大整数*/
BigNumber shaBigNumber(BigNumber );
