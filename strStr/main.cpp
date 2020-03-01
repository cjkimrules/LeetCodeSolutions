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

// Time Complexity is the (Size of Haystack) * (Size of Needle).
// We are looping through only the Haystack, so it may seem like the time complexity is
// (Size of Haystack), but that's not true for the worst case.
// When there are many repetitive chars in Haystack (refer #9 test case),
// we have to roll back Haystack Pointer (aka, "i" in for-loop), almost the size of needle.
// Worst case, we might have to loop back for all characters in haystack, so the worst of worst
// is (Size of Haystack) * (Size of Needle).

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
            // When the characters turns out mismatched. We still have to make sure
            // they are not repetitive letters. What I mean by that is
            // haystack: "llove", needle: "love", output: 1.
            // But it will output -1, not found, because once second "l" in haystack
            // and "o" in needle mismatched, it proceeds. We have to reset haystack's pointer as well.
            if(NeedlePointer != 0){
                NeedlePointer = 0;
                i = NeedleIndex;
            }
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
    Tester(7, "Repetitive #1", "llovesushi", "love", 1);
    Tester(8, "Repetitive #2", "lolovesushi", "love", 2); 
    Tester(9, "Repetitive #3", "aaaabbb", "aaab", 1); 
}