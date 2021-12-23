//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]

///
/// File: listdblx.cpp, listdbl.h
///       implements a doubly linked list with sentinel nodes
///       and test it interactively
///
/// 04/13/16:	Created by idebtor@gmail.com
/// 02/10/19:	C++ conversion, doubly linked list
/// 10/20/20:	randomize() - added for quicksort, swap_nodes() added
/// 
/// 1. This implements a doubly linked list with two sentinel nodes which
///     provide with benifits of coding consistency and easy maintenance.
/// 2. It does not implment C++ iterator (which is deprecated), but simulated
///    most of memeber functions defined in std::List.
///
/// The following command removes some invisible bad character in the code file.
///    iconv -f utf-8 -t utf-8 -c file.txt
///  will clean up UTF-8 file, skipping all the invalid characters in the cpp file.
///    -f is the source format
///    -t is the target format
///    -c skips any invalid sequence
///    -o sets for different output file

#include <iostream>
#include <cassert>
#include <iomanip>
#include "rand.h"
#include "listdbl.h"
using namespace std;

// returns the first node which List::head points to in the container.
pNode begin(pList p) {//완료
	return p->head->next;
}

// returns the tail node referring to the past -the last- node in the list. 
// The past -the last- node is the sentinel node which is used only as a sentinel 
// that would follow the last node. It does not point to any node next, and thus
// shall not be dereferenced. Because the way we are going use during the iteration, 
// we don't want to include the node pointed by this. this function is often used 
// in combination with List::begin to specify a range including all the nodes in 
// the list. This is a kind of simulated used in STL. If the container is empty, 
// this function returns the same as List::begin.
pNode end(pList p) {//완료
	return p->tail;          // not tail->next
}

pNode last(pList p) {//완료
	return p->tail->prev;
}

// returns the first node of the second half of the list.
// If the number of nodes are odd, it returns the one at the center.
// For even numbers, it returns the first node of the second half.
// For example, for list [0, 1, 2, 3, 4, 5, 6, 7], it returns 4.
#if 0   // method 1 - slower version
pNode half(pList p) {  //완료
    
    int N = size(p)/2;
    
    pNode curr = begin(p);
    for(int i=0; i<N; i++){
        curr = curr -> next;
    }
	return curr;
}
#else   // method 2 - rabbit and turtle
pNode half(pList p) {//완료
    
    pNode rabbit = begin(p) -> next;
    pNode turtle = begin(p);
    
    while(rabbit != turtle){
        if(rabbit == nullptr || rabbit->next == nullptr) break;
        turtle = turtle -> next;
        rabbit = rabbit -> next -> next;
    }
    /*
    while(rabbit != end(p)){
        rabbit = rabbit -> next -> next;
        turtle = turtle -> next;
    }
     */
    
    return turtle;
}
#endif




// returns the first node with val found, the tail sentinel node 
// returned by end(p) if not found. O(n)
#if 0  // for-loop version
pNode find(pList p, int val) {//완료
	DPRINT(cout << ">find val=" << val << endl;);

	cout << "replace this version: your code below\n";

	pNode curr = begin(p);//노드의 시작을 읽어오고,
	for (; curr != end(p); curr = curr->next)//curr가 끝까지 갈때까지, curr = curr -> next;
		if (curr->data == val) return curr;

	DPRINT(cout << "<find - not found\n";);
	return curr;//만약 못찾는다면 젤 끝값을 반환할듯.
}
#else  // while-loop version
pNode find(pList p, int val) {//완료
	DPRINT(cout << ">find val=" << val << endl;);
	
	pNode curr = begin(p);
    while(curr != end(p) && curr->data != val){
        curr = curr -> next;
    }
	return curr;
}
#endif




// swaps every two adjacent nodes in O(n).
// It swaps two values not the links while it goes through the list once.
void swap_pairs(pList p) {//완료
	if (size(p) < 2) return;
	pNode curr = begin(p);
	while (curr != end(p) && curr->next != end(p)) {
		swap(curr->data, curr->next->data);
		curr = curr->next->next;
	}
}

/// randomizes the list nodes in a naive method. It goes through the list twice.
/// In 1st loop, randomize the list while saving the result in another memory aux[], 
/// just like in the Fisher-Yates shuffle "inside-out" algorithm defined in nowic/src/rand.cpp.
/// In 2nd loop, overwrite each value in the list with the one in aux[] which is shuffled. 
/// In this algorithm, links in the linked-list are neither changed nor relinked.
void randomize(pList p) {//완료
	int N = size(p);
	if (N <= 1) return;

	srand((unsigned)time(nullptr));	    // initialize random seed
	int* aux = new (std::nothrow) int[N];
	assert(aux != nullptr);

	int j = 0;
	pNode curr = begin(p);     			// using the Fisher-Yates shuffle "inside-out"
	for (int i = 0; i < N; i++, curr = curr->next) {
		if (i != 0) j = rand_extended() % i;
		if (i != j) aux[i] = aux[j];
		aux[j] = curr->data;
	}

	j = 0;
	curr = begin(p);
	while (curr != end(p)) {
		curr->data = aux[j++];
		curr = curr->next;
	}
	delete[] aux;
}

// Removes all elements from the list container(which are destroyed),
// and leaving the container with a size of 0.
void clear(pList p) {//완료
	if (empty(p)) return;

	DPRINT(cout << ">clear: ";);
	pNode curr = begin(p);
	while (curr != end(p)) {
		pNode prev = curr;
		curr = curr->next;
		delete prev;
	}

	p->head->next = p->tail;			// set tail at head
	p->tail->prev = p->head;			// set head at tail
	cout << "\n\tCleared...\n";
}

// returns true if the list is empty, false otherwise. 
// To clear a list, see List::clear.
bool empty(pList p) {//완료
	return begin(p) == end(p);
}

// returns the number of nodes in the list container.
int size(pList p) {//완료
	int count = 0;
	for (pNode c = begin(p); c != end(p); c = c->next)
		count++;
	return count;
}

//////////////////////////////////////////////////////////////////////////
/////////// Make the best use of the following two fucntions  ////////////
///////////         insert() and erase()                      ////////////
//////////////////////////////////////////////////////////////////////////
// inserts a new node with val at the position of the node x.
// The new node is actually inserted in front of the node x.
// This effectively increases the list size by one. O(1)
void insert(pNode x, int val) {//완료
	DPRINT(cout << ">insert val=" << val << endl;);
	pNode node = new Node{ val, x->prev, x }; // 새로운 노드의 prev와 뒤를 설정해줘서 생성함.
	x->prev = x->prev->next = node;//2줄을 이렇게도 표현가능함.
	DPRINT(cout << "<insert\n";);
}

// removes from the list a single node x given.
// This effectively reduces the container by one which is destroyed.
// It is specifically designed to be efficient inserting and removing 
// a node regardless of its positions in the list such as front, back 
// or in the middle of the list. O(1)

//이렇게 erase함수는 overloading 되어 두개로 이루어져있음.
void erase(pNode x) {//완료
	x->prev->next = x->next;
	x->next->prev = x->prev;
	delete x;
}

void erase(pList p, pNode x) {//완료	// checks if x is either tail or head
	if (x == p->tail || x == p->head || x == nullptr) return;
	x->prev->next = x->next;
	x->next->prev = x->prev;
	delete x;
}
///////////////////////////////////////////////////////////////////////////

/////////////////////// pop ///////////////////////////////////////////////
// removes the first node in the list. O(1)
void pop_front(pList p) {//완료
	DPRINT(cout << ">pop_front\n";);
	if (!empty(p)) erase(begin(p));
	DPRINT(cout << "<pop_front\n";);
}

// removes the last node in the list. O(1)
void pop_back(pList p) {//완료
	DPRINT(cout << ">pop_back\n";);
	if (!empty(p)) erase(end(p)->prev);
	DPRINT(cout << "<pop_back\n";);
}

// removes the first node with val and does nothing if not found.
// Unlike member function List::erase which erases a node by its 
// position. Unlike pop(), pop_all() removes all the nodes with 
// the value given.
void pop(pList p, int val) {//완료
	DPRINT(cout << ">pop val=" << val << endl;);
    erase(find(p,val));
	DPRINT(cout << "<pop\n";);
}

// removes all the nodes with the same value given. O(n)
// This goes through the list once, not multiple times. Unlike 
// erase(), which erases a node by its position node, this function 
// removes nodes by its value. Unlike pop_all(), pop() removes the
// first node with the value given. 
#if 0   // step count over 2n version
void pop_all(pList p, int val) {//완료
	DPRINT(cout << ">pop_all val=" << val << endl;);

	cout << "replace this slow version: your code below\n";

	while (find(p, val) != end(p)) {
		pop(p, val);
	} // slower version
}
#else
void pop_all(pList p, int val) {//완료
	DPRINT(cout << ">pop_all val=" << val << endl;);

	for (pNode c = begin(p); c != end(p); c = c->next) {
        if( c->data == val) {
            c = c -> next;
            erase(p,c -> prev);
            c = c -> prev;
            //cout << "hi" << endl;
        }
	} 	// O(n) 
} // faster version
#endif

// deletes N number of nodes, starting from the end. 
// It deletes all the nodes if N is zero which is the default 
// or out of the range of the list.  Since it simply calls 
// pop_back() which is O(1) repeatedly, it is O(n).
void pop_backN(pList p, int N) {//완료
	DPRINT(cout << ">pop_backN N=" << N << endl;);
	int psize = size(p);
	if (N <= 0 || N > psize) N = psize;
	for (int i = 0; i < N; i++) {
		if (i % 10000 == 0)
			cout << setw(7) << "\r\tpopping [" << psize - i - 1 << "]        ";
		pop_back(p);
	}
	cout << "\n";
	DPRINT(cout << "<pop_backN\n";);
}

/////////////////////// push ///////////////////////////////////////////////
// inserts a new node with val at the beginning of the list. O(1)
void push_front(pList p, int val) {//완료	// inserts a node at front of list
	DPRINT(cout << ">push_front val=" << val << endl;);
	insert(begin(p), val);
	DPRINT(cout << "<push_front\n";);
}

// adds a new node with val at the end of the list and returns the 
// first node of the list. O(1)
void push_back(pList p, int val) {//완료
	DPRINT(cout << ">push_back val=" << val << endl;);
	insert(end(p), val);
	DPRINT(cout << "<push_back\n";);
}

// inserts a new node with val at the position of the node with x.
// The new node is actually inserted in front of the node with x. O(n)
// if x is not found, it does not push it. 
void push(pList p, int val, int x) {//value가 입력하는 새로운 노드의 값. x는 넣을 위치의 값.//완료
	DPRINT(cout << ">push val=" << val << endl;);
    pNode targetNode = find(p,x);
    insert(targetNode,val);
	DPRINT(cout << "<push\n";);
}

// adds N number of new nodes at the end of the list. O(n)
// Randomly generated numbers in the range of [0..(N + size(p))]
// are pushed to the end of the list. 
void push_backN(pList p, int N) {//완료
	DPRINT(cout << ">push_backN N=" << N << endl;);
	int psize = size(p);
	int range = N + psize;
    int a = 0;
    for(int i=0; i < N; i++){
        push_back(p ,a = rand_extended() % range);
    }

	cout << "\n";
	DPRINT(cout << "<push_backN N=" << N << endl;);
}

// adds N number of new nodes at the end of the list. O(n)
// It simply inserts the same value given for N times.
void push_backN(pList p, int N, int value) {//완료
	DPRINT(cout << ">push_backN N=" << N << "value=" << value << endl;);
	int psize = size(p);

	for (int i = 0; i < N; i++) {
		push_back(p, value);
		if (i % 10000 == 0)
			cout << setw(7) << "\r\tpushing [" << i + psize << "]=" << value << "        ";
	}
	cout << "\n";
	DPRINT(cout << "<push_backN\n";);
}

/////////////////////// unique, reverse, shuffle ///////////////
// removes extra nodes that have duplicate values from the list.
// It removes all but the first node from every consecutive group 
// of equal nodes. Notice that a node is only removed from the 
// list if it compares equal to the node immediately preceding it. 
// Thus, this function is especially useful for sorted lists. O(n)
void unique(pList p) {//완로
	DPRINT(cout << ">unique N=" << size(p) << endl;);
	if (size(p) <= 1) return;

    for(pNode x = begin(p); x != end(p); x = x->next){
        if(x->data == x->prev->data){
            x = x -> prev;
            erase(p,x->next);
            //x = x -> prev;
        }
    }
	DPRINT(cout << "<unique";);
}

// reverses the order of the nodes in the list. 
// The entire operation does not involve the construction and
// destruction of any element. Nodes are not moved, but poiters
// are moved within the list. O(n)
void reverse(pList p) {//완료
	DPRINT(cout << ">reverse\n";);
	if (size(p) <= 1) return;
	// Using a loop, swap prev and next in every node in the list
	// including two sentinel nodes.
	// Once finished, then swap two sentinel nodes.
	pNode curr = p->head;
	while (curr != nullptr) {
		swap(curr->prev, curr->next);
		curr = curr->prev;     // NOT curr->next since two nodes were swapped!
	}
	swap(p->head, p->tail);    // now just swap the head and tail
	
	DPRINT(cout << "<reverse\n";);
}

// returns so called "perfectly shuffled" list. O(n)
// For example, 1234567890 returns 6172839405.
// The first half and the second half are interleaved each other. 
// The shuffled list begins with the second half of the original p.
// The entire operation does not involve the construction, 
// destruction of any element. It does not invoke insert().
void shuffle(pList p) {
	DPRINT(cout << ">shuffle\n";);
	if (size(p) <= 1) return;    // nothing to shuffle

    pNode mid = half(p);
    pNode que = begin(p);
    //일단 떼어내기.
    mid -> prev -> next = nullptr;
    mid -> prev = p -> head;
    que -> prev = nullptr;
    p -> head -> next = mid;
    //
    pNode prev = nullptr;
    while(que != nullptr){
        prev = que;
        que = que -> next;
        mid = mid -> next;
        insert( mid, prev -> data );
    }
    
    //que앞에 있는 헤드를 mid앞에 있는 헤드로 옮겨주기.
    

	DPRINT(cout << "<shuffle\n";);
}

///////////////////////// sort /////////////////////////////////////////////

bool less(int x, int y) { return x <= y; }   // for ascending order
bool more(int x, int y) { return x >= y; }   // for descending order

// returns the node of which value is smaller than x firstly encountered
// the tail sentinel node which is returned by end(p) otherwise. 
// for example:   pList: 3 5 7 9   x: 6  returns 5
pNode less(pList p, int z) {//완료
	pNode x = begin(p);
    
    while(x != end(p) && x->data > z){
        x = x -> next;
    }
    
	return x;
}

// returns the node of which value is greater than x firstly encountered.
// the tail sentinel node which is returned by end(p) otherwise. 
// for example:   pList: 3 5 7 9   x: 6  returns 7
pNode more(pList p, int z) {//완료
	pNode x = begin(p);
    
    while(x != end(p) && x->data < z){
        x = x -> next;
    }
	
	return x;
}

// returns true if sorted either by either ascending or descending 
bool sorted(pList p) {//완료
	DPRINT(cout << ">sorted up or dn\n";);
	return sorted(p, ::less) || sorted(p, more);
}

// returns true if sorted according to the compare function provided
// for example: 
// returns true if p: 1 2 3, comp:less 
// returns false if p: 1 2 3, comp:more
// returns true if p: 1 2 2 3 7, comp: less 
// returns true if p: 7 7 2 1 1, comp: more
bool sorted(pList p, bool (*comp)(int a, int b)) {//완료
	DPRINT(cout << ">sorted? " << endl;);
	if (size(p) <= 1) return true;  // since ascending or descending
    pNode curr = begin(p);
    bool answer = 0;
    while(curr->next != end(p)){
        answer = comp(curr->data,curr->next->data);
        if(answer == false) break;
        curr = curr -> next;
    }
	DPRINT(cout << "<sorted: true\n";);
	return answer;
}

// inserts a node with val in sorted in the "sorted" list. O(n)
void push_sorted(pList p, int val) {//완료
	DPRINT(cout << "<push_sorted val=" << val << endl;);
    pNode target = nullptr;
    if(sorted(p,::more)){
        target = ::less(p,val);
    }
    else{
        target = more(p,val);
    }
    insert(target,val);

	DPRINT(cout << "<push_sorted\n";);
}

///////////////////////// show //////////////////////////////////////
// shows the values of all the nodes in the list if all is true or 
// the list size is less than show_n * 2. If there are more than 
// (show_n * 2) nodes, then it shows only show_n number of nodes from 
// the beginning and the end in the list.
void show(pList p, bool all, int show_n) {//완료
	DPRINT(cout << "show(" << size(p) << ")\n";);
	if (empty(p)) {
		cout << "\n\tThe list is empty.\n";
		return;
	}
	int i;
	pNode curr;
	const int N = size(p);

	cout << "FRONT";
	if (all || N <= show_n * 2) {//만약 전부출력해야하는거라면.
		for (i = 1, curr = begin(p); curr != end(p); curr = curr->next, i++) {
			cout << "\t" << curr->data;
			if (i % show_n == 0) cout << endl;
		}
		if (N % show_n != 0) cout << endl;
		return;
	}

	// print the first show_n data items
    //처음에 show n개 만큼 출력했다.
    else{
        for (i = 1, curr = begin(p); i <= show_n; curr = curr->next, i++)
            cout << "\t" << curr->data;

            cout << "\n\t...  " << half(p)->data << "  ...\n";

        // print the last show_n data items
        // move the pointer to the place where show_n data items are left.
        //그리고 show_n개 만큼 가야한다.
        for(int k=0; k < N-2*show_n; k++){
            curr = curr -> next;
        }
        for (i=1; curr != end(p) && i <= show_n; curr = curr->next, i++)
            cout << "\t" << curr->data;
        
    }
	
    
	cout << "\n";
}





/*
 void show(pList p, bool all, int show_n) {//완료
     DPRINT(cout << "show(" << size(p) << ")\n";);
     if (empty(p)) {
         cout << "\n\tThe list is empty.\n";
         return;
     }
     int i;
     pNode curr;
     const int N = size(p);

     cout << "FRONT";
     if (all || N <= show_n * 2) {//만약 전부출력해야하는거라면.
         for (i = 1, curr = begin(p); curr != end(p); curr = curr->next, i++) {
             cout << "\t" << curr->data;
             if (i % show_n == 0) cout << endl;
         }
         if (N % show_n != 0) cout << endl;
         return;
     }

     // print the first show_n data items
     //처음에 show n개 만큼 출력했다.
     
     for (i = 1, curr = begin(p); curr != end(p) && i <= show_n; curr = curr->next, i++)
         cout << "\t" << curr->data;

     if (N > show_n * 2)//만약 한줄에 보여주는 갯수 * 2보다 전체갯수가 많으면, 생략출력.
         cout << "\n\t...  " << half(p)->data << "  ...\n";
     else
         cout << "\n";

     // print the last show_n data items
     // move the pointer to the place where show_n data items are left.
     //그리고 show_n개 만큼 가야한다.
     for(int k=0; k < N-2*show_n; k++){
         curr = curr -> next;
     }
     for (i=1; curr != end(p) && i <= show_n; curr = curr->next, i++)
         cout << "\t" << curr->data;
     
     cout << "\n";
 }

 */
