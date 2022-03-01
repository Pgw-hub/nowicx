#include <iostream>

using namespace std;

void bubble(int* list_h, int N);

int main(){
    int list[] = {9,5,6,3,4,7,8,2,1};
    int size = sizeof(list)/sizeof(list[0]);
    void (*bub)(int*, int) = bubble;


    for(auto x : list){
        cout << x << "\t";
    }
        cout << endl;
    bub(list, size);
    for(auto x : list){
        cout << x << "\t";
    }
}

void bubble(int* list_h, int N){
    for(int i=0; i < N -1; i++){
        for(int j=0; j< N-i-1; j++){
            if(list_h[j] > list_h[j+1]){
                swap(list_h[j],list_h[j+1]);
            }
        }
    }
}