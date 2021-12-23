//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]

// C++ for C Coders & Data Structures
// Lecture note by idebtor@gmail.com
// 
// selection sort 
// The selection sort improves on the bubble sort by making only one exchange 
// for every pass through the list. In order to do this, a selection sort 
// looks for the largest value as it makes a pass and, after completing the 
// pass, places it in the proper location. As with a bubble sort, after the 
// first pass, the largest item is in the correct place. After the second pass, 
// the next largest is in place. This process continues and requires n−1 passes 
// to sort n items, since the final item must be in place after the (n−1)st pass.
// Its time complexity is O(n^2).
//
// 2019/02/02: Created by idebtor@gmail.com
// 2021/01/20: comparator default argument added 
// 
// To build and run,
// Set #if 1 to activate main() function at the bottom of the file first. 
// > g++ -std=c++11 selection.cpp -o selection
// > ./selection
//
// To use DEBUG or test it, compile with -D option and turn #if 1 on.
// Then build it with -D option run it as shown below:
// > g++ -std=c++11 -DDEBUG selection.cpp -o selection
// > ./selection
//
// To add this function to a static library libsort.a, 
// 1. set #if 0 to deactivate main() function at the bottom of the file first. 
// 2. compile first to produce ~.o file. 
// 3. add it to libsort.a as shown below.
// > g++ -std=c++11 -c selection.cpp      # produce selection.o
// > ar r libsort.a selection.o           # insert or update selection.o in libsort.a
// > ar t libsort.a                       # show objects in libsort.a 
//
/******************************************************************************
  Lab05 - Understanding a better coding in C/C++
  - NMN(No magic number)
  - DRY(Don't repeat yourself)
  - Use new and delete instead of malloc(), free()
  - Use assert() after new to check the memory allocation status
  - rand() and mod operator % 
  - Learn about a better coding after all.
*******************************************************************************/
#include <stdio.h>
#include <cstdio>
#include <iostream>

using namespace std;
void printlist(int *list, int N, int show_n=10, int per_line=20);


void selection_sort(int *list, int n, bool (*comp)(int, int)) {
  for (int i = 0; i < n; i++) {   
    int min = i;
    for (int j = i + 1; j < n; j++)
      if (comp(list[j],list[min])) min = j;
    int temp = list[i];
    list[i] = list[min];
    list[min] = temp;
  }
}

#if 1
// two comparator functions 
    // The value returned indicates whether the element passed as first argument
    // is considered to go before the second in the specific ordering.
    // more() and less() are equivalent to greater<int>() and less<int>() in STL. 
    bool more(int x, int y) { return x > y; }   // for descending order
    bool less(int x, int y) { return x < y; }   // for ascending order 

    // your code here - the function prototype with a default comparator argument
    void selection_sort(int *list, int n, bool (*comp)(int, int)=::less);
    //초기화를 시켜주면 안적어도 default값이 설정되는 것임.단 c++은 순서가 중요.

int main(int argc, char *argv[]) {
  //int list[] = { 3, 4, 1, 7, 0, 9, 6, 5, 2, 8 };
  //int n = sizeof(list)/sizeof(list[0]);
  int n =0;
  string answer ="";
  while(n <= 1){
    cout << "Enter a number of samples to sort(q to quit): ";
    getline(cin,answer);
    try {
      n = stoi(answer);
      if(answer =="q" || stoi(answer) > 1) break;
    }
    catch(...){
    }
  }

  int* list;
  list = new (nothrow)int[stoi(answer)];
  assert(list != nullptr);

  for(int i = 0; i < stoi(answer); i++){
    list[i] = rand()%stoi(answer);
  }

  // use printlist() to show the list initialized
  cout << "UNSORTED("<< n << "): " << endl;
  printlist(list,n);

  // ascending order 
  selection_sort(list, n,::less);
  cout << "SORTED("<< n << "): " << endl;
  printlist(list,n);

  // descending order using more() fp.
  selection_sort(list, n, more);
  cout << "SORTED(" << n << "): descending using fp\n";
  printlist(list, n);


  cout << "Happy Coding~~" << endl;
  delete [] list;
  return 0;
}
#endif