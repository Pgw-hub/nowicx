#include <iostream>

using namespace std;

int main(const int argc, char** argv){

    char msg[7] = "hello";
    char* ptr;

    ptr = msg;
    
    cout << "ptr's address" << ptr << endl;
    cout << "ptr[0]= "<< *ptr << endl;

    ptr++;
    
    cout << "ptr[0]= "<< *ptr << endl;
    
    

}

