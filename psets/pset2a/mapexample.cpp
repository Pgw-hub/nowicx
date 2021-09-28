#include <iostream>
#include <map>

using namespace std;

int main(){
    map<string, int> table;
    cout << "using keys as array indices\n";
    table["John"] =21;
    table["Paul"] =23;
    table["Pete"] =24;
    table["Adam"] =25;

    for(auto x : table){
        cout << "name: " << x.first << "\t";
        cout << "age: " << x.second << endl;
    }

    cout << "using iterator\n";
    for(auto it= table.begin(); it != table.end(); ++it){
        cout << "name: " << it -> first << "\t";
        cout << "age: " << it -> second << endl;
    }

    cout << table.key(25);
    //여기서 왜 it 앞에다가 꼭 해줘야하는건가? + iterator 인터페이스를 제공하는 거 같은데, 꺽새를 통해서 접근하는 것을 보면 정확히 뭔지 알아보기

    return 0;
}