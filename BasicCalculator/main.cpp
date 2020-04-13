/******************************************************************************
Author: CJ Kim
Date: 4/12/2020
Title: Basic Calculator
Explain: +,-,*,/,(),Ans,sqrt
		 sqrt of negative numbers are not supported by "i", it's NaN.
		 Only allowed bracket is "(" and ")".
		 Other brackets will be taken as unknown.
*******************************************************************************/

#include <iostream>
#include <iomanip>
#include <cctype>
#include <vector>
#include <string>
#include "Calculator.h"

using namespace std;

string StringToLower(string input){
    string output = "";
    for(int i = 0; i < input.size(); i ++){
        output += tolower(input[i]);
    }
    return output;
}

int main(){
    Calculator* calc = new Calculator();

    string input;
    cout << "Type 'h' for help" << endl;
    cout << "> ";
    getline(cin, input);

    while(StringToLower(input) != "quit"){
    	if(StringToLower(input) == "h"){
    		// Display help
    		cout << "====================== HELP ======================" << endl;
    		cout << "(Note: Capitalization of letters are ignored.)" << endl;
    		cout << "1. 'quit' to exit." << endl;
    		cout << "1. 'h' for help." << endl;
    		cout << "2. 'a' for previous calculation (aka 'Ans')" << endl;
    		cout << "3. 'sqrt' for square root." << endl;
    		cout << "==================================================" << endl;
    		cout << "" << endl;
    	}else{
	        cout << calc->Calculate(input) << endl;
	        cout << endl;
    	}

    	// Next input
        cout << "> ";
        getline(cin, input);
    }

    delete calc;
}