/******************************************************************************
Author: CJ Kim
Date: 4/3/2020
Title: Number to English
Explain: Given an integer less than 2^31 - 1.
         Convert that number into English Text.

		 Input: 123
		 Output: "One Hundred Twenty Three"
*******************************************************************************/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Time Complexity is Linear (we loop through each digit twice)
// Memory Space is N. (we use arraylist storing from lowest digit and print backwards)

// 0 to 2^31-1 (2147483647)
// Billion is the max word we need.

string FirstDigit(int a){
    switch(a){
        case 1:
            return "One";
        case 2:
            return "Two";
        case 3:
            return "Three";
        case 4:
            return "Four";
        case 5:
            return "Five";
        case 6:
            return "Six";
        case 7:
            return "Seven";
        case 8:
            return "Eight";
        case 9:
            return "Nine";
        default:
            return "DEADBEEF";
    }
}

string TenthDigit(int a){
    switch(a){
        case 1:
            return "Ten";
        case 2:
            return "Twenty";
        case 3:
            return "Thirty";
        case 4:
            return "Forty";
        case 5:
            return "Fifty";
        case 6:
            return "Sixty";
        case 7:
            return "Seventy";
        case 8:
            return "Eighty";
        case 9:
            return "Ninety";
        default:
            return "DEADBEEF";
    }
}

// 11 ~ 19
string SpecialCase(int a){
    switch(a){
        case 11:
            return "Eleven";
        case 12:
            return "Twelve";
        case 13:
            return "Thirteen";
        case 14:
            return "Fourteen";
        case 15:
            return "Fifteen";
        case 16:
            return "Sixteen";
        case 17:
            return "Seventeen";
        case 18:
            return "Eighteen";
        case 19:
            return "Nineteen";
        default:
            return "DEADBEEF";
    }
}

// 0 ~ 10, 20 ~ 99
string GeneralCase(int a){
    string ret = "";

    int HighDigit = a / 10;
    int LowDigit = a % 10;

    if(HighDigit != 0){
        ret += TenthDigit(HighDigit);
    }

    if(HighDigit != 0 && LowDigit != 0){
        ret += " ";
    }

    if(LowDigit != 0){
        ret += FirstDigit(LowDigit);
    }
    return ret;
}

// Every 2 digits need special care since 12 is not One Ten Two in English.
// It's Twelve. It's best to divide each section into 1000.
string NumToEng(uint32_t Number){
    vector<string> Nums;

    string EveryThousand[] = {"", "Thousand", "Million", "Billion"};
    int Power = 0;

    while(Number){
        Nums.push_back(EveryThousand[Power]);

        // First two digits..
        int low2 = Number % 100;
        Number /= 100;

        if(low2 > 10 && low2 < 20){
            Nums.push_back(SpecialCase(low2));
        }else{
            Nums.push_back(GeneralCase(low2));
        }

        int Hundredth = Number % 10;
        Number /= 10;

        if(Hundredth != 0){
            Nums.push_back("Hundred");
            Nums.push_back(FirstDigit(Hundredth));
        }

        Power ++;
    }



    string ret = Nums[Nums.size() - 1];
    for(int i = Nums.size() - 2; i >= 0; i --){
        if(Nums[i] != ""){
            ret += " ";
        }
        ret += Nums[i];  
    }

    return ret;
}


void Tester(const int TestNum, const string Memo, uint32_t input, string output){
    cout << "#" << TestNum << " " << Memo << "            ";

    if(NumToEng(input) == output){
        cout << "Passed" << endl;
    }else{
        cout << "Failed" << endl;
    }
}

int main(){
    Tester(1, "1 Digit", 1, "One");
    Tester(2, "2 Digits", 12, "Twelve");
    Tester(3, "3 Digits", 123, "One Hundred Twenty Three");
    Tester(4, "3 Digits with 0", 103, "One Hundred Three");
    Tester(5, "4 Digits", 1004, "One Thousand Four");
    Tester(6, "5 Digits", 12345, "Twelve Thousand Three Hundred Forty Five");
    Tester(7, "7 Digits", 1234567, "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven");
    Tester(8, "10 Digits", 1234567891, "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One");
    Tester(9, "Number with 0", 1234567890, "One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety");
}
