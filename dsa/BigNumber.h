#pragma once
#include<iostream>
#include<string>
#include<stack>
#include<stdarg.h>
#include"sha.h"
#define MAXLENGTH 128   //�����ƵĴ�������󳤶�
#define DSALENGTH 1024	//DSAǩ��������p�ĳ���
#define SLENGTH 160		//DSA��������������S�ĳ��ȣ���СΪ160


class BigNumber {
private:
	bool sign = 0;			//����������Ϊ���ڻ�����ûʹ����
	int length;				//���������ȣ�ָʾ����ĳ���
	uint32_t number[MAXLENGTH] ;
	void addBigNumber(BigNumber&, BigNumber&, BigNumber&);

	/*�޷��Ŵ������ӷ�*/
	void unsignedaddBigNumber(BigNumber&, BigNumber&, BigNumber&);

	/*�޷��Ŵ���������*/
	void unsignedsubBigNumber(BigNumber&, BigNumber&, BigNumber&);

	/*�޷��Ŵ������˷�*/
	void unsignedmulBigNumber(BigNumber&, BigNumber&, BigNumber&);

	/*�޷��Ŵ���������*/
	void unsigneddivBigNumber(BigNumber&, BigNumber&, BigNumber&, BigNumber&);
public:

	/*�޷��Ŵ������Ƿ���ȣ���ȷ���1������Ϊ0*/
	bool unsignedisEqual(BigNumber, BigNumber);

	/*���캯������64Ϊ�޷�������������������*/
	BigNumber(uint64_t);

	/*Ĭ�Ϲ��캯������ֵΪ0*/
	BigNumber();

	/*����sting��������������n�������*/
	BigNumber(std::string,int n);

	/*����Ļ����޷��Ŵ�����*/
	void unsignedprintBigNumber();

	/*�Ƚ��޷��Ŵ�������С�����ڷ���0�����ڷ���1�����򷵻�-1*/
	int compareBigNumber(BigNumber, BigNumber);
	BigNumber operator+(BigNumber);
	BigNumber operator-(BigNumber);
	BigNumber operator*(BigNumber);
	BigNumber operator/(BigNumber);
	BigNumber operator%(BigNumber);
	BigNumber operator=(BigNumber);

	/*�޷��Ŵ������Ƚ�,a>b����1�����򷵻�0*/
	int isBig(BigNumber a,BigNumber b);
	
	/*�����޷��Ŵ���������this �� a�����Լ��*/
	BigNumber gcd(BigNumber a);
	
	/*����thisģn����Ԫ*/
	BigNumber inverseBigNumber(BigNumber n);
	int Jacobi(BigNumber);

	/*����this^bmodc*/
	BigNumber bigNumMod(BigNumber b,BigNumber c);

	/*������ת��λ�ַ�����ʮ���Ƶ���ʽ���ַ���*/
	std::string BigNumberToString();

	/*�������һ��nλ������(nλ������λ)*/
	BigNumber generatePrimeNumber(int n);

	/*Miller-Rabin���Բ���*/
	int Miller_Rabin();

	void generateDsaprimenumber(BigNumber &P,BigNumber &Q);

	/*����b �� a ���Ľ��������һ�������������ı�this �� a ��ֵ*/
	 BigNumber operator^(BigNumber a);

	 /*����a^b*/
	 BigNumber powerBigNumber(BigNumber a,BigNumber b);

	 /*�������һ��nλ�����������*/
	 void generateNumber(uint32_t n);

	 /*��������д���ļ������ܿɱ����,����ʱ����0*/
	 int writeBigNumbertofile(std::fstream* ,int n,...);
}; 

