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
	BigNumber P, Q,G,X,Y,H;
	P.generateDsaprimenumber(P,Q);
	while (1) {
		/*此处为实现方便，H的长度可以任意H的值但要小于p-1*/
		H.generateNumber(DSALENGTH-1);
		G = H.bigNumMod((P - BigNumber(1)) / Q, P);
		if (!G.unsignedisEqual(G, BigNumber(1)))break;
	}

	/*随机选取一个160位的x,x的值要小于q*/
	while (1) {
		X.generateNumber(SLENGTH);
		if (X.isBig(Q, X))break;
	}
	Y = G.bigNumMod(X, P);

	BigNumber text(1);
	BigNumber shatext = shaBigNumber(text);
	
	/*******************签名操作***********************/

	BigNumber R, K, S,IK;
	/*产生一个小于q的随机数k*/
	K.generateNumber(100);
	/*计算K的逆元*/
	IK = IK.inverseBigNumber(K);
	BigNumber tmp = G.bigNumMod(K, P);
	R = tmp.bigNumMod(BigNumber(1), Q);
	tmp = IK * (shatext + (X*R));
	S = tmp.bigNumMod(BigNumber(1), Q);
	cout << "消息的签名为" << endl;
	R.unsignedprintBigNumber();
	S.unsignedprintBigNumber();

	/*******************验证签名***********************/

	BigNumber W, U1, U2, V;
	/*计算S的逆元W*/
	W = W.inverseBigNumber(S);
	tmp = shatext * W;
	U1 = tmp.bigNumMod(BigNumber(1), Q);
	tmp = R * W;
	U2 = tmp.bigNumMod(BigNumber(1), Q);
	tmp = G.powerBigNumber(G, U1);
	tmp = tmp * Y.powerBigNumber(Y, U2);
	tmp = tmp.bigNumMod(BigNumber(1), P);
	V = tmp.bigNumMod(BigNumber(1), Q);
	if (V.unsignedisEqual(V, R)) {
		cout << "签名有效" << endl;
	}
	else {
		cout << "签名无效" << endl;
	}


	//BigNumber a(2);
	//BigNumber b(500);
	//BigNumber c;
	//c = a.powerBigNumber(a, b);
	//c.unsignedprintBigNumber();

	//fstream file;
	//file.open("1.txt",ios::in|ios::out);
	//shaMessage(&file,hashvalue);
	//cout << hex<<hashvalue[0] <<hashvalue[1]<<hashvalue[2]<<hashvalue[3]<<hashvalue[4]<< endl;
	getchar();
	return 0;
}

