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
char get_op(string opstr);

int main(){
    int a { get_int()}; // getint를 통해서 얻은 값을 int a 에 저장한다는 얘기임.
    char op { get_op("+_*/")};
    int b { get_int()};

    int (*fpr)(int,int)=NULL;

    switch(op){
        case '+' :
            fpr = add;//여기를 지나가긴하는데, 
            break;
        case '*' :
            fpr = mul;
            break;
        case '-' :
            fpr = sub;
            break;
        case '/' :
            fpr = dvd;
            break;
        default: break;
    }
    cout << a << " " << op << " " << b << " = " << (*fpr)(a,b);
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
char get_op(string opstr){
    char op;
    do{
        stringstream ss;
        string str;
        cout << "Enter an operator( " << opstr << " ): ";
        getline(cin, str);
        ss << str;
        ss >> op;//
    } while(opstr.find(op) == string::npos);
    return op;
}