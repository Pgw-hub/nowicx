//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]



#include "clock.h"



int main (void) {
  pClock clk = new Clock{11, 58, 56};//메모리를 위해 new로 clk라는 이름의 구조체하나를 만듬.
  for(int i = 0; i < 6; ++i) {
      tick(clk);
      show(clk);
  }//여기에서는 6번 출력을 하고, 
  runs(clk,'\r');//그리고 그 이후에 하나씩 돌린다. 
  delete clk;
  return 0;
}

