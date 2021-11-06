//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]



#include <iostream>
#include <iomanip>
#include <unistd.h> //sleep을 위해.
#include <ostream>//flush를 위해서 사용해주어야함. flush는 버퍼의 내용을 날려주는것임.
#include "clock.h"

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

void show(pClock ptr,char end = '\n'){//나중에 driver에서 겹쳐서 사용해야하기때문에 이걸 사용하는듯.
    std::cout.fill('0');//2칸마련, 빈칸 0삽입.
    std::cout << std::setw(2) << ptr->hr << ":" <<std::setw(2) << ptr->min << ":" << std::setw(2) << ptr->sec << end << std::flush;//stew = setwidth;
}


void runs(pClock ptr, char end = '\n'){
    while(true){
       sleep(1);//1초 잠자기
       tick(ptr);
       show(ptr,end);//optional argument 사용.
    }
}
