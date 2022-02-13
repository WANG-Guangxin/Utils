#include "union_find.h"

union_find::union_find(int count){
    this->count = count;
    parent.resize(count);
    weight = vector<int>(count,1);
    for(int i = 0; i < count;i++){
        parent[i] = i;
    }
}

union_find::~union_find(){}

int union_find::get_count(){
    return this->count;
}

int union_find::find(int x){
    while(x != parent[x]){
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

bool union_find::is_connected(int x,int y){
    int root_x = find(x);
    int root_y = find(y);
    return root_x == root_y;
}

void union_find::connect(int x,int y){
    int root_x = find(x);
    int root_y = find(y);
    if(root_x == root_y){
        return;
    }
    else{
        if(weight[root_x] < weight[root_y]){
            parent[root_x] = root_y;   
            weight[root_y] += weight[root_x];
        }
        else{
            parent[root_y] = root_x;
            weight[root_x] += weight[root_y];
        }
        this->count--;
    }
}
