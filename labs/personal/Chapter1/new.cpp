#include <iostream>

using namespace std;

int main(const int argc, char** argv){



int* pi = new int;//uninitialized
int* pi2 = new int();//initialized to 0
int* pi3 = new int[7];// 7 ints are initialized to 0

//문자열
string* pi4 = new string("hello");
string* pi5 = new string[7]();
char* pi6 = new char[7]();//brace{} need to be used for initializing the array type of string;depending on version
string pi7[2];


pi6 = "ThankYou";
// strcpy(pi6,"hello");
pi7[0] = "안녕하세요";

cout << pi[0] <<endl;
cout << pi2[0] <<endl;
cout << pi3[0] <<endl;
cout << "pi4 :스트링 동적 할당입니다 > " <<pi4 <<endl;
cout << "pi5 : string 동적 배열입니다 >" <<pi5[0] << endl;
// cout << pi5 <<endl; // error
cout <<" pi6 : char* 문자열입니다 >"<< pi6 <<endl;
cout <<" pi6 : char* 문자열입니다 + 1 >"<< pi6+1 <<endl;
cout <<" pi6 : char* 문자열입니다 + 2 >"<< pi6+2 <<endl;
// *pi6 = 'O';수정불가.
// cout <<" pi6 : char* 문자열 변경 후>"<< pi6 <<endl;
cout << "pi7 :스트링 정적배열입니다. >" << pi7 <<endl;

// cout << pi6[1][2] << endl;

delete pi;
delete pi2;
delete[] pi3;
delete pi4;
delete[] pi5;
}
