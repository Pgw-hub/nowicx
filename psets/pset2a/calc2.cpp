//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]

#include<iostream>
#include<sstream>
using namespace std;

int add(int a, int b);
int mul(int a, int b);
int sub(int a, int b);
int dvd(int a, int b);
int get_int();
pair<char,int> get_op(string opstr);

int main(){
    int (*fpr[4])(int, int) = { add , sub, mul, dvd }; 

    int a { get_int()};
    pair<char,int>op {get_op("+-*/")};//다 찾아서 왔고 op에는 Map형식으로 찾은 인덱스와, operator char이 들어있음.
    int b { get_int()};

    cout << a << " " << op.first << " " << b << " = " << fpr[op.second](a,b);
}

int add(int a, int b){ return a+b; }
int mul(int a, int b){ return a*b; }
int sub(int a, int b){ return a-b; }
int dvd(int a, int b){ if(b != 0) return a / b;
                       else return 0; 
                       }

int get_int(){
    int x;
    do{
        cout << "Enter an integer: ";
        string str;
        getline(cin, str);
        try{
            x = stoi(str);
            break;
        }
        catch(invalid_argument& e){
            cerr << e.what() << "error occurred. Retry~" <<endl;
        }
    }
    while(true);//이건뭐지..?
    return x;
}


//String 과 string의 차이, stringstrem
pair<char,int> get_op(string opstr){
    char op;
    do{
        stringstream ss;
        string str;
        cout << "Enter an operator( " << opstr << " ): ";
        getline(cin, str);
        ss << str;
        ss >> op;//str에서 ss로 공백제거?하고, 그걸 op에 담고,

    } while(opstr.find(op) == string::npos);// do-while문. 무조건 한번은 실행되는데 while문 내에 값이 만족하지 않을떄까지 돈다.
    //opstr에서 op를 찾는다. 그런데 없으면 계속 다시 돌아가고, 있으면 0을 반환하여 멈춘다.
    int index = opstr.find(op);
    pair<char, int> m;
    m = make_pair(op,index);
    return m;
}