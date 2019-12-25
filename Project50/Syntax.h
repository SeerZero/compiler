#pragma once
#include"Scan.h"
#include"Scan.h"
#include"Parse.h"
#include"SyncTable.h"

class Syntax {
public:
	Scan scanner;
	SyncTable ct;
	int errPos;
	int errLine;
	string errMessage;
	stack<int>lrProcess;
	stack<string>name;
	int syn();
	int guiyue(int id);
	vector<Synbl>synbl;
	vector<FourExp>fourExp;
	vector<FourExp>youhuaExp;
	vector<Consl>consl;
	Vall vall;
	int cnt = 0;
	bool bif = 0, bwhile = 0;
	int kuohaonum = 0;
	int conlnum = 0;
	string nextName();
	string change(int s);
	int changetoint(string s);
	vector<Pfinfl>pfinfl;
	int funcv = 0;
	int funcn = 0;
	int funcnum = 0;
	int line, pos;
	bool bel;
	void show();
	void youhua();
};