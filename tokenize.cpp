#include "tokenize.hpp"

ASTTree::ASTTree() {
	root = nullptr;
}

ASTTree::ASTTree(Expression* rootNode) {
	root = copyTree(rootNode);
}

ASTTree::~ASTTree() {
	postOrderDelete(root);
}

Expression* ASTTree::copyTree(Expression* node) {
	if (node == nullptr) {
		return nullptr;
	}

	Expression* newNode = new Expression();

	newNode->boolean = node->boolean;
	newNode->type = node->type;
	newNode->number = node->number;
	newNode->stringValue = node->stringValue;
	
	for (auto i : node->children) {
		newNode->children.push_back(copyTree(i));
	}

	return newNode;
}

void ASTTree::postOrderDelete(Expression* node) {

	if (node == nullptr) {
		return;
	}
	for (auto i : node->children) {
		postOrderDelete(i);
	}

	delete node;
}

//Tokenize input string
listType toTokenForm(std::istream& in) {

	//Tokenized input
	listType tokenized = {};
	std::string currToken;

	while (in >> currToken) {
		//If a '(' and another token are right next to each other
		//Split them up, add the '(' token, and move on
		int subStrStart = 0;
		int subStrEnd = 0;
		for (std::size_t i = 0; i < currToken.size(); i++) {
			if (currToken[i] == '(' || currToken[i] == ')') {
				if (i != 0 && subStrEnd != 0) {
					tokenized.push_back(currToken.substr(subStrStart, subStrEnd));
				}
				tokenized.push_back(currToken.substr(i, 1));
				subStrStart = i + 1;
				subStrEnd = 0;
			}
			else if (currToken[i] == ';') {
				std::string dummy;
				std::getline(in, dummy);
				break;
			}
			else {
				subStrEnd++;
			}
		}

		std::string endString = currToken.substr(subStrStart);
		if (endString != "" && endString[0] != ';') {
			tokenized.push_back(endString);
		}
	}
	
	if (tokenized.size() == 1) {
		throw std::runtime_error("Error: Invalid Expression. Could not parse");
	}

	return tokenized;
}

Expression* readTokens(listType & tokens) {
	std::string currToken = tokens.front();
	tokens.pop_front();

	if (currToken == "(") {
        int atomSize = tokens.size();
        Expression* AST = readTokens(tokens);
        
		//Read in children nodes from here on
		while (tokens.size() > 0 && tokens.front() != ")") {
			AST->children.push_back(readTokens(tokens));
		}
		
		if (tokens.size() == 0 || atomSize == tokens.size()) {
            tokens.clear();
            AST->boolean = true;
            AST->stringValue = "Error";
            return AST;
		}
		tokens.pop_front();
		return AST;
	}
	if (currToken == ")") {
        tokens.clear();
		Expression* Error = new Expression(true);
		Error->stringValue = "Error";
		return Error;
	}
	//Return the children of a parent
	Expression* atom = atomize(currToken);
	if (atom->boolean && atom->stringValue == "Error") {
		tokens.clear();
	}
	return atom;
}

Expression* atomize(std::string token) {
	Expression* AST = new Expression();

	//If token is a number, atomize to number otherwise 
	//return an atomized string
	if (isNumber(token)) {
		AST->type = Number;
		//Convert string to long
		AST->number = stod(token);
		AST->stringValue = format(AST->number);
	}
	else if (token == "True") {
		AST->type = Boolean;
		AST->boolean = true;
		AST->stringValue = token;
	}
	else if (token == "False") {
		AST->type = Boolean;
		AST->boolean = false;
		AST->stringValue = token;
	}
	else {
		AST->type = Symbol;
		if (isdigit(token[0])) {
            AST->boolean = true;
            AST->stringValue = "Error";
            return AST;
		}
		AST->stringValue = token;
	}

	return AST;
}

bool isNumber(std::string String) {

	bool decimalInString = false;
	bool eInString = false;

	//Check single character possiblilties
	if (String.size() == 1 && !isdigit(String[0])) {
		return false;
	}
    if (String.size() > 1 && String.substr(0,2) == "-e") {
        return false;
    }

	//Look at each character of a string to determine if it's a number
	//Look for negative signs, '.'
	for (unsigned i = 0; i < String.size(); i++) {
		if (String[i] == '-') {
			if (i != 0 && String[i - 1] != 'e') {
				return false;
			}
		}
		else if (String[i] == '.') {
			if (decimalInString) {
				return false;
			}
			decimalInString = true;
		}
		else if (String[i] == 'e') {
			if (eInString) {
				return false;
			}
			eInString = true;
		}
		else if (!isdigit(String[i])) {
			return false;
		}
	}
	return true;
}