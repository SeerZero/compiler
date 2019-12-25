#include"run.h"
void run::huibian()
{
	int start = 0;
	string start_string;
	string return_string;
	int judge_maohao = 0;
	all_ten_to_sixteen();
	for (int i = 0; i < length; i++)
	{
		if (Qin[i].first == "func")
		{
			if (Qin[i].second == "main")
			{
				start = 1;
				cout << std::left << setw(15) << "SSEG" << std::left << setw(15) << "SEGMENT" << endl;
				cout << std::left << setw(15) << "STK"<< std::left << setw(15) << "DB" << std::left << setw(20) << "2000 DUP (0)" << endl;
				cout << std::left << setw(15) << "SSEG" << std::left << setw(15) << "ENDS" << endl;
				cout << std::left << setw(15) << "DSEG" << std::left << setw(15) << "SEGMENT" << endl;
				cout << std::left << setw(15) << "RUL" << std::left << setw(15) << "DB" << std::left << setw(20) << "2000 DUP (0)" << endl;
				cout << std::left << setw(15) << "DSEG" << std::left << setw(15) << "ENDS" << endl;
				cout << std::left << setw(15) << "CSEG" << std::left << setw(15) << "SEGMENT" << endl;
				cout << std::left << setw(15) << "ASSUME" << std::left << setw(15) << "CS:CSEG,DS:DSEG,SS:SSEG" << endl;
				cout << std::left << setw(15) << "START:";
				cout << std::left << setw(10) << "MOV" << std::left << setw(15) << "AX,DSEG" << endl << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << std::left << setw(15) << "DS,AX" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << std::left << setw(15) << "AX,SSEG" << endl << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << std::left << setw(15) << "SS,AX" << endl;
				int address = 1000;
				for (int j = 0; j < syn.consl.size(); j++)
				{
					cout << std::left << setw(15) << " " << std::left << setw(10) 
						<< "MOV" << "WORD PTR   DS:[" << address 
						<< "H],"<< syn.consl[j].name << endl;
					address = address + 4;
				}
				judge_maohao = 0;
			}
			else
			{
				start_string = Qin[i].second;
				start = 0;
				cout << std::left << setw(15) << Qin[i].second << std::left << setw(10) << "PORC" << "NEAR" << endl;
			}
		}
		else if (Qin[i].first == "end")
		{
			if (start == 1)
			{
				if (judge_maohao == 0)
				{
					cout << std::left << setw(15) << " ";
				}
				else
				{
					judge_maohao = 0;
				}
				cout << std::left << setw(10) << "MOV" << "AH,4CH" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "INT" << "21H" << endl;
				cout << std::left << setw(15) << "CSEG" << std::left << setw(10) << "ENDS" << endl;
				cout << std::left << setw(15) << "END" << std::left << setw(10) << "START" << endl;
			}
			else
			{
				if (judge_maohao == 0)
				{
					cout << std::left << setw(15) << " ";
				}
				else
				{
					judge_maohao = 0;
				}
				cout  << "RET" << endl;
				cout << std::left << setw(15) << start_string << std::left << setw(10) << "ENDP" << endl << endl << endl;
			}
		}
		else if (Qin[i].first == "ife" || Qin[i].first == "if")
		{
			if (judge_maohao == 0)
			{
				cout << std::left << setw(15) << " ";
			}
			else
			{
				judge_maohao = 0;
			}
			if (Qin[i].first == "ife")
			{
				if (if_ssum1 == 0)
				{
					if_else1 = if_sum1;
					if_end1 = if_sum1;
				}
				cout << std::left << setw(10) << "MOV" << "AH,DS:[" << Qin[i].second << "H]" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "CMP" << "AH,1" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "JNE" << else_word[if_else1] << endl;
				if_else1++;
				if_sum1++;
				if_ssum1++;
			}
			else
			{
				if (if_ssum2 == 0)
				{
					if_end2 = if_sum2;
				}
				cout << std::left << setw(10) << "MOV" << "AH,DS:[" << Qin[i].second << "H]" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "CMP" << "AH,1" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "JNE" << no_else_word[if_end2] << endl;
				if_end2++;
				if_sum2++;
				if_ssum2++;
			}
		}
		else if (Qin[i].first == "el")
		{
			if (judge_maohao == 0)
			{
				cout << std::left << setw(15) << " ";
			}
			else
			{
				judge_maohao = 0;
			}
			cout << std::left << setw(10) << "JMP" << endif_word[if_end1] << endl;
			if_end1++;
			if_else1--;
			cout << std::left << setw(15) << else_word[if_else1] + ":";
			judge_maohao = 1;
		}
		else if (Qin[i].first == "iee" || Qin[i].first == "ie")
		{
			if (judge_maohao == 1)
			{
				cout << endl;
			}
			if (Qin[i].first == "iee")
			{
				if_end1--;
				cout << std::left << setw(15) << endif_word[if_end1] + ":";
				if_ssum1--;
			}
			else
			{
				if_end2--;
				cout << std::left << setw(15) << no_else_word[if_end2] + ":";
				if_ssum2--;
			}
			judge_maohao = 1;
		}
		else if (Qin[i].first == "wh")
		{
			if (judge_maohao == 1)
			{
				cout << endl;
			}
			if (while_end == 0)
			{
				while_sum = while_ssum;
				endwhile_sum = while_ssum;
			}
			cout << std::left << setw(15) << while_word[while_sum] + ":";
			word_continue.push(while_sum);
			while_sum++;
			while_end++;
			while_ssum++;
			judge_maohao = 1;
		}
		else if (Qin[i].first == "do")
		{
			if (judge_maohao == 0)
			{
				cout << std::left << setw(15) << " ";
			}
			else
			{
				judge_maohao = 0;
			}
			cout << std::left << setw(10) << "MOV" << "AH,DS:[" << Qin[i].second << "H]" << endl;
			cout << std::left << setw(15) << " " << std::left << setw(10) << "CMP" << "AH,1" << endl;
			cout << std::left << setw(15) << " " << std::left << setw(10) << "JNE" << endwhile_word[endwhile_sum] << endl;
			word_break.push(endwhile_sum);
			endwhile_sum++;
		}
		else if (Qin[i].first == "we")
		{
			if (judge_maohao == 0)
			{
				cout << std::left << setw(15) << " ";
			}
			else
			{
				judge_maohao = 0;
			}
			int out1;
			int out2;
			out1 = word_continue.top();
			out2 = word_break.top();
			endwhile_sum--;
			while_sum--;
			if (out1 == while_sum)
			{
				word_continue.pop();
			}
			if (out2 == endwhile_sum)
			{
				word_break.pop();
			}
			cout << std::left << setw(10) << "JMP" << while_word[while_sum] << endl;
			cout << std::left << setw(15) << endwhile_word[endwhile_sum] + ":";
			while_end--;
			judge_maohao = 1;
		}
		else if (Qin[i].first == "co")
		{
			if (judge_maohao == 0)
			{
				cout << endl << std::left << setw(15) << " ";
			}
			else
			{
				judge_maohao = 0;
			}
			int out;
			out = word_continue.top();
			cout << std::left << setw(10) << "JMP" << while_word[out] << endl;
		}
		else if (Qin[i].first == "br")
		{
			if (judge_maohao == 0)
			{
				cout << endl << std::left << setw(15) << " ";
			}
			else
			{
				judge_maohao = 0;
			}
			int out;
			out = word_break.top();
			cout << std::left << setw(10) << "JMP" << endwhile_word[out] << endl;
		}
		else if (Qin[i].first == "re")
		{
			if (judge_maohao == 0)
			{
				cout << std::left << setw(15) << " ";
			}
			else
			{
				judge_maohao = 0;
			}
			for (int t = 0; t < length; t++)
			{
				if (Qin[t].first == start_string)
				{
					return_string = Qin[t].fourth;
					break;
				}
			}
			cout << std::left << setw(10) << "MOV" << "DS:[" << return_string << "],DS:[" << Qin[i].fourth << "]" << endl;
		}
		else
		{
			if (Qin[i].first == "*")
			{
				if (judge_maohao == 0)
				{
					cout << std::left << setw(15) << " ";
				}
				else
				{
					judge_maohao = 0;
				}
				cout << std::left << setw(10) << "MOV" << "AX,DS:[" << Qin[i].second << "H]" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "BX,DS:[" << Qin[i].third << "H]" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "MUL" << "BX" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "DS:[" << Qin[i].fourth << "H],AX" << endl;
			}
			else if (Qin[i].first == "%")
			{
				if (judge_maohao == 0)
				{
					cout << std::left << setw(15) << " ";
				}
				else
				{
					judge_maohao = 0;
				}
				cout << std::left << setw(10) << "MOV" << "DX,0" << endl;
				cout << std::left << setw(10) << "MOV" << "AX,DS:[" << Qin[i].second << "H]" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "BX,DS:[" << Qin[i].third << "H]" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "DIV" << "BX" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "DS:[" << Qin[i].fourth << "H],DX" << endl;
			}
			else if (Qin[i].first == "+")
			{
				if (judge_maohao == 0)
				{
					cout << std::left << setw(15) << " ";
				}
				else
				{
					judge_maohao = 0;
				}
				cout << std::left << setw(10) << "MOV" << "AX,DS:[" << Qin[i].second << "H]" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "BX,DS:[" << Qin[i].third << "H]" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "ADD" << "AX,BX" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "DS:[" << Qin[i].fourth << "H],AX" << endl;
			}
			else if (Qin[i].first == "-")
			{
				if (judge_maohao == 0)
				{
					cout << std::left << setw(15) << " ";
				}
				else
				{
					judge_maohao = 0;
				}
				cout << std::left << setw(10) << "MOV" << "AX,DS:[" << Qin[i].second << "H]" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "BX,DS:[" << Qin[i].third << "H]" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "SUB" << "AX,BX" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "DS:[" << Qin[i].fourth << "H],AX" << endl;
			}
			else if (Qin[i].first == "/")
			{
				if (judge_maohao == 0)
				{
					cout << std::left << setw(15) << " ";
				}
				else
				{
					judge_maohao = 0;
				}
				cout << std::left << setw(10) << "MOV" << "DX,0" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "AX,DS:[" << Qin[i].second << "H]" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "BX,DS:[" << Qin[i].third << "H]" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "DIV" << "BX" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "DS:[" << Qin[i].fourth << "H],AX" << endl;
			}
			else if (Qin[i].first == "&&")
			{
				if (judge_maohao == 0)
				{
					cout << std::left << setw(15) << " ";
				}
				else
				{
					judge_maohao = 0;
				}
				cout << std::left << setw(10) << "MOV" << "AH,DS:[" << Qin[i].second << "H]" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "BH,DS:[" << Qin[i].third << "H]" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "AND" << "AH,BH" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "DS:[" << Qin[i].fourth << "H],AH" << endl;
			}
			else if (Qin[i].first == "||")
			{
				if (judge_maohao == 0)
				{
					cout << std::left << setw(15) << " ";
				}
				else
				{
					judge_maohao = 0;
				}
				cout << std::left << setw(10) << "MOV" << "AH,DS:[" << Qin[i].second << "H]" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "BH,DS:[" << Qin[i].third << "H]" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "OR" << "AH,BH" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "DS:[" << Qin[i].fourth << "H],AH" << endl;
			}
			else if (Qin[i].first == "!=")			//语法限制没有不等于
			{
				if (judge_maohao == 0)
				{
					cout << std::left << setw(15) << " ";
				}
				else
				{
					judge_maohao = 0;
				}
				if (bool_DB_or_DW(i) == 1)
				{
					cout << setw(10) << "MOV" << "AH,DS:[" << Qin[i].second << "H]" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "BH,DS:[" << Qin[i].third << "H]" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "CMP" << "AH,BH" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "JE" << "EQUAL" << num1[n1] << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "AL,1" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "JMP" << "END_UNEQUAL" << num2[n2] << endl;
					cout << std::left << setw(15) << "EQUAL" + num1[n1] + ":";
					cout << std::left << setw(10) << "MOV" << "AL,0" << endl;
					cout << std::left << setw(15) << "END_UNEQUAL" + num2[n2] + ":";
					cout << std::left << setw(10) << "MOV" << "DS:[" << Qin[i].fourth << "H],AL" << endl;
				}
				else
				{
					cout << setw(10) << "MOV" << "AX,DS:[" << Qin[i].second << "H]" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "BX,DS:[" << Qin[i].third << "H]" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "CMP" << "AX,BX" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "JE" << "EQUAL" << num1[n1] << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "AL,1" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "JMP" << "END_UNEQUAL" << num2[n2] << endl;
					cout << std::left << setw(15) << "EQUAL" + num1[n1] + ":";
					cout << std::left << setw(10) << "MOV" << "AL,0" << endl;
					cout << std::left << setw(15) << "END_UNEQUAL" + num2[n2] + ":";
					cout << std::left << setw(10) << "MOV" << "DS:[" << Qin[i].fourth << "H],AL" << endl;
				}
				n1++;
				n2++;
			}
			else if (Qin[i].first == "!")		//语法限制没有！
			{
				if (judge_maohao == 0)
				{
					cout << std::left << setw(15) << " ";
				}
				else
				{
					judge_maohao = 0;
				}
				cout << std::left << setw(10) << "MOV" << "AH,DS:[" << Qin[i].second << "H]" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "NOT" << "AH" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "DS:[" << Qin[i].fourth << "H],AH" << endl;
			}
			else if (Qin[i].first == ">")
			{
				if (judge_maohao == 0)
				{
					cout << std::left << setw(15) << " ";
				}
				else
				{
					judge_maohao = 0;
				}
				if (bool_DB_or_DW(i) == 1)
				{
					cout << setw(10) << "MOV" << "AH,DS:[" << Qin[i].second << "H]" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "BH,DS:[" << Qin[i].third << "H]" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "CMP" << "AH,BH" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "JNA" << "UNABOVE" << num1[n1] << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "AL,1" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "JMP" << "END_ABOVE" << num2[n2] << endl;
					cout << std::left << setw(15) << "UNABOVE" + num1[n1] + ":";
					cout << std::left << setw(10) << "MOV" << "AL,0" << endl;
					cout << std::left << setw(15) << "END_ABOVE" + num2[n2] + ":";
					cout << std::left << setw(10) << "MOV" << "DS:[" << Qin[i].fourth << "H],AL" << endl;
				}
				else
				{
					cout << setw(10) << "MOV" << "AX,DS:[" << Qin[i].second << "H]" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "BX,DS:[" << Qin[i].third << "H]" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "CMP" << "AX,BX" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "JNA" << "UNABOVE" << num1[n1] << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "AL,1" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "JMP" << "END_ABOVE" << num2[n2] << endl;
					cout << std::left << setw(15) << "UNABOVE" + num1[n1] + ":";
					cout << std::left << setw(10) << "MOV" << "AL,0" << endl;
					cout << std::left << setw(15) << "END_ABOVE" + num2[n2] + ":";
					cout << std::left << setw(10) << "MOV" << "DS:[" << Qin[i].fourth << "H],AL" << endl;
				}
				n1++;
				n2++;
			}
			else if (Qin[i].first == "<")
			{
				if (judge_maohao == 0)
				{
					cout << std::left << setw(15) << " ";
				}
				else
				{
					judge_maohao = 0;
				}
				if (bool_DB_or_DW(i) == 1)
				{
					cout << setw(10) << "MOV" << "AH,DS:[" << Qin[i].second << "H]" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "BH,DS:[" << Qin[i].third << "H]" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "CMP" << "AH,BH" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "JNB" << "UNBELOW" << num1[n1] << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "AL,1" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "JMP" << "END_BELOW" << num2[n2] << endl;
					cout << std::left << setw(15) << "UNBELOW" + num1[n1] + ":";
					cout << std::left << setw(10) << "MOV" << "AL,0" << endl;
					cout << std::left << setw(15) << "END_BELOW" + num2[n2] + ":";
					cout << std::left << setw(10) << "MOV" << "DS:[" << Qin[i].fourth << "H],AL" << endl;
				}
				else
				{
					cout << setw(10) << "MOV" << "AX,DS:[" << Qin[i].second << "H]" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "BX,DS:[" << Qin[i].third << "H]" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "CMP" << "AX,BX" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "JNB" << "UNBELOW" << num1[n1] << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "AL,1" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "JMP" << "END_BELOW" << num2[n2] << endl;
					cout << std::left << setw(15) << "UNBELOW" + num1[n1] + ":";
					cout << std::left << setw(10) << "MOV" << "AL,0" << endl;
					cout << std::left << setw(15) << "END_BELOW" + num2[n2] + ":";
					cout << std::left << setw(10) << "MOV" << "DS:[" << Qin[i].fourth << "H],AL" << endl;
				}
				n1++;
				n2++;
			}
			else if (Qin[i].first == "==")
			{
				if (judge_maohao == 0)
				{
					cout << std::left << setw(15) << " ";
				}
				else
				{
					judge_maohao = 0;
				}
				if (bool_DB_or_DW(i) == 1)
				{
					cout << setw(10) << "MOV" << "AH,DS:[" << Qin[i].second << "H]" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "BH,DS:[" << Qin[i].third << "H]" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "CMP" << "AH,BH" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "JNE" << "UNEQUAL" << num1[n1] << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "AL,1" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "JMP" << "END_EQUAL" << num2[n2] << endl;
					cout << std::left << setw(15) << "UNEQUAL" + num1[n1] + ":";
					cout << std::left << setw(10) << "MOV" << "AL,0" << endl;
					cout << std::left << setw(15) << "END_EQUAL" + num2[n2] + ":";
					cout << std::left << setw(10) << "MOV" << "DS:[" << Qin[i].fourth << "H],AL" << endl;
				}
				else
				{
					cout << setw(10) << "MOV" << "AX,DS:[" << Qin[i].second << "H]" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "BX,DS:[" << Qin[i].third << "H]" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "CMP" << "AX,BX" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "JNE" << "UNEQUAL" << num1[n1] << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "AL,1" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "JMP" << "END_EQUAL" << num2[n2] << endl;
					cout << std::left << setw(15) << "UNEQUAL" + num1[n1] + ":";
					cout << std::left << setw(10) << "MOV" << "AL,0" << endl;
					cout << std::left << setw(15) << "END_EQUAL" + num2[n2] + ":";
					cout << std::left << setw(10) << "MOV" << "DS:[" << Qin[i].fourth << "H],AL" << endl;
				}
				n1++;
				n2++;
			}
			else if (Qin[i].first == "=")
			{
				if (judge_maohao == 0)
				{
					cout << std::left << setw(15) << " ";
				}
				else
				{
					judge_maohao = 0;
				}
				cout << std::left << setw(10) << "MOV" << "CX,DS:[" << Qin[i].second << "H]" << endl;
				cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "DS:[" << Qin[i].fourth << "H],CX" << endl;
			}
			else if (Qin[i].first == ">=")
			{
				if (judge_maohao == 0)
				{
					cout << std::left << setw(15) << " ";
				}
				else
				{
					judge_maohao = 0;
				}
				if (bool_DB_or_DW(i) == 1)
				{
					cout << setw(10) << "MOV" << "AH,DS:[" << Qin[i].second << "H]" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "BH,DS:[" << Qin[i].third << "H]" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "CMP" << "AH,BH" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "JB" << "BELOW" << num1[n1] << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "AL,1" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "JMP" << "END_ABOVEQUAL" << num2[n2] << endl;
					cout << std::left << setw(15) << "BELOW" + num1[n1] + ":";
					cout << std::left << setw(10) << "MOV" << "AL,0" << endl;
					cout << std::left << setw(15) << "END_ABOVEQUAL" + num2[n2] + ":";
					cout << std::left << setw(10) << "MOV" << "DS:[" << Qin[i].fourth << "H],AL" << endl;
				}
				else
				{
					cout << setw(10) << "MOV" << "AX,DS:[" << Qin[i].second << "H]" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "BX,DS:[" << Qin[i].third << "H]" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "CMP" << "AX,BX" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "JB" << "BELOW" << num1[n1] << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "AL,1" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "JMP" << "END_ABOVEQUAL" << num2[n2] << endl;
					cout << std::left << setw(15) << "BELOW" + num1[n1] + ":";
					cout << std::left << setw(10) << "MOV" << "AL,0" << endl;
					cout << std::left << setw(15) << "END_ABOVEQUAL" + num2[n2] + ":";
					cout << std::left << setw(10) << "MOV" << "DS:[" << Qin[i].fourth << "H],AL" << endl;
				}
				n1++;
				n2++;
			}
			else if (Qin[i].first == "<=")
			{
				if (judge_maohao == 0)
				{
					cout << std::left << setw(15) << " ";
				}
				else
				{
					judge_maohao = 0;
				}
				if (bool_DB_or_DW(i) == 1)
				{
					cout << setw(10) << "MOV" << "AH,DS:[" << Qin[i].second << "H]" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "BH,DS:[" << Qin[i].third << "H]" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "CMP" << "AH,BH" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "JA" << "ABOVE" << num1[n1] << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "AL,1" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "JMP" << "END_BELOQUAL" << num2[n2] << endl;
					cout << std::left << setw(15) << "ABOVE" + num1[n1] + ":";
					cout << std::left << setw(10) << "MOV" << "AL,0" << endl;
					cout << std::left << setw(15) << "END_BELOQUAL" + num2[n2] + ":";
					cout << std::left << setw(10) << "MOV" << "DS:[" << Qin[i].fourth << "H],AL" << endl;
				}
				else
				{
					cout << setw(10) << "MOV" << "AX,[" << Qin[i].second << "H]" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "BX,DS:[" << Qin[i].third << "H]" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "CMP" << "AX,BX" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "JA" << "ABOVE" << num1[n1] << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "MOV" << "AL,1" << endl;
					cout << std::left << setw(15) << " " << std::left << setw(10) << "JMP" << "END_BELOQUAL" << num2[n2] << endl;
					cout << std::left << setw(15) << "ABOVE" + num1[n1] + ":";
					cout << std::left << setw(10) << "MOV" << "AL,0" << endl;
					cout << std::left << setw(15) << "END_BELOQUAL" + num2[n2] + ":";
					cout << std::left << setw(10) << "MOV" << "DS:[" << Qin[i].fourth << "H],AL" << endl;
				}
				n1++;
				n2++;
			}
		}
		if (Qin[i].first == start_string)
		{
			if (judge_maohao == 0)
			{
				cout << std::left << setw(15) << " ";
			}
			else
			{
				judge_maohao = 0;
			}
			cout << std::left << setw(10) << "CALL" << Qin[i].first << endl;
		}
	}
}
void run::Begin()
{
	while_sum = 0;
	endwhile_sum = 0;
	while_end = 0;
	while_ssum = 0;
	if_else1 = 0;
	if_end1 = 0;
	if_end2 = 0;
	if_sum1 = 0;
	if_sum2 = 0;
	if_ssum1 = 0;
	if_ssum2 = 0;
	n1 = 0;
	n2 = 0;
	string s;
	num1[0] = "0"; num1[1] = "1"; num1[2] = "2"; num1[3] = "3"; num1[4] = "4"; num1[5] = "5"; num1[6] = "6"; num1[7] = "7"; num1[8] = "8"; num1[9] = "9"; num1[10] = "10"; num1[11] = "11";
	for (int i = 0; i < 12; i++)
	{
		num2[i] = num1[i];
		else_word[i] = "ELSE" + num1[i];
		endif_word[i] = "ENDIF_ELSE" + num1[i];
		endwhile_word[i] = "ENDWHILE" + num1[i];
		while_word[i] = "WHILE" + num1[i];
		no_else_word[i] = "END_IF" + num1[i];
	}

	for (int i = 0; i < syn.fourExp.size(); i++)
	{
		Qin.push_back(syn.fourExp[i]);
	}
	length = Qin.size();
}
void run::read()
{
	Synbl li;
	for (int i = 0; i < syn.synbl.size(); i++)
	{
		li = syn.synbl[i];
		Guo.push_back(li);
	}
	length_sybnl = Guo.size();
}
string run::ten_to_sixteen(string ten_string)
{
	string sixteen_string;
	int ten_sum = atoi(ten_string.c_str());
	int a, b, c, d;
	if (ten_sum >= 1000)
	{
		sixteen_string = ten_string;
	}
	else
	{
		a = 0;
		b = ten_sum / 256;
		c = (ten_sum - b * 256) / 16;
		d = ten_sum - b * 256 - c * 16;
		string a1 = int_to_string(a);
		string b1 = int_to_string(b);
		string c1 = int_to_string(c);
		string d1 = int_to_string(d);
		sixteen_string = a1 + b1 + c1 + d1;
	}
	return sixteen_string;
}
string run::int_to_string(int one_sum)
{
	string one_string;
	switch (one_sum)
	{
	case 0:one_string = "0"; break;
	case 1:one_string = "1"; break;
	case 2:one_string = "2"; break;
	case 3:one_string = "3"; break;
	case 4:one_string = "4"; break;
	case 5:one_string = "5"; break;
	case 6:one_string = "6"; break;
	case 7:one_string = "7"; break;
	case 8:one_string = "8"; break;
	case 9:one_string = "9"; break;
	case 10:one_string = "A"; break;
	case 11:one_string = "B"; break;
	case 12:one_string = "C"; break;
	case 13:one_string = "D"; break;
	case 14:one_string = "E"; break;
	case 15:one_string = "F"; break;
	default:break;
	}
	return one_string;
}
void run::add_bool()
{
	int i, j, k;
	for (i = 0; i < length; i++)
	{
		if (Qin[i].first == "==" || Qin[i].first == ">=" || Qin[i].first == "<=" || Qin[i].first == ">" || Qin[i].first == "<" || Qin[i].first == "!")
		{
			if (bool_DB.empty())
			{
				bool_DB.push_back(Qin[i].fourth);
			}
			else
			{
				k = 0;
				for (j = 0; j < bool_DB.size(); j++)
				{
					if (Qin[i].fourth == bool_DB[j])
					{
						k = 1;
						break;
					}
				}
				if (k == 1)
				{
					bool_DB.push_back(Qin[i].fourth);
				}
			}
		}
	}
}
int run::bool_DB_or_DW(int address)
{
	int k = 0;
	for (int i = 0; i < bool_DB.size(); i++)
	{
		if (bool_DB[i] == Qin[i].second)
		{
			k = 1;
			break;
		}
	}
	if (k == 0)
	{
		return 0;
	}
	return 1;
}
void run::all_ten_to_sixteen()
{
	for (int i = 0; i < length; i++)
	{
		if (Qin[i].first != "func"&&Qin[i].first != "end")
		{
			Qin[i].second = ten_to_sixteen(Qin[i].second);
			Qin[i].third = ten_to_sixteen(Qin[i].third);
			Qin[i].fourth = ten_to_sixteen(Qin[i].fourth);
		}
	}
}
