#include <iostream>
#include <iomanip>

struct Clock{
    int hr, min, sec;
};

void tick(Clock* ptr);
void show(Clock* ptr);

int main(void){//굳이 정수형을 리턴하고 void를 매개로 받는 이유..?
    Clock clock = {14, 38, 56};//14시 38분 56초로 initiating.
    
    for(int i=0; i < 6; ++i){
        tick(&clock);
        show(&clock);
    }
    return 0;
}

void tick(Clock* ptr){
    ptr -> sec++;
    if(ptr -> sec ==60){
        ptr -> sec = 0;
        ptr -> min++;
    }
    if(ptr -> min == 60 && ptr ->sec == 60){
        ptr -> sec = 0;
        ptr -> min = 0;
        ptr -> hr++;
    }
}

void show(Clock* ptr){
    std::cout.fill('0');//2칸마련, 빈칸 0삽입.
    std::cout << std::setw(2) << ptr->hr << ":" <<std::setw(2) << ptr->min << ":" << std::setw(2) << ptr->sec << std::endl;//stew = setwidth;
}
