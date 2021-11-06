//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]

// infix.cpp :
//
// The program evaluates a given infix expression which is fully parenthesized.
// It uses Dijkstra's two-stack algorithm. For simplicity of coding, however,
// the expression is to be fully parenthesized.
// For example:
//   ((3 - 1 ) * 5) + 4
//   2 * ((34 - 4) * 2)
//   1 + (((12 * 2) / 4) - 1)
//
// Author: idebtor@gmail.com
// 2020.04.05	created and assert() added
//
#include <iostream>
#include <cassert>
#include <cmath>
using namespace std;

#ifdef DEBUG
#define DPRINT(func) func;
#else
#define DPRINT(func) ;
#endif

#if 0    //////////////////////////////////////////////////////////////////////
// set #if 1, if you want to use this stack using vector instead of STL stack.
// a basic stack functinality only provided for pedagogical purpose only.
#include <vector>
template <typename T>
struct stack {
	vector<T> item;

	bool empty() const {
		return item.empty();
	}
	auto size() const {
		return item.size();
	}
	void push(T const& data) {
		item.push_back(data);
	}
	void pop() {
		if (item.empty())
			throw out_of_range("stack<>::pop(): pop stack");
		item.pop_back();
	}
	T top() const {
		if (item.empty())
			throw out_of_range("stack<>::top(): top stack");
		return item.back();
	}
};
#else  /////////////////////////// using STL stack //////////////////////////
#include <stack>
#endif ///////////////////////////////////////////////////////////////////////

template <typename T>
void printStack(stack<T> orig) {
	
	if(orig.empty()) return;
	while(!orig.empty()){
		T a = orig.top();
		orig.pop();
		printStack(orig);
		orig.push(a);
	}
}

// performs arithmetic operations.
double apply_op(double a, double b, char op) {
	switch (op) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': return a / b;
	}
	cout << "Unsupported operator encountered: " << op << endl;
	return 0;
}

// there is a bug...
double compute(stack<double>& va_stack, stack<char>& op_stack) {
	double right  = va_stack.top(); va_stack.pop();//top하고 pop하기.
	double left = va_stack.top(); va_stack.pop();//top하고 pop.
	char op = op_stack.top(); op_stack.pop();//op하나 꺼내기.
	double value = apply_op(left, right, op);//여기서 계산한 결과값을 value에 넣음.
	va_stack.push(value);
	DPRINT(cout << " va/op_stack.pop: " << value << endl;);
	return value;
}

// returns value of expression after evaluation.
double evaluate(string tokens) {//기준
	DPRINT(cout << ">evaluate: tokens=" << tokens << endl;);
	stack<double>  va_stack;              // stack to store operands or values
	stack<char> op_stack;                 // stack to store operators.
	double value = 0;
	string temp = "";
	int size = 0;
	double ivalue = 0;

	for (size_t i = 0; i < tokens.length(); i++) {//한줄로 쭉 받고, 아까처럼 char로 받는게 아니라, 
		// token is a whitespace or an opening brace, skip it.
		
		if (isspace(tokens[i]) || tokens[i] == '(') continue;
		DPRINT(cout << " tokens[" << i << "]=" << tokens[i] << endl;);

		// current token is a value(or operand), push it to va_stack.
		if (isdigit(tokens[i])) {//그 자리가 숫자일경우에,
			temp += tokens[i];//354
			size++;//3

			if(!isdigit(tokens[i+1])){//만약 다음 자리가 숫자가 아니라면 -> 받아온숫자 계산 후 
				for(int j=0;j<size;j++){//3까지 0,1,2 세번반복
					ivalue += (temp[j]-'0')*pow(10,size-1-j);//3 * 10^2 + 5 * 10^1 + 4 * 10^0
				}
				va_stack.push(ivalue);
				temp = "";
				size = 0;
				ivalue = 0;
			}
			//만약에 정수가 연속적을 들어온다면,...i값을 저장하고있고, 그리고, 들어오는 i의 값이 연속적이지 않을경우 전에 저장해두었던 값들을 정하기. 
			//ivalue = tokens[i] - '0';// 48을 빼는 것이다.
			//va_stack.push(ivalue); //결국에 ivalue 라는 값을 넣는다. 
		} 
		else if (tokens[i] == ')') { // 오른쪽 괄호일경우에
			double answer = compute(va_stack,op_stack);
		}
		else { // 연산자라면
			op_stack.push(tokens[i]);
		}
	}
	while(op_stack.size() != 0){
		compute(va_stack, op_stack);
	}	

	DPRINT(cout << "tokens exhausted: now, check two stacks:" << endl;);
	DPRINT(printStack(va_stack);  cout << endl;);
	DPRINT(printStack(op_stack);  cout << endl;);

	//cout << "your code here: process if !op_stack.empty() \n";
	assert(op_stack.size() == 0);

	//cout << "your code here: post-conditions\n";
	assert(va_stack.size() == 1);

	//cout << "your code here: return & clean-up\n";
	value = va_stack.top();
	va_stack.pop();

	return value;
}
