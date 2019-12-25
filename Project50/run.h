#pragma once
#include"Syntax.h"
#define MaxSize 50
class run {
public:
	Syntax syn;
	int n1, n2;
	stack<int>word_continue;
	stack<int>word_break;
	int while_sum;
	int endwhile_sum;
	int while_end;
	int while_ssum;
	int if_else1;
	int if_end1;
	int if_end2;
	int if_sum1;
	int if_sum2;
	int if_ssum1;
	int if_ssum2;
	int return_1;
	int return_2;
	string else_word[12];
	string endif_word[12];
	string no_else_word[12];
	string num1[12];
	string num2[12];
	string while_word[12];
	string endwhile_word[12];
	vector<FourExp>Qin;
	vector<Synbl>Guo;
	vector<string>int_sum;
	vector<string>bool_DB;
	void Begin();
	void huibian();
	void read();
	void add_bool();
	void all_ten_to_sixteen();
	string ten_to_sixteen(string ten_sum);
	string int_to_string(int one_sum);
	int bool_DB_or_DW(int address);
	int length;
	int length_sybnl;
};
