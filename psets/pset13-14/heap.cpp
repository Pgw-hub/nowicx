//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]

/*
* Files: heap.cpp, heap.h, driver.cpp - min/maxheap 
*        heapv.cpp, heapv.h, heapvDriver.cpp - using std::vector
*  implements a max/min heap that is used to represent a priority queue.
*
*  It implements both max-heap and min-heap while swapping
*  the compare functions. The compare function for max-heap to use
*  is less() while more() is used for min-heap.
*  The heap structure carries this compare function as a function
*  pointer. It can be changed anytime, it can be re-evalaute the
*  heap and convert any binary tree or CBT into min-heap or max-heap.
*
*  It supports the usual insert and delete - the - maximum operations,
*  along with methods for peeking at the maximum key, testing if the
*  heap is empty, and iterating through the keys. It uses an array
*  structure to store in a complete binary tree structure.
*  The insert and delete - the - maximum operations take logarithmic
*  amortized time.The max, size, and empty operations take
*  constant time.
*
*  Heap construction takes time proportional to the specified capacity
*  or the number of items used to initialize the data structure.
*  It uses successive doulbing to increase the memory as the number
*  of nodes increases. Similarly, it deallocates its memory dynamically
*  as the nodes get removed. A one - based and one dimensional array
*  is used to simplify parent and child calculations.
*
*  @author Youngsup Kim, idebtor@gmail.com
*  2014/04/01	Creation
*  2020/05/05	Added heapprint() using treeprint functions
*/

#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>
#include "heap.h"
using namespace std;

// sets the compare function less() for maxheap, more() for minheap.
void setType(heap p, bool maxType) {//완료
	p->comp = maxType ? ::less : more;
}

// deallocates a heap.
void clear(heap p) {//완료
	if (empty(p)) return;
	// delete[] p->nodes;
	free(p->nodes);
	return;
}

// returns the number of items in heap
int size(heap p) {//완료
	return empty(p) ? 0 : p->N;
}

int capacity(heap p) {//완료
	return p->capacity;
}
int height(int n) {//사이즈를 받으면,
	return log2(n);
}
int height(heap p) {//완료
	return height(size(p));
}

int minimum(heap p) {//완료
	int key = p->nodes[1];
	for (int i = 2; i <= p->N; i++) {
		if (key > p->nodes[i]) key = p->nodes[i];
	}
	return key;
}

int maximum(heap p) {//완료
	int key = p->nodes[1];

	for (int i = 2; i <= p->N; i++) {
		if (key < p->nodes[i]) key = p->nodes[i];
	}
	return key;
}

// resizes the node array in heap
void reserve(heap p, int capa) {//완료
	DPRINT(cout << ">reserve old=" << p->capacity << "  new=" << capa << endl;);
	// realloc() : The contents of the block are unchanged up to the shorter
	// of the new and old sizes, although the new block can be in a different location.
	int *nodes = (int *)realloc(p->nodes, capa * sizeof(int));
	assert(nodes != nullptr);
	p->nodes = nodes;//늘린것으로 다시 재지정해주고
	p->capacity = capa;//캐파 바꾼것도 다시 원래 캐파로 재지정.
	DPRINT(cout << "<reserve capacity=" << capa << endl;);
}

// inserts a new key to the max-heap or min-heap.
void grow(heap p, int key) {//완료
	DPRINT(cout << ">grow key=" << key << endl;);
	
    if(full(p))//새로 만들어주기 전에 꽉찼는지 확인해주고 늘려주는거임.
        reserve(p,p->capacity * 2);
    
    p->nodes[++p->N] = key;
    swim(p,p->N);

	DPRINT(cout << "<grow N=" << p->N << endl;);
	return;
}

// removes the root key in maxheap or minheap.
void trim(heap p) {//완료
	if (empty(p)) return;
	DPRINT(cout << ">trim\n";);

    swap(p,1,p->N--);
    sink(p,1);
    
    if((p->N)*4 == p->capacity)
        reserve(p, p->capacity/2);

	DPRINT(cout << "<trim N=" << p->N << endl;);
}


// returns true(or index of the heap) if the key exists, false otherwise.
// In C/C++, 0 is treated as false, all other numbers treated as true.
int contains(heap p, int key) {//완료
	if (empty(p)) return 0;
    for(int i=1; i<=p->N; i++){
        if(key == p->nodes[i]){
            return p->nodes[i];
        }
    }
	return 0;
}

// replaces a key with a new key and keeps heap-ordered if it is a heap.
// if it is not a heap, simply replace a key with a new value.(CBT)
void replace(heap p, int oldKey, int newKey) {//완료
	if (empty(p)) return;
	DPRINT(cout << ">replace " << oldKey << " --> " << newKey << endl;);

	bool heap_ordered = heapOrdered(p);
	for (int i = 1; i <= p->N; i++) {
		if (oldKey == p->nodes[i]) {
			p->nodes[i] = newKey;
			if (heap_ordered) {
				swim(p, i);
				sink(p, i);
			}
			break;
		}
	}
	DPRINT(cout << "<replace";);
}

// Is this heap empty?
bool empty(heap p) {//완료
	return p == NULL || p->N == 0 ? true : false;
}

// is this heap full?
bool full(heap p) {//완료
	return p && (p->N == p->capacity - 1) ? true : false;
}

/////// helper functions to restore the heap invariant ///////
bool more(heap p, int i, int j) {//완료
	return p->nodes[i] > p->nodes[j];
}

bool less(heap p, int i, int j) {//완료
	return p->nodes[i] < p->nodes[j];
}

void swap(heap p, int i, int j) {//완료
	swap(p->nodes[i], p->nodes[j]);  // using std::swap()
}

void swim(heap p, int k) {//완료
	DPRINT(cout << " swim key=" << p->nodes[k] << " k=" << k << " N=" << p->N << endl;);
    while(k>1 && p->comp(p,k/2,k)){
        swap(p,k/2,k);
        k = k/2;
    }
}

void sink(heap p, int k) {//완료
	DPRINT(cout << " sink key=" << p->nodes[k] << " k=" << k << " N=" << p->N << endl;);

    while( 2*k <= p->N){
        int j = 2*k;
        if(j < p->N && p->comp(p,j,j+1)) j++;
        if(!p->comp(p,k,j)) break;
        swap(p,k,j);
        k = j;
    }

#ifdef DEBUG
	cout << "\tafter sink N=" << p->N << " k=" << endl;
	for (k = 1; k <= p->N; k++)
		cout << p->nodes[k] << " ";
	cout << endl;
#endif
}

/*************************************************************************
*  Check integrity of heap data structure
*************************************************************************/

// is it heap-ordered at a node k? 
bool heapOrderedAt(heap p, int k) {//완료
	if (k > p->N) return true; // check it upto the last internal node.

	if ((2 * k  <= p->N) && p->comp(p, k, 2 * k))  return false;
	if ((2 * k + 1 <= p->N) && p->comp(p, k, 2 * k + 1)) return false;

	return heapOrderedAt(p, 2 * k) && heapOrderedAt(p, 2 * k + 1);
}

// is it heap-ordered? 
bool heapOrdered(heap p) {//완료
	if (empty(p)) return false;
	return heapOrderedAt(p, 1);
}

// sorts using min/maxheap
// if maxheap, it sorts them in ascending order
// if minheap, it sorts them in descending order
void heapsort(heap p) {//완료
	DPRINT(cout << ">heapsort N=" << p->N << endl;);
    int NOrigin = p -> N;
    int CapaOrigin = p -> capacity;
    heapify(p);
    while(p->N >= 1){
        trim(p);
    }
    
    p-> N = NOrigin;
    reserve(p,CapaOrigin);
    //솔트를 하고 나서 바capa가 안바뀜
    
	std::cout << "\n\tSorted: ";
	for (int i = 1; i <= p->N; i++)
		std::cout << p->nodes[i] << " ";
	std::cout << std::endl;
	DPRINT(cout << "<heapsort N=" << p->N << endl;);
}

/////////////////// Complete Binary Tree //////////////////////////
// instantiates a complete binary tree with given data and its size.
heap newCBT(int *a, int n) {//완료
	DPRINT(cout << ">newCBT n=" << n << endl;);
	int capacity = (int) exp2((double)height(n));//일단 방을 그마늠 만들어두고,
	heap p = new Heap{ capacity };
	p->N = n;
	for (int i = 0; i < n; i++)
		p->nodes[i + 1] = a[i];

	DPRINT(cout << "<newCBT " << endl;);
	return p;
}

// inserts a new key to the tree.
// if the size reaches the capacity, double the array size.
void growCBT(heap p, int key) {//완료
	DPRINT(cout << ">growCBT key=" << key << endl;);
    
    if(full(p))
        reserve(p, p->capacity * 2);
    
    p->N++;
    p->nodes[p->N] = key;

	DPRINT(cout << "<growCBT N=" << p->N << endl;);
}

// removes the last node on the heap
// if the size becomes 1/4 of the capacity, reserve it in half.
void trimCBT(heap p) {//완료
	DPRINT(cout << ">trimCBT " << endl;);
	
    
    if((p->N)*4 == p->capacity)
        reserve(p,p->capacity/2);
    
    p->nodes[p->N] = NULL;
    p->N--;

	DPRINT(cout << "<trimCBT N=" << p->N << endl;);
}

// restores the max/min heap property -
// parent is larger/smaller than its children)
void heapify(heap p) {//완료
	DPRINT(cout << ">heapify" << endl;);
	// start at the last internal node(or parent of the last node)
	// since leaf nodes already satisfy the max/min priority property
	// This is O(n) algorithm
    int last_inode = p->N/2;
    while(last_inode >= 1){
        sink(p,last_inode--);
    }
	DPRINT(cout << "<heapify" << endl;);
}

// returns an extended random number of which the range is from 0
// to (RAND_MAX + 1)^2 - 1. // We do this since rand() returns too 
// small range [0..RAND_MAX) where RAND_MAX is usually defined as 
// 32767 in cstdlib. Refer to the following link for details
// https://stackoverflow.com/questions/9775313/extend-rand-max-range
unsigned long rand_extended(int range) {//완료
	if (range < RAND_MAX) return rand();
	return rand() * RAND_MAX + rand();
}

// returns an int array that has randomly mixed numbers
// between start to start + N
void randomN(int start, int N, int* arr) {//완료
	if (N <= 1) return;
	for (int i = 0; i < N; i++) arr[i] = start + i;
	// shuffle the array contents
	for (int i = 0; i < N; i++) {
		int x = rand_extended(N) % (N - 1);
		int t = arr[i];
		arr[i] = arr[x];
		arr[x] = t;
	}
#ifdef DEBUG
	cout << "randomN: ";
	for (int i = 0; i < N; i++) cout << arr[i] << " ";
	cout << endl;
#endif
}








void growN(heap p, int count, bool heapOrdered) {//완료
    // int max = empty(p) ? 1 : maximum(p) + 1;
    // void(*insertFunc)(heap h, int key) = heapOrdered ? grow : growCBT;
    DPRINT(cout << ">growN" << endl;);
    // 1. Find the max key(max) in heap or CBT.
    int max = empty(p) ? 1 : maximum(p) + 1; // 맥스르 찾는다.
    // 2. Set a function pointer to the function to insert a node
    void(*insertFunc)(heap h, int key) = heapOrdered ? grow : growCBT; //그로우 함수를 어떻게 사용할건지 함수펑션에 넣어줌.
    // 3. Allocate a Key type array such as keys to store random keys.
    int* key = new int[count];
    // 4. Invoke randomN() function to generate keys in the range
    //    [(max + 1)..(max + count)]
    randomN(max,count,key);
    // 5. Invoke the function to insert keys in keys[], but one key at a time.
    for(int i=0; i<count; i++){
        insertFunc(p,key[i]);
    }
    // 6. Print the heap if DEBUG is defined whenever a node is inserted.
    
    // 7. Don't forget freeing the array of keys you allocated in Step 3.
    delete[] key;
	
	
	DPRINT(cout << "<growN" << endl;);
}





void trimN(heap p, int count, bool heapOrdered) {//완료
	DPRINT(cout << ">trimN" << endl;);
    // 1. If the node count to delete is larger than the heap size,
    //    set the node count to the heap size.
    if(count >= p->N) count = p->N;
    // 2. Set a function pointer to the function to delete a node
    void(*deleteFunc)(heap h) = heapOrdered ? trim : trimCBT; //그로우 함수를 어떻게
    // 3. Invoke the function to delete the node one by one.
    for(int i=0; i<count; i++){
        deleteFunc(p);
    }
    // (4. Print the heap if DEBUG is defined whenever a node is deleted.)

	

	DPRINT(cout << "<trimN" << endl;);
}

///////////////////// helper functions /////////////////////////////////
// prints elements present in a vector in a line, show_n items per line 
void show_vector(vector<int> vec, int show_n) {//완료
	int size = (int) vec.size();
	if (size < show_n)
		for (auto i : vec) cout << i << " ";
	else {
		for (int i = 0; i < show_n / 2; ++i)
			cout << vec[i] << " ";
		cout << "... ";
		for (int i = size - show_n / 2; i < size; ++i)
			cout << vec[i] << " ";
	}
}
