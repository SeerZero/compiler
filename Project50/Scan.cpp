#include"Scan.h"
#include"Token.h"
void Scan::init_keyAndDel() {
	/*
			填写初始化界符
			填写初始化关键字
	*/
	scan_key.push_back("int");
	scan_key.push_back("if");
	scan_key.push_back("while");
	scan_key.push_back("else");
	scan_key.push_back("void");
	scan_key.push_back("program");
	scan_key.push_back("var");
	scan_key.push_back("char");
	scan_key.push_back("string");
	scan_key.push_back("break");
	scan_key.push_back("continue");
	scan_key.push_back("return");
	scan_del.push_back("(");
	scan_del.push_back("=");
	scan_del.push_back(">");
	scan_del.push_back("<");
	scan_del.push_back(">=");
	scan_del.push_back("==");
	scan_del.push_back("<=");
	scan_del.push_back("{");
	scan_del.push_back("}");
	scan_del.push_back(")");
	scan_del.push_back(":");
	scan_del.push_back(";");
	scan_del.push_back("+");
	scan_del.push_back("-");
	scan_del.push_back("*");
	scan_del.push_back("/");
	scan_del.push_back(",");
	scan_del.push_back("!=");
	scan_del.push_back("&&");
	scan_del.push_back("||");
	scan_del.push_back("%");
}
Scan::Scan() {
	init_keyAndDel();
	head = 0;
	line = 1;
	order = 0;
	judge = 0;
	c = '@';
	file = "hello.txt";
	infile.open(file.data());
	assert(infile.is_open());
	infile >> noskipws;
}
Token Scan::next() {  //返回一个token的全部信息
	Token a;
	if (!infile.eof())
	{
		if (c == '#')
		{
			cout << "扫描结束!!!" << endl;
			exit(0);
		}
		while (c == ' ')//消除空格
		{
			infile >> c;
			head++;
		}
		if (c == '\n')//消除换行以及\t
		{
			head = 0;
			line++;
			infile >> c;
			while (c == '\t')
			{
				infile >> c;
				head++;
			}
			if (c == '#')
			{
				cout << "扫描结束!!!" << endl;
				exit(0);
			}
		}
		if (c == '/')//消除注释以及判断除号O
		{
			infile >> c;
			if (c == '*')//形如此类
			{
				while (true)
				{
					infile >> c;
					if (c == '*')
					{
						infile >> c;
						if (c == '/')
						{
							infile >> c;
							break;
						}
					}
					else if (c == '\n')
					{
						line++;
						head = 0;
					}
				}
			}
			else  if (c == '/')/*形如此类*/
			{
				char buf[1000];
				infile.getline(buf, 1000);
				head = 0;
				line++;
				infile >> c;
			}
			else//除号
			{
				a.pos = order;
				order++;
				a.name = "/";
				a.name2 = "/";
				a.token_id = 3;
				a.length = 1;
				a.type = "界符";
				a.identifier_id = 15;
				a.line_pos = head;
				a.line_number = line;
				head++;
				token_type.push_back("del");
				token_id.push_back(15);
				return a;
			}
		}
		if (c == '\n')//消除换行以及\t
		{
			head = 0;
			line++;
			infile >> c;
			while (c == '\t')
			{
				infile >> c;
				head++;
			}
			if (c == '#')
			{
				exit(0);
			}
		}
		s.clear();
		a.pos = order;
		order++;
		a.line_number = line;
		a.line_pos = head;
		if (c == '@')
		{
			infile >> c;
		}
		while (!infile.eof())
		{
			//常数
			if (c >= '0'&&c <= '9')
			{
				a.type = "整型";
				a.token_id = 4;
				s.append(1, c);
				infile >> c;
				head++;
				if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z'))
				{
					s.append(1, c);
					Token t;
					cout << "error!!!\t词法分析报错\tline:" << line << "\tpos:" << head<<endl;
					order--;
					t.is_error = 1;
					return t;
				}
				while (c >= '0'&&c <= '9')
				{
					s.append(1, c);
					infile >> c;
					head++;
				}
				if (c == '.')
				{
					a.type = "浮点";
					a.token_id = 5;
					s.append(1, c);
					infile >> c;
					head++;
				}
				while (c >= '0'&&c <= '9')
				{
					s.append(1, c);
					infile >> c;
					head++;
				}
				a.length = s.size();
				a.name = s;
				if (a.type == "整型")
				{
					a.name2 = "int_num";
					if (scan_int.empty())
					{
						scan_int.push_back(s);
						a.identifier_id = 0;
					}
					else
					{
						int i0 = 0;
						int i;
						int i1 = scan_int.size();
						for (i = 0; i < i1; i++)
						{
							if (scan_int[i] == s)
							{
								i0 = 1;
								break;
							}
						}
						if (i0 == 0)
						{
							scan_int.push_back(s);
						}
						else
						{
							i1 = i;
						}
						a.identifier_id = i1;
						token_type.push_back("int");
						token_id.push_back(i1);
					}
				}
				if (a.type == "浮点")
				{
					a.name2 = "double_num";
					if (scan_float.empty())
					{
						scan_float.push_back(s);
						a.identifier_id = 0;
					}
					else
					{
						int i0 = 0;
						int i;
						int i1 = scan_float.size();
						for (i = 0; i < i1; i++)
						{
							if (scan_float[i] == s)
							{
								i0 = 1;
								break;
							}
						}
						if (i0 == 0)
						{
							scan_float.push_back(s);
						}
						else
						{
							i1 = i;
						}
						a.identifier_id = i1;
					}
				}
				break;
			}
			//标识符以及关键字
			else if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z'))
			{
				a.type = "标识符";
				a.token_id = 2;
				a.name2 = "id";
				s.append(1, c);
				infile >> c;
				head++;
				while ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z') || (c >= '0'&&c <= '9'))
				{
					s.append(1, c);
					infile >> c;
					head++;
				}
				for (int key = 0; key < scan_key.size(); key++)
				{
					if (s == scan_key[key])
					{
						a.type = "关键词";
						a.token_id = 1;
						a.name = s;
						a.name2 = s;
						a.length = s.size();
						a.identifier_id = key;
						token_type.push_back("key");
						token_id.push_back(key);
						break;
					}
				}
				a.length = s.size();
				a.name = s;
				if (a.type == "标识符")
				{
					if (scan_identifier.empty())
					{
						scan_identifier.push_back(s);
						a.identifier_id = 0;
					}
					else
					{
						int i0 = 0;
						int i;
						int i1 = scan_identifier.size();
						for (i = 0; i < i1; i++)
						{
							if (scan_identifier[i] == s)
							{
								i0 = 1;
								break;
							}
						}
						if (i0 == 0)
						{
							scan_identifier.push_back(s);
						}
						else
						{
							i1 = i;
						}
						a.identifier_id = i1;
						token_type.push_back("identify");
						token_id.push_back(i1);
					}
				}
				break;
			}
			//界符
			else if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '{' || c == '}' || c == '>' || c == '<' || c == '=' || c == ';' || c == ':' || c == ',' || c == '%' || c == '!')
			{
				a.type = "界符";
				a.token_id = 3;
				s.append(1, c);
				infile >> c;
				head++;
				if (((s == ">") || (s == "<") || (s == "=") || (s == "!")) && c == '=')
				{
					s.append(1, c);
					infile >> c;
					head++;
				}
				for (int i = 0; i < scan_del.size(); i++)
				{
					if (s == scan_del[i])
					{
						a.name = s;
						a.name2 = s;
						a.identifier_id = i;
						a.length = s.size();
						token_type.push_back("del");
						token_id.push_back(i);
						break;
					}
				}
				break;
			}
			//字符
			else if (c == 39)
			{
				a.type = "字符";
				a.token_id = 6;
				s.append(1, c);
				infile >> c;
				head++;
				while (c != 39)
				{
					s.append(1, c);
					infile >> c;
					head++;
				}
				s.append(1, c);
				infile >> c;
				head++;
				a.length = s.size();
				a.name = s;
				a.name2 = s;
				if (scan_str.empty())
				{
					scan_str.push_back(s);
					a.identifier_id = 0;
				}
				else
				{
					int i0 = 0;
					int i;
					int i1 = scan_str.size();
					for (i = 0; i < i1; i++)
					{
						if (scan_str[i] == s)
						{
							i0 = 1;
							break;
						}
					}
					if (i0 == 0)
					{
						scan_str.push_back(s);
					}
					else
					{
						i1 = i;
					}
					a.identifier_id = i1;
				}
				break;
			}
			//字符串
			else if (c == '"')
			{
				a.type = "字符串";
				a.token_id = 7;
				s.append(1, c);
				infile >> c;
				head++;
				while (c != '"')
				{
					s.append(1, c);
					infile >> c;
					head++;
				}
				s.append(1, c);
				infile >> c;
				head++;
				a.length = s.size();
				a.name = s;
				a.name2 = s;
				if (scan_str.empty())
				{
					scan_str.push_back(s);
					a.identifier_id = 0;
				}
				else
				{
					int i0 = 0;
					int i;
					int i1 = scan_str.size();
					for (i = 0; i < i1; i++)
					{
						if (scan_str[i] == s)
						{
							i0 = 1;
							break;
						}
					}
					if (i0 == 0)
					{
						scan_str.push_back(s);
					}
					else
					{
						i1 = i;
					}
					a.identifier_id = i1;
				}
				break;
			}
			else if (c == '\n')
			{
				line++;
				head = 0;
				infile >> c;
			}
			else if (c == '\t')
			{
				head++;
				infile >> c;
			}
			else if (c == '\#')
			{
				cout << "扫描结束！！！" << endl;
				exit(0);
			}
			else if (c == ' ')
			{
			head++;
			infile >> c;
 }
			else
			{
				cout << "error!!!\t词法分析报错\tline:" << line << "\tpos:" << head<<endl;
				Token t;
				t.is_error = 1;
				return t;
			}
		}
	}
	return a;
}
void Scan::show()
{
	int five = 0;
	cout << "token" << endl;
	for (int i = 0; i < token_type.size(); i++)
	{
		if (five == 5)
		{
			cout << endl;
			five = 0;
		}
		cout << "\t("<<token_type[i]<<","<<token_id[i]<<")";
		five++;
	}
	cout << endl;
	five = 0;
	cout << "scan_key:" << endl;
	for (int i = 0; i <scan_key.size(); i++)
	{
		if (five == 5)
		{
			cout << endl;
			five = 0;
		}
		cout << std::left << setw(15) << scan_key[i];
		five++;
	}
	cout << endl;
	five = 0;
	cout << "scan_int:" << endl;
	for (int i = 0; i < scan_int.size(); i++)
	{
		if (five == 5)
		{
			cout << endl;
			five = 0;
		}
		cout << std::left << setw(15) << scan_int[i];
		five++;
	}
	cout << endl;
	five = 0;
	cout << "scan_identify:" << endl;
	for (int i = 0; i < scan_identifier.size(); i++)
	{
		if (five == 5)
		{
			cout << endl;
			five = 0;
		}
		cout << std::left << setw(15) << scan_identifier[i];
		five++;
	}cout << endl;
	five = 0;
	cout << "scan_del:" << endl;
	for (int i = 0; i < scan_del.size(); i++)
	{
		if (five == 5)
		{
			cout << endl;
			five = 0;
		}
		cout << std::left << setw(15) << scan_del[i];
		five++;
	}
	cout << endl;
	five = 0;
}
