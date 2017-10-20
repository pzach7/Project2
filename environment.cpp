#include "environment.hpp"

envNode::envNode(bool logic) {
	type = Boolean;
	boolean = logic;
    if (logic) {
        stringValue = "True";
    }
    else {
        stringValue = "False";
    }
}

envNode::envNode(double num) {
	type = Number;
	number = num;
	stringValue = format(num);
}

envNode::envNode(std::string String) {
	type = Symbol;
	stringValue = String;
}

envNode::envNode(arithmeticProcedure math) {
	type = Procedure;
	aProc = math;
}

envNode::envNode(logicProcedure logic) {
	type = LogicProcedure;
	lProc = logic;
}

envNode::envNode(std::tuple<double,double> value){
    type = Point;
    start = value;
    stringValue = format(std::get<0>(value)) + "," + format(std::get<1>(value));
}
envNode::envNode(std::tuple<double,double> newStart, 
           std::tuple<double,double> end){
    type = Line;
    stringValue = "(" + format(std::get<0>(newStart)) + "," + format(std::get<1>(newStart)) +
    ")(" + format(std::get<0>(end)) + "," + format(std::get<1>(end)) + ")";
    start = newStart;
    centEnd = end;
}
// Construct an Expression with a single Arc atom with center
// point center, starting point start, and spanning angle angle in radians 
envNode::envNode(std::tuple<double,double> center, 
           std::tuple<double,double> newStart, 
           double newAngle){
    type = typeArc;
    stringValue = "(" + format(std::get<0>(center)) + "," + format(std::get<1>(center)) +
    ")(" + format(std::get<0>(newStart)) + "," + format(std::get<1>(newStart)) + ") " + format(newAngle);
    start = newStart;
    centEnd = center;
    angle = newAngle;
}

double add(expressionList numbers) {
	double sum = 0;
    if (numbers.size() == 0) {
        throw InterpreterSemanticError
			("Error: Invalid number of arguments");
    }
	for (Expression i : numbers) {
		if (i.type == Number) {
			sum += i.number;
		}
		else if (i.type == Symbol) {
			throw InterpreterSemanticError
			("Error: Unknown Symbol");
		}
		else {
			throw InterpreterSemanticError
			("Error: Tried to add a non-number");
		}
	}
	return sum;
}
double mult(expressionList numbers) {
	double product = 1;
    if (numbers.size() == 0) {
        throw InterpreterSemanticError
			("Error: Invalid number of arguments");
    }
	for (Expression i : numbers) {
		if (i.type == Number) {
			product *= i.number;
		}
		else if (i.type == Symbol) {
			throw InterpreterSemanticError
			("Error: Unknown Symbol");
		}
		else {
			throw InterpreterSemanticError
			("Error: Tried to add a non-number");
		}
	}
	return product;
}
double subOrNeg(expressionList numbers) {
	double result = 0;
	//Validate type is correct
	for (Expression i : numbers) {
		if (i.type != Number) {
			if (i.type == Symbol) {
				throw InterpreterSemanticError
				("Error: Unknown Symbol");
			}
			else {
				throw InterpreterSemanticError
				("Error: Tried to subtract or negate a non-number");
			}
		}
	}
	//Check for correct number of operators and compute
	if (numbers.size() == 1) {
		result = numbers.front().number * -1;
	}
	else if (numbers.size() == 2) {
		result = numbers.front().number - numbers.back().number;
	}
	else {
		throw InterpreterSemanticError
		("Error: Invalid number of arguments for subtract or negate");
	}
	return result;
}
double divide(expressionList numbers){
	double result = 0;
	for (Expression i : numbers) {
		if (i.type != Number) {
			if (i.type == Symbol) {
				throw InterpreterSemanticError
				("Error: Unknown Symbol");
			}
			else {
				throw InterpreterSemanticError
				("Error: Tried to divide a non-number");
			}
		}
	}
	//Check for correct number of operators and compute
	if (numbers.size() == 2) {
		result = numbers.front().number / numbers.back().number;
	}
	else {
		throw InterpreterSemanticError
		("Error: Invalid Number of arguments for divide");
	}

	return result;
}
double sine(expressionList numbers){
    double result = 0.0;

	if (numbers.size() == 1 && numbers.front().type == Number) {
		result = sin(numbers.front().number);
	}
	else {
			throw InterpreterSemanticError
			("Error: Invalid number of arguments or type");
	}

	return result;
}

double cosine(expressionList numbers){
    double result = 0.0;

	if (numbers.size() == 1 && numbers.front().type == Number) {
		result = cos(numbers.front().number);
	}
	else {
			throw InterpreterSemanticError
			("Error: Invalid number of arguments or type");
	}

	return result;
}

double arctangent(expressionList numbers){
    double result = 0.0;

    for (Expression i : numbers) {
		if (i.type != Number) {
            throw InterpreterSemanticError
            ("Error: Tried to divide a non-number");
		}
	}
    
	if (numbers.size() == 2) {
		result = atan2(numbers.front().number, numbers.back().number);
	}
	else {
			throw InterpreterSemanticError
			("Error: Invalid number of arguments or type");
	}

	return result;
}

//All M-ary, logic procedures
bool logicAnd(expressionList logics){
	bool result = true;

	for (Expression i : logics) {
		if (i.type == Boolean) {
			result = result & i.boolean;
		}
		else {
			if (i.type == Symbol) {
				throw InterpreterSemanticError
				("Error: Unknown Symbol");
			}
			else {
				throw InterpreterSemanticError
				("Error: Tried to 'and' a non-boolean");
			}
		}
	}

	return result;
}
bool logicOr (expressionList logics){
	bool result = false;

	for (Expression i : logics) {
		if (i.type == Boolean) {
			result = result | i.boolean;
		}
		else if (i.type == Symbol) {
			throw InterpreterSemanticError
			("Error: Unknown Symbol");
		}
		else {
			throw InterpreterSemanticError
			("Error: Tried to 'or' a non-boolean");
		}
	}

	return result;
}
//All binary, logic procedures
bool lessThan(expressionList numbers){
	bool result = false;

	for (Expression i : numbers) {
		if (i.type != Number) {
			if (i.type == Symbol) {
				throw InterpreterSemanticError
				("Error: Unknown Symbol");
			}
			else {
				throw InterpreterSemanticError
				("Error: Tried to compare a non-number");
			}
		}
	}

	if (numbers.size() == 2) {
		if (numbers.front().number < numbers.back().number) {
			result = true;
		}
	}
	else {
		throw InterpreterSemanticError
		("Error: Invalid number of arguments to compare");
	}
	return result;
}
bool lessThanEqual(expressionList numbers){
	bool result = false;
	
	for (Expression i : numbers) {
		if (i.type != Number) {
			if (i.type == Symbol) {
				throw InterpreterSemanticError
				("Error: Unknown Symbol");
			}
			else {
				throw InterpreterSemanticError
				("Error: Tried to compare a non-number");
			}
		}
	}

	if (numbers.size() == 2) {
		if (numbers.front().number <= numbers.back().number) {
			result = true;
		}
	}
	else {
		throw InterpreterSemanticError
		("Error: Invalid number of arguments to compare");
	}
	return result;
}
bool greaterThan(expressionList numbers){
	bool result = false;

	for (Expression i : numbers) {
		if (i.type != Number) {
			if (i.type == Symbol) {
				throw InterpreterSemanticError
				("Error: Unknown Symbol");
			}
			else {
				throw InterpreterSemanticError
				("Error: Tried to compare a non-number");
			}
		}
	}

	if (numbers.size() == 2) {
		if (numbers.front().number > numbers.back().number) {
			result = true;
		}
	}
	else {
		throw InterpreterSemanticError
		("Error: Invalid number of arguments to compare");
	}

	return result;
}
bool greaterThanEqual(expressionList numbers){
	bool result = false;

	for (Expression i : numbers) {
		if (i.type != Number) {
			if (i.type == Symbol) {
				throw InterpreterSemanticError
				("Error: Unknown Symbol");
			}
			else {
				throw InterpreterSemanticError
				("Error: Tried to compare a non-number");
			}
		}
	}

	if (numbers.size() == 2) {
		if (numbers.front().number >= numbers.back().number) {
			result = true;
		}
	}
	else {
		throw InterpreterSemanticError
		("Error: Invalid number of arguments to compare");
	}

	return result;
}
bool equal(expressionList numbers){
	bool result = false;

	for (Expression i : numbers) {
		if (i.type != Number) {
			if (i.type == Symbol) {
				throw InterpreterSemanticError
				("Error: Unknown Symbol");
			}
			else {
				throw InterpreterSemanticError
				("Error: Tried to compare a non-number");
			}
		}
	}

	if (numbers.size() == 2) {
		if (numbers.front().number == numbers.back().number) {
			result = true;
		}
	}
	else {
		throw InterpreterSemanticError
		("Error: Invalid number of arguments to compare");
	}

	return result;
}

//All Unary, logic commands
bool logicNot(expressionList logics){
	bool result = false;

	if (logics.size() == 1) {
		if (logics.front().boolean == result) {
			result = true;
		}
	}
	else {
		if (logics.size() == 1 && logics.front().type == Symbol) {
			throw InterpreterSemanticError
			("Error: Unknown Symbol");
		}
		else {
			throw InterpreterSemanticError
			("Error: Invalid number of arguments or type for 'not'");
		}
	}

	return result;
}


Expression point(expressionList numbers) {
	for (Expression i : numbers) {
		if (i.type != Number) {
				throw InterpreterSemanticError
				("Error: Argument type must be a number");
		}
	}
    
    Expression newPoint = Expression();
    
	if (numbers.size() == 2) {
        newPoint.type = Point;
        newPoint.stringValue = format(numbers.front().number) + "," + format(numbers.back().number);
		newPoint.start = std::make_tuple(numbers.front().number, numbers.back().number);
	}
	else {
		throw InterpreterSemanticError
		("Error: Invalid number of arguments");
	}

	return newPoint;
}

Expression line(expressionList points) {
	for (Expression i : points) {
		if (i.type != Point) {
				throw InterpreterSemanticError
				("Error: Argument type must be a Point");
		}
	}
    
    Expression newLine = Expression();
	if (points.size() == 2) {
        newLine.type = Line;
        newLine.stringValue = "(" + points.front().stringValue + ")(" + points.back().stringValue + ")";
		newLine.start = points.front().start;
        newLine.centEnd = points.back().start;
	}
	else {
		throw InterpreterSemanticError
		("Error: Invalid number of arguments");
	}

	return newLine;
}

Expression arc (expressionList args) {
    Expression newArc = Expression();
    if (args.size() != 3) {
        throw InterpreterSemanticError
		("Error: Invalid number of arguments");
    }
    if (args.back().type != Number) {
        throw InterpreterSemanticError
		("Error: Invalid argument type");
    }
    newArc.type = typeArc;
    newArc.angle = args.back().number;
    args.pop_back();
	for (Expression i : args) {
		if (i.type != Point) {
				throw InterpreterSemanticError
				("Error: Argument type must be a Point");
		}
	}
    newArc.start = args.back().start;
    newArc.centEnd = args.front().start;
    newArc.stringValue = "(" + args.front().stringValue + ")(" + args.back().stringValue + ") "+ format(newArc.angle);

	return newArc;
}


Environment::Environment() {
	//Set up map with default operations mapping to functions
	env = { { "not", envNode(&logicNot) }, {"and", envNode(&logicAnd)},
	{ "or", envNode(&logicOr) }, { "<", envNode(&lessThan) },
	{ "<=", envNode(&lessThanEqual) }, { ">", envNode(&greaterThan) },
	{ ">=", envNode(&greaterThanEqual) }, { "=", envNode(&equal) },
	{ "+", envNode(&add) }, { "-", envNode(&subOrNeg) },
	{ "*", envNode(&mult) },{ "/", envNode(&divide) },
    { "sin", envNode(&sine) },{ "cos", envNode(&cosine) },
	{ "arctan", envNode(&arctangent) }, { "pi", envNode(atan2(0,-1)) } };
}

Environment::~Environment() {

}

int Environment::getMapSize() {
    return env.size();
}

void Environment::update(std::string str, Expression node) {
	envNode newNode = envNode();
	newNode.type = node.type;

	if (node.type != None) {
		newNode.boolean = node.boolean;
		newNode.number = node.number;
		newNode.stringValue = node.stringValue;
        newNode.start = node.start;
        newNode.centEnd = node.centEnd;
        newNode.angle = node.angle;
		auto search = env.find(str);
		if (search != env.end()) {
			throw InterpreterSemanticError
			("Error: Symbol is already defined");
		}
		env.insert({ str, newNode });
	}
	else {
		throw InterpreterSemanticError
		("Error: Error during evaluation");
	}
}

Expression Environment::lookup(std::string str, expressionList list) {
	
	auto search = env.find(str);

	if (search == env.end()) {
		Expression empty = Expression();
		return empty;
	}
	Expression result;

	if (search->second.type == Boolean) {
		result = Expression(search->second.boolean);
	}
	else if (search->second.type == Number) {
		result = Expression(search->second.number);
	}
    else if (search->second.type == Point) {
		result = Expression(search->second.start);
    }
    else if (search->second.type == Line) {
        result = Expression(search->second.start,
                            search->second.centEnd);
    }
    else if (search->second.type == typeArc) {
        result = Expression(search->second.centEnd,
                            search->second.start,
                            search->second.angle);
    }
	else if (search->second.type == Procedure) {
		if (list.size() != 0) {
			result = Expression((search->second.aProc)(list));
		}
		else {
			throw InterpreterSemanticError
			("Error: Error during evaluation");
		}
	}
	else if (search->second.type == LogicProcedure) {
		if (list.size() != 0) {
			result = Expression((search->second.lProc)(list));
		}
		else {
			throw InterpreterSemanticError
			("Error: Error during evaluation");
		}
	}
	else {
		result = Expression(lookup(search->second.stringValue, list));
	}

	return result;
}

