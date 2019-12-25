#pragma once
#include"LibFunc.h"

struct Synbl {
	string name;  //调用token表token号（包括了name和type）
	string type;
	char cat;  //种类
	int addr;  //地址
	Synbl(string s,string t, char c, int a) :name(s),type(t), cat(c), addr(a) {}
	void show();
	Synbl() {}
};

struct Tapel {
	int tval;	//记录一个类型码序列  类型代码
	int tpoint;  //类型具体描述代码
};
struct Lenl {
	int len;	//类型长度
};

struct Ainfl {
	int low, up;  //下界，上界
	int ctp;      //指向类型
	int clen;     //单元(单位)长度
};

struct Pfinfl {
	string name;
	int level, off, fn,entry; //层次号，区距，参数个数，入口地址
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
	int level;			//函数的层级
	int OldSp;			//old sp      0
	int retu;			//返回地址     1
	int extdisplay;		//全局display    2
	int num;			//参数个数     3
	vector<verb>xingcan;		//形参单元,lr内存地址，name名字
	int displaystart;	//dispaly的起始地址
	vector<int>display;
	int localverbstart;		//局部变量的起始地址.
	vector<verb>localverb;	//
	map<string, int>m;		//标识符名称的起始地址  遵循最小作用域优先
	int localverbnow;
};

struct FourExp {
	string first, second, third, fourth;
	FourExp() {}
	FourExp(string a, string b, string c, string d) :first(a), second(b), third(c), fourth(d) {}
};
