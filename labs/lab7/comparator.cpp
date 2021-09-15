//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]

// file: comparator.cpp
// author: idebtor@gmail.com
// 2021/02/02: created and added in sort.h, libsort.a
//
// the following comparator function prototypes are included in sort.h 
// The value returned indicates whether the element passed as first argument
// is considered to go before the second in the specific ordering.
// more() and less() are equivalent to greater<int>() and less<int>() in STL. 
//
bool more(int x, int y) { return x > y; }   // for descending order
bool less(int x, int y) { return x < y; }   // for ascending order 
