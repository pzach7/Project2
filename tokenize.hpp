#include <fstream>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "expression.hpp"

typedef std::string symbol;
typedef std::list<std::string> listType;
typedef std::list<Expression*> nodeList;
typedef std::list<Expression> expressionList;

class ASTTree {
public:
	//Default Constructor, creates empty tree
	ASTTree();
	//Constructor, creates AST given root node of existing AST
	ASTTree(Expression* rootNode);
	~ASTTree();

	//Post order traversal of tree
	void postOrderDelete(Expression* node);

	//Head/root of the tree (top node), maybe make private
	Expression* root;

	Expression* copyTree(Expression* node);
};

/**
	Description: Convert an input into a list of individual tokens
	Parameters: An input stream
	Returns: List of individual tokens
*/
listType toTokenForm(std::istream& in);

/**
	Description: Convert an list of tokens into an AST
	Parameters: List of individual tokens
	Returns: An Expression pointer
*/
Expression* readTokens(listType & tokens);

/**
	Description: Convert a string into an AST node
	Parameters: An input stream
	Returns: an Expression pointer
*/
Expression* atomize(std::string token);

bool isNumber(std::string String);
