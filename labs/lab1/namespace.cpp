#include <iostream>

using namespace std;

inline int sq(int x, int y) { return x * y ; }
void foo(int& a, int& b);
void swap(int& a, int& b);

namespace one { int var = 5;}
namespace two { int var = 3;}


int main(){
    string name;

    cout << "이름을 입력하시오" << endl;
    cin >> name;
    cout << "your name is" << name << endl;
    cout << one :: var << endl;
    cout << two :: var << endl;

    foo(one :: var, two :: var); // 덧셈

    int inline_result = sq(one :: var, two :: var); // 곱셈

    cout << inline_result << endl;

    swap(one :: var, two :: var);

    cout << one :: var << " , " << two :: var << endl;

}

void foo(int& i, int& j){
    // cout << "Give two numbers \n";
    // cin >> i >> j;
    cout << "Sum = " << i + j << endl;
}

void swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}