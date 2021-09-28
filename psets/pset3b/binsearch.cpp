//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]

#include <iostream>
#include <iomanip>
using namespace std;

#ifdef DEBUG
#define DPRINT(func) func;
#else
#define DPRINT(func) ;
#endif

int binarysearch(int *data, int key, int lo, int hi) {
	DPRINT(cout << "key=" << key << " lo=" << lo << " hi=" << hi << endl;);
	if ( lo > hi ) return lo;//lo 와 hi 가 같아지는 경우는 결국 못찾았을 경우밖에 없다.
	int mi = (lo + hi)/2;
	if (key == data[mi]) return mi;//결국 같을떄까지 찾을 텐데, 이렇게 리턴하는건 mi이다. 즉 data의 인덱스를 리턴하는것임.
	else if (key < data[mi]) return binarysearch( data, key, lo, mi-1);
	else return binarysearch( data, key, mi + 1, hi);
}

// randomly generate a key to search between list[0] and list[size-1].
int get_a_key(int *list, int size) {
  	int key = rand() % (list[size - 1] + 1 - list[0]) + list[0];
	return key;
}

// calls binarysearch(data, key, lo, hi) "size" number of times
// while generating a new random key at every call of the function.
// and also displays the results. If the key is found in the list,
// it displays its index in the list. If the key is not found, it
// displays where it is supposed to be appeared if there is one.
void binarysearch(int *list, int size) {
	DPRINT(cout << ">binarysearch: size=" << size << endl;)
	int key = get_a_key(list, size);
	int idx = binarysearch(list, key, 0, size);
	int index=0;
	for(int i=0;i<size;i++){
		if(key == list[i]) index =1;
	}
	cout << "     " << key <<"        is";
	if(index!=1) cout << " not ";
	else cout << "     ";
	cout << "@list[" << idx << "]" << endl;
	DPRINT(cout << "<binarysearch\n";)
}

//////// The following code is the same in binsearchDriver.cpp //////////
//////// This is given at your convenience. /////////////////////////////
#if 1
int main() {
	// char list[] = { 'a', 'c', 'e', 'g' };
	// char list[] = { 'a', 'c', 'e', 'g', 'i', 'k' };
	// int list[] = { 0, 1, 4, 6 };
	int list[] = { 3, 5, 6, 8, 9, 11 };

	int size = sizeof(list) / sizeof(list[0]);//사이즈 구하기
	srand((unsigned)time(nullptr));    // turn off this line during debugging

	cout << "  list: ";//리스트 출력
	for (auto x: list) 
		cout << x << " "; 	
	cout << endl;

	for (auto x: list) //6번 돌린다는 얘기임.
		binarysearch(list, size);
}
#endif
