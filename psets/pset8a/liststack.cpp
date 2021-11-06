//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]

// liststack.cpp
// This program implements a stack using singly-linked list
// without a head structure and without sentinel nodes. It simply links
// node to node. The caller is responsible for maintaining the the first
// node (head) of the list. Most functions need the first node to work
// with the list and returns the first node of the list since it may be
// changed inside of the functions.
//
// 2020/10/01 Created by idebtor@gmail.com
#include "liststack.h"

// removes all the nodes from the list (which are destroyed),
// and leaving the container nullptr or its size to 0.
pNode clear(pNode p) {//노드를 다 지우는 것.
	if (empty(p)) return nullptr;
	Node* curr = p;
	while (curr != nullptr) {
        Node* zap = curr;
        curr = curr->next;
		delete zap;
	}
	cout << "\n\tCleared...\n";
	return nullptr;
}

// returns the number of nodes in the list.
int size(pNode p) {//node가 총얼마나 연결되어있는지 확인하기./
	if (empty(p)) return 0;
	int count = 0;
	while(p!=nullptr){
		p = p->next;
		count++;
	}
	return count;
}

// sets the min and max values that are passed as references in the list
void minmax(pNode p, int& min, int& max) {//리턴하는게 없기 때문에 head값이 바뀔것을 걱정할 필요없음.
	if (empty(p)) {
		min = max = 0;
		return;
	}
	min = p->data;
	max = p->data;
	while(p!=nullptr){
		if(p->data > max) max = p->data;
		if(p->data < min) min = p->data;
		p = p->next;//얘가 위로 가는 거랑 밑으로 가는거랑 무슨상관이지.....
	}
}

// returns true if the list is empty or no nodes.
// To remove all the nodes of a list, see clear().
bool empty(pNode p) {
	return p == nullptr;
}

// inserts a new node with val at the beginning of the list.
// This effectively increases the list size by N.
pNode push(pNode p, int val, int N) {
	DPRINT(cout << ">push val=" << val << " N="<< N << endl;);
    
	pNode head = p;//nullptr을 가르킴.
	pNode tempNode[N];
    
    for(int i=0; i<N; i++){
		tempNode[i] = nullptr;
        tempNode[i] = new Node {val++, head};
        head = tempNode[i];
    }
	DPRINT(cout << "<push size=" << size(p) << endl;);
    
	return head;
}

// removes N nodes in the list and returns the new first node.
// This deallocates the removed node, effectively reduces its size by N.
pNode pop(pNode p, int N) {
	DPRINT(cout << ">pop size=" << size(p) << " N="<< N << endl;);
	if (empty(p)) return nullptr;
    else if (N > size(p)){
        clear(p);
        return nullptr;
    }
	pNode head = p;
	for(int i=0; i<N; i++){
		pNode zap = head;
		head = head -> next;
		delete zap;
	}
	DPRINT(cout << "<pop size=" << size(p) << endl;);
	return head;
}

// returns the first node in the list. This does not destroy the node.
pNode top(pNode p) {
	if(empty(p)) return nullptr;
	else return p;
}

// shows all the list elements, show_n items per line  if all is true.
// shows the first and the last show_n items in the list if all is false.
void show(pNode p, bool all, int show_n) {
	DPRINT(cout << "show(" << size(p) << ")\n";);
	if (empty(p)) {
		cout << "\n\tThe list is empty.\n";
		return;
	}

	int i;
	pNode curr;
	const int N = size(p);
	cout << endl << "TOP ";//curr은 p이다. head라는 것임.
	if (all || N <= show_n * 2) {//all 이 트루이거나 리스트의 사이즈가 N, >= show_n*2
		for (i = 1, curr = p; curr != nullptr; curr = curr->next, i++) {
			cout << "\t" << curr->data;
			if (i % show_n == 0) cout << endl;
		}
		return;
	}
	
	// print the first show_n items
	if(!all || N > show_n * 2){
		int j;
		curr = p;
		for (j=0; j<show_n; j++) {
			cout << "\t" << curr->data;
			curr = curr->next;
		}
		cout << endl;
		cout << "\n...left out...\n";
		cout << endl;
		// print the last show_n items
		// Firstly, move the pointer to the place where show_n items are left.
		int k;
		for(k=j; k<N-show_n; k++){//이동한다.
			curr = curr->next;
		}
		
		for(int m=0;m<show_n;m++){
			cout << "\t" << curr->data;
			curr = curr->next;
		}
		cout << endl;
	}
}
