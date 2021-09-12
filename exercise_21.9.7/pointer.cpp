//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]

#include <iostream>
using namespace std;

int main(){
    int* pi;
    pi = new int;
    *pi = 24;//we have yet to allocate the memory at pi. memory allocation first with new.
    cout << "i = " << *pi << endl;
    delete pi;
    return 0;
}

//quiz 
//1 : run-time error
//2 : 위 코드입니다.


