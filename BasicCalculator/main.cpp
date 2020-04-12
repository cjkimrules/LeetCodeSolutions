/******************************************************************************
Author: CJ Kim
Date: 2/28/2020
Title: Basic Calculator
Explain: Addition and Subtraction with brackets.
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

static Calculator* calc;

string StringToLower(string input){
    string output = "";
    for(int i = 0; i < input.size(); i ++){
        output += tolower(input[i]);
    }
    return output;
}

int main(){
    calc = new Calculator();

    string input;
    cout << "Type 'quit' to exit" << endl;
    cout << "> ";
    getline(cin, input);

    while(StringToLower(input) != "quit"){
        cout << calc->Calculate(input) << endl;
        cout << endl;

        cout << "> ";
        getline(cin, input);
    }

    delete calc;
}