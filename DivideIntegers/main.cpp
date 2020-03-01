/******************************************************************************
Author: CJ Kim
Date: 2/29/2020

Title: Divide Two Integers
Explain: Given two inputs called "Dividend" and "Divisor".
         Task is to return the number Dividend / Divisor without using
         (Multiplication), (Division), (Mod).
         
         Example:
         Input : 10, 3
         Output : 3
*******************************************************************************/

#include <iostream>
#include <string>

using namespace std;


// Time Complexity is (Size of Quotient).

int divide(int dividend, int divisor){
    // We are forbidden to use *, /, %. But we can still use +, -, bit-wise.
    // Mutiplication is multiple steps of addition.

    // Calculate what the output sign will be, and make both dividend and divisor positive.
    bool OutputIsPositive = true;
    if(dividend < 0){
        OutputIsPositive = !OutputIsPositive;
        dividend *= -1;
    }
    if(divisor < 0){
        OutputIsPositive = !OutputIsPositive;
        divisor *= -1;
    }

    int result = 0;
    while(dividend >= 0){
        dividend -= divisor;
        result ++;
    }

    // We always drop decimal points, but above while loop always rounds up.
    // So remove 1 from "result".
    result --;

    return OutputIsPositive ? result : -result;
}

void Tester(const int TestNum, const string Memo, const int dividend, const int divisor, const int output){
    cout << "#" << TestNum << " " << Memo << "            ";
    if(divide(dividend, divisor) == output){
        cout << "Passed" << endl;
    }else{
        cout << "Failed" << endl;
    }
}

int main(){
    Tester(1, "No Remainder", 12, 3, 4);
    Tester(1, "Positive, Positive", 10, 3, 3);
    Tester(1, "Positive, Negative", 10, -3, -3);
    Tester(1, "Negative, Positive", -10, 3, -3);
    Tester(1, "Negative, Negative", -10, -3, 3);
}