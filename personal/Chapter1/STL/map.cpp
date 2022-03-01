#include <string>
#include <iostream>
#include <map>
#include <utility>

using namespace std;

int main(){
    map<int,string> team;

    team[52] = "park";
    team.insert(pair<int,string>(40,"geon"));
    team.insert(make_pair(30,"woo"));

    for(map<int,string>::iterator it = team.begin(); it != team.end(); ++it){
        cout << (*it).first << ": " << (*it).second << endl;
    }

    // cout << "team[52] : " << team[52] << endl;
    // cout << "size : " << team.size() << endl;
}