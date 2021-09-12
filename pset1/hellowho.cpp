// gets the max value in the list and returns its index
//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]

/*
* * * * * * * *
file: hellowho.cpp
It prints "Hello World!" or "Hello" with a given name.
The completed code should work as shown below. “>” is a prompt of the console.
To run the program without a command line argument: > ./hello
  > Enter a name: John Lee
  > Hello John Lee!
*   > Enter a name: Peter Kim
*   > Hello Peter Kim!
*   > Enter a name:<Enter>
*   > Hello World!
*> *
* To run the program with a command line argument:
* > ./hello John "Dr. Lee" "Handong Global University" peter
*   > Hello John!
* > Hello Dr. Lee!
*   > Hello Handong Global University!
*   > Hello peter!
* > Hello World! *>
* To run the program through a pipe
* (names.txt contains a list of names as shown below:)
* * * * * * * * * *
> cat names.txt | ./hello
> Enter a name: Hello john!
> Enter a name: Hello Dr. Lee!
> Enter a name: Hello Handong Global University! > Enter a name: Hello Peter!
> Enter a name: Hello World!
2020/02/10: Created, idebtor@gmail.com 2020/12/15: working in vs code
*/

#include <iostream>
#include <string>
using namespace std;

int main() {
    while(true){
        string name = "";
        cout << "Enter a name: ";
        getline(cin,name);
        cout << "Hello " << name << endl;
        // Use setvbuf() to prevent the output from buffered on console.
        // setvbuf(stdout, NULL, _IONBF, 0); cout << "Your code here" << endl;
        if(name == ""){
            cout << "Hello World!\n";
            break;
        }
        setvbuf(stdout, NULL, _IONBF, 0);//setvbuf 는 버퍼의 크기를 동적으로 지정할 수 있는 버퍼인데,
                                         // _IONBF를 사용할 경우 버퍼를 사용하지않고 바로 입출력한다는 것이다.
    }
    // Use system("pause") to prevent the terminal from disappearing // as soon as the program terminates as in Visual Studio sometimes. // system("pause");
    return EXIT_SUCCESS;
}