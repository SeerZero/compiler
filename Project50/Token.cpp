#include"Token.h"
Token::Token(string type,string name,int pos,int linenumber,int token_id,int length,int line_pos,int identifier_id)
{
    this->type = type;
    this->pos = pos;
    this->line_number = line_number;
    this->line_pos=line_pos;
    this->length = length;
    this->identifier_id=identifier_id;
    this->token_id=token_id;
    this->name=name;
 }
 void Token::show()
 {
     cout<<std::left<<setw(15)<<this->pos<<std::left<<setw(15)<<this->name;
     cout<<std::left<<setw(15)<<this->line_number<<std::left<<setw(15)<<this->line_pos;
     cout<<std::left<<setw(15)<<this->identifier_id<<std::left<<setw(15)<<this->token_id;
     cout<<std::left<<setw(15)<<this->type<<std::left<<setw(15)<<this->length<<endl;
 }
 bool Token::check_keyWord()//�ؼ���

{

if(this->token_id == TOKEN_TYPE_KEYWORD)

return true;

return false;

}

bool Token::check_identifier()//��ʶ��

{

if(this->token_id == TOKEN_TYPE_IDENTIFIER)

return true;

return false;

}

bool Token::check_delimiter()//���
        {

if(this->token_id == TOKEN_TYPE_DELIMITER)

return true;

return false;

}

bool Token::check_int()//����
        {

if(this->token_id == TOKEN_TYPE_INT)

return true;

return false;

}

bool Token::check_float()//����
{

if(this->token_id == TOKEN_TYPE_FLOAT)

return true;

return false;

}
bool Token::check_d_leftParentheses()//������
{
    if((this->token_id==TOKEN_TYPE_DELIMITER) && (this->name=="("))
    {
        return true;
    }
    return false;
}
bool Token::check_d_rightParentheses()//������
{
    if(this->token_id==TOKEN_TYPE_DELIMITER && this->name==")")
    {
        return true;
    }
    return false;
}
bool Token::check_d_leftbig()//"{"
{
    if(this->token_id==TOKEN_TYPE_DELIMITER && this->name=="{")
    {
        return true;
    }
    return false;
}
bool Token::check_d_rightbig()//"}"
{
    if(this->token_id==TOKEN_TYPE_DELIMITER && this->name=="}")
    {
        return true;
    }
    return false;
}
bool Token::check_d_and()
{
    if(this->token_id==TOKEN_TYPE_DELIMITER && this->name=="&&")
    {
        return true;
    }
    return false;
}
bool Token::check_d_not()
{
    if(this->token_id==TOKEN_TYPE_DELIMITER && this->name=="!")
    {
        return true;
    }
    return false;
}
bool Token::check_d_equal()
{
    if(this->token_id==TOKEN_TYPE_DELIMITER && this->name=="=")
    {
        return true;
    }
    return false;
}
bool Token::check_d_unequal()
{
    if(this->token_id==TOKEN_TYPE_DELIMITER && this->name=="!=")
    {
        return true;
    }
    return false;
}
bool Token::check_d_or()
{
    if(this->token_id==TOKEN_TYPE_DELIMITER && this->name=="||")
    {
        return true;
    }
    return false;
}
bool Token::check_d_sub()//����
{
    if(this->token_id==TOKEN_TYPE_DELIMITER && this->name=="-")
    {
        return true;
    }
    return false;
}
bool Token::check_d_maohao()//":"
{
    if(this->token_id==TOKEN_TYPE_DELIMITER && this->name==":")
    {
        return true;
    }
    return false;
}
bool Token::check_d_fenhao()//";"
{
    if(this->token_id==TOKEN_TYPE_DELIMITER && this->name==";")
    {
        return true;
    }
    return false;
}
bool Token::check_d_add()//�Ӻ�
{
    if(this->token_id==TOKEN_TYPE_DELIMITER && this->name=="+")
    {
        return true;
    }
    return false;
}
bool Token::check_d_mul()//�˺�
{
    if(this->token_id==TOKEN_TYPE_DELIMITER && this->name=="*")
    {
        return true;
    }
    return false;
}
bool Token::check_d_div()//����
{
    if(this->token_id==TOKEN_TYPE_DELIMITER && this->name=="/")
    {
        return true;
    }
    return false;
}
bool Token::check_k_int()//�ؼ���int
{
    if(this->token_id==TOKEN_TYPE_INT && this->name=="int")
    {
        return true;
    }
    return false;
}
bool Token::check_k_if()//�ؼ���if
{
    if(this->token_id==TOKEN_TYPE_INT && this->name=="if")
    {
        return true;
    }
    return false;
}
bool Token::check_k_while()//�ؼ���while
{
    if(this->token_id==TOKEN_TYPE_INT && this->name=="while")
    {
        return true;
    }
    return false;
}
bool Token::check_k_else()//�ؼ���else
{
    if(this->token_id==TOKEN_TYPE_INT && this->name=="else")
    {
        return true;
    }
    return false;
}
bool Token::check_id()//�ؼ���case
{
    if(this->name2=="id")
    {
        return true;
    }
    return false;
}

