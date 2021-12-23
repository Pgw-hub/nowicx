//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]

// bubble sort by idebtor@gmail.com
// The bubble sort makes multiple passes through a list. It compares adjacent 
// items and exchanges those that are out of order. Each pass through the list 
// places the next largest value in its proper place.  It is important to note 
// that once the largest value in the list is part of a pair, it will continually 
// be moved along until the pass is complete.In essence, each item “bubbles” up 
// to the location where it belongs. Its time complexity is O(n^2).
// 
// 2019/02/02: Created by idebtor@gmail.com
// 2021/01/20: comparator default argument added 
// 
// To build and run,
// Set #if 1 to activate main() function at the bottom of the file first. 
// > g++ -std=c++11 bubble.cpp -o bubble
// > ./bubble
//
// To use DEBUG or test it, compile with -D option and turn #if 1 on.
// Then build it with -D option run it as shown below:
// > g++ -std=c++11 -DDEBUG bubble.cpp -o bubble
// > ./bubble
//
// To add this function to a static library libsort.a, 
// 1. set #if 0 to deactivate main() function at the bottom of the file first. 
// 2. compile first to produce ~.o file. 
// 3. add it to libsort.a as shown below.
// > g++ -std=c++11 -c bubble.cpp         # produce bubble.o
// > ar r libsort.a bubble.o              # insert or update bubble.o in libsort.a
// > ar t libsort.a                       # list objects in libsort.a 

#include <iostream>
using namespace std;

#ifdef DEBUG
#define DPRINT(func) func;
#else
#define DPRINT(func) ;
#endif

#if 0
void bubblesort(int *list, int n) {
  DPRINT(cout << "BUBBLE SORTING...\n");//dprint는 디버그시에만 보이는 듯듣하다.
  for (int i = 0; i < n - 1; i++) {
    bool swapped = false; //swapped라는 변수를 하나 만든다.
    for (int j = 0; j < n - i - 1; j++) { // last i element is already in place
      if (list[j + 1] < list[j]) {        // hard-code comparison: works only for ascending
        swapped = true;
        swap(list[j + 1], list[j]);
      }
    }
    DPRINT(for(int x = 0; x < n; x++) cout << list[x] << " "; cout << endl);
    if (!swapped) break;//바꿀게 더이상 없으면 위에서 swapped변수가 1로 바뀌지 않고 0으로 유지 되기떄문에 break;
  }
}
#endif

// bubblesort using a comparator function passed as a function pointer.
void bubblesort(int *list, int n, bool (*comp)(int, int)) {//이렇게 같은 이름으로 함수가 사용한것을 overloading이라고함.
  //cout << "넘겨받고 난 후 : " << comp(2,3) <<endl;//-->1이 나와야함. 비교도 잘함.
  DPRINT(cout << "BUBBLE SORTING...fp\n");//funcpointer comp를 사용해서 받겠다는 것임. 우리*comp를사용하면됨. 
  for (int i = 0; i < n - 1; i++) {
    bool swapped = false; //swapped라는 변수를 하나 만든다.
    for (int j = 0; j < n -1 -i; j++) { // last i element is already in place
      if (comp(list[j+1],list[j])) {        // hard-code comparison: works only for ascending
        swapped = true;
        swap(list[j+1], list[j]);
      }
    }
    DPRINT(for(int x = 0; x < n; x++) cout << list[x] << " "; cout << endl); 
    if (!swapped) break;//바꿀게 더이상 없으면 위에서 swapped변수가 1로 바뀌지 않고 0으로 유지 되기떄문에 break;
  }
}

#if 1
// two comparator functions 
// The value returned indicates whether the element passed as first argument
// is considered to go before the second in the specific ordering.
// more() and less() are equivalent to greater<int> and less<int> in STL. 
bool more(int x, int y) { return x > y; }   // for descending order
bool less(int x, int y) { return x < y; }   // for ascending order 
void bubblesort(int *list, int n, bool (*comp)(int, int)=::less);

/*
bool evenfirst(int x, int y) {
  // if x(2nd element) is even and y is odd, x goes first (swap needed)
  if ((x % 2 == 0) && !(y % 2 == 0)) return true;
 
  // if x(2nd element) is odd and y is even, y goes first (no swap needed)
  if (!(x % 2 == 0) && (y % 2 == 0)) return false;
 
  // otherwise sort in ascending order (x:2nd element, y:1st element)
  return ::less(x, y);
}
*/

int main() {
  int list[] = { 3, 4, 1, 7, 0, 9, 6, 5, 2, 8 };
  int N = sizeof(list) / sizeof(list[0]);//이게 배열의 size를 magic number없이 사용하게 해주는 것임.
  //cout << sizeof(list) << endl ;
  //cout << sizeof(list[0]) << endl ;
  //보면 알수 있지만 sizeof는 메모리할당만큼의 크기를 보여준다.
  /*
  cout << " less결과: " <<::less(2,3)<<endl;//1
                            // j,j+1  -->1 -->밑에서 바꿔야함. 2와 3 ->3 2로
  cout << " less결과: " <<::less(3,2)<<endl;//0
  */                        // 
  cout << "UNSORTED: " << endl;
  for (auto x: list) cout << x << "  "; 
  cout << endl << endl;

  bubblesort(list, N);//여기에서 보낸다.//::는 std::less와 구분만 해주기 위함이다.
  cout << "[1]BUBBLE SORTED:" << endl;
  for (auto x: list) cout << x << "  "; 
  cout << endl << endl;

  bubblesort(list, N, more);
  cout << "[2]BUBBLE SORTED - descending using fp: " << endl;
  for (auto x: list) cout << x << "  "; 
  cout << endl << endl;

  bubblesort(list, N);//여기에서 보낸다.//::는 std::less와 구분만 해주기 위함이다.
  cout << "[3]BUBBLE SORTED - ascending using less() fp: " << endl;
  for (auto x: list) cout << x << "  "; 
  cout << endl << endl;

  /*
  bubblesort(list, N, evenfirst);//여기에서 보낸다.//::는 std::less와 구분만 해주기 위함이다.
  cout << "[3]BUBBLE SORTED - evenfirst: " << endl;
  for (auto x: list) cout << x << "  "; 
  cout << endl << endl;
  */
}
#endif 




#if 0
// this sort() using STL is provided for your reference. 
#include <algorithm>

int main(int argc, char *argv[]) {
  int list[] = { 3, 4, 1, 7, 0, 9, 6, 5, 2, 8 };
  int N = sizeof(list) / sizeof(list[0]);

  for (auto x: list) cout << x << " ";
  cout << endl << endl;

  sort(list, list + N);
  for (auto x: list) cout << x << " ";
  cout << endl << endl;

  sort(list, list + N, std::greater<int>();
  for (auto x: list) cout << x << " ";
  cout << endl << endl;

  sort(list, list + N, std::less<int>());
  for (auto x: list) cout << x << " ";
  cout << endl << endl;
}
#endif
