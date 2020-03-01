/******************************************************************************
Author: CJ Kim
Date: 2/29/2020

Title: Implement strStr
Explain: Given two inputs called "haystack" and "needle".
         Task is to return the index of needle in haystack.
         Index of first occurrence.
         Return -1 when not found, return 0 when needle is an empty string.
         
         Example:
         Input : "hello", "ll"
         Output : 2
*******************************************************************************/

#include <iostream>
#include <string>

using namespace std;


void String_toLower(string& input){
    for(int i = 0; i < input.size(); i ++){
        input[i] = tolower(input[i]);
    }
}

// Not specified in the problem, but in this program, we will make this,
// NOT-case sensitive. Aka, "Aba" will be treated the same as "aba".
// Haystack: "Aba", needle: "ab", output: 0.

// Time Complexity is the Number of Characters in Haystack.

int strStr(string haystack, string needle){
    if(needle == "") return 0;

    String_toLower(haystack);
    String_toLower(needle);

    // Loop through entire haystack characters, and compare those characters
    // with currently looking needle character.
    int NeedlePointer = 0;
    int NeedleIndex = 0;
    for(int i = 0; i < haystack.size(); i ++){
        if(haystack[i] == needle[NeedlePointer]){
            // When it's first time seeing identical char, we keep the record of its index.
            if(NeedlePointer == 0){
                NeedleIndex = i;
            }

            // Keep checking next char.
            NeedlePointer ++;

            // Once I reach the size of the Needle without resetting the Pointer,
            // we have found the match. So return the index value.
            if(NeedlePointer == needle.size()){
                return NeedleIndex;
            }
        }else{
            NeedlePointer = 0;
        }
    }

    // If "NeedleIndex" was not returned during for-loop and got to this point,
    // then there was no "Needle" found in the "Haystack". Return not found.
    return -1;
}

void Tester(const int TestNum, const string Memo, const string haystack, const string needle, const int output){
    cout << "#" << TestNum << " " << Memo << "            ";
    if(strStr(haystack, needle) == output){
        cout << "Passed" << endl;
    }else{
        cout << "Failed" << endl;
    }
}

int main(){
    Tester(1, "Default", "hello", "ll", 2);
    Tester(2, "Capitalized", "HELLO", "ll", 2);
    Tester(3, "Uncapitalized", "hello", "LL", 2);
    Tester(4, "Not Found #1", "aaaaa", "ba", -1);
    Tester(5, "Not Found #2", "iloveyou", "loves", -1);
    Tester(6, "Needle is Larger", "YOU", "yours", -1);
}