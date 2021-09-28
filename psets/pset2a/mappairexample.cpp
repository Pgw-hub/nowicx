#include <iostream>
#include <map> //이렇게 꼭 삽입을 해줘야함.

using namespace std;

int main(){
    map<char, int> chart {  pair<char,int>('A',65),
                            pair<char,int>('C',67),
                            make_pair('D',68),
                            make_pair('B',66),
                            };
    
    for(auto item : chart){
        cout << "ascii: " << item.first << "\t";
        cout << "code: " << item.second << endl;
    }

    cout << "using iterator\n";
    for(auto it= chart.begin(); it != chart.end(); ++it){
        cout << "ascii: " << it -> first << "\t";
        cout << "code: " << it -> second << endl;
    }

    cout << chart['B'] << endl;
    //여기서 왜 it 앞에다가 꼭 해줘야하는건가? + iterator 인터페이스를 제공하는 거 같은데, 꺽새를 통해서 접근하는 것을 보면 정확히 뭔지 알아보기

    return 0;
}