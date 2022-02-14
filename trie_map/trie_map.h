#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int R = 256; // ASCII 码数量

class Node{
public:
    int val;
    vector<Node*> child;
    Node(int val){
        this->val = val;
        this->child.resize(R);
    }
    Node(){
        this->val = -1;
        this->child.resize(R);
    }
};

class trie_map{
private:
    Node* root;
    Node* get_node(Node* x,string key); //从 Node 节点开始搜索key
    int count; // 字典树中 key 的数量
    void traverse(Node* p,string prefix,vector<string>& res);
    bool has_key_with_pattern(Node* p,string pattern,int idx);
    void traverse(Node* p,string pattern,int idx,string path,vector<string>& res);
    Node* put(Node* p ,string key,int val,int i);
    Node* remove(Node* p,string key,int i);
public:
    trie_map();
    ~trie_map();

    void insert(string key,int val); // 插入 key
    int find(string key); // 查找 key
    void remove(string key); // 删除 key
    vector<string> keys_with_prefix(string prefix); // 包含 prefix 前缀的所有key
    bool contain(string key); // 是否包含 key
    string longest_prefix(string query); // 查询 query中包含的最长前缀
    string shortest_prefix(string query); // 查询 query中包含的最短的前缀
    bool has_key_with_prefix(string prefix); // 是否存在以prefix 为前缀的key
    vector<string> keys_with_pattern(string pattern); //通配符 . 匹配任意字符，返回所有匹配的key
    bool has_key_with_pattern(string pattern); //通配符 . 匹配任意字符，判断是否存在匹配的key
    int size(); // 返回 字典树中 key 的数量
};

class trie_set{
private:
    trie_map map;
public:
    trie_set(){};
    ~trie_set(){};
    void add(string key){
        map.insert(key,0);
    }

    void remove(string key){
        map.remove(key);
    }

    bool contain(string key){
        return map.contain(key);
    }

    string longest_prefix(string query){
        return map.longest_prefix(query);
    }
    string shortest_prefix(string query){
        return map.shortest_prefix(query);
    }

    vector<string> keys_with_prefix(string prefix){
        return map.keys_with_prefix(prefix);
    }

    bool has_key_with_prefix(string prefix){
        return map.has_key_with_prefix(prefix);
    }
    vector<string> keys_with_pattern(string pattern){
        return map.keys_with_pattern(pattern);
    }
    bool has_ket_with_pattern(string pattern){
        return map.has_key_with_pattern(pattern);
    }
    int size(){
        return map.size();
    }
};
