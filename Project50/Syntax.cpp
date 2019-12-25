#include"Syntax.h"
//ע��дһ�±���
//��һ�º���

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

int Syntax::syn() {		//LR��1������������
	vall.num = 0;
	vall.OldSp = 0;
	vall.retu = 0;
	vall.extdisplay = 0;
	vall.display.push_back(0);
	vall.localverbstart = 5;
	vall.localverbnow = 5;
	//��ʼ����
	lrProcess.push(0);			//��ʼ״̬��0
	Token nowToken;				//��ǰ����token
	string w;
	int xk, lastOperator = 0;  //xk����ǰջ����lastOperator�ϴ��ǹ�Լ�����ƽ�
	while (1) {
		xk = lrProcess.top();
		if (lastOperator == 0) {		//����ϴ����ƽ��������һ������
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
			w = nowToken.name2;					//����ϴ��ǹ�Լ��������ϴι�Լʽ�ӵ���
		}
		ct.R(xk, w);	//��ѯxk״̬����w��ת��	
		//cout << xk << ' ' << w << ' ' << ct.state << endl;
		if (ct.state < 0 && ct.state != -1000) {		//��Լ
			while (ct.state < 0 && ct.state != -1000) {
				//cout << xk << "��Լ" << endl;
				cout << ct.guocheng << endl;
				//cout << ct.id << endl;
				for (int i = 0; i < ct.num; i++)lrProcess.pop();
				xk = lrProcess.top();
				w = ct.w;
				//w==��ɶ�ͳ�ջ��д���ű�
				if(guiyue(-ct.state)==-1)return -1;
				ct.R(xk, w);
			}
			if (ct.state > 0 && ct.state != 1000) {  //�ƽ�
		//		cout << xk << "��"<<w<<"�ƽ�"<<ct.state << endl;
				if (nowToken.name == "return")nowToken.name2 = "return";
				if (w == "id"||w=="int_num")name.push(nowToken.name);
				lrProcess.push(ct.state);
				lastOperator = 1;
			}
			else if (ct.state == 1000) {
				cout << "LR(1)�����ɹ�" << endl;
				break;
			}
			else if (ct.state = -1000) {
				cout << "error��  �﷨����  " << "   line: " << nowToken.line_number + 1 << " pos:" << nowToken.pos << endl;
				return -1;
			}
		}
		else if (ct.state > 0 && ct.state != 1000) {  //�ƽ�
		//	cout << xk << "��" << w << "�ƽ�" << ct.state << endl;
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
			cout << "LR(1)�����ɹ�" << endl;
			break;
		}
		else if (ct.state = -1000) {
			cout << "error��  �﷨����  " << "   line: " << nowToken.line_number+1 << " pos:" << nowToken.pos << endl;
			return -1;
		}
	}
	//freopen("��˲�������.txt", "w", stdout);
	return 1;
}

int Syntax::guiyue(int id) {
	string n, n1, n2,n3;
	switch (id) {
	case 11:
		fourExp.push_back(FourExp("end", "func", "_", "_"));		//����������
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
	case 5:			//����������ű�
		if (funcn == 1)break;
		n = name.top();
		name.pop();
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 3));
		vall.localverbnow += 4;
		vall.m[n] = vall.localverbnow - 4;
		synbl.push_back(Synbl(n, "i", 'v', vall.localverbnow - 4));
		break;
	case 29:		//��ֵ���ʽ
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		if (vall.m.count(n1) == 0) {
			cout << "error! �����������  δ����ı�ʶ�� " << n1 << ' ' << "line:"<<line<<' '<<"por:"<<pos << endl;
			return -1;
		}
		if(vall.m.count(n2) == 0) {
			cout << "error! �����������  δ����ı�ʶ�� " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		fourExp.push_back(FourExp("=", n2, "_", n1));
		break;
	case 31:			//����ʽ
		++cnt;
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		cnt++;
		n = nextName();
		if (vall.m.count(n1) == 0) {
			cout << "error! �����������  δ����ı�ʶ�� " << n1 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		if (vall.m.count(n2) == 0) {
			cout << "error! �����������  δ����ı�ʶ�� " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		fourExp.push_back(FourExp("||", n1, n2, n));
		name.push(n);
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 1));
		vall.localverbnow += 2;
		vall.m[n] = vall.localverbnow - 2;
		break;
	case 33:			//����ʽ
		++cnt;
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		n = nextName();
		if (vall.m.count(n1) == 0) {
			cout << "error! �����������  δ����ı�ʶ�� " << n1 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		if (vall.m.count(n2) == 0) {
			cout << "error! �����������  δ����ı�ʶ�� " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		fourExp.push_back(FourExp("&&", n1, n2, n));
		name.push(n);
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 1));
		vall.localverbnow += 2;
		vall.m[n] = vall.localverbnow - 2;
		break;
	case 35:			//���ڱ��ʽ
		++cnt;
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		n = nextName();
		if (vall.m.count(n1) == 0) {
			cout << "error! �����������  δ����ı�ʶ�� " << n1 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		if (vall.m.count(n2) == 0) {
			cout << "error! �����������  δ����ı�ʶ�� " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		fourExp.push_back(FourExp("==", n1, n2, n));
		name.push(n);
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 1));
		vall.localverbnow += 2;
		vall.m[n] = vall.localverbnow - 2;
		break;
	case 37:			//С�ڱ��ʽ
		++cnt;
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		n = nextName();
		if (vall.m.count(n1) == 0) {
			cout << "error! �����������  δ����ı�ʶ�� " << n1 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		if (vall.m.count(n2) == 0) {
			cout << "error! �����������  δ����ı�ʶ�� " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		fourExp.push_back(FourExp("<", n1, n2, n));
		name.push(n);
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 1));
		vall.localverbnow += 2;
		vall.m[n] = vall.localverbnow - 2;
		break;
	case 38:			//���ڱ��ʽ
		++cnt;
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		n = nextName();
		if (vall.m.count(n1) == 0) {
			cout << "error! �����������  δ����ı�ʶ�� " << n1 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		if (vall.m.count(n2) == 0) {
			cout << "error! �����������  δ����ı�ʶ�� " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		fourExp.push_back(FourExp(">", n1, n2, n));
		name.push(n);
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 1));
		vall.localverbnow += 2;
		vall.m[n] = vall.localverbnow - 2;
		break;
	case 39:			//С�ڵ��ڱ��ʽ
		++cnt;
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		n = nextName();
		if (vall.m.count(n1) == 0) {
			cout << "error! �����������  δ����ı�ʶ�� " << n1 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		if (vall.m.count(n2) == 0) {
			cout << "error! �����������  δ����ı�ʶ�� " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		fourExp.push_back(FourExp("<=", n1, n2, n));
		name.push(n);
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 1));
		vall.localverbnow += 2;
		vall.m[n] = vall.localverbnow - 2;
		break;

	case 40:			//���ڱ��ʽ
		++cnt;
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		n = nextName();
		if (vall.m.count(n1) == 0) {
			cout << "error! �����������  δ����ı�ʶ�� " << n1 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		if (vall.m.count(n2) == 0) {
			cout << "error! �����������  δ����ı�ʶ�� " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		fourExp.push_back(FourExp(">=", n1, n2, n));
		name.push(n);
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 1));
		vall.localverbnow += 2;
		vall.m[n] = vall.localverbnow - 2;
		break;

	case 42:			//�������ʽ
		++cnt;
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		n = nextName();
		if (vall.m.count(n1) == 0) { 
			cout << "error! �����������  δ����ı�ʶ�� " << n1 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		if (vall.m.count(n2) == 0) {
			cout << "error! �����������  δ����ı�ʶ�� " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		fourExp.push_back(FourExp("-", n1, n2, n));
		name.push(n);
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 3));
		vall.localverbnow += 4;
		vall.m[n] = vall.localverbnow - 4;
		break;
	case 43:			//�ӷ����ʽ
		++cnt;
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		n = nextName();
		if (vall.m.count(n1) == 0) {
			cout << "error! �����������  δ����ı�ʶ�� " << n1 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		if (vall.m.count(n2) == 0) {
			cout << "error! �����������  δ����ı�ʶ�� " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		fourExp.push_back(FourExp("+", n1, n2, n));
		name.push(n);
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 3));
		vall.localverbnow += 4;
		vall.m[n] = vall.localverbnow - 4;
		break;
	case 45:			//�˷����ʽ
		++cnt;
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		n = nextName();
		if (vall.m.count(n1) == 0) {
			cout << "error! �����������  δ����ı�ʶ�� " << n1 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		if (vall.m.count(n2) == 0) {
			cout << "error! �����������  δ����ı�ʶ�� " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		fourExp.push_back(FourExp("*", n1, n2, n));
		name.push(n);
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 3));
		vall.localverbnow += 4;
		vall.m[n] = vall.localverbnow - 4;
		break;
	case 46:			//�������ʽ
		++cnt;
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		n = nextName();
		if (vall.m.count(n1) == 0) {
			cout << "error! �����������  δ����ı�ʶ�� " << n1 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		if (vall.m.count(n2) == 0) {
			cout << "error! �����������  δ����ı�ʶ�� " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		fourExp.push_back(FourExp("/", n1, n2, n));
		name.push(n);
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 3));
		vall.localverbnow += 4;
		vall.m[n] = vall.localverbnow - 4;
		break;
	case 47:			//ȡ����ʽ
		++cnt;
		n2 = name.top();
		name.pop();
		n1 = name.top();
		name.pop();
		if (vall.m.count(n1) == 0) {
			cout << "error! �����������  δ����ı�ʶ�� " << n1 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		if (vall.m.count(n2) == 0) {
			cout << "error! �����������  δ����ı�ʶ�� " << n2 << ' ' << "line:" << line << ' ' << "pos:" << pos << endl;
			return -1;
		}
		n = nextName();
		fourExp.push_back(FourExp("%", n1, n2, n));
		name.push(n);
		vall.localverb.push_back(verb(n, vall.localverbnow, vall.localverbnow + 3));
		vall.localverbnow += 4;
		vall.m[n] = vall.localverbnow - 4;
		break;
	case 53:			//if���ʽ�Ľ��� ie
		if (bel) {
			bel = 0;
			fourExp.push_back(FourExp("iee", "_", "_", "_"));
		}
		else {
			fourExp.push_back(FourExp("ie", "_", "_", "_"));
		}
		break;
	case 54:			//��else��if���ʽ�Ľ���    while���ʽ�Ľ���   
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
	case 55:			//while�Ľ���
		fourExp.push_back(FourExp("we", "_", "_", "_"));
		break;
	case 510:			//if���ʽ�Ŀ�ʼ
		n = name.top();
		name.pop();
		fourExp.push_back(FourExp("if", n, "_", "_"));
		bif = 0;
		break;
	case 520:			//while���ʽ�Ŀ�ʼ
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
	cout << "���ű�" << endl;
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
	cout << endl << "��Ԫʽ" << endl;
	for (int i = 0; i < fourExp.size(); i++) {
		if (fourExp[i].first == "func")cout << endl;
		cout << fourExp[i].first << ' ' << fourExp[i].second << ' ' << fourExp[i].third << ' ' << fourExp[i].fourth << endl;
	}
	cout << endl << "��Ԫʽ��ַ��ʽ" << endl;
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
		//(l,r-1)Ϊһ����

		for (int i = l; i < r; i++) {
			//��ֵ�Ż�
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
			//�������ʽ
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
			//���ø�ֵ
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