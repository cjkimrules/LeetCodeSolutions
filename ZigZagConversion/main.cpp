/******************************************************************************
Author: CJ Kim
Date: 2/28/2020

Title: ZigZag Conversion
Explain: Given an input string, divide that string into down-up zigzag shape,
         then output a string by rows. Number of rows will also be an input.
         
         Example:
         Input : YOUSHALLNOTPASS, 4
         Y  L  A
         O AL PS
         UH NT S
         S  O

         Output : YLAOALPSUHNTSSO
*******************************************************************************/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/* A few things to note:
 * When the input says 4, there will be 4 rows.
 * And there is a pattern, down-up, down-up, down-up, etc.
 * If we slice each "section", then we can immediately see that
 * the top and bottom letters are always 1 each at any # of rows.
 * Total number of letters in each section = 2 * (rows) - 2
 * 
 * 1st row : 1st letter
 * 2nd row : 2nd letter + last letter in the section
 * 3rd row : 3rd letter + 2nd last letter in the section
 * etc...
 */

// The time complexity is Size of "input" string.
// It loops through the entire input string twice.

string* ZigZagConversion(const string* input, const int RowSize){
    vector<vector<char>> Letters(RowSize);

    // We will loop through all the characters in the "input" string.
    // Since we can calculate the size of each "Section", we will divide
    // "input" string into Sections.
    int SectionPointer = 0;
    const int SectionSize = 2 * RowSize - 2;
    for(int i = 0; i < input->size(); i ++){
        if(SectionPointer < RowSize){
            // This is when we are moving downwards in zigzag.
            Letters[SectionPointer].push_back((*input)[i]);
        }else{
            // This is when we are moving upwards in zigzag.
            
            /* Index during one section when RowSize = 4
             * 0
             * 1   5
             * 2 4
             * 3
             * 
             * For 0-3, we can use SectionPointer.
             * For 4-5, we will use 2 * RowSize - SectionPointer - 2.
             */
            Letters[2 * RowSize - SectionPointer - 2].push_back((*input)[i]);
        }

        SectionPointer ++;
        if(SectionPointer == SectionSize)
            SectionPointer = 0;
    }

    // Now loop through all Letters BY ROW, and add them to a string.
    string* output = new string();
    for(vector<char> row : Letters){
        for(char letter : row){
            (*output) += letter;
        }
    }

    return output;
}

void Tester(const int TestNum, const string Memo, const string* input, const int rows, const string* output){
    cout << "#" << TestNum << " " << Memo << "            ";
    if(*ZigZagConversion(input, rows) == *output){
        cout << "Passed" << endl;
    }else{
        cout << "Failed" << endl;
    }
}

int main(){
    string input = "PAYPALISHIRING";
    string output = "PAHNAPLSIIGYIR";
    Tester(1, "3 Rows", &input, 3, &output);

    input = "YOUSHALLNOTPASS";
    output = "YLAOALPSUHNTSSO";
    Tester(2, "4 Rows", &input, 4, &output);
    
    input = "PAYPALISHIRING";
    output = "PINALSIGYAHRPI";
    Tester(3, "4 Rows", &input, 4, &output);

    input = "EVERYDAYLIFEISTHEPROBLEM";
    output = "ELEVYIHPMEAFTRERDESOLYIB";
    Tester(4, "5 Rows", &input, 5, &output);
}