/******************************************************************************
Author: CJ Kim
Date: 3/1/2020

Title: Search in Rotated Sorted Array
Explain: Given an array of ints. They are sorted ascending manner then at
         a pivot, rotate those two sections. {1,2,3,4,5} becomes {3,4,5,1,2}.
         Safely assume no duplicates. Time complexity must be Log(Size of Array)
         Return -1 when not found.

         Input: {3,4,5,1,2}, 1, Output: 3
         Input: {3,4,5,1,2}, 0, Output: -1
*******************************************************************************/

#include <iostream>
#include <string>
#include <vector>

using namespace std;



// Time Complexity is Log(Size of Array) as given in the problem.

/* SOLUTION APPROACH DOCUMENT
 * 
 * There are 2 possible ways for us to think to solve this problem.
 * Find where it has a reverse (suddenly gets smaller), and separately look at two arrays.
 * Or, just start doing binary search and tweak a bit of how it does the search.
 * 
 * This can be definitely solved in linear time by looping through the array and find the
 * reverse and make it into a proper sorted array. Then do binary search, but that makes it
 * linear time, not log time.
 * 
 * First, we start from the half way. We take a look at lower half first.
 * When we detect higher number than previous number, find higher half,
 * if that was lower number than find lower half.
 * 
 * Take a look at this example.
 *              v
 * {10,11,1,2,3,4,5,6,7,8,9}
 * We start at value 4. As we have promised, we take a look at lower half first.
 *        v
 * {10,11,1,2,3,4,5,6,7,8,9}
 * Value 1 is smaller than previous value 4, so we keep looking at the lower half.
 * Because we know betwen 1 and 4, there was no decrease which means no reverse.
 *     v   
 * {10,11,1,2,3,4,5,6,7,8,9}
 * When we detect higher number, make sure there is no other higher number in between value 1 and 11.
 * Because value 11 might not be the highest number (which is where reverse happens).
 * In this case we were lucky and found the highest, we know it because the index 1 and 2 have no inner values.
 * 
 * Now we found the reverse, we split the array into 2 (not literally, we will still use one array),
 * and use binary search for the one that the number is in.
 * If our finding value was smaller than the first element value, we know to find it from the second half.
 * If it was the same or greater than the first element value, we know to find it from the first half.
 * 
 * After we do this for upper half (in case we didn't find the right value), we can safely assume
 * there was no reverse and just use binary search the normal way.
 */


void FindValue(const vector<int>& nums, int& Low, int& High, int& PrevVal, int MidPoint){
    // Low never gets equal to or greater than High, they stop when they are next to each other.
    // Check with "-1".
    while(Low < High){
        int Mid = Low + (High + 1 - Low) / 2;
        // If Mid was lower, that means from Mid to High, it's ascending correctly.
        // Take a look at lower half.
        if(nums[Mid] < PrevVal){
            High = Mid;
        }
        // If Mid was higher, then in between Mid and High, there must be a reverse.
        // Take a look at higher half.
        else if(nums[Mid] > PrevVal){
            if(Low == Mid){
                Low ++;
            }else{
                Low = Mid;
            }
        }else{
            High --;
        }

        PrevVal = nums[Mid];
    }
}


// This method takes a look at list of numbers and find where the reverse is happening in Log N time.
// Return value will be the index of Highest Number
// Input: {10,11,1,2,3,4,5,6,7,8,9}, Output: 1
int FindReverseIndex(vector<int>& nums){
    // This could be done in recursive way, but there is no guarantee on the size of the list.
    // We will not use recursion to save the stack overflow.

    int Low = 0;
    int High = (nums.size() / 2) - 1;
    int Value = nums[High];

    FindValue(nums, Low, High, Value, High);

    // If we found it, Low has the index of Highest Number and PrevVal has the value.
    // One way to know whether we found it or not is to check Low, if there weren't any,
    // Then we know Low must've stayed at 0 unchanged since they are sorted.
    if(Low != 0){
        return Low;
    }

    Low = nums.size() / 2;
    High = nums.size() - 1;
    Value = nums[Low];

    FindValue(nums, Low, High, Value, Low);
    
    if(High != nums.size() - 1){
        // Low is from 0 to upper half. We need to make sure to convert the index back to
        // index of Entire Array.
        return Low;
    }

    // There may ba an awkward case where we have divided exactly where the reverse was occurring.
    // Last step is to ensure that didn't happen. If prev is bigger, then we know reverse happened.
    if(nums.size() > 1 && (nums[nums.size() / 2 - 1] > nums[nums.size() / 2])){
        return nums.size() / 2 - 1;
    }
    // When it was not found, return -1 as index to indicate this array is sorted without reverse.
    return -1;
}

int BinarySearch(vector<int>& nums, int target){
    int Low = 0;
    int High = nums.size() - 1;

    while(Low < High){
        int Mid = Low + (High - Low) / 2;

        if(nums[Mid] < target){
            if(Low == Mid){
                Low ++;
            }else{
                Low = Mid;
            }
        }else if(nums[Mid] > target){
            High = Mid;
        }else{
            High --;
        }
    }

    // If the number was not found, then return -1.
    if(nums[Low] != target) return -1;

    return Low;
}

// If not found, returns -1
int search(vector<int>& nums, int target){
    int index = FindReverseIndex(nums);
    
    // If this is sorted without reverse, find all range as binary search.
    if(index == -1){
        return BinarySearch(nums, target);
    }else{
        // If first element (where reverse happened) is smaller than the target value,
        // we know we have to look for it in the higher values, which is first half.
        if(nums[0] <= target){
            // We add 1 to "nums.begin() + index + 1" because it's exclusive.
            vector<int> LowerHalf(nums.begin(), nums.begin() + index + 1);
            return BinarySearch(LowerHalf, target);
        }
        // If the value we are looking for is smaller than the first value, we know
        // it will be in the lower values, which is second half.
        // Make sure the index returned is the index of Highest. Add 1 to it to point
        // to the lowest number in the array.
        else{
            vector<int> UpperHalf(nums.begin() + index + 1, nums.end());
            // Make sure to add the offset (index + 1) to adjust the returned index
            // since we only did binary search with the upper half.
            return BinarySearch(UpperHalf, target) + index + 1;
        }
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
    vector<int> test;

    test.assign({4,5,6,7,0,1,2});
    Tester(1, "Starts High Number, Find Low Number, Odd Size", test, 0, 4);
    test.assign({3,4,5,6,7,0,1,2});
    Tester(2, "Starts High Number, Find Low Number, Even Size", test, 0, 5);
    test.assign({6,7,0,1,2,3,4});
    Tester(3, "Starts Low Number, Find High Number, Odd Size", test, 7, 1);
    test.assign({6,7,0,1,2,3,4,5});
    Tester(4, "Starts Low Number, Find High Number, Even Size", test, 6, 0);
    test.assign({1,2,3,4,5,6,7});
    Tester(4, "No Reverse, Increasing Order, Odd Size", test, 3, 2);
    test.assign({1,2,3,4,5,6});
    Tester(4, "No Reverse, Increasing Order, Even Size", test, 6, 5);
    test.assign({3,4,5,6,7,0,1,2});
    Tester(4, "Not Found", test, 9, -1);
}
