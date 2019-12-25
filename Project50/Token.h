#pragma once
#include"LibFunc.h"
#include<iomanip>
/*
	const int token_eof =-1;
	��������ʽ����LexicalAnalysis.h 11-20��  //�е㲹�䣬��tokenʶ���������
*/
const int TOKEN_TYPE_EOF            = -1; // Token ĩβ
const int TOKEN_TYPE_UNKNOWN        = 0;// δ֪
const int TOKEN_TYPE_KEYWORD        = 1; // �ؼ���
const int TOKEN_TYPE_IDENTIFIER     = 2;  // ��ʶ��
const int TOKEN_TYPE_DELIMITER      = 3;   // ���
const int TOKEN_TYPE_INT            = 4;   // ����
const int TOKEN_TYPE_FLOAT          = 5; // ����
const int TOKEN_TYPE_CHAR           = 6;  // �ַ�
const int TOKEN_TYPE_STR            = 7;  // �ַ���
const int TOKEN_TYPE_COMMENT        = 8;  // ע��
struct Token {
public:                  //	            ��int main()�е�   main  Ϊ��
	int pos;             //λ�ã�����   		             2
	string name;
	string name2;        //����                             main
	string type;    	     //����                          _identifier
	int token_id;        //token��Ӧ����id                   1
	int identifier_id;   //���ű��е�id                      1
	//���ڱ���
	int line_number;     //������							 1
	int line_pos;        //�ڸ��еĵڼ���λ��(0��ʼ)         4
	int length;          //����=name.size()                  4

	int is_error;		//�Ƿ����
	Token() {}			 //�޲ι��캯��
Token(string type,string name,int pos,int linenumber,int token_id,int length,int line_pos,int identifier_id);
void show();
bool check_keyWord();//�ؼ���
bool check_identifier();//��ʶ��
bool check_delimiter();//���
bool check_int();//����
bool check_float();//����
bool check_d_leftParentheses();//������
bool check_d_rightParentheses();//������
bool check_d_sub();//����
bool check_d_add();//�Ӻ�
bool check_d_mul();//�˺�
bool check_d_div();//����
bool check_k_int();//�ؼ���int
bool check_k_if();//�ؼ���if
bool check_k_while();//�ؼ���while
bool check_k_else();//�ؼ���else
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
