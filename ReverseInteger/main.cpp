/******************************************************************************
Author: CJ Kim
Date: 2/29/2020

Title: Reverse Integer
Explain: Given a signed 32-bit integer, reverse digits.
         When reversed integer is out of range [-2^31, 2^31-1], then return 0.
         
         Example:
         Input : 1234
         Output : 4321
*******************************************************************************/

#include <iostream>
#include <string>

using namespace std;


// The time complexity is Size of "input" string.
// It loops through the entire input string twice.

int ReverseInteger(const signed int input){
    
}

void Tester(const int TestNum, const string Memo, const int input, const int output){
    cout << "#" << TestNum << " " << Memo << "            ";
    if(ReverseInteger(input) == output){
        cout << "Passed" << endl;
    }else{
        cout << "Failed" << endl;
    }
}

int main(){
    int input = 123;
    int output = 321;
    Tester(1, "Positive 3 Digits", input, output);

    input = -123;
    output = -321;
    Tester(2, "Negative 3 Digits",input, output);
}