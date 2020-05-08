#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//记录函数名和标识是否为可重入函数
typedef struct Function {
    string name;    //函数名
    int Reentrant;  //不可重入：0；可重入：1
    Function(string s, int Reentrant):name(s), Reentrant(Reentrant) {}
} Function;

vector<Function> func_lib;  //库函数记录，主要是系统调用
vector<Function> user_func; //用户函数记录

void init() {
    func_lib.push_back(Function("printf",0));
    func_lib.push_back(Function("malloc",0));
}

int main(int argc, char * argv []) {


    init();

    ifstream f;
    f.open("/Users/Ares/magic/Multi-Computing/hw3/ReentranFunc.ll",ios::in);

    string line;
    while(getline(f,line)) {
        string::iterator it, s;
        it = find(line.begin(),line.end(),'@');
        if(it == line.end()) continue;

        //寻找全局变量
        if( line.find("global")  != string::npos) {
            string name;
            it++;
            while(*it != ' ') {
                name += *it;
                it++;
            }
            func_lib.push_back(Function(name,0));
        }

        //判断是否为 Reentrant Function
        if(line.find("define") != string::npos ) {
            string func_name;
            int Reentrant = 1;
            it++;
            while(*it != '(') {
                func_name += *it;
                it++;
            }
            //函数内部
            while(true) {
                getline(f,line);
                it = find(line.begin(),line.end(),'@');
                if(it == line.end() && line.find("ret") == string::npos) continue;
                if(it == line.end() && line.find("ret") != string::npos) break;

                string name;
                it++;
                while(true) {
                    if(*it < '0' || (*it > '9'&& *it <'A') || (*it > 'Z' && *it < 'a' && *it != '_') || *it > 'z') break;
                    name += *it;
                    it++;
                }
                vector<Function>::iterator i = func_lib.begin();
                while( i != func_lib.end() ) {
                    if(i->name == name) {
                        if(i->Reentrant == 0) {
                            Reentrant = 0;
                            break;
                        }
                    }
                    i++;
                }
                if(line.find("ret") != string::npos || Reentrant == 0) break;
            }
            func_lib.push_back(Function(func_name,Reentrant));
            user_func.push_back(Function(func_name,Reentrant));
        }
    }
    vector<Function>::iterator it = user_func.begin();
    while(it != user_func.end()) {
        cout<<it->name<<":";
        if(it->Reentrant) cout<<"Reentrant\n";
        else cout<<"no\n";
        it++;
    }
    return 0;
}