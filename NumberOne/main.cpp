/******************************************************************************
Author: CJ Kim
Date: 4/14/2020
Title: Count Digit One
Explain: All unsigned integer from 1 to given N.
		 Count how many times digit 1 was encountered.

		 Input: 14
		 Output: 7 (1,10,11,12,13,14)
*******************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

// Time Complexity is O(N x M)
// N = # of digits, M = average # of digits per number.

int CountDigitOne(int n){
	int count = 0;

	for(int i = 1; i <= n; i ++){
		int num = i;
		while(num){
			if(num % 10 == 1){
				count ++;
			}
			num /= 10;
		}
	}
	return count;
}


void Tester(const int TestNum, const string Memo, int input, int output){
    cout << "#" << TestNum << " " << Memo << "            ";

    if(CountDigitOne(input) == output){
        cout << "Passed" << endl;
    }else{
        cout << "Failed" << endl;
    }
}

int main(){
	for(int i = 1; i < 10; i ++){
		Tester(i, "One Digit Number", i, 1);
	}

    Tester(10, "Passed 10s #1", 24, 13);
    Tester(11, "Passed 10s #2", 49, 15);
}