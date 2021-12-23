//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]

// mergesort.cpp by idebtor@gmail.com
// A typical recursive implementation of mergesort in C++.
//
// 2020/02/02: Created by idebtor@gmail.com
// 2021/01/20: comparator default argument added 
// 
// To build and run,
// Set #if 1 to activate main() function at the bottom of the file first. 
// > g++ -std=c++11 merge.cpp -o merge
// > ./merge
//
// To use DEBUG or test it, compile with -D option and turn #if 1 on.
// Then build it with -D option run it as shown below:
// > g++ -std=c++11 -DDEBUG merge.cpp -o merge
// > ./merge
//
// To add this function to a static library libsort.a, 
// 1. set #if 0 to deactivate main() function at the bottom of the file first. 
// 2. compile first to produce ~.o file. 
// 3. add it to libsort.a as shown below.
// > g++ -std=c++11 -c merge.cpp         # produce merge.o
// > ar r libsort.a merge.o              # insert or update merge.o in libsort.a
// > ar t libsort.a                      # show objects in libsort.a 

#include <iostream>
#include <cassert>
using namespace std;

#ifdef DEBUG
#define DPRINT(func) func;
#else
#define DPRINT(func) ;
#endif

// a helper function to check two elementes sorted.
// include two elements same value as sorted.
int sorted(int *a, int i, int j, bool(*comp)(int a,int b)) {
    return comp(a[i],a[j]) || a[i]==a[j];                // two elements same value as sorted
}

void merge(int *a, int *aux, int lo, int mi, int hi, bool(*comp)(int a,int b)) {
    assert(sorted(a, lo,   mi ,comp));		// precondition: a[lo..mi]   sorted
    assert(sorted(a, mi+1, hi ,comp));		// precondition: a[mi+1..hi] sorted
    for (int k = lo; k <= hi; k++)	aux[k] = a[k];

    int i = lo;
    int j = mi + 1;
    for (int k = lo; k <= hi; k++) {
        if      (i > mi)          a[k] = aux[j++];     // A is exhausted, take B[j]
        else if (j > hi)          a[k] = aux[i++];     // B is exhausted, take A[i]
        else if (comp(aux[j],aux[i])) a[k] = aux[j++];     // B[j] <  A[i], take B[j]
        else                      a[k] = aux[i++];     // A[i] <= B[j], take A[i]
    }
    assert(sorted(a, lo, hi, comp));		// postcondition: a[lo..hi] sorted
}

void mergesort(int *a, int *aux, int lo, int hi, bool(*comp)(int a,int b)) {//시작과 끝을 lo와 hi로 받음.
    if (hi <= lo) return;//재귀종료조건임.

    int mi = lo + (hi - lo) / 2;//반으로 나눠야 하기에 mi설정.
    mergesort(a, aux, lo, mi,comp);//반으로 나눈것중 아랫것,계속 재귀
    mergesort(a, aux, mi + 1, hi,comp);//반으로 나눈것중 위에것. 계쏙 재귀
    merge(a, aux, lo, mi, hi,comp);
}

void mergesort(int *a, int N, bool(*comp)(int a,int b)) {
    int *aux = new (nothrow) int[N];
    assert(aux != nullptr);

    mergesort(a, aux, 0, N - 1,comp);//aux는 배열이다. 배열의 주소와, 배열자체를 보내는거임. 그리고 시작과, 끝값, 함수포인터 보냄.
    delete[] aux;
}

#if 0

bool more(int x, int y) { return x > y; }   // for descending order
bool less(int x, int y) { return x < y; }  
void mergesort(int *list, int n, bool (*comp)(int, int)=::less); 

int main() {
    // char a[] = {'M','E','R','G','E','S','O','R','T','E','X','A','M','P','L','E'};
    // int a[] = { 54, 26, 93, 17, 77, 31, 44, 55, 20 };
	int a[] = { 3, 4, 1, 7, 0, 9, 6, 5, 2, 8 };
    int N = sizeof(a) / sizeof(a[0]);

    cout << "UNSORTED: \n"; 
    for (auto x: a) cout << x << " "; 
    cout << endl << endl;;

    mergesort(a, N);
    cout << "MERGE SORTED: \n"; 
    for (auto x: a) cout << x << " "; 
    cout << endl << endl;;

    // Uncomment the next line and modify the code above to make it work. 
    mergesort(a, N, more); 
    cout << "MERGE SORTED using more fp: \n"; 
    for (auto x: a) cout << x << " "; 
    cout << endl << endl;
    cout << "Happy Coding~~";
    return 0;
}
#endif

