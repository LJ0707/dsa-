#include<iostream>
#include<string>
#include<stack>
#include<fstream>
#include"sha.h"
#include"BigNumber.h"

using namespace std;

uint32_t hashvalue[5];

int main(int argc,char** argv) {
	if (argc == 1) {
		cout << "dsa -i|s|v [filename]" << endl << endl;
		cout << "-i    初始化大素数，计算密钥" << endl << endl;
		cout << "-s|v   签名文件或验证签名" << endl << endl;
	}

	BigNumber P, Q,G,X,Y,H;
	BigNumber tmp;
	BigNumber R, K, S, IK;
	BigNumber shatext;
	if (argc == 2 | argc == 3) {
		if (argv[1][1] == 'i') {
			cout << "现在进行大素数查找， 并计算公钥私钥,请稍等" << endl << endl;
			P.generateDsaprimenumber(P, Q);
			while (1) {
				/*此处为实现方便，H的长度可以任意H的值但要小于p-1*/
				H.generateNumber(DSALENGTH - 1);
				//H.unsignedprintBigNumber();
				G = H.bigNumMod((P - BigNumber(1)) / Q, P);
				if (G.isBig(G, BigNumber(1)))break;
			}

			/*随机选取一个160位的x,x的值要小于q*/
			while (1) {
				X.generateNumber(SLENGTH - 1);
				if (X.isBig(Q, X))break;
			}
			Y = G.bigNumMod(X, P);


			cout << "初始化完毕:  " << endl;
			cout << "P: ";
			P.unsignedprintBigNumber();
			cout << endl;
			cout << "Q: ";
			Q.unsignedprintBigNumber();
			cout << endl;
			cout << "G: ";
			G.unsignedprintBigNumber();
			cout << endl;
			cout << "Y: ";
			Y.unsignedprintBigNumber();
			cout << endl;
			cout << "以上为公开的，其中Y为公开密钥 ,并已经写入文件\"public.txt\"" << endl<<endl;
			fstream file;
			file.open("public.txt", ios::out);
			if (file.fail()) {
				cout << "文件写入失败" << endl;
				exit(0);
			}
			P.writeBigNumbertofile(&file, 4, P, Q, G, Y);
			file.close();
			file.open("private.txt", ios::out);
			if (file.fail()) {
				cout << "文件写入失败" << endl;
				exit(0);
			}
			cout << "X: ";
			X.unsignedprintBigNumber();
			cout << endl;
			cout << "X为你的私钥，不公开，并已经写入文件\"private.txt\"" << endl;
			X.writeBigNumbertofile(&file, 4, P, Q, G, X);
			file.close();
		}
		/*******************签名操作***********************/
		else if (argv[1][1] == 's') {
			/*首先得到文件的hash值*/
			fstream file1;
			file1.open(argv[2], ios::in);
			if (file1.fail()) {
				cout << "文件打开失败" << endl;
				exit(0);
			}
			shatext = shaFile(&file1);
			file1.close();
			/*接下来读取文件私钥*/
			file1.open("private.txt", ios::in);
			if (file1.fail()) {
				cout << "文件打开失败" << endl;
				exit(0);
			}
			for (int i = 0; i < 4; i++) {
				string s;
				file1 >> s;
				if (i == 0)P = BigNumber(s, 10);
				else if (i == 1)Q = BigNumber(s, 10);
				else if (i == 2)G = BigNumber(s, 10);
				else X = BigNumber(s, 10);
			}
			file1.close();
			file1.open("signature.txt", ios::out);
			/*产生一个小于q的随机数k*/
			K.generateNumber(100);
			/*计算K的逆元*/
			IK = K.inverseBigNumber(Q);
			//cout << "IK: ";
			//IK.unsignedprintBigNumber();
			tmp = G.bigNumMod(K, P);
			R = tmp.bigNumMod(BigNumber(1), Q);
			tmp = IK * (shatext + (X*R));
			S = tmp.bigNumMod(BigNumber(1), Q);
			cout << "消息的签名为: " << endl;
			cout << "R: ";
			R.unsignedprintBigNumber();
			cout << endl;
			cout << "S: ";
			S.unsignedprintBigNumber();
			cout << endl;
			R.writeBigNumbertofile(&file1, 2, R, S);
			file1.close();
		}
		/*******************验证签名***********************/
		else if (argv[1][1] == 'v') {
			/*首先得到文件的hash值*/
			fstream file1;
			string s;
			file1.open(argv[2], ios::in);
			if (file1.fail()) {
				cout << "文件打开失败" << endl;
				exit(0);
			}
			shatext = shaFile(&file1);
			file1.close();
			/*接下来读取文件私钥*/
			file1.open("public.txt", ios::in);
			if (file1.fail()) {
				cout << "文件打开失败" << endl;
				exit(0);
			}
			for (int i = 0; i < 4; i++) {
				file1 >> s;
				if (i == 0)P = BigNumber(s, 10);
				else if (i == 1)Q = BigNumber(s, 10);
				else if (i == 2)G = BigNumber(s, 10);
				else Y = BigNumber(s, 10);
			}
			file1.close();
			/*接下来读取文件的签名R S*/
			file1.open("signature.txt", ios::in);
			if (file1.fail()) {
				cout << "文件打开失败" << endl;
				exit(0);
			}
			file1 >> s;
			R = BigNumber(s, 10);
			file1 >> s;
			S = BigNumber(s, 10);
			file1.close();
			/*接下来为验证工作*/
			BigNumber W, U1, U2, V;
			/*计算S的逆元W*/
			W = S.inverseBigNumber(Q);
			tmp = shatext * W;
			U1 = tmp.bigNumMod(BigNumber(1), Q);
			tmp = R * W;
			U2 = tmp.bigNumMod(BigNumber(1), Q);
			tmp = G.bigNumMod(U1, P);
			tmp = tmp * Y.bigNumMod(U2, P);
			tmp = tmp.bigNumMod(BigNumber(1), P);
			V = tmp.bigNumMod(BigNumber(1), Q);
			cout << "R: ";
			R.unsignedprintBigNumber();
			cout << endl;
			cout << "V: ";
			V.unsignedprintBigNumber();
			cout << endl;
			if (V.unsignedisEqual(V, R)) {
				cout << "签名有效" << endl;
			}
			else {
				cout << "签名无效" << endl;
			}
		}
		else {
			cout << "请输入正确参数" << endl;
		}
	}
	else {
		cout << "请输入正确参数" << endl;
	}
	return 0;
}

