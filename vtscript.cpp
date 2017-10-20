#include "interpreter.hpp"
#include <sstream>

int fileMode(std::string filename) {
    std::ifstream file(filename);
		if (file.is_open()) {
			Interpreter inter = Interpreter();
			bool parseOkay = inter.parse(file);
			if (parseOkay) {
                Expression result;
                try {
                    result = inter.eval();
                }
                catch (InterpreterSemanticError msg) {
                    std::cout << msg.what() << std::endl;
                    std::string error = "Error";
                    result = Expression(error);
                }
				if (result.type != None && result.stringValue != "Error") {
					std::cout << "(" << result.stringValue << ")" << std::endl;
				}
				else {
					return -1;
				}
			}
			else {
                std::cout << std::endl;
                std::cout << "Error: Invalid expression, could not parse" << std::endl;
				return -1;
			}
		}
		else {
			std::cout << "Error: Could not open file" << std::endl;
			return -1;
		}
    return 0;
}

int stringMode(std::string filename) {
    std::istringstream file(filename);

    Interpreter inter = Interpreter();
    bool parseOkay = inter.parse(file);
    if (parseOkay) {
        Expression result;
        try {
            result = inter.eval();
        }
        catch (InterpreterSemanticError msg) {
            std::cout << msg.what() << std::endl;
            std::string error = "Error";
            result = Expression(error);
        }
        if (result.type != None && result.stringValue != "Error") {
            std::cout << "(" << result.stringValue << ")" << std::endl;
        }
        else {
            return -1;
        }
    }
    else {
        std::cout << std::endl;
        std::cout << "Error: Invalid expression, could not parse" << std::endl;
        return -1;
    }
    return 0;
}

int replMode() {
    Interpreter inter = Interpreter();
    std::string input;
    while (true) {
        Environment preRunEnv = inter.getEnv();
        std::cout << "vtscript> ";
        std::getline(std::cin, input);
        std::istringstream file(input);
        if (file.peek() == EOF) {
            std::cout << std::endl;
            break;
        }
        bool parseOkay = inter.parse(file);
        if (parseOkay) {
            Expression result;
            try {
                result = inter.eval();
            }
            catch (InterpreterSemanticError msg) {
                std::cout << msg.what() << std::endl;
                std::string error = "Error";
                result = Expression(error);
            }
            if ((result.type != None || result.children.size() != 0) && result.stringValue != "Error") {
                std::cout << "(" << result.stringValue << ")" << std::endl;
            }
            else {
                //reset environment
                inter.setEnv(preRunEnv);
            }
            std::cout << std::endl;
        }
        else {
        std::cout << "Error: Invalid expression, could not parse" << std::endl;
        std::cout << std::endl;
        }
    }
    return 0;
}

int main(int argc, char * argv[]) {

	if (argc == 2) {
        return fileMode(argv[1]);
	}
	else if (argc == 3 && std::string(argv[1]) == "-e") {
		return stringMode(argv[2]);
	}
	else if (argc == 1) {
		//REPL mode
		return replMode();
	}
    std::cout << "Error: Invalid command line arguments";
    return -1;
}