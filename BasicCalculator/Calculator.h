#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include "CalcTree.h"

using namespace std;

class Calculator{
	CalcTree* m_tree;

	bool BracketCounter(string a_input);
	void ParseTree(CalcTree* a_tree, vector<string>* a_inputs, int& index);
	long double CalculateTree();

public:
	Calculator();
	~Calculator();
	long double Calculate(string a_input);
};

#endif