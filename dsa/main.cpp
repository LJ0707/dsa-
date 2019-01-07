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
		/*�˴�Ϊʵ�ַ��㣬H�ĳ��ȿ�������H��ֵ��ҪС��p-1*/
		H.generateNumber(DSALENGTH-1);
		G = H.bigNumMod((P - BigNumber(1)) / Q, P);
		if (!G.unsignedisEqual(G, BigNumber(1)))break;
	}

	/*���ѡȡһ��160λ��x,x��ֵҪС��q*/
	while (1) {
		X.generateNumber(SLENGTH);
		if (X.isBig(Q, X))break;
	}
	Y = G.bigNumMod(X, P);

	BigNumber text(1);
	BigNumber shatext = shaBigNumber(text);
	
	/*******************ǩ������***********************/

	BigNumber R, K, S,IK;
	/*����һ��С��q�������k*/
	K.generateNumber(100);
	/*����K����Ԫ*/
	IK = IK.inverseBigNumber(K);
	BigNumber tmp = G.bigNumMod(K, P);
	R = tmp.bigNumMod(BigNumber(1), Q);
	tmp = IK * (shatext + (X*R));
	S = tmp.bigNumMod(BigNumber(1), Q);
	cout << "��Ϣ��ǩ��Ϊ" << endl;
	R.unsignedprintBigNumber();
	S.unsignedprintBigNumber();

	/*******************��֤ǩ��***********************/

	BigNumber W, U1, U2, V;
	/*����S����ԪW*/
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
		cout << "ǩ����Ч" << endl;
	}
	else {
		cout << "ǩ����Ч" << endl;
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

