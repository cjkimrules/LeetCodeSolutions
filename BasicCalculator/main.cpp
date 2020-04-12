/******************************************************************************
Author: CJ Kim
Date: 4/12/2020
Title: Basic Calculator
Explain: Basic Calculator
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
    cout << "Type 'A' for previous calculation" << endl;
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