//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]

#include<iostream>
#include<vector>
#include<cassert>

using namespace std;

// gets the max value in the list and returns its index
int getmax(vector<int> vec) {
    assert(vec.size() > 0);
    auto max = vec[0];
    auto max_i = 0;
    size_t idx = 0;
    for (size_t i = 0; i < vec.size(); i++) {
        if(vec.at(i) > max ){//맥스를 찾고나서 그 찾은 것을 99로 바꿔준다.
            max = vec.at(i);
            max_i = i;
        }
    }
    idx = vec.at(max_i);
    return idx;
}

// sets the max value in the list to 99
void setmax(vector<int> vec) {
    size_t idx = getmax(vec);//여기서는 get max로 보내고 그걸 idx에다가만 넣어준다.
    idx = 99; 
}

// With a given list, find the max value, then set it to 99 in setmax()
// In main(), we do not see the max value change that was made in setmax(), 
// since functions are using pass-by-value on purpose.
int main(int argc, char *argv[]) {
    vector<int> list1 = {43, 10, 20, 75, 22, 33};
    vector<int> list2 = {33, 13, 45, 19, 39, 22};
    //list1를 출력.
    cout << ">list1: "; 
    for (auto x: list1) cout << x << " "; 
    cout << endl;

    setmax(list1);//setmax로 백터자체를 보내고,
    //list1다시 출력
    cout << "<list1: "; 
    for (auto x: list1) cout << x << " "; 
    cout << endl << endl;

    //list2 출력
    cout << ">list2: "; 
    for (auto x: list2) cout << x << " "; 
    cout << endl; 
    setmax(list2);

    //list2 다시 출력
    cout << "<list2: "; 
    for (auto x: list2) cout << x << " "; 
    cout << endl; 

    return 0;
}