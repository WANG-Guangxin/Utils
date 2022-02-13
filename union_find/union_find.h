#ifndef UNION_FIND_H
#define UNION_FIND_H
#include<vector>
using namespace std;

class union_find{
private:
    int count;
    vector<int> parent;
    vector<int> weight;
    int find(int x);

public:
    union_find(int count);
    ~union_find();
    int get_count(void);
    bool is_connected(int x,int y);
    void connect(int x,int y);
};


#endif