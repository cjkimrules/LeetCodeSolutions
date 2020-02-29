/******************************************************************************
Author: CJ Kim
Date: 2/29/2020

Title: Container with Most Water
Explain: Given an array of heights with indices being x-axis value.
         Find the maximum area with 2 of heights.
*******************************************************************************/

#include <iostream>
#include <string>
#include <vector>

using namespace std;


// Time Complexity is size of array.

// The simplest to implement has time complexity of squared (quadratic).
// For every height, we pair it with every other height and compare all areas.
//
// We can also achieve the same answer by looping through all heights once.
// We start from both ends and narrowing heights closer by eliminating the shorter one.
// Hopefully by eliminating shorter one, we get a higher one to get bigger area.

int MaxArea(const vector<int>& height){
    int lowBound = 0;
    int highBound = height.size() - 1;
    int max = 0;

    while(lowBound < highBound){
        int ShorterHeight = height[lowBound] < height[highBound] ? height[lowBound] : height[highBound];
        int area = ShorterHeight * (highBound - lowBound);

        if(area > max) max = area;

        // Depending on which one was the shorter, move on to the next (narrower) to eliminate it.
        if(ShorterHeight == height[lowBound])   lowBound ++;
        else                                    highBound --;
    }

    return max;
}

void Tester(const int TestNum, const string Memo, const vector<int>& height, const int output){
    cout << "#" << TestNum << " " << Memo << "            ";
    if(MaxArea(height) == output){
        cout << "Passed" << endl;
    }else{
        cout << "Failed" << endl;
    }
}

int main(){
    vector<int> v{1,8,6,2,5,4,8,3,7};
    Tester(1, "Simple", v, 49);

    v.assign({1,25,6,30,5,4,8,3,7});
    Tester(1, "Tall but Narrow", v, 50);
    
    v.assign({1,8,6,2,5,4,8,3,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2});
    Tester(1, "Short but Wide", v, 72);
}
