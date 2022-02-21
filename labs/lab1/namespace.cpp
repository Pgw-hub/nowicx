#include <iostream>

using namespace std;

inline int sq(int x, int y) { return x * y ; }

namespace one { int var = 5;}
namespace two { int var = 3;}
void foo();

int main(){
    string name;
    cout << "이름을 입력하시오" << endl;
    cin >> name;
    cout << "your name is" << name << endl;
    cout << one :: var << endl;
    cout << two :: var << endl;

    foo();

    int inline_result = sq(3,5);

    cout << inline_result << endl;
}

void foo(){
    int i,j;
    cout << "Give two numbers \n";

    cin >> i >> j;
    cout << "Sum = " << i + j << endl;
}