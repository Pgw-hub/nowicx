#include <iostream>
#include <set>

using namespace std;

set<int> s;


int main(){
    for(int i = 1; i <= 100; i++){
    s.insert(i);
    }
    
    s.insert(42);
    // does nothing, 42 already exists in set
    for(int i = 2; i <= 100; i += 2){
        s.erase(i);
    }  // Erase even values
    
    int n = int(s.size());
    if (s.find(42) != s.end()){
        cout << "42 is in set" << endl;
    }
    else{
        cout << "42 is not in set" << endl;
    }
        
    // insert 100 elements, [1..100]
    // n will be 50


}
