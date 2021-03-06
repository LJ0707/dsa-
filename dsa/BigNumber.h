#pragma once
#include<iostream>
#include<string>
#include<stack>
#include<stdarg.h>
#include"sha.h"
#define MAXLENGTH 128   //二进制的大整数最大长度
#define DSALENGTH 512	//DSA签名中素数p的长度
#define SLENGTH 160		//DSA生成中任意序列S的长度，最小为160


class BigNumber {
private:
	bool sign = 0;			//大整数符号为现在基本上没使用上
	int length;				//大整数长度，指示数组的长度
	uint32_t number[MAXLENGTH] ;
	void addBigNumber(BigNumber&, BigNumber&, BigNumber&);

	/*无符号大整数加法*/
	void unsignedaddBigNumber(BigNumber&, BigNumber&, BigNumber&);

	/*无符号大整数减法*/
	void unsignedsubBigNumber(BigNumber&, BigNumber&, BigNumber&);

	/*无符号大整数乘法*/
	void unsignedmulBigNumber(BigNumber&, BigNumber&, BigNumber&);

	/*无符号大整数除法*/
	void unsigneddivBigNumber(BigNumber&, BigNumber&, BigNumber&, BigNumber&);
public:

	/*无符号大整数是否相等，相等返回1，否则为0*/
	bool unsignedisEqual(BigNumber, BigNumber);

	/*构造函数根据64为无符号数构建大整数对象*/
	BigNumber(uint64_t);

	/*默认构造函数，数值为0*/
	BigNumber();

	/*根据sting构建大整数对象，n代表进制*/
	BigNumber(std::string,int n);

	/*向屏幕输出无符号大整数*/
	void unsignedprintBigNumber();

	/*比较无符号大整数大小，等于返回0，大于返回1，否则返回-1*/
	int compareBigNumber(BigNumber, BigNumber);
	BigNumber operator+(BigNumber);
	BigNumber operator-(BigNumber);
	BigNumber operator*(BigNumber);
	BigNumber operator/(BigNumber);
	BigNumber operator%(BigNumber);
	BigNumber operator=(BigNumber);

	/*无符号大整数比较,a>b返回1，否则返回0*/
	int isBig(BigNumber a,BigNumber b);
	
	/*计算无符号大整数对象this 和 a的最大公约数*/
	BigNumber gcd(BigNumber a);
	
	/*计算this模n的逆元*/
	BigNumber inverseBigNumber(BigNumber n);
	int Jacobi(BigNumber);

	/*计算this^bmodc*/
	BigNumber bigNumMod(BigNumber b,BigNumber c);

	/*大整数转换位字符串，十进制的形式的字符串*/
	std::string BigNumberToString();

	/*随机返回一个n位大素数(n位二进制位)*/
	BigNumber generatePrimeNumber(int n);

	/*Miller-Rabin素性测试*/
	int Miller_Rabin();

	void generateDsaprimenumber(BigNumber &P,BigNumber &Q);

	/*计算b 和 a 异或的结果并返回一个大整数，不改变this 和 a 的值*/
	 BigNumber operator^(BigNumber a);

	 /*计算a^b*/
	 BigNumber powerBigNumber(BigNumber a,BigNumber b);

	 /*随机返回一个n位的随机大整数*/
	 void generateNumber(uint32_t n);

	 /*将大整数写入文件，接受可变参数,出错时返回0*/
	 int writeBigNumbertofile(std::fstream* ,int n,...);
}; 

