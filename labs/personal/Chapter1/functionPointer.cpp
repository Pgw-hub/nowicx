#include <iostream>

using namespace std;

int gcd(int x, int y);
string GetName(string firstname, string lastname);
int fun(int x, int y);
int foo(int x, int y);
int add(int x, int y);



int main(const int argc, char** argv){

    int (*funtionPointer)(int, int) = gcd;
    string (*GN)(string,string) = GetName;
    int (*fpArray[])(int,int) = {fun,foo,add};
    string firstname = "Park";
    string lastname = "geonwoo";

    int size = sizeof(fpArray)/sizeof(fpArray[0]);

    cout << "gcd 계산 함수 " << gcd(255, 111) << endl;

    cout << "my name is " << GN(firstname,lastname) << endl;

    for(int i=0; i<size; i++){
        cout << "fp output = " << fpArray[i](2,3) << endl;
    }

}



//함수
int gcd(int x, int y){
    if(y == 0) return x;
    return gcd(y, x % y);
}

string GetName(string firstname, string lastname){
    
    string name = firstname + lastname;

    return name; 
}

int fun(int x, int y) {
    return x * 2 + y; 
}

int foo(int x, int y) {
    return x + y * 2; 
}

int add(int x, int y) {
    return x + y; 
}


