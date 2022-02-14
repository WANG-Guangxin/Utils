#include "trie_map.h"
#include <iostream>
#include <string>


using namespace std;

int main(){

    trie_map map;
    map.insert("abc",3);
    map.insert("abcde",5);
    map.insert("bcdef",8);
    cout << map.contain("ad") << endl;
    map.insert("abcd",3);
    map.insert("abe",3);
    cout << map.find("abc") << endl;
    cout << map.size() << endl;
    cout << map.has_key_with_prefix("bcd") << endl;
    cout << map.has_key_with_pattern(".bc.") << endl;
    cout << map.has_key_with_pattern("ab.") << endl;
    cout << map.contain("xxxxxx") << endl;
    map.remove("abc");
    vector<string> res;
    // res = map.keys_with_prefix("ab");
    // for(auto& s:res){
    //     cout << s << " " ;
    // }
    // cout << endl;
    // res.clear();
    res = map.keys_with_pattern("a..");
    for(auto& s : res){
        cout << s << " ";
    }


    return 0;

}

