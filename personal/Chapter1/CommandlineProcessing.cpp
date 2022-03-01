#include <iostream>

using namespace std;

int main(const int argc, char** argv){

    cout << "this is how command line processing work.( argc, argv)" << endl;

    cout << "You entered: " << argc << "arguments:" << endl;

    for(int i=0; i < argc; ++i){
        cout << i << " = "<< argv[i] << endl;
    }
    return 0;
}