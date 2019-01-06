#include<iostream>
#include<string>
#include<stack>
#include<fstream>
#include"sha.h"
#include"BigNumber.h"

using namespace std;

uint32_t hashvalue[5];
BigNumber P;
BigNumber Q;
BigNumber G;

int main(int argc,char**argv) {
	BigNumber p = p.generatePrimeNumber(256);
	BigNumber one(1);
	BigNumber zero(0);
	BigNumber tmp = p - one;
	BigNumber q;
	q.generateDsaprimenumber(p,q);


	BigNumber a(2);
	BigNumber b(500);
	BigNumber c;
	c = a.powerBigNumber(a, b);
	c.unsignedprintBigNumber();

	fstream file;
	file.open("1.txt",ios::in|ios::out);
	shaMessage(&file,hashvalue);
	cout << hex<<hashvalue[0] <<hashvalue[1]<<hashvalue[2]<<hashvalue[3]<<hashvalue[4]<< endl;
	getchar();
	BigNumber result = shaBigNumber(one);
	result.unsignedprintBigNumber();
	return 0;
}

