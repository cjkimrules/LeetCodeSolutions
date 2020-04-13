#ifndef _CALCTREE_H_
#define _CALCTREE_H_

#include <vector>
#include <cmath>
#include <cctype>
#include <string>
#include <queue>
#include <iostream>

using namespace std;

class CalcTree;

class CalcNode{
public:
	long double m_val;
	string m_symbol;
	CalcTree* m_subTree;

	CalcNode* m_parent;
	CalcNode* m_left;
	CalcNode* m_right;

	CalcNode(long double a_val, string a_sym, CalcTree* a_subTree);
	~CalcNode();
	bool isNumber();
	bool isSymbol();
	bool isSubTree();
};


class CalcTree{
	void Add_TreeBecomesLeftSubTree(CalcNode* a_newRoot);
	void Add_ReplaceRightSubTree(CalcNode* a_newNode);
	void Add_FindNumberPair(CalcNode* a_newNumber);

public:
	CalcNode* m_root;

	CalcTree();
	~CalcTree();
	void Add(long double a_num, string a_symbol, CalcTree* a_subTree);
	long double Compute();
	void Destroy();
};

#endif