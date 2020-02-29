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
#include <cmath>

using namespace std;


// FindDigitCount will return the number of digits in "input".
// "1234" will return 4. "123456" will return 6. 
int FindDigitCount(const int input){
    int digit = 1;
    int divider = 10;

    // Keep looping until we reach division equal to 0.
    // In programming, 4 / 10 = 0. Since they are not floats or doubles.
    while(input / divider != 0){
        divider *= 10;
        digit ++;
    }

    return digit;
}

// GetDigit will return the Digit value at "CountFromLowest".
// If number is 48230 and CountFromLowest is 2. It will return 3.
// 2nd digit from the lowest is 3.
int GetDigit(const int number, const int CountFromLowest){
    // Remainder by 10^CountFromLowest.
    // Divide by 10^(CountFromLowest - 1)
    int digit = number % (int) pow(10, CountFromLowest);
    digit = digit / (int) pow(10, CountFromLowest - 1);

    return digit;
}

// Time Complexity is (Number of Digits) * Log(Number of Digits)
// We loop through all the decimal digits of an input integer.
// During each loop, we use c++ library "pow" which calculates in
// log(exponent) time. For our worst exponent is the number of digits.

int ReverseInteger(const signed int input){
    const int DigitCount = FindDigitCount(input);

    int Reversed = 0;
    // Loop from the lowest digit.
    for(int i = 1; i <= DigitCount; i ++){
        int digit = GetDigit(input, i);
        digit = digit * (int) pow(10, DigitCount - i);
        Reversed += digit;
    }

    // If overflow happened, the sign will change.
    if((input > 0 && Reversed > 0) || (input < 0 && Reversed < 0))
        return Reversed;
    else
        return 0;
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
    
    input = 430;
    output = 34;
    Tester(3, "Lowest Digit as 0", input, output);

    input = 1927694925;
    output = 0;
    Tester(4, "Positive Overflow",input, output);
    
    input = -1927694925;
    output = 0;
    Tester(5, "Negative Overflow",input, output);
}