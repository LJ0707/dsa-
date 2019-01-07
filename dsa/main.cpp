#include<iostream>
#include<string>
#include<stack>
#include<fstream>
#include"sha.h"
#include"BigNumber.h"

using namespace std;

uint32_t hashvalue[5];

int main(int argc,char**argv) {
	BigNumber P, Q,G,X,Y,H;
	P.generateDsaprimenumber(P,Q);
	while (1) {
		/*�˴�Ϊʵ�ַ��㣬H�ĳ��ȿ�������H��ֵ��ҪС��p-1*/
		H.generateNumber(DSALENGTH-1);
		//H.unsignedprintBigNumber();
		G = H.bigNumMod((P - BigNumber(1)) / Q, P);
		G.unsignedprintBigNumber();
		if (G.isBig(G, BigNumber(1)))break;
	}

	/*���ѡȡһ��160λ��x,x��ֵҪС��q*/
	while (1) {
		X.generateNumber(SLENGTH-1);
		X.unsignedprintBigNumber();
		if (X.isBig(Q, X))break;
	}
	Y = G.bigNumMod(X, P);

	BigNumber text(1);
	BigNumber shatext = shaBigNumber(text);
	cout << "��ʼ�����:  " << endl;
	cout << "P: ";
	P.unsignedprintBigNumber();
	cout << "Q: ";
	Q.unsignedprintBigNumber();
	cout << "G: ";
	G.unsignedprintBigNumber();
	cout << "Y: ";
	Y.unsignedprintBigNumber();
	cout << "����Ϊ�����ģ�����YΪ������Կ ,���Ѿ�д���ļ�\"public.txt\"" << endl;
	fstream file;
	file.open("public.txt",ios::out);
	if (file.fail()) {
		cout << "�ļ�д��ʧ��" << endl;
		exit(0);
	}
	P.writeBigNumbertofile(&file,4,P,Q,G,Y);
	file.close();
	file.open("private.txt",ios::out);
	if (file.fail()) {
		cout << "�ļ�д��ʧ��" << endl;
		exit(0);
	}
	cout << "X";
	X.unsignedprintBigNumber();
	cout << "XΪ���˽Կ�������������Ѿ�д���ļ�\"private.txt\"" << endl;
	X.writeBigNumbertofile(&file,1,X);
	file.close();
	/*******************ǩ������***********************/

	BigNumber R, K, S,IK;
	/*����һ��С��q�������k*/
	K.generateNumber(100);
	/*����K����Ԫ*/
	IK = K.inverseBigNumber(Q);
	cout << "IK: ";
	IK.unsignedprintBigNumber();
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
	W = S.inverseBigNumber(Q);
	tmp = shatext * W;
	U1 = tmp.bigNumMod(BigNumber(1), Q);
	tmp = R * W;
	U2 = tmp.bigNumMod(BigNumber(1), Q);
	tmp = G.bigNumMod(U1, P);
	tmp = tmp * Y.bigNumMod(U2, P);
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

