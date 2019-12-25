#pragma once
#include"LibFunc.h"
#include<iomanip>
/*
	const int token_eof =-1;
	用这种形式搬运LexicalAnalysis.h 11-20行  //有点补充，和token识别关联起来
*/
const int TOKEN_TYPE_EOF            = -1; // Token 末尾
const int TOKEN_TYPE_UNKNOWN        = 0;// 未知
const int TOKEN_TYPE_KEYWORD        = 1; // 关键字
const int TOKEN_TYPE_IDENTIFIER     = 2;  // 标识符
const int TOKEN_TYPE_DELIMITER      = 3;   // 界符
const int TOKEN_TYPE_INT            = 4;   // 整型
const int TOKEN_TYPE_FLOAT          = 5; // 浮点
const int TOKEN_TYPE_CHAR           = 6;  // 字符
const int TOKEN_TYPE_STR            = 7;  // 字符串
const int TOKEN_TYPE_COMMENT        = 8;  // 注释
struct Token {
public:                  //	            以int main()中的   main  为例
	int pos;             //位置（词序）   		             2
	string name;
	string name2;        //内容                             main
	string type;    	     //类型                          _identifier
	int token_id;        //token对应类型id                   1
	int identifier_id;   //符号表中的id                      1
	//用于报错
	int line_number;     //所在行							 1
	int line_pos;        //在该行的第几个位置(0开始)         4
	int length;          //长度=name.size()                  4

	int is_error;		//是否错误
	Token() {}			 //无参构造函数
Token(string type,string name,int pos,int linenumber,int token_id,int length,int line_pos,int identifier_id);
void show();
bool check_keyWord();//关键词
bool check_identifier();//标识符
bool check_delimiter();//界符
bool check_int();//整型
bool check_float();//浮点
bool check_d_leftParentheses();//“（”
bool check_d_rightParentheses();//“）”
bool check_d_sub();//减号
bool check_d_add();//加号
bool check_d_mul();//乘号
bool check_d_div();//除号
bool check_k_int();//关键词int
bool check_k_if();//关键词if
bool check_k_while();//关键词while
bool check_k_else();//关键词else
bool check_d_fenhao();//";"
bool check_d_maohao();//":"
bool check_d_leftbig();//"{"
bool check_d_rightbig();//"}"
bool check_id();
bool check_d_and();//
bool check_d_not();//
bool check_d_or();//
bool check_d_equal();//
bool check_d_unequal();//
}
;
