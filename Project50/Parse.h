#pragma once
#include"LibFunc.h"

struct Synbl {
	string name;  //����token��token�ţ�������name��type��
	string type;
	char cat;  //����
	int addr;  //��ַ
	Synbl(string s,string t, char c, int a) :name(s),type(t), cat(c), addr(a) {}
	void show();
	Synbl() {}
};

struct Tapel {
	int tval;	//��¼һ������������  ���ʹ���
	int tpoint;  //���;�����������
};
struct Lenl {
	int len;	//���ͳ���
};

struct Ainfl {
	int low, up;  //�½磬�Ͻ�
	int ctp;      //ָ������
	int clen;     //��Ԫ(��λ)����
};

struct Pfinfl {
	string name;
	int level, off, fn,entry; //��κţ����࣬������������ڵ�ַ
	Pfinfl() {}
	Pfinfl(string n,int a,int b):name(n),level(a),off(4),fn(b){}
	void show();
};

struct Consl {
	string name;
	int data;
	int addr;
	Consl() {}
	Consl(string a, int b, int c) :name(a), data(b), addr(c) {};
};

struct verb {
	string name;
	int l, r;
	verb(string a, int b, int c) :name(a), l(b), r(c) {}
};

struct Vall {
	int start;
	int level;			//�����Ĳ㼶
	int OldSp;			//old sp      0
	int retu;			//���ص�ַ     1
	int extdisplay;		//ȫ��display    2
	int num;			//��������     3
	vector<verb>xingcan;		//�βε�Ԫ,lr�ڴ��ַ��name����
	int displaystart;	//dispaly����ʼ��ַ
	vector<int>display;
	int localverbstart;		//�ֲ���������ʼ��ַ.
	vector<verb>localverb;	//
	map<string, int>m;		//��ʶ�����Ƶ���ʼ��ַ  ��ѭ��С����������
	int localverbnow;
};

struct FourExp {
	string first, second, third, fourth;
	FourExp() {}
	FourExp(string a, string b, string c, string d) :first(a), second(b), third(c), fourth(d) {}
};
