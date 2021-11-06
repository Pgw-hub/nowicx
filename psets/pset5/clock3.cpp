//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]

#include <iostream>
#include <iomanip>

struct Clock{
    int hr, min, sec;
};

using pClock = Clock*;
void tick(pClock ptr);
void show(pClock ptr);

//diffrent from using namespace ~~~


int main(void){//굳이 정수형을 리턴하고 void를 매개로 받는 이유..?
    pClock ptr = new Clock {14,38,56};
    //Clock clock = {14, 38, 56};//14시 38분 56초로 initiating.
    
    for(int i=0; i < 6; ++i){
        tick(ptr);
        show(ptr);
    }
    delete ptr;
    return 0;
}


void tick(pClock ptr){
    ptr -> sec++;
    if(ptr -> sec ==60){
        ptr -> sec = 0;
        ptr -> min++;
        if(ptr -> min == 60){
        ptr -> min = 0;
        ptr -> hr++;
        }
    }
}

void show(pClock ptr){
    std::cout.fill('0');//2칸마련, 빈칸 0삽입.
    std::cout << std::setw(2) << ptr->hr << ":" <<std::setw(2) << ptr->min << ":" << std::setw(2) << ptr->sec << std::endl;//stew = setwidth;
}
