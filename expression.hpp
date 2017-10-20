#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <list>
#include <limits>
#include <cmath>
#include <tuple>

enum ExpressionType
{
	None,
	Boolean,
	Symbol,
	Number,
    Point,
    Line,
    typeArc,
	//The following three are only for the enviornment
	Procedure, 
	LogicProcedure
};

struct Expression {
public:
	// Default construct an Expression of type None
	Expression();
    ~Expression();
    
    //Copy Constructor
    Expression(const Expression &newExp);

	// Construct an Expression with a single Boolean atom with value
	Expression(bool value);

	// Construct an Expression with a single Number atom with value
	Expression(double value);

	// Construct an Expression with a single Symbol atom with value
	Expression(const std::string & value);
    
    // Construct an Expression with a single Point atom with value
    Expression(std::tuple<double,double> value);

    // Construct an Expression with a single Line atom with starting
    // point start and ending point end
    Expression(std::tuple<double,double> newStart, 
               std::tuple<double,double> end);

    // Construct an Expression with a single Arc atom with center
    // point center, starting point start, and spanning angle angle in radians 
    Expression(std::tuple<double,double> center, 
               std::tuple<double,double> newStart, 
               double newAngle);

	// Equality operator for two Expressions, two expressions are equal if the have the same 
	// type, atom value, and number of arguments
	bool operator==(const Expression & exp) const noexcept;

	ExpressionType type;
	std::string stringValue;
	double number;
	bool boolean;
    //Acts as both start tuple for Arc & Line, and Value for Point
    std::tuple<double, double> start;
    //Acts as center for arc and end value for Line
    std::tuple<double, double> centEnd;
    double angle;
	std::list<Expression*> children;
};

std::string format(double value);

#endif