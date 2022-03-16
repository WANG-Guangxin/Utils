#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

// g++ quick_sort.cpp --std=c++11 -o quick_sort


class Quick{
public:
    static void sort(vector<int>& nums){
        shuffle(nums);
        sort(nums,0,nums.size()-1);
    }
    static void sort(vector<int>& nums,int low ,int high){
        if(low >= high){
            return;
        }
        int p = partition(nums,low,high);
        sort(nums,low,p-1);
        sort(nums,p+1,high);
    }
    static void shuffle(vector<int>& nums){
        int n = nums.size() - 1;
        for(int i = n;i > 0;--i){
            int x = rand() % i + 1;
            swap(nums[i],nums[x]);
        }
    }
    static int partition(vector<int>& nums,int low,int high){
        int p = nums[low];
        int i = low + 1,j = high;
        while(i <= j){
            while(i < high && nums[i] <= p){
                ++i;
            }
            while( j > low && nums[j] > p){
                --j;
            }
            if(i >= j){
                break;
            }
            swap(nums[i],nums[j]);
        }
        swap(nums[low],nums[j]);
        return j;
    }

};



int main(){
    srand(time(nullptr));
    vector<int> nums = {5,3,7,2,9,3,8,4,7,1,0,10};
    for(auto& n:nums){
        cout << n << " ";
    }
    cout << endl;
    Quick::sort(nums);
    for(auto& n:nums){
        cout << n << " ";
    }
    return 0;
}
