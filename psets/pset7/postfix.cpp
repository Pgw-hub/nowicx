//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]

// postfix.cpp :
//
// The program evaluates a given postfix expression and produces a fully
// parenthesized infix expression. If the postfix expression may be 
// evaluated to a numeric value if it is expressed using numerically.
// For simplicity of coding, however, the postfix expression consists
// of single character operands and operators only and may have spaces.
//
// Author: idebtor@gmail.com
// 2020.04.05	Creation
// 2020.10.03	evaluation of numerical postfix expressions
//
#include <iostream>
#include <stack>
#include <cassert>
#include <sstream>

using namespace std;

#ifdef DEBUG
#define DPRINT(func) func;
#else
#define DPRINT(func) ;
#endif

// change the printStack to use template once you finish part 1 in step 1.
// prints the stack contents from the bottom. 
template<typename T>
void printStack(stack<T> orig) {
	stack<T> temp;
	
	while(!orig.empty()){
		temp.push(orig.top());
		orig.pop();
	}
	
	while(!temp.empty()){
		orig.push(temp.top());
		temp.pop();
	}
	/*
	if(orig.empty()) return;

	stack<T> temp;
	while(!orig.empty()){
		T a = orig.top();
		orig.pop();
		printStack(orig);
		temp.push(a);
	}
	*/
}

// returns a fully parenthesized infix expression in string after postfix evaluation.
string evaluate(string tokens) {//expression을 tokens로 받아옴.
	stack<string> st;//스택을 사용.

	for (char token : tokens) {//tokens 단위로 받으면 띄어쓰기를 기준으로 받아옴.
		if (isspace(token)) continue;  // if token is a whitespace, skip it.//스페이스이면 아래 코드를 전체 다 뛰어넘음.
		DPRINT(cout << "token: " << token << endl;);

		// current token is a value(or operand), push it to st.
		if (token == '+' || token == '-' || token == '*' || token == '/') {
			assert(st.size()>=2);
			string right = st.top();
			//cout << "rignt = " << right <<endl;
			st.pop();
			string left = st.top();
			//cout << "left = " << left <<endl;
			st.pop();
			//cout << "size = " << st.size() << endl;
			string unitedtoken = '('+left + token + right + ')';
			st.push(unitedtoken);
		}
		else {  // push the operand
			DPRINT(cout << "  push: " << token << endl;);
			// convert token(char type) to a string type and push it to the 
			stringstream ss;
			string s;
			ss << token;//stringstream의 원리 이 부등호 때문에 자꾸 너무 헷갈리게 느껴진다.
			ss >> s;
			//cout << "pushed : " << s << endl;
			st.push(s);
		}
	}

	DPRINT(cout << "token exhausted: \n";);
	DPRINT(printStack(st););
	DPRINT(cout << "stack size() should be 1.\n";);
	assert(st.size() == 1);
	string infixed_exp = st.top();
	st.pop();
	DPRINT(cout << "<evaluate() returns " << "your expr" << endl;);
	return infixed_exp;
}

// returns true if the tokens consist of '+', '-', '*', '/', spaces, and 
// digits (0 ~ 9), false otherwise.
bool is_numeric(string tokens) {

	//스페이스를 제외하고 모든 string 이 숫자인지를 확인해야함. 스트링 즉 지금 ascii로 표현이 되어있을텐데, 그 숫자안에 범위인지 확인.
	for(char token : tokens){
		if (isspace(token)) continue;
		else if (token == '+' || token == '-' || token == '*' || token == '/') continue;
		else if (48 > token || token > 57) {
			return false;
		}
	}
	return true;
}

// returns a numeric value after evaluating the postfix evaluation.
double evaluate_numeric(string tokens) {
	stack<double> st;
	double answer = 0;

	for (char token : tokens) {
		if (isspace(token)) continue;  // if token is a whitespace, skip it.
		DPRINT(cout << "token: " << token << endl;);
		

		// if token is a operator, evaluate; if a digit(or operand), push it to st.
		if (token == '+' || token == '-' || token == '*' || token == '/') {
			assert(st.size()>=2 || st.size());
			double right = st.top();
			st.pop();
			double left = st.top();
			st.pop();
			if(token == '+') answer = left + right;
			else if(token == '-') answer = left - right;
			else if(token == '*') answer = left * right;
			else if(token == '/') answer = left / right;
			//스트링으로 저장되어있는 연산자를 실제 연산자로 바꿀 수 있는가.		
			st.push(answer);
		}
		else { // push the operand (digit) in a value to the stack
			// convert token to a numeric data type and push it the stack
			stringstream ss;
			double d;
			ss << token;
			ss >> d;
			st.push(d);
		}
	}

	DPRINT(cout << "token exhausted: check the stack, its size() should be 1.\n";);
	DPRINT(printStack(st););
	assert(st.size() == 1);
	//cout << "your code here" << endl;
	DPRINT(cout << "<evaluate() returns " << expr << endl;);
	return answer;
}
