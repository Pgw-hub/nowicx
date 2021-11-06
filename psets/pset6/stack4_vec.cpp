//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]

#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;
#define DPRINT(func) func ;


struct Stack{
    vector<string> item;
};

using stack = Stack*;

stack newStack(){
    stack s = new Stack;
    return s;
}

void free(stack s){
    delete s;
}

int size(stack s){
    return s->item.size();
}

bool empty(stack s){//bool값은 return 값에 조건문을 사용할 수 있다.
    return s->item.empty();
}

string top(stack s){
    return s->item.back();
}

void pop(stack s){
    s ->item.pop_back();
    //DPRINT(cout << "size / capacity(after pop) = "  <<s->N << "/"<< s->capacity << endl);
}

void push(stack s, string a){
    s->item.push_back(a);
    DPRINT(cout << " size / capacity(after push["<< a <<"]) = " <<s->item.size() << "/"<< s->item.capacity() << endl);
}

void printStack(stack s){
    if(empty(s)) return;
    else{
        for(int i=0;i<s->item.size();i++){
            cout << s->item[i] << '\t';
        }
        cout << endl;
    }
}

void printStack_fromBottom(stack s){
    if(empty(s)) return;
    else{
        for(int i=s->item.size()-1;i>=0;i--){
            cout << s->item[i] << '\t';
        }
        cout << endl;
    }
}

int main(){
    //int list[] = {1,2,3,4,5,0,6,0,0,7,0,0,0,8}
    string list[] = {"to","be","or","not","to","-","be","-","-","that","-","-","-","is"};
    stack s = new Stack;    
    for(auto item : list){
        if(item != "-" )
        push(s,item);
        else{
            cout <<"pop : "<< top(s) << ' '<< endl;
            pop(s);
        }
    }
    cout << "\nsize: " << size(s) << endl;
    cout << "\ntop : " << top(s) << endl;
    cout << "\nstack T: "; printStack(s);
    cout << "\nstack B: "; printStack_fromBottom(s);
    cout << "\nHappy Coding";
    free(s);
}