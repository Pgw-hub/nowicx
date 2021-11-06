//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]



struct Clock{//clock이름의 구조체.
    int hr, min, sec;
};

using pClock = Clock*;

void tick(pClock clk);
void show(pClock clk);
void runs(pClock clk);
