#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <map>
#include<string>
#include <set>
#define offset 31//终结符数目
#define ooffset 26//非终结符数目
using namespace std;

static map<string,int> symbol;

static const int dollar = 1;
class	item_node
{
public:
	int			cfg_no;				//产生式编号
	int			dot_pos;				//加点位置
	int			possible_prefix;		//可能出现输入符号的Tag
	item_node(int a,int b,int c){
        cfg_no = a;
        dot_pos = b;
        possible_prefix = c;
	}
	item_node(){}
};


class sentence{//每一个句子
public:
    string left;
    int left_num;//左部的总序号
    vector<string> right;
    vector<int> right_num;//右部的总序号
    vector<vector<int>> right_int;//右部根据symbol表的分词序号
    divide(){
        for(int i=0;i<right.size();i++){
            int n;
            vector<int> t;
            string tem = right[i];
            while(( n = tem.find(' '))!=string::npos){
                string ttem = tem.substr(0,n);
                t.push_back(symbol[ttem]);
                tem.erase(0,n+1);
            }
            t.push_back(symbol[tem]);
            t.push_back(dollar);
            right_int.push_back(t);

        }
    }
    sentence(){
    }
};

class SyncTable{
public:
    vector<vector<int>> cfg_list;
    int action_goto[500][offset+ooffset];//LR(1)分析表，纵坐标是状态（从0开始），横坐标是字符编号，正值是跳转到的状态，负值是规约的产生式序号（非|版，从1开始）
    vector<sentence> syntax;//文法（句子集合）
    int sen_num=1;//全局句子序号
    void make_map(){//终结符、非终结符map制作
        int i=1;//终结符对应序号为doc表
        string s[]={"$","%","&&","(",")","*","+","-","/",";","<","<=","=","==",">",">=","break","continue","double","double_num","e","id","if","int","int_num","return","void","while","{","||","}"};
        for(int i=0;i<offset;i++){
            symbol.insert(pair<string ,int>(s[i],i+1));
        }
        for(i=0;i<syntax.size();i++)//非终结符对应序号为产生式序号+终结符偏移量
        {
            symbol.insert(pair<string,int>(syntax[i].left,syntax[i].left_num+offset));
        }
    }

    int is_terminal(string a){
        return (symbol[a]<=offset)&&(symbol[a]>=1);
    }

    int is_nonterminal(string a){
        return (symbol[a]>=offset+1)&&(symbol[a]<=offset+syntax.size());
    }


    void load_syntex(){//把文法从文件读入
        ifstream in("syn.txt");
        string line;
        if(in){
            while(getline(in,line)){
                string subline;
                subline = line;
                subline.erase(0,1);
                int b_num = subline.find(' ');
                sentence tem;
                tem.left_num = atoi((subline.substr(0,b_num)).c_str());
                subline.erase(0,b_num+1);
                b_num = subline.find(' ');
                tem.left = subline.substr(0,b_num);
                subline.erase(0,b_num+4);
                while((b_num = subline.find(" | "))!= string::npos){
                    tem.right.push_back(subline.substr(0,b_num));
                    subline.erase(0,b_num+3);
                    tem.right_num.push_back(sen_num++);
                    vector<int>t;
                    t.push_back(tem.left_num);
                    t.push_back(tem.right.size());
                    cfg_list.push_back(t);
                }
                tem.right.push_back(subline);
                tem.right_num.push_back(sen_num++);
                vector<int>t;
                t.push_back(tem.left_num);
                t.push_back(tem.right.size());
                cfg_list.push_back(t);
                syntax.push_back(tem);
            }
        make_map();
        for(int i=0;i<syntax.size();i++)
            syntax[i].divide();
        }
        else{
            cout<<"没有该文件!"<<endl;
        }
    }

    void show_syntex(){//打印所有文法产生式
        for(int i=0;i<syntax.size();i++){
            cout<<"xuhao:"<<syntax[i].left_num<<endl<<"zuobu:"<<endl<<syntax[i].left<<"."<<endl;
            cout<<"youbu:"<<endl;
            for(int j=0;j<syntax[i].right_num.size();j++){
                cout<<syntax[i].right_num[j]<<":"<<syntax[i].right[j]<<"."<<endl;
            }
            cout<<"youbufenchi:"<<endl;
            for(int j=0;j<syntax[i].right_int.size();j++){
                for(int k=0;k<syntax[i].right_int[j].size();k++)
                    cout<<syntax[i].right_int[j][k]<<" ";
                cout<<endl;
            }
            cout<<endl;
        }
    }

    void find_first(set<int> & first_list,int left_num,int right_num,int dot){

        if(dot<syntax[left_num-1].right_int[right_num-1].size()){
            int tem=syntax[left_num-1].right_int[right_num-1][dot];
            if(tem>=1&&tem<=offset)
                first_list.insert(tem);
            else if(tem>=offset+1&&tem<=offset+ooffset) {
                for(int i=0;i<syntax[tem-offset-1].right.size();i++){
                    if(tem!=syntax[tem-offset-1].right_int[i][0])
                        find_first(first_list,tem-offset,i+1,0);
                }
            }
            else{
            cout<<endl<<"Error"<<endl;
            }
            }
        else{
            first_list.insert(1);
        }
    }

    set<int> first(int left_num,int right_num,int dot){//第num个产生式，dot位置之后的
        set<int> first_list;
        find_first(first_list,left_num,right_num,dot);
        return first_list;
    }

    void show_symbol(){
        map<string,int>::iterator iter;
        for(iter=symbol.begin();iter!=symbol.end();iter++)
        {
            cout<<iter->first<<' '<<iter->second<<endl;
        }
    }



    vector<vector<item_node>> closure_item;//项目集簇

    vector<item_node>& get_closure(vector<item_node> &closure)
    {
        set<int> s_temp;
        for(int pos=0;pos<closure.size();pos++){
            int cfg_no = closure[pos].cfg_no;
            int left_num = cfg_list[cfg_no-1][0];
            if(closure[pos].dot_pos==0)
                s_temp.insert(left_num);
        }

        for (int pos=0; pos<closure.size();pos++)		//对于closure的每一个项目依次求
        {
            int cfg_no = closure[pos].cfg_no;		//产生式编号
            int dot_pos = closure[pos].dot_pos;		//加点
            int prefix = closure[pos].possible_prefix;	//可能出现的非终结符Tag
            int left_num = cfg_list[cfg_no-1][0];
            int right_num = cfg_list[cfg_no-1][1];
            int non_tml = syntax[left_num-1].right_int[right_num-1][dot_pos];
            int left_tml = left_num + offset;
            if (non_tml>=offset+1&&non_tml<=offset+ooffset&&!(left_tml==non_tml&&dot_pos==0)&&s_temp.find(non_tml)==s_temp.end())		//加点位置下一个字符是非终结符，继续扩展
            {
                s_temp.insert(non_tml);
                int num = non_tml - offset-1;
                for(int i=0;i<syntax[num].right.size();i++)
                    {
                        set<int>::iterator iter;
                        set<int> ttem=first(cfg_list[cfg_no-1][0],cfg_list[cfg_no-1][1],dot_pos+1);
                        int possible;
                        for(iter = ttem.begin();iter!=ttem.end();iter++)
                            possible = *iter;
                        item_node tem(syntax[num].right_num[i],0,possible);//？？？？？？
                        closure.push_back(tem);
                    }
            } //end  if
        } //end for

        return closure;
    }




    vector<item_node> get_goto(const int i, const int x)
    {
        vector<item_node> j;
        //遍历第i个项目集中的每个项目
        for (int k=0; k<closure_item[i].size(); k++)
        {
            int cfg_no = closure_item[i][k].cfg_no;
            int dot_pos = closure_item[i][k].dot_pos;
            int prefix = closure_item[i][k].possible_prefix;
            int left_num = cfg_list[cfg_no-1][0];
            int right_num = cfg_list[cfg_no-1][1];
            //对于项目集中的每个项目，只要加点位置下一个字符Tag为x，把加点后的项目加入到新项目集
            //cout<<"i "<<i<<" x "<<x<<endl;
            //cout<<syntax[left_num-1].right_int.size()<<endl<<dot_pos<<endl<<syntax[left_num-1].right_int[right_num-1][dot_pos]<<endl;
            if (syntax[left_num-1].right_int[right_num-1].size()>dot_pos && syntax[left_num-1].right_int[right_num-1][dot_pos]==x && x!=dollar)
            {
                item_node* p_item = new item_node;
                p_item->possible_prefix = prefix;
                p_item->cfg_no = cfg_no;
                p_item->dot_pos = dot_pos+1;		//加点位置后移1位
                j.push_back(*p_item);
                delete p_item;
            }
        }
        return get_closure(j);			//求得新项目集并返回
    }

    void show_item(vector<item_node> &tem){
        cout<<endl<<endl<<"项目集："<<endl;
        for(int i=0;i<tem.size();i++)
        {
            cout<<"    第 "<<i<<" 个item"<<endl;
            cout<<"        产生式序号："<<tem[i].cfg_no<<endl;
            cout<<"        打点位置："<<tem[i].dot_pos<<endl;
            cout<<"        可能的字符："<<tem[i].possible_prefix<<endl;
        }
        cout<<endl<<endl;
    }

    void show_item2(item_node &tem){
        cout<<"        产生式序号："<<tem.cfg_no<<endl;
        cout<<"        打点位置："<<tem.dot_pos<<endl;
        cout<<"        可能的字符："<<tem.possible_prefix<<endl;
    }

    int item_equal(item_node &a,item_node &b){
        if(a.cfg_no==b.cfg_no&&a.dot_pos==b.dot_pos&&a.possible_prefix==b.possible_prefix)
            return 1;
        return 0;
    }

    int items_equal(vector<item_node> &a,vector<item_node> b){
        if(a.size()!=b.size())
            return 0;
        else{
            for(int i=0;i<a.size();i++){
                int flag = 0;
                for(int j=0;j<b.size();j++)
                    if(item_equal(a[i],b[j])){
                        b.erase(b.begin()+j);
                        flag=1;
                        break;}
                if(flag==0)
                    return 0;
            }
            return 1;
        }
    }

    int is_exisit(int n,vector<item_node> tem){
        for(int i=0;i<n;i++){
            int k = items_equal(tem,closure_item[i]);
            if(k)
                return i;}
        return -1;
    }

    int make_items()
    {
        for(int i=0;i<500;i++)
            for(int j=0;j<offset+ooffset;j++)
                action_goto[i][j]=-1000;
        vector<item_node> item_tmp;
        item_node* tmp = new item_node;
        tmp->possible_prefix = dollar;//???????????????????
        tmp->cfg_no = 1;//????????????????
        tmp->dot_pos = 0;
        item_tmp.push_back(*tmp);//第一个项目集第一个项目
        closure_item.push_back(get_closure(item_tmp));		//把第一个项目集的闭包压入项目集簇中
        //show_item(item_tmp);

        static int count = 0;
        for (int i=0; i<closure_item.size(); i++)
        {
            set<int> set_temp;
            //cout<<"第 "<<i<<" 个closure"<<endl;
            for (int j=0; j<closure_item[i].size(); j++)		//由I0状态扩展，直到项目集不再增大为止
            {//对项目集的每个项目求闭包
                vector<item_node> goto_tmp;
                int prefix = closure_item[i][j].possible_prefix;
                int cfg_no = closure_item[i][j].cfg_no;
                int dot_pos = closure_item[i][j].dot_pos;
                int left_num = cfg_list[cfg_no-1][0];
                int right_num = cfg_list[cfg_no-1][1];
                int str_nxdot = syntax[left_num-1].right_int[right_num-1][dot_pos];
                //cout<<"    第 "<<j<<" 个item"<<endl;
                //show_item2(closure_item[i][j]);
                //cout<<"        点后字符："<<str_nxdot<<endl<<endl<<endl;
                if (str_nxdot!=dollar && set_temp.find(str_nxdot)==set_temp.end())
                {
                    //1.移进
                    //cout<<"    得到 " <<str_nxdot<<" 移进增加状态 ";
                    set_temp.insert(str_nxdot);
                    goto_tmp = get_goto(i, str_nxdot);
                    if(goto_tmp.size()==0)
                        return 2;
                }
                else
                {
                    //2. 规约R(j) begin-

                    if (cfg_no!=1 && str_nxdot==dollar)
                    {
                        if (action_goto[i][prefix-1]==-1000)//ERROR
                        {
                            action_goto[i][prefix-1] = -(int)cfg_no;		//填规约时分析表
                        }
                        else if(-cfg_no!=action_goto[i][prefix-1])
                        {
                            cout << "Reduction conflict state: " << i << " want to fill:" <<-cfg_no<< "  existed value:"<<action_goto[i][prefix-1]<<endl;;
                        }
                    }
                    //3. 接受Accept---
                    if (cfg_no==1 && prefix==dollar && dot_pos==syntax[left_num-1].right.size())
                    {
                        if (action_goto[i][dollar-1]==-1000)
                            action_goto[i][dollar-1] = 1000;
                        else
                        {
                            cerr << "Accept conflict\n";
                        }
                    }
                    //end---
                    continue;
                }
                if (goto_tmp.size()>0)		//移进动作，填分析表
                {
                    int n=is_exisit(closure_item.size(),goto_tmp);
                    if(n+1){
                        action_goto[i][str_nxdot-1] = n;
                        //cout<<n<<endl;
                        //cout<<"第一个："<<endl;
                        //show_item(goto_tmp);
                        //cout<<"第二个："<<endl;
                        //show_item(closure_item[n]);
                    }
                    else{
                    closure_item.push_back(goto_tmp);
                    action_goto[i][str_nxdot-1] = closure_item.size()-1;}
                    //cout<<closure_item.size()-1<<endl;
                } //end if
            } //end for
            //for(int j=0;j<closure_item[i].size();j++)
               // show_item(closure_item[j]);
            //cout<<endl<<endl;
        } //end for
        delete tmp;
        return closure_item.size();
    }

    void show_itemarray(){
        freopen("out.txt","w",stdout);
        string s[]={"   $","%","&&","(",")","*","+","-","/",";","<","<=","=","==",">",">=","break","continue","double","double_num","e","id","if","int","int_num","return","void","while","{","||","}"};
        for(int i=0;i<=30;i++)cout<<s[i]<<"     ";
        cout<<endl;
        for(int i=0;i<500;i++){
                cout<<" "<<i<<"  ";
            for(int j=0;j<offset+ooffset;j++){
                if(action_goto[i][j]==-1000)cout<<"x    ";
                else if(action_goto[i][j]==1000)cout<<"OK   ";
                else
                cout<<action_goto[i][j]<<"  ";

            }
            cout<<endl;
        }
    }


    int value_of_array(int a,string b){

    }

    void init(){
        load_syntex();
        make_items();
        show_itemarray();
    }

    SyncTable(){
        init();
    }

    int state;
    int num;
    void fresh(string a,int b){
        int c = symbol[a];
        state  = action_goto[b][c-1];
        if(state<0&&state>-1000){
            int left_num =  cfg_list[-state-1][0];
            int right_num =  cfg_list[-state-1][1];
            num = syntax[left_num-1].right_int[right_num-1].size()-1;
        }
        else
            num = 0;
    }

};



int main(){
    SyncTable a;
}
