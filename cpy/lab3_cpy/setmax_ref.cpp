//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]

#include<iostream>
#include<vector>
#include<cassert>

using namespace std;
void getmax(vector<int>& s_list){
    auto max = s_list[0];
    auto max_i = 0;
    size_t idx = 0;
    for (size_t i = 0; i < s_list.size(); i++) {
        if(s_list.at(i) > max ){//맥스를 찾고나서 그 찾은 것을 99로 바꿔준다.
            max = s_list.at(i);
            max_i = i;
        }
    }
    s_list.at(max_i) = 99;
}





void setmax(vector<int>& s_list){
    getmax(s_list);

}

// With a given list, find the max value, then set it to 99.
int main(int argc, char *argv[]) {
    vector<int> list1 = {43, 10, 20, 75, 22, 33};
    vector<int> list2 = {33, 13, 45, 19, 39, 22};

    cout << ">list1: "; 
    for (auto x: list1) cout << x << " ";   
    cout << endl;
    setmax(list1);
    cout << "<list1: "; 
    for (auto x: list1) cout << x << " ";   
    cout << endl << endl;

    cout << ">list2: "; 
    for (auto x: list2) cout << x << " ";   
    cout << endl; 
    setmax(list2);
    cout << "<list2: "; 
    for (auto x: list2) cout << x << " ";   
    cout << endl; 

    return 0;
}