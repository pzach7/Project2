#include "expression.hpp"

// Default construct an Expression of type None
Expression::Expression() {
	type = None;
	stringValue = "None";
	number = -0.0;
	boolean = false;
    start = std::make_tuple(-0.0,-0.0);
    centEnd = std::make_tuple(-0.0,-0.0);
    angle = -0.0;
	children = {};
}

Expression::~Expression() {

}

//Copy Constructor
Expression::Expression(const Expression &newExp) {
    type = newExp.type;
	stringValue = newExp.stringValue;
	number = newExp.number;
	boolean = newExp.boolean;
    start = newExp.start;
    centEnd = newExp.centEnd;
    angle = newExp.angle;
	children = newExp.children;
}

// Construct an Expression with a single Boolean atom with value
Expression::Expression(bool value) {
	type = Boolean;
	if (value) {
		stringValue = "True";
	}
	else {
		stringValue = "False";
	}
	number = -0.0;
	boolean = value;
    start = std::make_tuple(-0.0,-0.0);
    centEnd = std::make_tuple(-0.0,-0.0);
    angle = -0.0;
	children = {};
}

// Construct an Expression with a single Number atom with value
Expression::Expression(double value) {
	type = Number;
	number = value;
	stringValue = format(value);
	boolean = false;
    start = std::make_tuple(-0.0,-0.0);
    centEnd = std::make_tuple(-0.0,-0.0);
    angle = -0.0;
	children = {};
}

// Construct an Expression with a single Symbol atom with value
Expression::Expression(const std::string & value) {
	type = Symbol;
	stringValue = value;
	number = -0.0;
	boolean = false;
    start = std::make_tuple(-0.0,-0.0);
    centEnd = std::make_tuple(-0.0,-0.0);
    angle = -0.0;
	children = {};
}

// Construct an Expression with a single Point atom with value
Expression::Expression(std::tuple<double,double> value) {
    type = Point;
	stringValue = format(std::get<0>(value)) + "," + format(std::get<1>(value));
	number = -0.0;
	boolean = false;
    start = value;
    centEnd = std::make_tuple(-0.0,-0.0);
    angle = -0.0;
	children = {};
}

// Construct an Expression with a single Line atom with starting
// point start and ending point end
Expression::Expression(std::tuple<double,double> newStart, 
           std::tuple<double,double> end){
    type = Line;
	stringValue = "(" + format(std::get<0>(newStart)) + "," + format(std::get<1>(newStart)) +
    ")(" + format(std::get<0>(end)) + "," + format(std::get<1>(end)) + ")";
	number = -0.0;
	boolean = false;
    start = newStart;
    centEnd = end;
    angle = -0.0;
	children = {};
}

// Construct an Expression with a single Arc atom with center
// point center, starting point start, and spanning angle angle in radians 
Expression::Expression(std::tuple<double,double> center, 
           std::tuple<double,double> newStart, double newAngle){
    type = typeArc;
	stringValue = "(" + format(std::get<0>(center)) + "," + format(std::get<1>(center)) +
    ")(" + format(std::get<0>(newStart)) + "," + format(std::get<1>(newStart)) + ") " + format(newAngle);
	number = -0.0;
	boolean = false;
    start = newStart;
    centEnd = center;
    angle = newAngle;
	children = {};
}

// Equality operator for two Expressions, two expressions are equal if the have the same 
// type, atom value, and number of arguments
bool Expression::operator==(const Expression & exp) const noexcept {
    
    //Test numberical values with epsilon since double numbers don't
    //Always compare exactly
    bool sameNum = (number == exp.number || 
        std::abs(number - exp.number) < std::numeric_limits<double>::epsilon());
    bool sameStart0 = (std::get<0>(start) == std::get<0>(exp.start) ||
        std::abs(std::get<0>(start) - std::get<0>(exp.start) ) < std::numeric_limits<double>::epsilon());
    bool sameStart1 = (std::get<1>(start) == std::get<1>(exp.start) ||
        std::abs(std::get<1>(start) - std::get<1>(exp.start) ) < std::numeric_limits<double>::epsilon());
    bool sameCentEnd0 = (std::get<0>(centEnd) - std::get<0>(exp.centEnd) || 
        std::abs(std::get<0>(centEnd) - std::get<0>(exp.centEnd) ) < std::numeric_limits<double>::epsilon());
    bool sameCentEnd1 = (std::get<0>(centEnd) - std::get<0>(exp.centEnd) || 
        std::abs(std::get<1>(centEnd) - std::get<1>(exp.centEnd) ) < std::numeric_limits<double>::epsilon());
    bool sameAngle = (angle == exp.angle || 
        std::abs(angle - exp.angle) < std::numeric_limits<double>::epsilon());
    
    //Test if type is the same
    bool sameType = (exp.type == type);
    //Test if stringValue is the same, if not, it doesn't matter if it's not
    //Symbol type
    bool sameString = false;
    if (exp.stringValue == stringValue || (sameType && type != Symbol)) {
        sameString = true;
    }
    
	return (exp.boolean == boolean && sameType && sameNum && sameString 
        && exp.children.size() == children.size() && sameStart0 && sameStart1
        && sameCentEnd0 && sameCentEnd1 && sameAngle);
}

//Cut trailing zeros
std::string format(double value) {
    //The following temporarily redirects the cout to convert result->number 
    //To a string
    std::streambuf* oldOutput = std::cout.rdbuf();
    std::ostringstream stringNumber;
    std::cout.rdbuf( stringNumber.rdbuf() );
    std::cout << value;
    std::cout.rdbuf( oldOutput );

    return stringNumber.str();
}