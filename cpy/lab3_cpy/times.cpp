//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]
   
    #include <iostream>
    #include <vector>

    using namespace std;

    #if 1
    // mulitply even number elements in the list by 10
    // without using reference variable.
    int main(int argc, char *argv[]) {
        vector<int> list = { 0, 1, 2, 2, 4, 5, 6, 7, 8, 8, 10 };
        vector<int>& s_list = list;
        for (size_t i = 0; i < list.size(); i++) {//여기서 짝수 구분하고 곱하기 10해서 다시 값을 넣기
            if(s_list.at(i)%2==0){
                s_list.at(i) = s_list.at(i)*10;
            }
            //cout << x << " "; 이건 왜 또 한번 출력하는 건지?
        }
        for (auto x: list) cout << x << " ";
        return 0;
    }
    #else 
    // mulitply even number elements in the list by 10
    // using reference variable.
    int main(int argc, char *argv[]) {
        vector<int> list = { 0, 1, 2, 2, 4, 5, 6, 7, 8, 8, 10 };

        cout << "your code here\n"; 

        for (auto x: list) cout << x << " ";
        return 0;
    }
    #endif


    //if가 2개 있는 건 어떻게 설정하는걱ㄴ지.