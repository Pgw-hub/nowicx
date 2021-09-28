#include <iostream>

using namespace std;


void greet(int times);

int main(){
    void (*fp1)(int) = &greet;
    fp1(3);
    return 0;
}

void greet(int times){
    for(int i=0;i<times;i++){
        cout << "Hello World" << endl;
    }
}