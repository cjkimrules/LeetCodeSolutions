
#include "Calculator.h"

bool Calculator::BracketCounter(string a_input){
	// For Opening, Count + 1
	// For Closing, Count - 1
	int count = 0;

	for(int i = 0; i < a_input.size(); i ++){
		if(a_input[i] == '('){
			count ++;
		}else if(a_input[i] == ')'){
			count --;

			// If Count ever becomes negative, then we know
			// there were more closing brackets then opening so far,
			// which we don't have a pair, and not allowed.
			// example : (1 + 2) + 2)
			if(count < 0){
				return false;
			}
		}
	}

	if(count == 0){
		return true;
	}
	
	return false;
}

Calculator::Calculator(){
	m_tree = new CalcTree();
	m_prevResult = 0;
}

Calculator::~Calculator(){
	delete m_tree;
}

bool isCharNumber(char c){
	int i = c - '0';

	if(i >= 0 && i <= 9){
		return true;
	}
	return false;
}

bool isCharSymbol(char c){
	if(c == '+' || c == '-' || c == '*' || c == '/'){
		return true;
	}
	return false;
}

// Return nullptr if the input string cannot be parsed.
vector<string>* ParseString(string a_input){
	// Remove all empty spaces
	string input = "";
	for(int i = 0; i < a_input.size(); i ++){
		if(a_input[i] != ' '){
			input += a_input[i];
		}
	}

	vector<string>* ret = new vector<string>();
	
	// We know expression always starts with number.
	// Also we know size of numbers is always 1 greater than the size of symbols.
	// '(' or ')' has no effect.
	bool isNumber = true;

	int pointer = 0;
	while(pointer < input.size()){
		string s = "";

		if(input[pointer] == '(' || input[pointer] == ')'){
			s += input[pointer];
			ret->push_back(s);
			pointer ++;
			continue;
		}

		if(isNumber){
			// Consider previous calculation first
			if(input[pointer] == 'A' || input[pointer] == 'a'){
				s += input[pointer];
				pointer ++;
			}
			else if(input[pointer] == 'S' || input[pointer] == 's'){
				string sub = input.substr(pointer, 4);
				for(int i = 0; i < sub.size(); i ++){
					sub[i] = tolower(sub[i]);
				}

				if(sub == "sqrt"){
					s = sub;
					pointer += 4;
					// Flip it here to cancel out the flip later on.
					// Because "sqrt" is treated like a number, but we still expect
					// to receive another number following it.
					isNumber = !isNumber;
				}else{
					delete ret;
					return nullptr;
				}
			}
			// When it was an actual number
			else{
				// In a numbering system, there can only be one dot.
				// ex) 12.4562.23 <- does not work.
				bool isDotAllowed = true;

				// Numbers can be anything from "1", "2.4", "-0.45", ".89"
				// "-" has to be distinguished because there is "-" for symbol.
				if(isCharNumber(input[pointer]) || input[pointer] == '.' || input[pointer] == '-'){
					if(input[pointer] == '.'){
						isDotAllowed = false;
					}

					s += input[pointer];
					pointer ++;
				}else{
					delete ret;
					return nullptr;
				}

				while(pointer < input.size() &&
						(isCharNumber(input[pointer]) || (isDotAllowed && input[pointer] == '.'))){
					if(input[pointer] == '.'){
						isDotAllowed = false;
					}

					s += input[pointer];
					pointer ++;
				}
			}
		}else{
			if(isCharSymbol(input[pointer])){
				s += input[pointer];
				pointer ++;
			}else{
				delete ret;
				return nullptr;
			}
		}

		isNumber = !isNumber;
		ret->push_back(s);
	}

    return ret;
}

// This is recursive as well.
// This loops until ")" is detected or reaches the end.
// Once it is reached, return currently created tree (possibly sub-tree).
// Once, returned, add that sub-tree as a CalcNode.
// Create a sub-tree once "(" is detected.
void Calculator::ParseTree(CalcTree* a_tree, vector<string>* a_inputs, int& a_index){
    for(int i = a_index; i < a_inputs->size(); i ++){
    	if(a_inputs->at(i) == "("){
    		CalcTree* subtree = new CalcTree();
    		int index = i + 1;
    		ParseTree(subtree, a_inputs, index);

    		a_tree->Add(0, "", subtree);

    		i = index;
    	}else if(a_inputs->at(i) == ")"){
    		a_index = i;
    		return;
    	}else if(a_inputs->at(i) == "+" || a_inputs->at(i) == "-" ||
    				a_inputs->at(i) == "*" || a_inputs->at(i) == "/" ||
    				a_inputs->at(i) == "sqrt"){
			a_tree->Add(0.0f, a_inputs->at(i), nullptr);
		}else{
			long double num;
			
			if(a_inputs->at(i) == "A" || a_inputs->at(i) == "a"){
				num = m_prevResult;
			}else{
				// If negative number
				if(a_inputs->at(i)[0] == '-'){
					num = -1 * stold(a_inputs->at(i).substr(1));
				}else{
					num = stold(a_inputs->at(i));
				}
			}

			a_tree->Add(num, "", nullptr);
		}
    }
}

long double Calculator::CalculateTree(){
	if(m_tree == nullptr) return 0;

	long double result = m_tree->Compute();
	m_tree->Destroy();

	m_prevResult = result;
	return result;
}

// ParseString is O(n), n = # of chars.
// ParseTree is O(kLog(k)), k = # of keywords.
// CalculateTree is O(k), with k memory space (for recursion stack).
//
// Note that n and k are different because a number "12345" has 5 characters.
// So n = 5, but it's essentially just one number, so k = 1.
// Thus, n and k doesn't really have relations.
//
// Total time complexity is O(n + kLog(k))
// Memory space is k.

long double Calculator::Calculate(string a_input){
	assert(("Bracket doesn't have proper pairing.", BracketCounter(a_input)));

	vector<string>* v = ParseString(a_input);
	if(v == nullptr){
		cout << "Input is not valid." << endl;
		return -1;
	}

	int startIndex = 0;
	ParseTree(m_tree, v, startIndex);

	long double ret = CalculateTree();
	delete v;

	return ret;
}