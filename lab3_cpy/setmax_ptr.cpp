// gets the max value in the list and returns its index
//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]


#include<iostream>
#include<vector>
#include<cassert>

using std::vector;
using std::cout;
using std::endl;


void getmax(vector<int>* vec) {
    assert(vec->size() > 0);
    auto max = 0;
    int max_i = 0;
    for (size_t i = 0; i < vec->size(); i++) {
        if(vec->at(i) > max){
            max = vec->at(i);
            max_i = i;
        }
    }
    vec->at(max_i) = 99;
}

// sets the max value to 99
// your code here - define setmax() here
void setmax(vector<int>* s_list){
    getmax(s_list);
}


// With a given list, find the max value, then set it to 99.
int main(int argc, char *argv[]) {
    vector<int> list1 = {43, 10, 20, 75, 22, 33};
    vector<int> list2 = {33, 13, 45, 19, 39, 22};

    cout << ">list1: "; 
    for (auto x: list1) cout << x << " "; cout << endl; 
    setmax(&list1);
    cout << "<list1: "; 
    for (auto x: list1) cout << x << " "; 
    cout << endl << endl;

    cout << ">list2: "; 
    for (auto x: list2) cout << x << " "; cout << endl; 
    setmax(&list2);
    cout << "<list2: "; 
    for (auto x: list2) cout << x << " "; 
    cout << endl; 

    return 0;
}