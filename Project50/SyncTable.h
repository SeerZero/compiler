#pragma once
#include"LibFunc.h"
#define offset 34//终结符数目
#define ooffset 32//非终结符数目
using namespace std;
class	item_node
{
public:
	int			cfg_no;				//产生式编号
	int			dot_pos;				//加点位置
	set<int>	possible_prefix;		//可能出现输入符号的Tag
	item_node(int a, int b, set<int> c);
	item_node();
};


class sentence {//每一个句子
public:
	string left;
	int left_num;//左部的总序号
	vector<string> right;
	vector<int> all_num;//右部在总表中的序号
	//vector<string>all_num;
	vector<int> right_num;//右部的总序号
	vector<vector<int>> right_int;//右部根据symbol表的分词序号
	void divide();
	sentence();
};

class SyncTable {
public:
	vector<vector<int>> cfg_list;
	int action_goto[500][offset + ooffset];//LR(1)分析表，纵坐标是状态（从0开始），横坐标是字符编号，正值是跳转到的状态，负值是规约的产生式序号（非|版，从1开始）
	vector<sentence> syntax;//文法（句子集合）
	int sen_num = 1;//全局句子序号
	string guocheng;
	int l_num;
	void make_map();

	int is_terminal(string a);

	int is_nonterminal(string a);

	void show_set(set<int> &a);

	void load_syntex();


	void show_syntex();

	void find_first(set<int> & first_list, int left_num, int right_num, int dot);

	set<int> first(int left_num, int right_num, int dot);

	void show_symbol();

	vector<vector<item_node>> closure_item;//项目集簇

	vector<item_node>& get_closure(vector<item_node> &closure);




	vector<item_node> get_goto(const int i, const int x);

	void show_item(vector<item_node> &tem);

	void show_item2(item_node &tem);

	int item_equal(item_node &a, item_node &b);

	int items_equal(vector<item_node> &a, vector<item_node> b);

	int is_exisit(int n, vector<item_node> tem);

	int make_items();

	void show_itemarray();

	void init();

	SyncTable();
	void save_list();

	int state;
	int id;
	string w;
	int num;
	void R(int b, string a);
};
