//아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]

#include <iostream>
#include <map>
using namespace std;
int main() {
    cout << "declare a map variable called table\n";
    map<string, int> table;

    cout << "initialize table using array[], insert(), pair<>, make_pair()\n";//선언시에 초기화할게 아니면 insert함수를 써줘야한다.
    table["Adam"] = 11;
    table.insert(pair<string,int>("John",21));
    table.insert(pair<string,int>("Paul",15));
    table.insert(make_pair("Pete",10));
    
    cout << "print table using range-based for loop\n";
    for(auto x :table){
        cout << "name : " << x.first << "\t age : " << x.second << endl; 
    }
    cout << endl;
    
    cout << "print table using iterator\n";
    for(auto it = table.begin(); it != table.end(); ++it){//왜 굳이 
        cout << "name : " << it->first << "\t age : " << it->second << endl; 
    }//iterator 는 왜 꺽새로 접근해야하는건지????
    
    cout << "define and initialize chart using pair<> and make_pair() only\n";
    map<char,int> chart { pair<char,int>('A',65),
                          pair<char,int>('B',66),
                          make_pair('C',67),
                          make_pair('D',68) };
    
    cout << endl;
    cout << "print chart using range-based for loop\n";     
    for(auto x : chart){
        cout << "ascii : " << x.first << "\t code : " << x.second << endl; 

    }     
    return 0; }
