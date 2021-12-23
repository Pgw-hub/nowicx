// file: printfunc.cpp // C++ for C Coders & Data Structures // Lecture note by idebtor@gmail.com 
#include <iostream>

void printfunc(int n, char *names[]) {

    for (int i = 0; i < n; i++)
       std::cout << "Hello " << names[i] << "!" << std::endl;

}
