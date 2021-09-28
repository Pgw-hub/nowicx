//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]


#include <iostream>//cout을 쓸려면 iostream을 꼭 include해주어야한다...

using namespace std;

long long unsigned factorial(int n) {
    if(n==0 || n==1) return n;
    auto result = n * factorial(n-1);
    return result;
    }//4를 입력한다고 했을때 마지막에는 결국 4와 factorial(3)을 곱한값이 들어간다.

int main(){
    int n[] = {1,2,3,4,5,8,12,20};
    for(auto x : n )
    cout << "factorial( " << x << " ) = " << factorial(x) << endl;
    return 0;
}
