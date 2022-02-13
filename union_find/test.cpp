#include "union_find.h"
#include <iostream>
using namespace std;

int main(){

    union_find uf(10);
    cout << uf.get_count() << endl;
    uf.connect(1,9);
    uf.connect(5,7);
    uf.connect(3,7);
    uf.connect(3,1);
    cout << uf.get_count() << endl;
    cout << (uf.is_connected(5,9)?1:0) << endl;

    return 0;
}