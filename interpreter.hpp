#include "environment.hpp"

Expression ifResult(expressionList stack);
Expression drawResult(expressionList stack);
Expression beginResult(expressionList stack);

class Interpreter {
public:
	// Default construct an Interpreter with the default environment and an empty AST
	Interpreter();
    ~Interpreter();
    
    void cleanInterpreter();
    
	// Given a vtscript program as a std::istream, attempt to parse into an internal AST
	// return true on success, false on failure
	bool parse(std::istream & expression) noexcept;

	//Helper function interEval(Expression* node) does eval recursively;
	Expression eval();

	// Evaluate the current AST and return the resulting Expression
	// throws InterpreterSemanticError if a semantic error is encountered
	// the exception message string should document the nature of the semantic error 
	Expression interEval(Expression* node);
    
    void setEnv(Environment newEnv);
    
    Environment getEnv();

private:
	//Internal AST tree for interpreter
	ASTTree tree;
	Environment env;
};
