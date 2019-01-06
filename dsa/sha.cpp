#include<iostream>
#include<fstream>
#include<string>
#include"sha.h"
#include"BigNumber.h"
#define LENGTH 512			//分组长度
#define F1(X,Y,Z) ((X&Y)|((~X)&Z))
#define F2(X,Y,Z) ((X^Y^Z))
#define F3(X,Y,Z) ((X&Y)|(X&Z)|(Y&Z))
#define F4(X,Y,Z) ((X^Y^Z))

uint64_t totalcount;
uint64_t roundtime;		//总循环次数

void initMessage(std::fstream *file,std::fstream *file1) {
	char ch;
	file->get(ch);
	while (!file->eof()) {
		file1->write(&ch,sizeof(char));
		file->get(ch);
	}
	file->close();
	ch = 128;			//先添加一个1
	file1->write(&ch,sizeof(char));
	ch = 0;
	totalcount = file1->tellg();
	uint64_t tmp = totalcount;
	while (!(totalcount%64==0)) {
		file1->write(&ch,sizeof(char));
		totalcount++;
	}
	if ((totalcount-tmp)<8) {
		for (int i = 0; i < 8;i++) {
			file1->write(&ch,sizeof(char));
		}
	}
	tmp = (tmp - 1) * 8;
	file1->seekp(-(int(sizeof(char)*8)),std::ios::end);
	tmp = (tmp << 32) | (tmp >> 32);
	tmp = ((tmp << 16) & 0xffff0000ffff0000) | ((tmp >> 16) & 0x0000ffff0000ffff);
	tmp = ((tmp << 8) & 0xff00ff00ff00ff00) | ((tmp >> 8) & 0x00ff00ff00ff00ff);
	file1->write((char*)&tmp,sizeof(char)*8);
	totalcount = file1->tellp()*8;
}

/*函数返回消息的第i个分组*/
void getMessage(std::fstream* file, int t,uint32_t *buffer) {
	uint32_t result=0;
	char *ch=new char[4];
	for (int i = 0; i < 16;i++) {
		file->read((char*)(&buffer[i]),sizeof(char)*4);
		buffer[i] = (buffer[i] << 16) | (buffer[i] >> 16);
		buffer[i] = ((buffer[i] << 8) & 0xff00ff00) | ((buffer[i] >> 8) & 0x00ff00ff);
	}
}

/*利用sha算法得到消息的哈希值，返回160位消息*/
void shaMessage(std::fstream *file,uint32_t *buffer) {
	std::fstream file1;
	file1.open("tmp",std::ios::binary|std::ios::out);
	if (file1.fail()) {
		std::cout << "文件打开失败" << std::endl;
		exit(0);
	}
	initMessage(file, &file1);
	file1.close();
	file1.open("tmp",std::ios::binary|std::ios::in);

	uint32_t A = 0x67452301;
	uint32_t B = 0xefcdab89;
	uint32_t C = 0x98badcfe;
	uint32_t D = 0x10325476;
	uint32_t E = 0xc3d2e1f0;

	uint32_t K[4] = { 0x5a827999,0x6ed9eba1,0x8f1bbcdc,0xca62c1d6 };

	uint32_t W[80];
	uint32_t M[16];

	roundtime = totalcount / 512;
	for (int t = 0; t < roundtime; t++) {
		uint32_t a = A;
		uint32_t b = B;
		uint32_t c = C;
		uint32_t d = D;
		uint32_t e = E;
		getMessage(&file1, t, M);
		for (int i = 0; i < 80; i++) {
			if (i < 16) {
				W[i] = M[i];
			}
			else {
				W[i] = ((W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16])>>31)| 
					((W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16]) << 1);
			}
		}
		for (int i = 0; i < 80; i++) {
			uint32_t temp;
			if (i >= 0 && i <= 19)temp = ((a >> 27) | (a << 5)) + F1(b, c, d) + e + W[i] + K[0];
			else if (i > 19 && i <= 39) temp = ((a >> 27) | (a << 5)) + F2(b, c, d) + e + W[i] + K[1];
			else if (i > 39 && i <= 59) temp = ((a >> 27) | (a << 5)) + F3(b, c, d) + e + W[i] + K[2];
			else if (i > 59 && i <= 79) temp = ((a >> 27) | (a << 5)) + F4(b, c, d) + e + W[i] + K[3];
			e = d;
			d = c;
			c = (b >> 2) | (b << 30);
			b = a;
			a = temp;
		}
		A += a;
		B += b;
		C += c;
		D += d;
		E += e;
	}
	buffer[0] = A;
	buffer[1] = B;
	buffer[2] = C;
	buffer[3] = D;
	buffer[4] = E;
}

/*利用sha算法计算大整数序列的hash值，返回值为大整数*/
BigNumber shaBigNumber(BigNumber value) {
	std::string s = value.BigNumberToString();
	std::fstream file;
	file.open("7.txt", std::ios::out);
	if (file.fail()) {
		std::cout << "文件建立失败" << std::endl;
		exit(0);
	}
	const char *ch = new char[s.length() + 1];
	file << s;
	file.close();
	uint32_t buffer[5];
	file.open("7.txt",std::ios::in);
	shaMessage(&file,buffer);
	if (remove("7.txt")) {
		std::cout << "文件删除失败" << std::endl;
		exit(0);
	}
	s.resize(160,'0');
	for (int i = 0; i < 5;i++) {
		for (int j = 0; j < 32; j++) {
			s[i * 32 + j] = char(((buffer[i] >> (31-j)) & 0x00000001)) + '0';
		}
	}
	BigNumber result(s,2);
	return result;

}

