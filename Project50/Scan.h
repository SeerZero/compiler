#ifndef SCAN_H_INCLUDED
#define SCAN_H_INCLUDED
#pragma once
#include"Token.h"
#include<vector>
#include <fstream>
#include <cassert>
#include <string>
//扫描器，存储分词结果
class Scan {
public:
	vector<string>scan_key;
	vector<string>scan_del;
	vector<string>scan_identifier;
	vector<string>scan_int;
	vector<string>scan_float;
	vector<string>scan_char;
	vector<string>scan_str;
	vector<string>token_type;
	vector<int>token_id;
	//vector<string>scan_identiferAndConst;
	string file;
	ifstream infile;
	string s;//存放name
	int head;//代表line_pos
	char c;//存放字符
	int line;//代表line_number
	int order;//代表pos
	int judge;//判断程序结束
	void init_keyAndDel();
	Scan();
	Token next();
	void show();
};
#endif
