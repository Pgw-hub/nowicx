/// 
/// Hashing is an important data structure which is designed to use 
/// a special function called the hash function. The function is used to 
/// map a given value with a particular key for faster access of elements. 
/// The efficiency of mapping depends of the efficiency of the hash 
/// function used.
/// Author Youngsup Kim, idebtor@gmail.com
/// 
/// //아너코드: On my honor, I pledge that I have neither received nor provided improper assistance in the completion of this assignment.
//Signed: [박건우]
//Student Number: [21901023]

#include <iostream>
#include <cassert>
#include <list>
#include <algorithm>
#include "hash1.h"
using namespace std;

// Notice that ht is passed by reference only whenever its pointer may be changed inside.
// Passing by reference has not been used for speed-up the code.
void clear(Hash*& ht) {//완료
    delete[] ht->hashtable;
    ht = new Hash{ 2 };                     // a magic number, using a small prime number 
}

int hashfunction(Hash* ht, int key) {//완료       // hash function for int key
    return (key % ht->tablesize);
}

int hashfunction(Hash* ht, string key) {//완료    // hash ft for strings
    int value = 0;
    for (auto x : key)
        value = 37 * value + x;

    value %= ht->tablesize;
    if (value < 0) value += ht->tablesize;
    return value;
}

int tablesize(Hash* ht) {//완료
    return ht->tablesize;
}

int nelements(Hash* ht) {//완료
    return ht->nelements;
}

double loadfactor(Hash* ht) {//완료
    return (double)ht->nelements / ht->tablesize;
}

double threshold(Hash* ht) {//완료
    return ht->threshold;
}

void threshold(Hash*& ht, double lf) {//완료
    ht->threshold = lf;
    if (loadfactor(ht) >= threshold(ht)) rehash(ht);
}

// https://stackoverflow.com/questions/4475996/given-prime-number-n-compute-the-next-prime
bool isprime(int x) {//완료
    for (int i = 3; true; i += 2) {
        int q = x / i;
        if (q < i) return true;
        if (x == q * i) return false;
    }
    return true;
}

int nextprime(int x) {//완료
    DPRINT(cout << "next_prime: " << x;);

    if (x <= 2) return 2;
    
    if (!(x & 1)) ++x;
    
    for (; !isprime(x); x += 2);

    DPRINT(cout << " --> " << x << endl;);
    return x;
}

// rehashes the hash table using successive doubling scheme and the next prime
// The hash table doubles its size but still prime. 
void rehash(Hash*& ht) {
    DPRINT(cout << "rehash: " << endl;);
    //현재 loadfactor가 threshold보다 크다는 것까지 검증완료.
    // create new double-sized and emtpy table, use nextprime()
    int old_size = tablesize(ht);
    int new_size = nextprime(2*old_size+1);
    
    // free old ht, then set the new ht
    //기존에 있던 값 임시 list에 넣어주기.
    list<string> l_temp;
    for(int i=0;i < old_size; i++){
        list<string>::iterator it = ht->hashtable[i].begin();
        for(it; it!=ht->hashtable[i].end(); it++){
            l_temp.push_back(*it);
        }
    }
    
    //새로운 ht만들기.
    double new_threshold = ht->threshold;
    clear(ht);
    ht = new Hash(new_size,new_threshold);
    
    //기존의 값을 다시 넣어주는 작업.
    int size = l_temp.size();
    for(int i=0; i<size; i++){
        //cout << "hi" << endl;
        insert(ht,l_temp.front());
        l_temp.pop_front();
    }
    //지금 rehash 내에 insert가 있다보니 Insert내에 rehash가 있다보니 계속해서 돈다.
    
    
    //tablesize다시 이볅해주고
    //배열에 기존 값들 넣어주기.
    /*
    string temp[old_size];
    list<string>* new_hashtable = new list<string>[new_size];
    int j=0;
    for(int i=0;i < old_size; i++){
        list<string>::iterator it = ht->hashtable[i].begin();
        for(it; it!=ht->hashtable[i].end(); it++){
            temp[j] = *it;
            j++;
        }
    }
    //delete 후 재설정.insert해주면됨.
    delete ht->hashtable;
    ht->nelements = 0;
    ht->tablesize = new_size;
    ht->hashtable = new_hashtable;
    
    for(auto key : temp){
        insert(ht,key);
    }
     */

    cout << "\tREHASHED(tablesize: " << old_size << " -> " << new_size << ")\n";
}

// inserts key to the table and returns true always; 
// rehash()'s are automatically performed if loadfactor >= threshold. 
bool insert(Hash*& ht, string key) {//완료
    DPRINT(cout << ">insert: " << key << endl;);
    int index = hashfunction(ht, key);
    ht->hashtable[index].push_back(key);
    ht->nelements++;
    
    // invoke rehash() only if necessary
    
    if(loadfactor(ht) >= ht->threshold)
        threshold(ht,loadfactor(ht));
    //바뀐 loadfactor을 구하고, 이걸 보내서, lf갱신해주고, 그 안에서 리해쉬필요하면 하기.

    DPRINT(cout << "<insert: " << key << endl;);
	return true;
}

// erases key and returns true if successful and false if unsuccessful
bool erase(Hash*& ht, string key) {
    DPRINT(cout << ">erase: " << key << endl;);

    // get the hash value for key and set the iterator variable: it
    int hash_value = hashfunction(ht,key);
    //반복자를 통해서 해당 엘리먼트를 찾으면 없에야한다. list내에 있는 원소를 없에는 거임.
    //erase(iterator)를 통해서 iterator가 가리키는 부분의 원소를 삭제해야 함.
    //vector반복문 내에 list반복문 사용해야 함.
       list<string>::iterator it = ht->hashtable[hash_value].begin();
       for(it; it!=ht->hashtable[hash_value].end(); it++){
           if(*it == key){
               ht->hashtable[hash_value].erase(it);
               ht->nelements--;
               return true;
           }
       }
    
//    for(int i=0; i < ht->tablesize; i++){
//        list<string>::iterator it = ht->hashtable[i].begin();
//        for(it; it!=ht->hashtable[i].end(); it++){
//            if(*it == key){
//                ht->hashtable[i].erase(it);
//                ht->nelements--;
//                return true;
//            }
//        }
//    }
    //화실히 행내에 리스트로 선언해줘야 암.
    // for loop using it, then return true if erased successfully.

    DPRINT(cout << "<erase failed: " << key << endl;);
    return false;
}

// searches the container for key and returns the bucket list to it if found,
list<string> find(Hash* ht, string key) {
    DPRINT(cout << ">find: " << key << endl;);
    list<string> empty_bucket;
    int index = hashfunction(ht, key);    // get the hash value for key 
    if (ht->hashtable[index].size() > 0) {
        //index가 같게 나오는 경우에는 그게 아니더라도 지금 나온다.
        //iterator 사용
        list<string>::iterator it = ht -> hashtable[index].begin();
        for(it; it!=ht->hashtable[index].end();it++){
            if(*it == key){
                return ht->hashtable[index];       // return the bucket list
            }
        }
    }

    DPRINT(cout << "<find: not found" << key << endl;);
    return empty_bucket;
}

// if show_empty is true, empty buckets are printed as well.
void show(Hash*& ht, bool show_empty) {
    cout << endl;
    for (int i = 0; i < tablesize(ht); i++) {
        if (ht->hashtable[i].size() > 0) {
            cout << "\t[" << i << "]  ";
            for (auto x : ht->hashtable[i]) {
                cout << x << " ";
            }
            cout << endl;
        }
        else if (show_empty) {
            cout << "\t[" << i << "]  ";
            cout << endl;
        }
    }
}

#if 0
int main() {
    // int hash_keys[] = { 1, 11, 12, 21, 14, 15 };       
    string hash_keys[] = { "a", "called", "gracia", "commissioned", "sola", "fide", "z" };

    int n = sizeof(hash_keys) / sizeof(hash_keys[0]);
    int tablesize = 7;

    Hash* ht = new Hash{ tablesize };

    for (int i = 0; i < n; i++)            //insert keys into the hash table
        insert(ht, hash_keys[i]);
    cout << "Hash table created:" << endl;
    show(ht);

    erase(ht, hash_keys[4]);
    erase(ht, hash_keys[5]);

    cout << "Hash table after erase():" << endl;
    show(ht);
    return 0;
}
#endif
