#include"Syntax.h"
//注意写一下报错
//加一下函数

string Syntax::change(int s) {
	string x = "";
	stack<int>stk;
	while (s != 0) {
		stk.push(s % 10);
		s /= 10;
	}
	while (!stk.empty()) {
		x.append(1, '0' + stk.top() % 10);
		stk.pop();
	}
	return x;
}
int Syntax::changetoint(string s) {
	int x = 0;
	for (int i = 0; i < s.size(); i++) {
		x *= 10;
		x += s[i] - '0';
	}
	return x;
}
string Syntax::nextName() {
	string s = "t";
	int x = cnt;
	stack<int>stk;
	while (x != 0) {
		stk.push(x % 10);
		x/= 10;
	}
	while (!stk.empty()) {
		s.append(1, '0' + stk.top());
		stk.pop();
	}
	return s;
}

int Syntax::syn() {		//LR（1）分析控制器
	vall.num = 0;
	vall.OldSp = 0;
	vall.retu = 0;
	vall.extdisplay = 0;
	vall.display.push_back(0);
	vall.localverbstart = 5;
	vall.localverbnow = 5;
	//初始化：
	lrProcess.push(0);			//开始状态放0
	Token nowToken;				//当前读的token
	string w;
	int xk, lastOperator = 0;  //xk，当前栈顶，lastOperator上次是归约还是移进
	while (1) {
		xk = lrProcess.top();
		if (lastOperator == 0) {		//如果上次是移进，则读下一个单词
			nowToken = scanner.next();
			line = nowToken.line_number;
			pos = nowToken.line_pos;
			if (nowToken.is_error==1)return 0;
			if (funcn == 1 && nowToken.name2 == "id")funcv++;
			if (nowToken.name == "if")bif = 1;
			else if (nowToken.name == "while")bwhile = 1;
			else if ((bif||bwhile)&&nowToken.name == "(")kuohaonum++;
			else if ((bif || bwhile) && nowToken.name == ")")kuohaonum--;
			else if (kuohaonum == 0) {
				if (bif)guiyue(510);
				if (bwhile)guiyue(520);
			}
			if (nowToken.name2 == "int_num") {
				if (vall.m.count(nowToken.name) == 0) {
					vall.m[nowToken.name] = conlnum * 4+1000;
					consl.push_back(Consl(nowToken.name, changetoint(nowToken.name), conlnum * 4 + 1000));
					conlnum++;
				}
			}
			w = nowToken.name2;
		}
		else {
			w = nowToken.name2;					//如果上次是归约，则等于上次归约式子的左部
		}
		ct.R(xk, w);	//查询xk状态遇到w的转移	
		//cout << xk << ' ' << w << ' ' << ct.state << endl;
		if (ct.state < 0 && ct.state != -1000) {		//归约
			while (ct.state < 0 && ct.state != -1000) {
				//cout << xk << "归约" << endl;
				cout << ct.guocheng << endl;
				//cout << ct.id << endl;
				for (int i = 0; i < ct.num; i++)lrProcess.pop();
				xk = lrProcess.top();
				w = ct.w;
				//w==那啥就出栈填写符号表。
				if(guiyue(-ct.state)==-1)return -1;
				ct.R(xk, w);
			}
			if (ct.state > 0 && ct.state != 1000) {  //移进
		//		cout << xk << "读"<<w<<"移进"<<ct.state << endl;
				if (nowToken.name == "return")nowToken.name2 = "return";
				if (w == "id"||w=="int_num")name.push(nowToken.name);
				lrProcess.push(ct.state);
				lastOperator = 1;
			}
			else if (ct.state == 1000) {
				cout << "LR(1)分析成功" << endl;
				break;
			}
			else if (ct.state = -1000) {
				cout << "error！  语法错误！  " << "   line: " << nowToken.line_number + 1 << " pos:" << nowToken.pos << endl;
				return -1;
			}
		}
		else if (ct.state > 0 && ct.state != 1000) {  //移进
		//	cout << xk << "读" << w << "移进" << ct.state << endl;
			if (w == "id" || w == "int_num")name.push(nowToken.name);
			if (nowToken.name == "while") {
				fourExp.push_back(FourExp("wh", "_", "_", "_"));
			}
			if (nowToken.name == "else") {
				fourExp.push_back(FourExp("el", "_", "_", "_"));
				bel = 1;
			}
			if (nowToken.name == "return")nowToken.name2 = "return";
			lrProcess.push(ct.state);
			lastOperator = 0;
		}
		else if (ct.state == 1000) {
			cout << "LR(1)分析成功" << endl;
			break;
		}
		else if (ct.state = -1000) {
			cout << "error！  语法错误！  " << "   line: " << nowToken.line_number+1 << " pos:" << nowToken.pos << endl;
			return -1;
		}
	}
	//freopen("后端测试样例.txt", "w", stdout);
	return 1;
}

int Syntax::guiyue(int id) {
	string n, n1, n2,n3;
	switch (id) {
	case 11:
		fourExp.push_back(FourExp("end", "func", "_", "_"));		//代表函数结束
		break;
	case 58:
		fourExp.push_back(FourExp("re0", "_", "_", "_"));
		break;
	case 59:
		n = name.top();
		name.pop();
		fourExp.push_back(FourExp("re", "_", "_", n));
		break;
	case 13:
		if (funcn == 1) {
			n = name.top();
			name.pop();
			fourExp.push_back(FourExp("func", n, "_", "_"));
			synbl.push_back(Synbl(n, "/", 'p', ++funcnum));
			pfinfl.push_back(Pfinfl(n, 0, 0));
		}
		funcn = 0;
		funcv = 0;
		break;
	case 12:
		funcn = 1;
		break;
	case 14:
		if (funcv == 2) {
			n2 = name.top();
			name.pop();
			n1 = name.top();
			name.pop();
			n = name.top();
			name.pop();
			fourExp.push_back(FourExp("func", n, "_", "_"));
			synbl.push_back(Synbl(n, "/", 'p', ++funcnum));
			vall.localverb.push_back(verb(n1, vall.localverbnow, vall.localverbnow + 3));
			vall.localverbnow += 4;
			vall.m[n1] = vall.localverbnow - 4;
			synbl.push_back(Synbl(n1, "i", 'V', vall.localverbnow - 4));
			vall.localverb.push_back(verb(n2, vall.localverbnow, vall.localverbnow + 3));
			vall.localverbnow += 4;
			vall.m[n2] = vall.localverbnow - 4;
			synbl.push_back(Synbl(n2, "i", 'V', vall.localverbnow - 4));
			pfinfl.push_back(Pfinfl(n, 0, 2));
		}
		if (funcv == 1) {
			n1 = name.top();
			name.pop();
			n = name.top();
			name.pop();
			fourExp.push_back(FourExp("func", n, "_", "_"));
			synbl.push_back(Synbl(n, "/", 'p', ++funcnum));
			vall.localverb.push_back(verb(n1, vall.localverbnow, vall.localverbnow + 3));
			vall.localverbnow += 4;
			vall.m[n1] = vall.localverbnow - 4;
			synbl.push_back(Synbl(n1, "i", 'V', vall.localverbnow - 4));
			pfinfl.push_back(Pfinfl(n, 0, 1));
		}
		if (funcv == 0) {
			n = name.top();
			name.pop();
			fourExp.push_back(FourExp("func", n, "_", "_"));
			synbl.push_back(Synbl(n, "/", 'p', ++funcnum));
			pfinfl.push_back(Pfinfl(n, 0, 0));
		}
		funcn = 0;
		funcv = 0;
		break;
	case 72:
		if (funcv == 2) {
			n2 = name.top();
			name.pop();
			n1 = name.top();
			name.pop();
			n = name.top();
			name.pop();
			cnt++;
			n3 = nextName();
			fourExp.push_back(FourExp(n, n1, n2, n3));
			name.push(n3);
			vall.localverb.push_back(verb(n3, vall.localverbnow, vall.localverbnow + 3));
			vall.localverbnow += 4;
			vall.m[n3] = vall.localverbnow - 4;
		}
		if (funcv == 1) {
			n1 = name.top();
			name.pop();
			n = name.top();
			name.pop();
			cnt++;
			n3 = nextName();
			fourExp.push_back(FourExp(n, n1, "_", n3));
			name.push(n3);
			vall.localverb.push_back(verb(n3, vall.localverbnow, vall.localverbnow + 3));
			vall.localverbnow += 4;
			vall.m[n3] = vall.localverbnow - 4;
		}
		if (funcv == 0) {
			n = name.top();
			name.pop();
			cnt++;
			n3 = nextName();
			fourExp.push_back(FourExp(n, "_", "_", n3));
			name.push(n3);
			vall.localverb.push_back(verb(n3, vall.localverbnow, vall.localverbnow + 3));
			vall.localverbnow += 4;
			vall.m[n3] = vall.localverbnow - 4;
		}
		funcn = 0;
		funcv = 0;
		break;
	case 5:			//变量名填符号表
		if (funcn == 1)break;
		n = name.top();
		name.pop();
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 3));
		vall.localverbnow += 4;
		vall.m[n] = vall.localverbnow - 4;
		synbl.push_back(Synbl(n, "i", 'v', vall.localverbnow - 4));
		break;
	case 29:		//赋值表达式
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		if (vall.m.count(n1) == 0) {
			cout << "error! 语义分析错误  未定义的标识符 " << n1 << ' ' << "line:"<<line<<' '<<"por:"<<pos << endl;
			return -1;
		}
		if(vall.m.count(n2) == 0) {
			cout << "error! 语义分析错误  未定义的标识符 " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		fourExp.push_back(FourExp("=", n2, "_", n1));
		break;
	case 31:			//或表达式
		++cnt;
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		cnt++;
		n = nextName();
		if (vall.m.count(n1) == 0) {
			cout << "error! 语义分析错误  未定义的标识符 " << n1 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		if (vall.m.count(n2) == 0) {
			cout << "error! 语义分析错误  未定义的标识符 " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		fourExp.push_back(FourExp("||", n1, n2, n));
		name.push(n);
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 1));
		vall.localverbnow += 2;
		vall.m[n] = vall.localverbnow - 2;
		break;
	case 33:			//与表达式
		++cnt;
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		n = nextName();
		if (vall.m.count(n1) == 0) {
			cout << "error! 语义分析错误  未定义的标识符 " << n1 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		if (vall.m.count(n2) == 0) {
			cout << "error! 语义分析错误  未定义的标识符 " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		fourExp.push_back(FourExp("&&", n1, n2, n));
		name.push(n);
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 1));
		vall.localverbnow += 2;
		vall.m[n] = vall.localverbnow - 2;
		break;
	case 35:			//等于表达式
		++cnt;
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		n = nextName();
		if (vall.m.count(n1) == 0) {
			cout << "error! 语义分析错误  未定义的标识符 " << n1 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		if (vall.m.count(n2) == 0) {
			cout << "error! 语义分析错误  未定义的标识符 " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		fourExp.push_back(FourExp("==", n1, n2, n));
		name.push(n);
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 1));
		vall.localverbnow += 2;
		vall.m[n] = vall.localverbnow - 2;
		break;
	case 37:			//小于表达式
		++cnt;
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		n = nextName();
		if (vall.m.count(n1) == 0) {
			cout << "error! 语义分析错误  未定义的标识符 " << n1 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		if (vall.m.count(n2) == 0) {
			cout << "error! 语义分析错误  未定义的标识符 " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		fourExp.push_back(FourExp("<", n1, n2, n));
		name.push(n);
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 1));
		vall.localverbnow += 2;
		vall.m[n] = vall.localverbnow - 2;
		break;
	case 38:			//大于表达式
		++cnt;
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		n = nextName();
		if (vall.m.count(n1) == 0) {
			cout << "error! 语义分析错误  未定义的标识符 " << n1 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		if (vall.m.count(n2) == 0) {
			cout << "error! 语义分析错误  未定义的标识符 " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		fourExp.push_back(FourExp(">", n1, n2, n));
		name.push(n);
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 1));
		vall.localverbnow += 2;
		vall.m[n] = vall.localverbnow - 2;
		break;
	case 39:			//小于等于表达式
		++cnt;
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		n = nextName();
		if (vall.m.count(n1) == 0) {
			cout << "error! 语义分析错误  未定义的标识符 " << n1 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		if (vall.m.count(n2) == 0) {
			cout << "error! 语义分析错误  未定义的标识符 " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		fourExp.push_back(FourExp("<=", n1, n2, n));
		name.push(n);
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 1));
		vall.localverbnow += 2;
		vall.m[n] = vall.localverbnow - 2;
		break;

	case 40:			//大于表达式
		++cnt;
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		n = nextName();
		if (vall.m.count(n1) == 0) {
			cout << "error! 语义分析错误  未定义的标识符 " << n1 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		if (vall.m.count(n2) == 0) {
			cout << "error! 语义分析错误  未定义的标识符 " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		fourExp.push_back(FourExp(">=", n1, n2, n));
		name.push(n);
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 1));
		vall.localverbnow += 2;
		vall.m[n] = vall.localverbnow - 2;
		break;

	case 42:			//减法表达式
		++cnt;
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		n = nextName();
		if (vall.m.count(n1) == 0) { 
			cout << "error! 语义分析错误  未定义的标识符 " << n1 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		if (vall.m.count(n2) == 0) {
			cout << "error! 语义分析错误  未定义的标识符 " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		fourExp.push_back(FourExp("-", n1, n2, n));
		name.push(n);
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 3));
		vall.localverbnow += 4;
		vall.m[n] = vall.localverbnow - 4;
		break;
	case 43:			//加法表达式
		++cnt;
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		n = nextName();
		if (vall.m.count(n1) == 0) {
			cout << "error! 语义分析错误  未定义的标识符 " << n1 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		if (vall.m.count(n2) == 0) {
			cout << "error! 语义分析错误  未定义的标识符 " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		fourExp.push_back(FourExp("+", n1, n2, n));
		name.push(n);
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 3));
		vall.localverbnow += 4;
		vall.m[n] = vall.localverbnow - 4;
		break;
	case 45:			//乘法表达式
		++cnt;
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		n = nextName();
		if (vall.m.count(n1) == 0) {
			cout << "error! 语义分析错误  未定义的标识符 " << n1 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		if (vall.m.count(n2) == 0) {
			cout << "error! 语义分析错误  未定义的标识符 " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		fourExp.push_back(FourExp("*", n1, n2, n));
		name.push(n);
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 3));
		vall.localverbnow += 4;
		vall.m[n] = vall.localverbnow - 4;
		break;
	case 46:			//除法表达式
		++cnt;
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		n = nextName();
		if (vall.m.count(n1) == 0) {
			cout << "error! 语义分析错误  未定义的标识符 " << n1 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		if (vall.m.count(n2) == 0) {
			cout << "error! 语义分析错误  未定义的标识符 " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		fourExp.push_back(FourExp("/", n1, n2, n));
		name.push(n);
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 3));
		vall.localverbnow += 4;
		vall.m[n] = vall.localverbnow - 4;
		break;
	case 47:			//取余表达式
		++cnt;
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		if (vall.m.count(n1) == 0) {
			cout << "error! 语义分析错误  未定义的标识符 " << n1 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		if (vall.m.count(n2) == 0) {
			cout << "error! 语义分析错误  未定义的标识符 " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		n = nextName();
		fourExp.push_back(FourExp("%", n1, n2, n));
		name.push(n);
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 3));
		vall.localverbnow += 4;
		vall.m[n] = vall.localverbnow - 4;
		break;
	case 53:			//if表达式的结束 ie
		if (bel) {
			bel = 0;
			fourExp.push_back(FourExp("iee", "_", "_", "_"));
		}
		else {
			fourExp.push_back(FourExp("ie", "_", "_", "_"));
		}
		break;
	case 54:			//带else的if表达式的结束    while表达式的结束   
		if (bel) {
			bel = 0;
			fourExp.push_back(FourExp("iee", "_", "_", "_"));
		}
		else {
			fourExp.push_back(FourExp("ie", "_", "_", "_"));
		}
		for (int i = fourExp.size() - 1; i >= 0; i--) {
			if (fourExp[i].first == "if") {
				fourExp[i].first = "ife";
				break;
			}
		}
		break;
	case 55:			//while的结束
		fourExp.push_back(FourExp("we", "_", "_", "_"));
		break;
	case 510:			//if表达式的开始
		n = name.top();
		name.pop();
		fourExp.push_back(FourExp("if", n, "_", "_"));
		bif = 0;
		break;
	case 520:			//while表达式的开始
		n = name.top();
		name.pop();
		fourExp.push_back(FourExp("do", n, "_", "_"));
		bwhile = 0;
		break;
	}

	return 0;
}

void Syntax::show() {
	cout << endl;
	cout << "符号表" << endl;
	cout << endl << "SYNBL" << endl;
	for (int i = 0; i < synbl.size(); i++)synbl[i].show();
	cout << endl << "PFINFL" << endl;
	for (int i = 0; i < pfinfl.size(); i++)pfinfl[i].show();
	cout << endl << "Consl" << endl;
	for (int i = 0; i < consl.size(); i++) {
		cout << consl[i].name << ' ' << consl[i].data << ' ' << consl[i].addr << endl;
	}
	cout << endl;
	cout << "VALL" << endl;
	for (int i = 0; i < vall.localverb.size(); i++) {
		cout << vall.localverb[i].name << ' ' << vall.localverb[i].l << ' ' << vall.localverb[i].r << endl;
	}
	cout << endl << "四元式" << endl;
	for (int i = 0; i < fourExp.size(); i++) {
		if (fourExp[i].first == "func")cout << endl;
		cout << fourExp[i].first << ' ' << fourExp[i].second << ' ' << fourExp[i].third << ' ' << fourExp[i].fourth << endl;
	}
	cout << endl << "四元式地址形式" << endl;
	for (int i = 0; i < fourExp.size(); i++) {
		if (fourExp[i].first == "func")cout << endl;
		if (fourExp[i].second != "_"&&vall.m.count(fourExp[i].second) != 0)fourExp[i].second = change(vall.m[fourExp[i].second]);
		if (fourExp[i].third != "_"&&vall.m.count(fourExp[i].third) != 0)fourExp[i].third = change(vall.m[fourExp[i].third]);
		if (fourExp[i].fourth != "_"&&vall.m.count(fourExp[i].fourth) != 0)fourExp[i].fourth = change(vall.m[fourExp[i].fourth]);
		cout << fourExp[i].first << ' ' << fourExp[i].second << ' ' << fourExp[i].third << ' ' << fourExp[i].fourth << endl;
	}
}

void Syntax::youhua() {
	int l = 0;
	int r = l+1;
	while (r != fourExp.size() - 1) {
		while (l < fourExp.size() - 1 && (fourExp[l].first == "if" || fourExp[l].first == "ife" || fourExp[l].first == "do" ||
			fourExp[l].first == "wh" || fourExp[l].first == "we" || fourExp[l].first == "ie" ||
			fourExp[l].first == "iee" || fourExp[l].first == "func" || fourExp[l].first == "end" ||
			fourExp[l].first == "el"))l++;
		r = l;
		while (r < fourExp.size() - 1 && (fourExp[r].first != "if" && fourExp[r].first != "ife" && fourExp[r].first != "do" &&
			fourExp[r].first != "wh" && fourExp[r].first != "we" && fourExp[r].first != "ie" &&
			fourExp[r].first != "iee" && fourExp[r].first != "func" && fourExp[r].first != "end" &&
			fourExp[r].first != "el"))r++;
		//(l,r-1)为一个块

		for (int i = l; i < r; i++) {
			//常值优化
			if (fourExp[i].second[0] >= '0'&&fourExp[i].second[0] <= '9'&&
				fourExp[i].third[0] >= '0'&&fourExp[i].third[0] <= '9') {
				int a = changetoint(fourExp[i].second);
				int b = changetoint(fourExp[i].third);
				int c;
				if (fourExp[i].first == "+")c = a + b;
				else if (fourExp[i].first == "-")c = a - b;
				else if (fourExp[i].first == "*")c = a * b;
				else if (fourExp[i].first == "/")c = a / b;
				else if (fourExp[i].first == "%")c = a % b;
				string s = change(c);
				fourExp[i].first = "=";
				fourExp[i].second = change(c);
				fourExp[i].third = "_";
				if (vall.m.count(s) == 0) {
					vall.m[s] = conlnum * 4 + 1000;
					consl.push_back(Consl(s, changetoint(s), conlnum * 4 + 1000));
					conlnum++;
				}
			}
			//公共表达式
			for (int j = i + 1; j < r; j++) {
				if (fourExp[i].first == fourExp[j].first&&fourExp[i].second == fourExp[j].second&&fourExp[i].third == fourExp[j].third
					&&fourExp[i].second!="_"&&fourExp[i].third!="_") {
					bool b = 1;
					for (int k = i; k <= j; k++) {
						if (fourExp[k].fourth == fourExp[i].second || fourExp[k].fourth == fourExp[i].third) {
							b = 0;
							break;
						}
					}
					if (b) {
						string s1 = fourExp[i].fourth;
						string s2 = fourExp[j].fourth;
						++cnt;
						string s = nextName();
						vall.localverb.push_back(verb(s, vall.localverbnow, vall.localverbnow + 3));
						vall.localverbnow += 4;
						vall.m[s] = vall.localverbnow - 4;
						vector <FourExp>::iterator theIterator = fourExp.begin() + i;
						fourExp.insert(theIterator, 1, FourExp(fourExp[i].first, fourExp[i].second, fourExp[i].third, s));
						i++; j++; r++;
						theIterator = fourExp.begin() + j;
						fourExp.erase(theIterator);
						j--; r--;
						theIterator = fourExp.begin() + i;
						fourExp.erase(theIterator);
						j--; i--; r--;
						for (int k = i; k < fourExp.size(); k++) {
							if (fourExp[k].first == s1 || fourExp[k].first == s2)fourExp[k].first = s;
							if (fourExp[k].second == s1 || fourExp[k].second == s2)fourExp[k].second = s;
							if (fourExp[k].third == s1 || fourExp[k].third == s2)fourExp[k].third = s;
							if (fourExp[k].fourth == s1 || fourExp[k].fourth == s2)fourExp[k].fourth = s;
						}
					}
				}
			}
			//无用赋值
			for (int j = i + 1; j < r; j++) {
				if (fourExp[j].fourth == fourExp[i].fourth) {
					bool b = 1;
					for (int k = i + 1; k < j; k++) {
						if (fourExp[k].second == fourExp[i].fourth || fourExp[k].second == fourExp[i].fourth) {
							b = 0;
						}
					}
					vector <FourExp>::iterator theIterator = fourExp.begin() + i;
					if (b) {
						fourExp.erase(theIterator);
						i--;
						j--;
						r--;
					}
				}
			}

		}
	}

}