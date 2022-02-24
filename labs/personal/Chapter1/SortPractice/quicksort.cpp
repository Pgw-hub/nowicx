#include <iostream>

using namespace std;


int partition(int* a, int lo, int hi){
    int pivot = a[hi];
    int i = lo -1;
    for(int j = lo; j< hi; j++){
        if(a[j] < pivot){
            i++;
            swap(a[i],a[j]);
        }
    }
    swap(a[hi],a[i+1]);
    return i+1;
}


void quicksort(int* a, int lo, int hi){
    if(lo < hi){
        int pi = partition(a,lo,hi);
        quicksort(a,lo,pi-1);
        quicksort(a,pi+1,hi);    
    }
}


void quicksort(int* a, int size){
    quicksort(a,0,size-1);
}

int main() {
	int list[] = { 54, 26, 93, 17, 77, 31, 44, 55, 20 };
	int N = sizeof(list) / sizeof(list[0]);

	cout << "UNSORTED: " << endl;
	for (auto x: list) cout << x << "  "; 
	cout << endl << endl;

	quicksort(list, N);
	cout << "QUICK SORTED: " << endl;
	for (auto x: list) cout << x << "  "; 
	cout << endl << endl;

	return 0;
}