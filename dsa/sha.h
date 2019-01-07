#pragma once
#include<iostream>
#include<fstream>
#include"BigNumber.h"

/*��ʼ����Ϣ���õ���Ϣ��λ��*/
void initMessage(std::fstream *file,std::fstream *);

/*����������Ϣ�ĵ�i������*/
void getMessage(std::fstream*,int,uint32_t* );

/*����sha�㷨�õ��ļ��Ĺ�ϣֵ������160λ��Ϣ*/
void shaMessage(std::fstream *file,uint32_t *);

/*����sha�㷨������������е�hashֵ������ֵΪ������*/
BigNumber shaBigNumber(BigNumber );

/*����sha�㷨�����ļ���hashֵ�����ر�ʾhashֵ�Ĵ�����*/
BigNumber shaFile(std::fstream*);
