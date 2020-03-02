/******************************************************************************
Author: CJ Kim
Date: 3/1/2020

Title: Search in Rotated Sorted Array
Explain: Given an array of ints. They are sorted ascending manner then at
         a pivot, rotate those two sections. {1,2,3,4,5} becomes {3,4,5,1,2}.
         Safely assume no duplicates. Time complexity must be Log(Size of Array)
         Return -1 when not found.

         Input: {3,4,5,1,2}, 1, Output: 3
*******************************************************************************/

#include <iostream>
#include <string>
#include <vector>

using namespace std;



// Time Complexity is Log(Size of Array) as given in the problem.

// We still want to approach this problem as if it was sorted and do the same
// binary search. One trick is that we CANNOT blindly believe the number we are
// looking at, so we need to check on its neighbors for every landing number.
//     v
// 4 5 6 1 2
// Here at index of 2, we will still check its neighbors (left and right) to see
// if there are any descending. If spotted, move accordingly.
// If we followed the wrong path, because of the rotation, then we remember
// which path we went and adjust its movement 2nd time. It will be still Log N time.

int search(vector<int>& nums, int target){
    int Low, High;

    if(nums[nums.size() / 2] == target){
        // If I find the target number (happens to be exactly at the middle),
        // then return it.
        return nums.size() / 2;
    }else if(nums[nums.size() / 2] < target){
        // Set Low as middle and look at the Higher portion of array.
        Low = nums.size() / 2;
        High = nums.size() - 1;
    }else{
        // Set High as middle and look at the Lower portion of array.
        Low = 0;
        High = nums.size() / 2;
    }

    // First time binary search, I'll call it a "Naive" search.
    // It will try to find the number like a normal binary search.
    // If the number was on the other side due to rotation, then we will have
    // "Adjusted" search.

    while(Low < High){

    }

    // The fact that we are still here is because the "Naive" search didn't work.
    // Now that we know that it doesn't work, we can tweek it a little. We cannot do this
    // before hand into "Naive" search, because we don't know where the rotation happened.
    bool isAscending;
    if(nums[nums.size() / 2] < target){
        // Set Low as middle and look at the Higher portion of array.
        Low = nums.size() / 2;
        High = nums.size() - 1;
    }else{
        // Set High as middle and look at the Lower portion of array.
        Low = 0;
        High = nums.size() / 2;
    }
}


void Tester(const int TestNum, const string Memo, vector<int>& input, const int target, const int output){
    cout << "#" << TestNum << " " << Memo << "            ";

    if(search(input, target) == output){
        cout << "Passed" << endl;
    }else{
        cout << "Failed" << endl;
    }
}

int main(){
    Tester(1, "Simple", vector<int>{4,5,6,7,0,1,2}, 0, 4);
    Tester(1, "Simple", vector<int>{4,5,6,7,0,1,2}, 3, -1);
}
