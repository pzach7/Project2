#include <unordered_map>
#include <math.h>
#include "interpreter_semantic_error.hpp"
#include "tokenize.hpp"

typedef double(*arithmeticProcedure)(expressionList);
typedef bool(*logicProcedure)(expressionList);

struct envNode {

	envNode() {};
	envNode(bool logic);
	envNode(double num);
	envNode(std::string String);
    envNode(std::tuple<double,double> value);
    envNode(std::tuple<double,double> newStart, 
               std::tuple<double,double> end);
    // Construct an Expression with a single Arc atom with center
    // point center, starting point start, and spanning angle angle in radians 
    envNode(std::tuple<double,double> center, 
               std::tuple<double,double> newStart, 
               double newAngle);
	envNode(arithmeticProcedure math);
	envNode(logicProcedure logic);

	ExpressionType type = None;
	double number = -0.0;
	bool boolean = false;
	std::string stringValue= "";
    //Acts as both start tuple for Arc & Line, and Value for Point
    std::tuple<double, double> start = std::make_tuple(-0.0,-0.0);
    //Acts as center for arc and end value for Line
    std::tuple<double, double> centEnd = std::make_tuple(-0.0,-0.0);
    double angle = -0.0;
	arithmeticProcedure aProc = nullptr;
	logicProcedure lProc = nullptr;
};

typedef std::unordered_map<std::string, envNode> envMap;

double add(expressionList numbers);
double mult(expressionList numbers);

//All Binary, non-logic procedures
//since subtraction and negation are indicated by the same '-'
//it does both, included under this section
double subOrNeg(expressionList numbers);
double divide(expressionList numbers);
double sine(expressionList numbers);
double cosine(expressionList numbers);
double arctangent(expressionList numbers);

//All M-ary, logic procedures
bool logicAnd(expressionList logics);
bool logicOr (expressionList logics);

//All binary, logic procedures
bool lessThan(expressionList numbers);
bool lessThanEqual(expressionList numbers);
bool greaterThan(expressionList numbers);
bool greaterThanEqual(expressionList numbers);
bool equal(expressionList numbers);

//All Unary, logic commands
bool logicNot(expressionList logics);

Expression point(expressionList numbers);
Expression line(expressionList points);
Expression arc(expressionList args);

class Environment {
public:
	// Default constructor that implements the 13 lisp operations
	//   and also defines pi
	Environment();
	~Environment();
    int getMapSize();
	//Updates environment variables, returns true if successful
	//Returns false if it already exists
	void update(std::string str, Expression node);
	Expression lookup(std::string str, expressionList list);

private:
	envMap env;
};