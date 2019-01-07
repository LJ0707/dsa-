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
		cout << "-i    ��ʼ����������������Կ" << endl << endl;
		cout << "-s|v   ǩ���ļ�����֤ǩ��" << endl << endl;
	}

	BigNumber P, Q,G,X,Y,H;
	BigNumber tmp;
	BigNumber R, K, S, IK;
	BigNumber shatext;
	if (argc == 2 | argc == 3) {
		if (argv[1][1] == 'i') {
			cout << "���ڽ��д��������ң� �����㹫Կ˽Կ,���Ե�" << endl << endl;
			P.generateDsaprimenumber(P, Q);
			while (1) {
				/*�˴�Ϊʵ�ַ��㣬H�ĳ��ȿ�������H��ֵ��ҪС��p-1*/
				H.generateNumber(DSALENGTH - 1);
				//H.unsignedprintBigNumber();
				G = H.bigNumMod((P - BigNumber(1)) / Q, P);
				if (G.isBig(G, BigNumber(1)))break;
			}

			/*���ѡȡһ��160λ��x,x��ֵҪС��q*/
			while (1) {
				X.generateNumber(SLENGTH - 1);
				if (X.isBig(Q, X))break;
			}
			Y = G.bigNumMod(X, P);


			cout << "��ʼ�����:  " << endl;
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
			cout << "����Ϊ�����ģ�����YΪ������Կ ,���Ѿ�д���ļ�\"public.txt\"" << endl<<endl;
			fstream file;
			file.open("public.txt", ios::out);
			if (file.fail()) {
				cout << "�ļ�д��ʧ��" << endl;
				exit(0);
			}
			P.writeBigNumbertofile(&file, 4, P, Q, G, Y);
			file.close();
			file.open("private.txt", ios::out);
			if (file.fail()) {
				cout << "�ļ�д��ʧ��" << endl;
				exit(0);
			}
			cout << "X: ";
			X.unsignedprintBigNumber();
			cout << endl;
			cout << "XΪ���˽Կ�������������Ѿ�д���ļ�\"private.txt\"" << endl;
			X.writeBigNumbertofile(&file, 4, P, Q, G, X);
			file.close();
		}
		/*******************ǩ������***********************/
		else if (argv[1][1] == 's') {
			/*���ȵõ��ļ���hashֵ*/
			fstream file1;
			file1.open(argv[2], ios::in);
			if (file1.fail()) {
				cout << "�ļ���ʧ��" << endl;
				exit(0);
			}
			shatext = shaFile(&file1);
			file1.close();
			/*��������ȡ�ļ�˽Կ*/
			file1.open("private.txt", ios::in);
			if (file1.fail()) {
				cout << "�ļ���ʧ��" << endl;
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
			/*����һ��С��q�������k*/
			K.generateNumber(100);
			/*����K����Ԫ*/
			IK = K.inverseBigNumber(Q);
			//cout << "IK: ";
			//IK.unsignedprintBigNumber();
			tmp = G.bigNumMod(K, P);
			R = tmp.bigNumMod(BigNumber(1), Q);
			tmp = IK * (shatext + (X*R));
			S = tmp.bigNumMod(BigNumber(1), Q);
			cout << "��Ϣ��ǩ��Ϊ: " << endl;
			cout << "R: ";
			R.unsignedprintBigNumber();
			cout << endl;
			cout << "S: ";
			S.unsignedprintBigNumber();
			cout << endl;
			R.writeBigNumbertofile(&file1, 2, R, S);
			file1.close();
		}
		/*******************��֤ǩ��***********************/
		else if (argv[1][1] == 'v') {
			/*���ȵõ��ļ���hashֵ*/
			fstream file1;
			string s;
			file1.open(argv[2], ios::in);
			if (file1.fail()) {
				cout << "�ļ���ʧ��" << endl;
				exit(0);
			}
			shatext = shaFile(&file1);
			file1.close();
			/*��������ȡ�ļ�˽Կ*/
			file1.open("public.txt", ios::in);
			if (file1.fail()) {
				cout << "�ļ���ʧ��" << endl;
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
			/*��������ȡ�ļ���ǩ��R S*/
			file1.open("signature.txt", ios::in);
			if (file1.fail()) {
				cout << "�ļ���ʧ��" << endl;
				exit(0);
			}
			file1 >> s;
			R = BigNumber(s, 10);
			file1 >> s;
			S = BigNumber(s, 10);
			file1.close();
			/*������Ϊ��֤����*/
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
			cout << "R: ";
			R.unsignedprintBigNumber();
			cout << endl;
			cout << "V: ";
			V.unsignedprintBigNumber();
			cout << endl;
			if (V.unsignedisEqual(V, R)) {
				cout << "ǩ����Ч" << endl;
			}
			else {
				cout << "ǩ����Ч" << endl;
			}
		}
		else {
			cout << "��������ȷ����" << endl;
		}
	}
	else {
		cout << "��������ȷ����" << endl;
	}
	return 0;
}

