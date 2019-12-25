#ifndef SCAN_H_INCLUDED
#define SCAN_H_INCLUDED
#pragma once
#include"Token.h"
#include<vector>
#include <fstream>
#include <cassert>
#include <string>
//ɨ�������洢�ִʽ��
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
	string s;//���name
	int head;//����line_pos
	char c;//����ַ�
	int line;//����line_number
	int order;//����pos
	int judge;//�жϳ������
	void init_keyAndDel();
	Scan();
	Token next();
	void show();
};
#endif
