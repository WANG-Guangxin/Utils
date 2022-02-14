#include "trie_map.h"

trie_map::trie_map(){
    root = new Node();
    this->count = 0;
}

trie_map::~trie_map(){
}

int trie_map::size(){
    return this->count;
}

Node* trie_map::get_node(Node* x,string key){
    Node* p = x;

    for(int i = 0; i < key.size();i++){
        if(p == nullptr){
            return nullptr;
        }
        char c = key.at(i);
        p = p->child[c];
    }

    return p;
}

bool trie_map::contain(string key){
    Node* p = get_node(root,key);
    if(p != nullptr && p->val != -1){
        return true;
    }
    return false;
}

int trie_map::find(string key){
    Node* p = get_node(root,key);
    if(p != nullptr){
        return p->val;
    }
    else{
        return -1;
    }
}

bool trie_map::has_key_with_prefix(string prefix){
    return get_node(root,prefix) != nullptr;
}

string trie_map::shortest_prefix(string query){
    Node* p = root;
    for(int i = 0;i < query.size();i++){
        if( p == nullptr){
            return "";
        }
        if( p->val != -1){
            return query.substr(0,i);
        }
        char c = query.at(i);
        p = p->child[c];
    }
    if(p != nullptr && p->val != -1){
        return query;
    }
    return "";
}

string trie_map::longest_prefix(string query){
    int max_len = 0;
    Node* p = root;
    for(int i = 0;i< query.size();i++){
        if( p == nullptr){
            break;
        }
        if( p->val != -1){
            max_len = i;
        }
        char c = query.at(i);
        p = p->child[c];
    }
    if( p != nullptr && p->val != -1){
        return query;
    }
    return query.substr(0,max_len);
}

vector<string> trie_map::keys_with_prefix(string prefix){
    vector<string> res;
    Node* p = get_node(root,prefix);
    if( p == nullptr) return res;
    traverse(p,prefix,res);
    return res;
}

void trie_map::traverse(Node* p,string prefix,vector<string>& res){
    string tmp = prefix;
    if(p == nullptr){
        return;
    }
    if( p->val != -1){
        res.emplace_back(prefix);
    }
    for(int i = 0;i < R;i++){
        tmp += (char)i;
        traverse(p->child[i],tmp,res);
        tmp = prefix;
    }
}

vector<string> trie_map::keys_with_pattern(string pattern){
    vector<string> res;
    string path;
    traverse(root,pattern,0,path,res);
    return res;
}

void trie_map::traverse(Node* p,string pattern,int idx,string path,vector<string>& res){
    if(p == nullptr){
        return;
    }
    if(idx == pattern.size()){
        if(p->val != -1){
            res.emplace_back(path);
        }
        return;
    }
    char c = pattern.at(idx);
    if( c == '.'){
        for(char j = 0; j < R;j++){
            path+=j;
            
            traverse(p->child[j],pattern,idx+1,path,res);
            path.pop_back();
        }
    }
    else{
        path+=c;
        traverse(p->child[c],pattern,idx+1,path,res);
        path.pop_back();
    }
}

bool trie_map::has_key_with_pattern(string pattern){
    return has_key_with_pattern(root,pattern,0);

}

bool trie_map::has_key_with_pattern(Node* p,string pattern,int idx){
    if( p == nullptr ){
        return false;
    }
    if( idx == pattern.size() ){
        return p->val != -1;
    }
    char c = pattern.at(idx);
    if( c == '.'){
        for(char j = 0;j < R;j++){
            if(has_key_with_pattern(p->child[j],pattern,idx+1)){
                return true;
            }
        }
    }
    else{
        return has_key_with_pattern(p->child[c],pattern,idx+1);
    }
    return false;
}

void trie_map::insert(string key,int val){
    if(contain(key) == false){
        this->count++;
    }
    root = put(root,key,val,0);
}

// 定义：向以 node 为根的 Trie 树中插入 key[i..]，返回插入完成后的根节点
Node* trie_map::put(Node* p ,string key,int val,int i){
    if(p == nullptr){
        p = new Node();
    }
    if(i == key.size()){
        p->val = val;
        return p;
    }
    char c = key.at(i);
    p->child[c] = put(p->child[c],key,val,i+1);
    return p;
}
void trie_map::remove(string key){
    if(contain(key) == false){
        return;
    }
    root = remove(root,key,0);
    count--;
}

Node* trie_map::remove(Node* p,string key,int i){
    if(p == nullptr){
        return nullptr;
    }
    if( i == key.size() ){
        p->val = -1;
    }
    else{
        char c = key.at(i);
        p->child[c] = remove(p->child[c],key,i+1);
    }

    if(p->val != -1){
        return p;
    }

    for(int c = 0;c < R;c++){
        if(p->child[c] != nullptr){
            return p;
        }
    }

    return nullptr;
}