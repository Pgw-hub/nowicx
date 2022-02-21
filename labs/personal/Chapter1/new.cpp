#include <iostream>

using namespace std;

int main(const int argc, char** argv){



int* pi = new int;//uninitialized
int* pi2 = new int();//initialized to 0
int* pi3 = new int[7]();// 7 ints are initialized to 0

string* pi4 = new string("hello");
string* pi5 = new string[7]();
// string* pi6 = new string[2]{"a","the"}; //brace{} need to be used for initializing the array type of string;

cout << pi[0] <<endl;
cout << pi2[0] <<endl;
cout << pi3[0] <<endl;
cout << pi4[0][1] <<endl;
// cout << pi5 <<endl; // error
cout << pi5[0] << endl;
// cout << pi6 <<endl;
// cout << pi6[1][2] << endl;

delete pi;
delete pi2;
delete[] pi3;
delete pi4;
delete[] pi5;
}
