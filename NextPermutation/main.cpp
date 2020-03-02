/******************************************************************************
Author: CJ Kim
Date: 2/29/2020

Title: Next Permutation
Explain: Given an array of ints. Find the next combination that is higher.
         Input: 1,2,3, Output: 1,3,2
*******************************************************************************/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void Swap(vector<int>& vec, int a, int b){
    int tmp = vec[a];
    vec[a] = vec[b];
    vec[b] = tmp;
}

void Reverse(vector<int>& vec, int low, int high){
    while(low < high){
        Swap(vec, low, high);
        low ++;
        high --;
    }
}


// Time Complexity is 

void NextPermutation(vector<int>& nums){
    // Get the last digit.
    int prev_index = nums.size() - 1;
    int prev_val = nums[prev_index];
    // We will loop through from the 2nd last digit.
    for(int i = nums.size() - 2; i >=0; i --){
        // If we detect a ascending order, we swap those two values.
        // Since we are going backwards (lowest digit to highest), our previous value
        // being larger will be ascending order.
        if(nums[i] < prev_val){
            // Find the number that is right above "nums[i]" between index = i+1 & index = last.
            int index = i + 1;
            while(nums[index] > nums[i]){
                index ++;
            }
            index --; // We are interested in the number that's above, not right below.

            Swap(nums, i, index);

            // Once swapping is done, reverse all the digits that follows after index = i;
            Reverse(nums, i + 1, nums.size()-1);

            return;
        }

        prev_val = nums[i];
    }

    // If it was never "return" from the for-loop, then we know this number is in descending order.
    // We reset back to the first combination (all ascending) by "Reverse" the entire array.
    Reverse(nums, 0, nums.size() - 1);
}

bool CompareVectors(const vector<int>& a, const vector<int>& b){
    if(a.size() != b.size()) return false;

    for(int i = 0; i < a.size(); i ++){
        if(a[i] != b[i]) return false;
    }
    return true;
}

void Tester(const int TestNum, const string Memo, vector<int> input, const vector<int>& output){
    cout << "#" << TestNum << " " << Memo << "            ";
    NextPermutation(input);
    if(CompareVectors(input, output)){
        cout << "Passed" << endl;
    }else{
        cout << "Failed" << endl;
    }
}

int main(){
    Tester(1, "Simple", vector<int>{1,2,3}, vector<int>{1,3,2});
    Tester(2, "End of Combination", vector<int>{3,2,1}, vector<int>{1,2,3});
    Tester(3, "Duplicates", vector<int>{1,5,1}, vector<int>{5,1,1});
    Tester(4, "Large Array", vector<int>{1,5,8,4,7,6,5,3,1}, vector<int>{1,5,8,5,1,3,4,6,7});
    Tester(5, "All Same Numbers", vector<int>{1,1,1,1}, vector<int>{1,1,1,1});
}
