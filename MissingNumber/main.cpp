/******************************************************************************
Author: CJ Kim
Date: 3/8/2020

Title: Missing Number
Explain: Given an array continaing n distinct numbers taken from 0, 1, .., n.
         Find the one that is missing from the array.

         Input: [3,0,1]
         Output: 2
*******************************************************************************/

#include <iostream>
#include <string>
#include <vector>

using namespace std;


// Time Complexity is size of array.
// Memory Space Usage is constant.

/* One thing to keep in mind is that the size of the array tells us what the max number should be.
 * If the size of the array is 5, we know the possible numbers are from 0 to 5. Total of 6 numbers
 * and one of them will be missing.
 * 
 * Since we can't use extra memory space, we can't use hashset to store data and check which one is
 * missing. So in this case we will approach the total sum.
 */

// If you input 5, this will return the sum of 1 through 5, using Gaussian Rules.
int GaussianSum(int number){
    return (number + 1) * number / 2;
}

int FindMissingNumber(vector<int>& nums){
    // Find the true sum.
    int Sum = GaussianSum(nums.size());

    // We know the missing number by calculating the difference between the actual sum and the sum of 
    // the given array.
    int NumSum = 0;
    for(int a : nums){
        NumSum += a;
    }

    return Sum - NumSum;
}

void Tester(const int TestNum, const string Memo, vector<int>& input, const int output){
    cout << "#" << TestNum << " " << Memo << "            ";

    if(FindMissingNumber(input) == output){
        cout << "Passed" << endl;
    }else{
        cout << "Failed" << endl;
    }
}

int main(){
    vector<int> v{3,0,1};
    Tester(1, "Simple #1", v, 2);

    v.assign({9,6,4,2,3,5,7,0,1});
    Tester(2, "Simple #2", v, 8);
}
