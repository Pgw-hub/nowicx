#include <iostream>
using namespace std;

struct Stack{
    string *item;//string we r gonna put element;
    int N;//size;
    int capacity;
};

using stack = Stack*;//stack의  포인터를  이렇게  지정.

//generating a new function to create a new stack. then it shoud return stackpointer.

//결국에 이 구조체로 쓰일 하나의 새로운 stack을 만들어야함. 이는 new를 써서 Stack 만큼의 메모리를 stack타입의 포인터 변수에게 할당해주어야힘.그럼 결국에 만들어지는 것은 스택포인터임. 따라서 스택 포인터 리턴.

stack newStack(int capacity){
    stack s = new Stack;
    //처음 만드는 거니까 다 선언을 새로 해주어야함.
    s -> N = 0;
    s -> capacity = capacity;//여기보면 이름을 같게하여 생성이 가능하다.
    s->item = new string[capacity];//new 뒤에는 얼마나 내가 할당해줄것인가를 적어주면 그만인것이다. 즉 위에는 선언한 Stack구조체만큼, 여기는 string 형식의 capa만큼.
    return s;
}

void free(stack s){
    delete[] s->item;
    delete s;
}

int size(stack s){
    return s->N;
}

bool empty(stack s){//bool값은 return 값에 조건문을 사용할 수 있다.
    return s->N == 0;
}

string top(stack s){
    return s->item[s->N - 1];
}

void pop(stack s){
    s -> N--;
}

void push(stack s, string a){
    s->item[s->N++] = a;
}

void printStack(stack s,int capacity){
    stack t = newStack(capacity);
    while(!empty(s)){
        cout << top(s) << ' ';
        push(t,top(s));
        pop(s);
    }
    while(!empty(t)){
        push(s,top(t));
        pop(t);
    }
}


void printStack_fromBottom(stack s,int capacity){
    stack t = newStack(capacity);
    while(!empty(s)){
        push(t,top(s));
        pop(s);
    }
    while(!empty(t)){
        cout << top(t) << ' ';
        pop(t);
    }
}

int main(){
    //int list[] = {1,2,3,4,5,0,6,0,0,7,0,0,0,8}
    string list[] = {"to","be","or","not","to","-","be","-","-","that","-","-","-","is"};
    int capacity = sizeof(list)/sizeof(list[0]);
    stack s = newStack(capacity);    
    for(auto item : list){
        if(item != "-" )
        push(s,item);
        else{
            cout << top(s) << ' ';
            pop(s);
        }
    }
    cout << "\nsize: " << size(s);
    cout << "\ntop : " << top(s);
    cout << "\nstack T: "; printStack(s,capacity);
    cout << "\nstack B: "; printStack_fromBottom(s,capacity);
    cout << "\nHappy Coding";
}