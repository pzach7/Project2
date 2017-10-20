#include "catch.hpp"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "tokenize.hpp"
#include "expression.hpp"
#include "test_config.hpp"

TEST_CASE( "Test Default constructor", "[tokenize]" ) {

  std::string program = "";

  std::istringstream iss(program);
  
  ASTTree tree = ASTTree();

  REQUIRE(tree.root == nullptr);
}

TEST_CASE( "Test to TokenForm with various valid spacing input", "[tokenize]" ) {
  
    listType compare = {"(","if","(","<","b","a",")","(","+","1","2",
                        ")","(","*","2","1",")",")"};
    std::vector<std::string> programs = {"(if(< b a)(+ 1 2)(* 2 1));comment", // close spacing
				       "( if( < b a)( + 1 2)(* 2 1)); comment", //Space after left paren
				       "(if (< b a) (+ 1 2) (* 2 1) ) ;comment", //Space before left
                       "(if(< b a )(+ 1 2 )(* 2 1 ) );comment", //Space before right paren
                       "(if(< b a) (+ 1 2) (* 2 1) );comment", //Space after right paren
				       "( if ( < b a ) ( + 1 2 ) ( * 2 1 ) ) ; comment"}; // All spaces
    for(auto s : programs){
      std::istringstream iss(s);

      listType tokens = toTokenForm(iss);
      
      bool thesame = true;
      
      std::size_t size = compare.size();
      std::size_t otherSize = tokens.size();
      
      for(std::size_t i = 0; i < size; i++) {
        tokens.pop_front();
        compare.pop_front();
      }
      REQUIRE(thesame == true);
    }
}

//possibly move to different module
TEST_CASE( "Require error be thrown when atom is invalid", "[tokenize]" ) {
  
      std::string program = "hello";
        
      std::istringstream iss(program);
      
      REQUIRE_THROWS_AS(toTokenForm(iss), std::runtime_error);
}

TEST_CASE( "Test isNumber with valid inputs", "[tokenize]" ) {
  
    std::vector<std::string> programs = {"1", "-1", "1.0", ".9",
                "34.45", "-98.5563", "-2e-2", "2."
                "1e4", "-3e-4", "4.5e5", "3.3e-3"}; // All spaces
    for(auto s : programs){
      
      bool isNum = isNumber(s);
      REQUIRE(isNum == true);
    }
}

TEST_CASE( "Test isNumber with invalid inputs", "[tokenize]" ) {
  
    std::vector<std::string> programs = {"4earl", "1-1", "1-",
                "--34.45", "-98..5563", 
                "1-e4", "4.5ee5",
                "a", "bbbb", "-e3"}; // All spaces
    for(auto s : programs){
      
      bool isNum = isNumber(s);
      REQUIRE(isNum == false);
    }
}