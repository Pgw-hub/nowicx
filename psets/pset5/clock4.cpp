//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]

#include <iostream>
#include <iomanip>
#include <unistd.h> //sleep을 위해.
#include <ostream>//flush를 위해서 사용해주어야함. flush는 버퍼의 내용을 날려주는것임.

struct Clock{
    int hr, min, sec;
};
using pClock = Clock*;
void tick(pClock ptr);
void show(pClock ptr);
void runs(pClock ptr);

//diffrent from using namespace ~~~


int main(void){//굳이 정수형을 리턴하고 void를 매개로 받는 이유..?
    pClock ptr = new Clock {14,38,56};
    //Clock clock = {14, 38, 56};//14시 38분 56초로 initiating.
    runs(ptr);
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

void show(pClock ptr, char end = '\n'){//나중에 driver에서 겹쳐서 사용해야하기때문에 이걸 사용하는듯.
    std::cout.fill('0');//2칸마련, 빈칸 0삽입.
    std::cout << std::setw(2) << ptr->hr << ":" <<std::setw(2) << ptr->min << ":" << std::setw(2) << ptr->sec << end << std::flush;//stew = setwidth;
    
}

void runs(pClock ptr){
    while(true){
       sleep(1);//1초 잠자기
       tick(ptr);
       show(ptr,'\r');//optional argument 사용.
    }
}
