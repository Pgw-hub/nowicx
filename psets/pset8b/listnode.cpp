//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]

// listnode.cpp
//
// Description:	This program implements a simple linked list of nodes
// without a head structure and without sentinel nodes. It simply links
// node to node. The caller is responsible for maintaining the the first
// node (head) of the list. Most functions need the first node to work
// with the list and returns the first node of the list since it may be
// changed inside of the functions.
//
// 03/13/19:	Created by idebtor@gmail.com
// 10/01/20:	show_timeit, inserrion sort, keep second half, zap duplicate
//
#include <iomanip>
#include <cstdlib>
#include <stack>
#include "listnode.h"
#include "rand.h"

#if 0
// a basic stack functinality only provided for pedagogical purpose
// To use STL stack, just comment out this section and inclucde <stack> above.
#include <vector>
template <typename T>
struct stack {
	vector<T> data;

	bool empty() const {
		return data.empty();
	}
	auto size() const {
		return data.size();
	}
	void push(T const& item) {
		data.push_back(item);
	}
	void pop() {
		if (data.empty())
			throw out_of_range("stack<>::pop(): pop stack");
		data.pop_back();
	}
	T top() const {
		if (data.empty())
			throw out_of_range("stack<>::top(): top stack");
		return data.back();
	}
};
#endif

// removes all the nodes from the list (which are destroyed),
// and leaving the container nullptr or its size to 0.
pNode clear(pNode p) {
	if (empty(p)) return nullptr;
	DPRINT(cout << "clear: ";);

	pNode curr = p;
	while (curr != nullptr) {
		pNode prev = curr;
		curr = curr->next;
		DPRINT(cout << prev->data << " ";);
		delete prev;
	}
	cout << "\n\tCleared...Happy Coding!\n";
	return nullptr;
}

// returns the number of nodes in the list.
int size(pNode p) {
	if (empty(p)) return 0;
	int count = 0;
	for (pNode c = p; c != nullptr; c = c->next, count++);
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
// returns the last node of in the list.
pNode last(pNode p) {
	if (empty(p)) return nullptr;
	while (p->next != nullptr) p = p->next;
	return p;
}

// returns true if the list is empty or no nodes.
// To remove all the nodes of a list, see clear().
bool empty(pNode p) {
	return p == nullptr;
}

// inserts a new node with val at the beginning of the list.
// This effectively increases the list size by one.
Node* push_front(Node* p, int val) {
	DPRINT(cout << "><push_front val=" << val << endl;);
	if (empty(p)) return new Node{ val };
	return new Node{ val, p };//여기가 새로운 노드를 생성하고, 새로운 노드의 next를 P 로 붙이는 과정.
}

// adds a new node with val at the end of the list and returns the
// first node of the list. This effectively increases the list size by one.
pNode push_back(pNode p, int val) {
	DPRINT(cout << "><push_back val=" << val << endl;);
    pNode head = p;//항상 헤드를 보관하고 있어야함으로 보관.
    while(p->next != nullptr){
        //끝까지 가서 데이터를 추가한다.
        p = p->next;
    }
    //현재 p의 next값이 새로운 노드의 값이 되어야한다.
    pNode backNode = new Node{val};//젤마지막은 nullptr을 가리켜도 됨.
    p->next = backNode;
	return head;
}

// inserts a new node with val at the position of the node with x.
// The new node is actually inserted in front of the node with x.
// It returns the first node of the list.
// If the position x is not found, it inserts it at the end of the list.
pNode push(pNode p, int val, int x) {
	if (empty(p)) return push_front(p, val);
	if (p->data == x) return push_front(p, val);//처음 시작하자마자 찾았다면 바로.
    
    //x를 가진 노드가 없으면 새노드를 리스트의 끝에 삽입합니다.
    //리스트에 존재하는 노드가 하나라면..
    //if( size(p) == 1 ){
    //    pNode curr
    //}
    //x값을 찾지 못했따면 pushback.
    
    pNode curr = p;
    pNode prev = nullptr;
    while(curr-> data != x){ //여기서 temp->data가 x가 아니면 계속 가는데,
        prev = curr;
        curr = curr -> next;

    }
    pNode insertNode = new Node{val,prev->next};
    prev -> next = insertNode;
    //head에서 접근할 수 밖에 없음. 넣고자 하는 val을 입력한뒤, x가 있는 곳으로 가서. 새로 입력한노드->x노드 이렇게 되야함. if문사용금지.
	return p;
}


// adds N number of new nodes at the front or back of the list.
// Values of new nodes are randomly generated in the range of
// [0..(N + size(p))]. 
// push_fp should be either a function pointer to push_front() 
// or push_back(). Use rand_extended() defined in nowic/include/rand.h.
Node* push_N(Node* p, int N, Node* (*push_fp)(Node*, int)) {
	DPRINT(cout << ">push_N = " << N << endl;);
    pNode curr = p;

	int range = N + size(p);//생성할 랜덤수의 범위 = 기존 리스트의 크기 + 생성할 변수들의 크기.
	srand((unsigned)time(nullptr));
    int num[N];
    for(int i=0; i<N; i++){
        num[i] = rand()%range;
        //지금 만든 벨류값을 넣어주면된다.
        curr = push_fp(curr,num[i]);
        
        //붙이 노드를 헤드로 만드는 과정을 해야함.
    }
    //unsigned long num = rand_extended();
    //cout << "rand num = " << num << endl;
    //}
    
    //반복문내에서 head도 같이 연결해주고 재 지정해주면서 보내야한다.
    
    //그전에 랜덤수를 생성해서 , n개만큼의 배열에 담아두고, 그 배열에서 하나씩 꺼내면서 값을 넣어주기.
	//여기에서 n번호출하는데, push_fp를 호출해서 사용하면됨,
    //즉 for(int i =0; i < n; i++){1.호출,){}

	DPRINT(cout << "<push_N = " << N << endl;);
	return curr;
}

// inserts a new node in sorted ascending order in the list. 
// The basic strategy is to iterate down the list looking for the place to insert 
// the new node. That could be the end of the list, or a point just before a node 
// which is larger than the new node.
Node* push_sorted(Node* p, int val) {
	if (empty(p) || val <= p->data) return push_front(p, val);
    

     pNode curr = p;
     pNode prev = nullptr;
	 //locate the node before the point of insertion
     //currdata가 nullptr이 아니면 계속 반복해서 비교하는데,
        //그 안에서 중간중간 멈춰서 해야함.
    while( curr != nullptr && curr -> data < val){//여기서 마지막에 추가하려고 할때마다 val가 없어서 오류가뜸.
        //지금 1 3 4 5 이렇게 저장되어있음.
        //여기서 5가 들어옴.
        //1과 5를 비교 1<=5 라서 계속 실행.
        //3과 5를 비교 계속 실행
        //4와 5를 비교
        //5와 5를 비교 같으면 멈춰야하는데,같아서 한번 더간다.
        prev = curr;
        curr = curr -> next;
    }
    pNode pushNode = new Node{val,prev->next};
    prev -> next = pushNode;

	return p;
}

// sorts the singly linked list using insertion sortand returns a new list sorted.
// Repeatedly, invoke push_sorted() with a value in the list such that push_sorted() 
// returns a newly formed list head.
Node* insertion_sort(Node* p) {
	if (empty(p)) return nullptr;
	if (size(p) < 2) return p;

	Node* sorted = nullptr;
    //여기 sorted에다가 계속 curr의 데이터를 넣는것임.
    pNode curr = p;
    while(curr != nullptr){
        sorted = push_sorted(sorted, curr->data);
        curr = curr -> next;
    }
    //clear(p);
	return sorted;
}

// removes the first node in the list and returns the new first node.
// This destroys the removed node, effectively reduces its size by one.
pNode pop_front(pNode p) {
	DPRINT(cout << ">pop_front size=" << size(p) << endl;);
    pNode zap = p;
    p = p -> next;
    delete zap;

	return p;
}

// removes the last node in the list, effectively reducing the
// container size by one. This destroys the removed node.
pNode pop_back(pNode p) {
	//DPRINT(cout << ">pop_back size=" << size(p) << endl;);
	if (empty(p)) return nullptr;

    pNode curr = p;
    pNode prev = nullptr;
    while(curr-> next != nullptr){
        prev = curr;
        curr = curr -> next;
    }
    prev -> next = nullptr;
    delete curr;
	DPRINT(cout << "<pop_back size=" << size(p) << endl;);
	return p;
}


// deletes N number of nodes, starting from the beginning or back of the list. 
// It deletes all the nodes if N is zero which is the default or out of 
// the range of the list. 
Node* pop_N(Node* p, int N, Node* (*pop_fp)(Node*)) {
	DPRINT(cout << ">pop_N N=" << N << endl;);
    
    if( N > size(p)){
        clear(p);
        return nullptr;
    }
    else{
        for(int i=0;i<N;i++){
            p = pop_fp(p);
        }
        DPRINT(cout << "<pop_N size=" << size(p) << endl);
        return p;
    }
}

// removes the first occurrence of the node with val from the list
pNode pop(pNode p, int val) {
	DPRINT(cout << ">pop val=" << val << endl;);
	if (empty(p)) return nullptr;    // nothing to delete

	if (p->data == val) return pop_front(p);

    //일단은 삭제하고 싶은 데이터를 찾고, 그 데이터의 전 데이터의 next가 삭제하고자하는 data의 next가 되어야함.
    pNode curr = p;
    pNode prev = nullptr;
    while(curr -> data != val){
        prev = curr;
        curr = curr -> next;
    }
    prev -> next = curr -> next;
    delete curr;

	DPRINT(cout << "<pop size=" << size(p) << endl;);
	return p;
}

// reverses a singly linked list using stack and returns the new head. 
// The last node becomes the head node. This function pushes all of its 
// nodes onto a stack. Then top/pop stack and relink the nodes again. 
// It does not create any new node, but recycles and relink them.
// Even though it goes through the list twice, its time complexity is 
// still O(n).This algorithm, however, takes much longer time than 
// in-place reverse algorithm of which the time complexity is also O(n).
Node* reverse_using_stack(Node* head) {
	if (empty(head)) return nullptr;    // nothing to reverse
	stack<Node*> s;
	pNode curr = head;
    while(curr -> next != nullptr){
        //리스트 안에 헤드를 스택에 넣어준다.
        s.push(curr);
        curr = curr->next;//굳이 연결을 끊어줄 필요는 없어보인다.
    }
    s.push(curr);
    curr = curr->next;
    
    head = s.top();
    curr = s.top();
    while(1){
        s.pop();
        if(s.empty()) break;
        curr -> next = s.top();
        curr = curr->next;
    }
    curr -> next = nullptr;//nullptr까지 실행하기 때문에 이게 중요/
	return head;//일단은 헤드가 1인것까지는 잘 실행이 된다. 헤드 다음연결이 잘되어있는지.
}

// reverses a singly linked list and returns the new head. The last node
// becomes the head node. 
Node* reverse_in_place(Node* head) {
	if (empty(head)) return nullptr;    // nothing to reverse
    //Node* curr = head;
	pNode prev = nullptr;
    pNode temp = nullptr;
    while(head != nullptr){
        //일단은 head의 Next를 어딘가에 저장해두고,
        temp = head -> next;
        head -> next = prev;
        prev = head;
        head = temp;
    }
	return prev;
}

// The function cut_in_two_halves() cuts the list in two halves. 
// It returns the first node of the first half and the first node of the 
// second half of the list. If there are odd number of nodes, the second 
// half keeps one more node than the first half. For example, 
// the second half keeps 5 nodes if there are 9 nodes.
// the size of the list must be equal to or greater than two.
pair<Node*, Node*> cut_in_two_halves(Node* p) {
    int a = size(p)/2;
    //반으로 나눈다음에 반으로 나눈데까지는 first의 last로 지정.
    pNode curr = p;
    pNode prev = nullptr;
    for(int i=0; i<a; i++){
        prev = curr;
        curr = curr->next;
    }
    prev -> next = nullptr;
    pNode second_first = curr;

	return make_pair(p, second_first);  // p's are just place-holders.
}

// removes consecutive items in the list, and leaves its neighbors unique.
// We can proceed down the listand compare adjacent nodes. When adjacent 
// nodes are the same, remove the second one.There's a tricky case where 
// the node after the next node needs to be noted before the deletion. 
// Your implementation must go through the list only once.
Node* zap_duplicates(Node* p) {
	if (empty(p)) return nullptr;
    pNode curr = p;
    pNode temp = nullptr;//3개까지는 필요없을 수 있음.
    while(curr -> next != nullptr){
        if(curr -> data == curr -> next-> data){//만약 같으면에서 실행되는 조건들. 다르면.
            temp = (curr -> next) -> next;
            curr -> next = temp;
        }
        else{
            curr = curr -> next;
        }
    }
	return p;
}

// shows the values of all the nodes in the list if all is true or
// the list size is less than or equal to show_n * 2. If there are more than
// (show_n * 2) nodes, then it shows only show_n number of nodes from
// the beginning and the end in the list.

void show(pNode p, bool all, int show_n) {
    //cout << "head's data " << p->data << endl;
    //cout << "head's next data " << (p->next)->data << endl;
    DPRINT(cout << "show(" << size(p) << ")\n";);
    if (empty(p)) {
        cout << "\n\tThe list is empty.\n";
        return;
    }

    int i;
    pNode curr;
    const int N = size(p);
    cout << endl << "FRONT ";//curr은 p이다. head라는 것임.
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

