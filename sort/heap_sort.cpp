#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

// g++ heap_sort.cpp --std=c++11 -o heap_sort
// ./heap_sort 10
class Sort{
public:
    static void heap_sort(vector<int>& nums){
        create_max_heap(nums);
        for(int i = nums.size()-1;i > 0;--i){
            swap(nums[0],nums[i]);
            adjust_down(nums,i);
        }
    }
    static void adjust_down(vector<int>& nums,int end){
        int i = 0;
        int left = 2 * i + 1,right = 2 * i + 2;
        while(i < end){
            if(left < end && right < end){
                int x = (nums[left] > nums[right]?left:right);
                swap(nums[i],nums[x]);
                i = x;
            }
            else if(left < end){
                swap(nums[i],nums[left]);
                i = left;
            }
            else if(right < end){
                swap(nums[i],nums[right]);
                i = right;
            }
            else{
                break;
            }
            left = 2 * i + 1;
            right = 2 * i + 2;

        }
    }
    static void create_max_heap(vector<int>& nums){
        int n = nums.size();
        for(int i = n/2;i >= 0; --i){
            adjust_up(nums,i);
        }
    }
    static void adjust_up(vector<int>& nums,int i){
        int n = nums.size();
        int left = 2 * i + 1,right = 2 * i + 2;
        int left_num,right_num;
        while(left < n || right < n){
            left_num = left < n ? nums[left]:INT32_MIN;
            right_num = right < n? nums[right]:INT32_MIN;
            if(nums[i] < left_num && nums[i] < right_num){
                swap(nums[i],nums[(left_num < right_num? right:left )]);
                i = (left_num < right_num? right:left );
            }
            else if(nums[i] < left_num){
                swap(nums[i],nums[left]);
                i = left;
            }
            else if(nums[i] < right_num){
                swap(nums[i],nums[right]);
                i = right;
            }
            else{
                return;
            }
            left = 2 * i + 1;
            right = 2 * i + 2;
        }
    }
};


int main(int argc,char** argv){
    vector<int> nums(atoi(argv[1]));
    srand(time(nullptr));
    cout << "排序前：";
    for(auto& n:nums){
        n = rand() % atoi(argv[1]);
        cout << n << " ";
    }
    cout << endl << "排序后：";
    Sort::heap_sort(nums);
    for(auto& n:nums){
        cout << n << " ";
    }
    cout << endl;

    return 0;
}
