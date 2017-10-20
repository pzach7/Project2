#include "interpreter.hpp"

Expression ifResult(expressionList stack) {
    if (stack.size() == 3) {
        bool operatorResult = stack.front().boolean;
        if (stack.front().type == Boolean) {
            stack.pop_front();
            if ((stack.front().type == Boolean || 
                stack.front().type == Number) && operatorResult) {
                return stack.front();
            }
            else if ((stack.back().type == Boolean ||
                stack.back().type == Number) && !operatorResult) {
                return  stack.back();
            }
        }
        else { //Improper type
            throw InterpreterSemanticError
            ("Error: Error during evaluation of 'if'");
        }
    }
    else { //incorrect number of arguments
        throw InterpreterSemanticError
        ("Error: Invalid number of arguments for 'if'");
    }
}

Expression drawResult(expressionList stack) {
    if (stack.size() != 0) {
        Expression result = Expression();
        //Loop through stack for children to draw, check for
        //correct type, assign them to child of result
        for (auto j : stack) {
            if (j.type == Point) {
                Expression * child = new Expression (j.start);
                result.children.push_back(child);
            }
            else if (j.type == Line) {
            Expression * child = new Expression (j.start, j.centEnd);
                result.children.push_back(child);
            }
            else if (j.type == typeArc) {
                Expression * child = new Expression (j.centEnd, j.start, j.angle);
                result.children.push_back(child);
            }
            else { //clean up children, throw error
                for (auto k : result.children) {
                    delete k;
                }
                throw InterpreterSemanticError
                ("Error: Invalid type of argument for special form 'draw'");
            }
        }
        return result;
    }
    throw InterpreterSemanticError
    ("Error: Invalid number of arguments for special form 'draw'");
}

Expression beginResult(expressionList stack) {
    if (stack.size() == 0) { 
        throw InterpreterSemanticError
        ("Error: Error during evaluation of 'begin'");
    }
    //If draw was used, save the graphics that are to be drawn
    unsigned int size = 1;
    for (auto j : stack) {
        if (j.type == None && j.children.size() != 0 
            && stack.size() > size) {
            Expression * child = new Expression(j);
            stack.back().children.push_back(child);
        }
        size++;
    }
    return stack.back(); //Evaluate to the last atom
}

Interpreter::Interpreter() {
	tree = ASTTree();
	env = Environment();
}

Interpreter::~Interpreter() {

}

void Interpreter::setEnv(Environment newEnv) {
    env = newEnv;
}

Environment Interpreter::getEnv() {
    return env;
}

bool Interpreter::parse(std::istream & expression) noexcept {
	try {
        //Delete previous tree
        
        //Tokenize the list
		listType&& tokenList = toTokenForm(expression);
		if (tokenList.size() == 0) {
			throw std::runtime_error
			("Error: Invalid Expression. Could not parse");
		}
        //Create AST out of tokens
		Expression* tokens = readTokens(tokenList);
		if (tokenList.size() != 0 || (tokens->boolean && tokens->stringValue == "Error")) {
            //Delete original, copied AST
            tree.postOrderDelete(tokens);
			throw std::runtime_error
			("Error: Invalid Expression. Could not parse");
		}
        
		//Copy the newly created tree to this object
		tree.root = tree.copyTree(tokens);
        
        //Delete orginal, copied AST
        tree.postOrderDelete(tokens);
        
		return true;
	}
	catch (std::runtime_error) {
		return false;
	}
}

Expression Interpreter::eval() {
    Expression result = interEval(tree.root);
    
    //Result shouldn't be a symbol
    if (result.type == Symbol) {
        throw InterpreterSemanticError
        ("Error: Error during evaluation");
    }
    return result;
}

Expression Interpreter::interEval(Expression* node) {
	expressionList stack = {};
	for (auto i : node->children) {
		Expression newEx = interEval(i);
		stack.push_back(newEx);
	}

	if (node->type == Symbol) {
		if (node->stringValue == "define") {
            if (stack.size() == 2 && stack.front().type == Symbol 
                && stack.back().type != None 
                && stack.back().type != Symbol) {
                env.update(stack.front().stringValue, stack.back());
                //Evaluates to what the new mapping is defined as
                return stack.back();
            }
            else { //Define type or argument error
                throw InterpreterSemanticError
                ("Error: Error during evaluation of 'define'");
            }
		}
		else if (node->stringValue == "if") {
			return ifResult(stack);
		}
		else if (node->stringValue == "begin") {
			return beginResult(stack);
		}
        else if (node->stringValue == "point") {
            return point(stack);
        }
        else if (node->stringValue == "line") {
            return line(stack);
        }
        else if (node->stringValue == "arc") {
            return arc(stack);
        }
        else if (node->stringValue == "draw"){
            return drawResult(stack);
        }
        else { //Otherwise look it in the environment
			Expression result = env.lookup(node->stringValue, stack);
			if (result.type == None) {
				result.type = node->type;
				result.stringValue = node->stringValue;
			}
			return result;
		}
	} 
	else if (node->type == Boolean) {
		return Expression(node->boolean);
	}
	else if (node->type == Number) {
		return Expression(node->number);
	}
	//Return empty node if node type isn't valid
	return Expression();
}


