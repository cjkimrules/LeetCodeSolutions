/******************************************************************************
Author: CJ Kim
Date: 4/13/2020
Title: Dungeon Game
Explain: m x n Dungeon.
		 Knight is at left-top.
		 Princess is at right-bottom.
		 Some rooms do dmg, some do healing.
		 Knight is only allowed to move right or down.
		 Find minimum required HP to get to the Princess
*******************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

// Imagine this case,
// 0  -1  -2
// x  x   4
// x  x   2
//
// Assume we must go right, right, down, down. The sum is 3.
// We may think we have the positive value, so we can say HP can start with minimum, 1.
// This is not true, because there is one time (top-right), where -3 will apply to HP.
// In order to survive that, we need HP of 4.
//
// We are not looking for the total sum of each cell Knight is visiting.
// We care for the lowest possible sum, and negate it and add 1. (-3 => 4).


// Time complexity is (m + n)! / (m! * n!)
// The worst case, this finds all possible paths and compare each numbers.
// Finding all paths in m x n grid is combination method.
// (m + n) chooses (m or n).
// (m + n)! / (m! * n!), yeah it's exponential.

int FindSumRecursive(vector<vector<int>> const& a_dungeon, int a_x, int a_y, int a_total, int a_worst){
	int currentTile = a_dungeon[a_y][a_x];

	int worst = a_worst;
	if(currentTile < 0){
		worst = min(a_total + currentTile, a_worst);
	}

	// Recursion condition case requires some calculations beforehand.
	if((a_y == a_dungeon.size() - 1) && (a_x == a_dungeon[0].size() - 1)){
		return worst;
	}

	int total = a_total + currentTile;

	// If I'm allowed to move in that direction, then do so.
	int right = numeric_limits<int>::min();
	int down = numeric_limits<int>::min();

	if(a_x < a_dungeon[0].size() - 1){
		right = FindSumRecursive(a_dungeon, a_x + 1, a_y, total, worst);
	}
	if(a_y < a_dungeon.size() - 1){
		down = FindSumRecursive(a_dungeon, a_x, a_y + 1, total, worst);
	}

	return max(right, down);
}

// Dungeon vector => [column][row]
int RequiredMinHP(vector<vector<int>> const& a_dungeon){
	if(a_dungeon.size() == 0 || a_dungeon[0].size() == 0){
		return -1;
	}

	int sum = FindSumRecursive(a_dungeon, 0, 0, 0, 0);
	if(sum < 0){
		return -sum + 1;
	}else{
		return 1;
	}
}

void CreateDungeon(vector<vector<int>>& a_dungeon, int a_x, vector<int>& a_val){
	a_dungeon.clear();

	for(int i = 0; i < a_val.size() / a_x; i ++){
		vector<int> v;

		for(int k = 0; k < a_x; k ++){
			v.push_back(a_val[i * a_x + k]);
		}

		a_dungeon.push_back(v);
	}
}

void Tester(const int a_testNum, const string a_memo, vector<vector<int>>& input, int output){
    cout << "#" << a_testNum << " " << a_memo << "            ";

    if(RequiredMinHP(input) == output){
        cout << "Passed" << endl;
    }else{
        cout << "Failed" << endl;
    }
}

int main(){
	vector<vector<int>> dungeon;
	vector<int> dungeon_raw;

	dungeon_raw.assign({-2, -3, 3, -5, -10, 1, 10, 30, -5});
	CreateDungeon(dungeon, 3, dungeon_raw);
	Tester(1, "3 x 3", dungeon, 7);

	dungeon_raw.assign({1, 5, 7, 2, 3, 1, 0, 6, 3});
	CreateDungeon(dungeon, 3, dungeon_raw);
	Tester(1, "3 x 3. All positive", dungeon, 1);

	// You can test more here! I'm lazy!
}
