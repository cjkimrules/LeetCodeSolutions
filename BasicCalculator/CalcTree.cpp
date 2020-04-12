
#include "CalcTree.h"

// There are 4 types
// 1. Number
// 2. +, - (Superior)
// 3. x, / (Inferior)
// 4. SubTree (Any calculation within Brackets)
CalcNode::CalcNode(long double a_val, string a_sym, CalcTree* a_subTree){
	m_val = a_val;
	m_symbol = a_sym;
	m_subTree = a_subTree;

	m_parent = nullptr;
	m_left = nullptr;
	m_right = nullptr;
}

CalcNode::~CalcNode(){
	if(m_subTree != nullptr){
		delete m_subTree;
	}
}

bool CalcNode::isNumber(){
	return !isSymbol() && !isSubTree();
}

bool CalcNode::isSymbol(){
	return !m_symbol.empty();
}

bool CalcNode::isSubTree(){
	return m_subTree != nullptr;
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

CalcTree::CalcTree(){
	m_root = nullptr;
}

CalcTree::~CalcTree(){
	Destroy();
}


/*
 * 1. For Number and SubTree,
 *			Find its pair. Empty spot is on the right side, because all subtrees are
 *			pushed to the left. If there's no root, it becomes the root.
 *
 * 2. For +, -
 * 			The entire tree becomes the left child of the +, - (aka. +, - becomes root)
 *
 * 3. For *, /
 *			If the root is a number, *, / becomes the root.
 *			The number becomes left child of the root.
 *
 *			If the root is + or -, it becomes the right child of the root.
 *			All right subtree becomes left child of *, /.
 *
 *			If the root is * or /, it becomes the root. (because for division, order matters)
 *			The entire tree becomes left child of the root.
 *
 * !!! For symbol, you must've had number or another symbol already as root.
 *		It is impossible to have symbol being added to the tree first.
 */

void CalcTree::Add_TreeBecomesLeftSubTree(CalcNode* a_newRoot){
	CalcNode* oldRoot = m_root;

	m_root = a_newRoot;
	m_root->m_left = oldRoot;
	oldRoot->m_parent = m_root;
}

void CalcTree::Add_ReplaceRightSubTree(CalcNode* a_newNode){
	CalcNode* oldRightSubTree = m_root->m_right;

	m_root->m_right = a_newNode;
	m_root->m_right->m_left = oldRightSubTree;
	oldRightSubTree->m_parent = m_root->m_right;
}

void CalcTree::Add_FindNumberPair(CalcNode* a_newNumber){
	// It's guaranteed that the empty spot will be on the right-most.
	// Iterate through the (height of the tree). Log of N time complexity.
	// Because both (+,-) and (*,/) cases, we push down subtrees to the left child,
	// so we know right child will be where the pair will be put.
	if(m_root == nullptr){
		m_root = a_newNumber;
		return;
	}

	CalcNode* current = m_root;

	while(current->m_right != nullptr){
		current = current->m_right;
	}

	current->m_right = a_newNumber;
	current->m_right->m_parent = current;
}

void CalcTree::Add(long double a_num, string a_symbol, CalcTree* a_subTree){
	CalcNode* newNode = new CalcNode(a_num, a_symbol, a_subTree);

	// 1. +, - (Superior)
	if(a_symbol == "+" || a_symbol == "-"){
		Add_TreeBecomesLeftSubTree(newNode);
	}
	// 2. x, / (Inferior)
	else if(a_symbol == "*" || a_symbol == "/"){
		if(m_root->isNumber() || m_root->isSubTree()){
			Add_TreeBecomesLeftSubTree(newNode);
		}else if(m_root->isSymbol() && (m_root->m_symbol == "*" || m_root->m_symbol == "/")){
			Add_TreeBecomesLeftSubTree(newNode);
		}else{
			Add_ReplaceRightSubTree(newNode);
		}
	}
	// 3. Number / SubTree for Brackets
	else{
		Add_FindNumberPair(newNode);
	}
}


long double CalcRecursion(CalcNode* a_base){
	if(a_base->isNumber()){
		return a_base->m_val;
	}

	if(a_base->m_symbol == "+"){
		return CalcRecursion(a_base->m_left) + CalcRecursion(a_base->m_right);
	}else if(a_base->m_symbol == "-"){
		return CalcRecursion(a_base->m_left) - CalcRecursion(a_base->m_right);
	}else if(a_base->m_symbol == "*"){
		return CalcRecursion(a_base->m_left) * CalcRecursion(a_base->m_right);
	}else if(a_base->m_symbol == "/"){
		return CalcRecursion(a_base->m_left) / CalcRecursion(a_base->m_right);
	}else{
		// Here, subTree.
		return CalcRecursion(a_base->m_subTree->m_root);
	}
}

long double CalcTree::Compute(){
	return CalcRecursion(m_root);
}

void CalcTree::Destroy(){
	if(m_root == nullptr) return;

	queue<CalcNode*> q;
	q.push(m_root);

	while(!q.empty()){
		CalcNode* current = q.front();

		if(current->m_left != nullptr){
			q.push(current->m_left);
		}
		if(current->m_right != nullptr){
			q.push(current->m_right);
		}

		q.pop();
		delete current;
	}

	m_root = nullptr;
}