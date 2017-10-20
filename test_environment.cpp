#include "catch.hpp"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "environment.hpp"
#include "test_config.hpp"

TEST_CASE( "Test envNode default constructor", "[environment]" ) {
  {
    envNode newNode = envNode(true);
  
    REQUIRE(newNode.type == Boolean);
    REQUIRE(newNode.boolean);
    REQUIRE(newNode.number == -0.0);
    REQUIRE(newNode.stringValue == "True");
    REQUIRE(newNode.start == std::make_tuple(-0.0,-0.0));
    REQUIRE(newNode.centEnd == std::make_tuple(-0.0,-0.0));
    REQUIRE(newNode.angle == -0.0);
    REQUIRE(newNode.aProc == nullptr);
    REQUIRE(newNode.lProc == nullptr);
  }
  {
    envNode newNode = envNode(false);
  
    REQUIRE(newNode.type == Boolean);
    REQUIRE(!newNode.boolean);
    REQUIRE(newNode.number == -0.0);
    REQUIRE(newNode.stringValue == "False");
    REQUIRE(newNode.start == std::make_tuple(-0.0,-0.0));
    REQUIRE(newNode.centEnd == std::make_tuple(-0.0,-0.0));
    REQUIRE(newNode.angle == -0.0);
    REQUIRE(newNode.aProc == nullptr);
    REQUIRE(newNode.lProc == nullptr);
  }
}

TEST_CASE( "Test envNode double constructor", "[environment]" ) {

  envNode newNode = envNode(4.565);
  
  REQUIRE(newNode.type == Number);
  REQUIRE(!newNode.boolean);
  REQUIRE(newNode.number == 4.565);
  REQUIRE(newNode.stringValue == "4.565");
  REQUIRE(newNode.start == std::make_tuple(-0.0,-0.0));
  REQUIRE(newNode.centEnd == std::make_tuple(-0.0,-0.0));
  REQUIRE(newNode.angle == -0.0);
  REQUIRE(newNode.aProc == nullptr);
  REQUIRE(newNode.lProc == nullptr);
}

TEST_CASE( "Test envNode String constructor", "[environment]" ) {
  std::string newString = "wowcool";
  envNode newNode = envNode(newString);
  
  REQUIRE(newNode.type == Symbol);
  REQUIRE(!newNode.boolean);
  REQUIRE(newNode.number == -0.0);
  REQUIRE(newNode.stringValue == "wowcool");
  REQUIRE(newNode.start == std::make_tuple(-0.0,-0.0));
  REQUIRE(newNode.centEnd == std::make_tuple(-0.0,-0.0));
  REQUIRE(newNode.angle == -0.0);
  REQUIRE(newNode.aProc == nullptr);
  REQUIRE(newNode.lProc == nullptr);
}

TEST_CASE( "Test envNode point constructor", "[environment]" ) {
  envNode newNode = envNode(std::make_tuple(5.0,10.0));
  
  REQUIRE(newNode.type == Point);
  REQUIRE(!newNode.boolean);
  REQUIRE(newNode.number == -0.0);
  REQUIRE(newNode.stringValue == "5,10");
  REQUIRE(newNode.start == std::make_tuple(5.0,10.0));
  REQUIRE(newNode.centEnd == std::make_tuple(-0.0,-0.0));
  REQUIRE(newNode.angle == -0.0);
  REQUIRE(newNode.aProc == nullptr);
  REQUIRE(newNode.lProc == nullptr);
}

TEST_CASE( "Test envNode Line constructor", "[environment]" ) {
  envNode newNode = envNode(std::make_tuple(5.0,10.0),std::make_tuple(3.0,1.0));
  
  REQUIRE(newNode.type == Line);
  REQUIRE(!newNode.boolean);
  REQUIRE(newNode.number == -0.0);
  REQUIRE(newNode.stringValue == "(5,10)(3,1)");
  REQUIRE(newNode.start == std::make_tuple(5.0,10.0));
  REQUIRE(newNode.centEnd == std::make_tuple(3.0,1.0));
  REQUIRE(newNode.angle == -0.0);
  REQUIRE(newNode.aProc == nullptr);
  REQUIRE(newNode.lProc == nullptr);
}

TEST_CASE( "Test envNode Arc constructor", "[environment]" ) {
  envNode newNode = envNode(std::make_tuple(5.0,10.0),std::make_tuple(3.0,1.0), 2);
  
  REQUIRE(newNode.type == typeArc);
  REQUIRE(!newNode.boolean);
  REQUIRE(newNode.number == -0.0);
  REQUIRE(newNode.stringValue == "(5,10)(3,1) 2");
  REQUIRE(newNode.start == std::make_tuple(3.0,1.0));
  REQUIRE(newNode.centEnd == std::make_tuple(5.0,10.0));
  REQUIRE(newNode.angle == 2);
  REQUIRE(newNode.aProc == nullptr);
  REQUIRE(newNode.lProc == nullptr);
}

TEST_CASE( "Test envNode logic Procedure constructor", "[environment]" ) {

  envNode newNode = envNode(&add);
  
  REQUIRE(newNode.type == Procedure);
  REQUIRE(!newNode.boolean);
  REQUIRE(newNode.number == -0.0);
  REQUIRE(newNode.stringValue == "");
  REQUIRE(newNode.start == std::make_tuple(-0.0,-0.0));
  REQUIRE(newNode.centEnd == std::make_tuple(-0.0,-0.0));
  REQUIRE(newNode.angle == -0.0);
  REQUIRE(newNode.aProc == &add);
  REQUIRE(newNode.lProc == nullptr);
}

TEST_CASE( "Test envNode arithmetic procedure constructor", "[environment]" ) {

  envNode newNode = envNode(&logicAnd);
  
  REQUIRE(newNode.type == LogicProcedure);
  REQUIRE(!newNode.boolean);
  REQUIRE(newNode.number == -0.0);
  REQUIRE(newNode.stringValue == "");
  REQUIRE(newNode.start == std::make_tuple(-0.0,-0.0));
  REQUIRE(newNode.centEnd == std::make_tuple(-0.0,-0.0));
  REQUIRE(newNode.angle == -0.0);
  REQUIRE(newNode.aProc == nullptr);
  REQUIRE(newNode.lProc == &logicAnd);
}

TEST_CASE( "Test default Environment", "[environment]" ) {

  Environment world = Environment();
  
  REQUIRE(world.getMapSize() == 16);
}

TEST_CASE( "Test Lookup in Environment, no errors", "[environment]" ) {

  expressionList mathList = {Expression(4.5), Expression(3.0)};
  expressionList logicList = {Expression(true), Expression(true)};
  expressionList empty = {};
  { //Map looks up number
    Environment world = Environment();
    std::string firstTerm = "new";
    world.update(firstTerm, 3.11);
    Expression newNode = world.lookup(firstTerm, empty);
    
    REQUIRE(newNode.type == Number);
    REQUIRE(!newNode.boolean);
    REQUIRE(newNode.number == 3.11);
    REQUIRE(newNode.stringValue == "3.11");
    REQUIRE(newNode.start == std::make_tuple(-0.0,-0.0));
    REQUIRE(newNode.centEnd == std::make_tuple(-0.0,-0.0));
    REQUIRE(newNode.angle == -0.0);
  }
  { //Map looks up boolean
    Environment world = Environment();
    std::string firstTerm = "new";
    world.update(firstTerm, true);
    Expression newNode = world.lookup(firstTerm, empty);
    
    REQUIRE(newNode.type == Boolean);
    REQUIRE(newNode.boolean);
    REQUIRE(newNode.number == -0.0);
    REQUIRE(newNode.stringValue == "True");
    REQUIRE(newNode.start == std::make_tuple(-0.0,-0.0));
    REQUIRE(newNode.centEnd == std::make_tuple(-0.0,-0.0));
    REQUIRE(newNode.angle == -0.0);
  }
  { //Map looks up other symbol
    Environment world = Environment();
    std::string firstTerm = "new";
    std::string secondTerm = "old";
    world.update(secondTerm, 3.11);
    world.update(firstTerm, secondTerm);
    Expression newNode = world.lookup(firstTerm, empty);
    
    REQUIRE(newNode.type == Number);
    REQUIRE(!newNode.boolean);
    REQUIRE(newNode.number == 3.11);
    REQUIRE(newNode.stringValue == "3.11");
    REQUIRE(newNode.start == std::make_tuple(-0.0,-0.0));
    REQUIRE(newNode.centEnd == std::make_tuple(-0.0,-0.0));
    REQUIRE(newNode.angle == -0.0);
  }
}

TEST_CASE( "Test Lookup in Environment, procedures & empty, no errors", "[environment]" ) {

  expressionList mathList = {Expression(4.5), Expression(3.0)};
  expressionList logicList = {Expression(true), Expression(true)};
  expressionList empty = {};
  { //Empty
    Environment world = Environment();
    std::string firstTerm = "new";
    Expression newNode = world.lookup(firstTerm, empty);
    
    REQUIRE(newNode.type == None);
    REQUIRE(!newNode.boolean);
    REQUIRE(newNode.number == -0.0);
    REQUIRE(newNode.stringValue == "None");
    REQUIRE(newNode.start == std::make_tuple(-0.0,-0.0));
    REQUIRE(newNode.centEnd == std::make_tuple(-0.0,-0.0));
    REQUIRE(newNode.angle == -0.0);
    
  }
  { //Map look up logic procedure
    Environment world = Environment();
    std::string firstTerm = "and";
    Expression newNode = world.lookup(firstTerm, logicList);
    
    REQUIRE(newNode.type == Boolean);
    REQUIRE(newNode.boolean);
    REQUIRE(newNode.number == -0.0);
    REQUIRE(newNode.stringValue == "True");
    REQUIRE(newNode.start == std::make_tuple(-0.0,-0.0));
    REQUIRE(newNode.centEnd == std::make_tuple(-0.0,-0.0));
    REQUIRE(newNode.angle == -0.0);
  }
  { //Map looks up arithmetic procedure
    Environment world = Environment();
    std::string firstTerm = "+";
    Expression newNode = world.lookup(firstTerm, mathList);
    
    REQUIRE(newNode.type == Number);
    REQUIRE(!newNode.boolean);
    REQUIRE(newNode.number == 7.5);
    REQUIRE(newNode.stringValue == "7.5");
    REQUIRE(newNode.start == std::make_tuple(-0.0,-0.0));
    REQUIRE(newNode.centEnd == std::make_tuple(-0.0,-0.0));
    REQUIRE(newNode.angle == -0.0);
  }
}

TEST_CASE( "Test Lookup in Environment, catch errors", "[environment]" ) {

  expressionList empty = {};
  { //Map look up logic procedure with empty list
    Environment world = Environment();
    std::string firstTerm = "and";
    REQUIRE_THROWS_AS(world.lookup(firstTerm, empty), 
                    InterpreterSemanticError);
  }
  { //Map looks up arithmetic procedure with empty list
    Environment world = Environment();
    std::string firstTerm = "+";
    REQUIRE_THROWS_AS(world.lookup(firstTerm, empty), 
                    InterpreterSemanticError);
  }
}

TEST_CASE( "Test update func in Environment, no errors", "[environment]" ) {
    Expression node = Expression(4.5);
    Environment world = Environment();
    std::string firstTerm = "new";
    world.update(firstTerm, node);
    Expression newNode = world.lookup(firstTerm, {});
    
    REQUIRE(newNode.type == Number);
    REQUIRE(!newNode.boolean);
    REQUIRE(newNode.number == 4.5);
    REQUIRE(newNode.stringValue == "4.5");
    REQUIRE(newNode.start == std::make_tuple(-0.0,-0.0));
    REQUIRE(newNode.centEnd == std::make_tuple(-0.0,-0.0));
    REQUIRE(newNode.angle == -0.0);
}

TEST_CASE( "Test update func in Environment, error checking", "[environment]" ) {
    {   //Try to add empty node
        Expression node = Expression();
        Environment world = Environment();
        std::string firstTerm = "new";
        REQUIRE_THROWS_AS(world.update(firstTerm, node), 
                    InterpreterSemanticError);
    }
    {   //Try to update already defined symbol
        Expression node = Expression(3.44);
        Environment world = Environment();
        std::string firstTerm = "pi";
        REQUIRE_THROWS_AS(world.update(firstTerm, node), 
                    InterpreterSemanticError);
    }
}

TEST_CASE( "Test + operator", "[environment]" ) {
    std::string word = "dummy";
    expressionList logicList = {Expression(true), Expression(false)};
    expressionList mathList = {Expression(1.5), Expression(2.0)};
    expressionList symbolList = {Expression(word), Expression(word)};
    {   //Successful add
        REQUIRE(add(mathList) == 3.5);
    }
    {   //Test all errors thrown for improper type & number of argumetns
        std::vector<expressionList> programs = {logicList, {},
                                symbolList};
        for(auto s : programs){
            REQUIRE_THROWS_AS(add(logicList), 
                        InterpreterSemanticError);
        }
    }
}

TEST_CASE( "Test * operator", "[environment]" ) {
    std::string word = "dummy";
    expressionList logicList = {Expression(true), Expression(false)};
    expressionList mathList = {Expression(1.5), Expression(2.0)};
    expressionList symbolList = {Expression(word), Expression(word)};
    {   //Successful multiply
        REQUIRE(mult(mathList) == 3.0);
    }
    {   //Test all errors thrown for improper type & number of argumetns
        std::vector<expressionList> programs = {logicList, {},
                                symbolList};
        for(auto s : programs){
            REQUIRE_THROWS_AS(mult(logicList), 
                        InterpreterSemanticError);
        }
    }
}

TEST_CASE( "Test subOrNeg operator", "[environment]" ) {
    std::string word = "dummy";
    expressionList logicList = {Expression(true), Expression(false)};
    expressionList mathList = {Expression(2.0), Expression(1.5)};
    expressionList oneMath = {Expression(1.5)};
    expressionList symbolList = {Expression(word), Expression(word)};
    {   //Successful subtraction
        REQUIRE(subOrNeg(mathList) == 0.5);
    }
    {   //Successful negation
        REQUIRE(subOrNeg(oneMath) == -1.5);
    }
    {   //Test all errors thrown for improper type & number of arguments
        std::vector<expressionList> programs = {logicList, {},
                                symbolList};
        for(auto s : programs){
            REQUIRE_THROWS_AS(subOrNeg(logicList), 
                        InterpreterSemanticError);
        }
    }
}

TEST_CASE( "Test / operator", "[environment]" ) {
    std::string word = "dummy";
    expressionList logicList = {Expression(true), Expression(false)};
    expressionList mathList = {Expression(5.0), Expression(2.0)};
    expressionList symbolList = {Expression(word), Expression(word)};
    {   //Successful divide
        REQUIRE(divide(mathList) == 2.5);
    }
    {   //Test all errors thrown for improper type & number of argumetns
        std::vector<expressionList> programs = {logicList, {},
                                symbolList};
        for(auto s : programs){
            REQUIRE_THROWS_AS(divide(logicList), 
                        InterpreterSemanticError);
        }
    }
}

TEST_CASE( "Test logic 'and' operator", "[environment]" ) {
    std::string word = "dummy";
    expressionList logicList = {Expression(true), Expression(true)};
    expressionList mathList = {Expression(5.0), Expression(2.0)};
    expressionList symbolList = {Expression(word), Expression(word)};
    {   //Successful 'and'
        REQUIRE(logicAnd(logicList));
    }
    {   //Test all errors thrown for improper type & number of argumetns
        std::vector<expressionList> programs = {mathList,
                                symbolList};
        for(auto s : programs){
            REQUIRE_THROWS_AS(logicAnd(mathList), 
                        InterpreterSemanticError);
        }
    }
}

TEST_CASE( "Test logic 'or'operator", "[environment]" ) {
    std::string word = "dummy";
    expressionList logicList = {Expression(true), Expression(true)};
    expressionList mathList = {Expression(5.0), Expression(2.0)};
    expressionList symbolList = {Expression(word), Expression(word)};
    {   //Successful
        REQUIRE(logicOr(logicList));
    }
    {   //Test all errors thrown for improper type & number of argumetns
        std::vector<expressionList> programs = {mathList,
                                symbolList};
        for(auto s : programs){
            REQUIRE_THROWS_AS(logicOr(mathList), 
                        InterpreterSemanticError);
        }
    }
}

TEST_CASE( "Test '<' operator", "[environment]" ) {
    std::string word = "dummy";
    expressionList logicList = {Expression(true), Expression(true)};
    expressionList mathList = {Expression(5.0), Expression(2.0)};
    expressionList lessThanList = {Expression(2.0), Expression(3.0)};
    expressionList symbolList = {Expression(word), Expression(word)};
    {   //Successful <, true
        REQUIRE(!lessThan(mathList));
    }
    {   //Successful <, false
        REQUIRE(lessThan(lessThanList));
    }
    {   //Test all errors thrown for improper type & number of argumetns
        std::vector<expressionList> programs = {logicList, {},
                                symbolList};
        for(auto s : programs){
            REQUIRE_THROWS_AS(lessThan(logicList), 
                        InterpreterSemanticError);
        }
    }
}

TEST_CASE( "Test '<='operator", "[environment]" ) {
    std::string word = "dummy";
    expressionList logicList = {Expression(true), Expression(true)};
    expressionList mathList = {Expression(5.0), Expression(2.0)};
    expressionList lessThanList = {Expression(3.0), Expression(3.0)};
    expressionList symbolList = {Expression(word), Expression(word)};
    {   //Successful <=, true
        REQUIRE(!lessThanEqual(mathList));
    }
    {   //Successful <=, false
        REQUIRE(lessThanEqual(lessThanList));
    }
    {   //Test all errors thrown for improper type & number of argumetns
        std::vector<expressionList> programs = {logicList, {},
                                symbolList};
        for(auto s : programs){
            REQUIRE_THROWS_AS(lessThanEqual(logicList), 
                        InterpreterSemanticError);
        }
    }
}

TEST_CASE( "Test '>' operator", "[environment]" ) {
    std::string word = "dummy";
    expressionList logicList = {Expression(true), Expression(true)};
    expressionList mathList = {Expression(5.0), Expression(2.0)};
    expressionList lessThanList = {Expression(2.0), Expression(3.0)};
    expressionList symbolList = {Expression(word), Expression(word)};
    {   //Successful >, false
        REQUIRE(!greaterThan(lessThanList));
    }
    {   //Successful >, true
        REQUIRE(greaterThan(mathList));
    }
    {   //Test all errors thrown for improper type & number of argumetns
        std::vector<expressionList> programs = {logicList, {},
                                symbolList};
        for(auto s : programs){
            REQUIRE_THROWS_AS(greaterThan(logicList), 
                        InterpreterSemanticError);
        }
    }
}

TEST_CASE( "Test '>=' operator", "[environment]" ) {
    std::string word = "dummy";
    expressionList logicList = {Expression(true), Expression(true)};
    expressionList mathList = {Expression(5.0), Expression(2.0)};
    expressionList lessThanList = {Expression(2.0), Expression(3.0)};
    expressionList symbolList = {Expression(word), Expression(word)};
    {   //Successful >=, false
        REQUIRE(!greaterThanEqual(lessThanList));
    }
    {   //Successful >=, true
        REQUIRE(greaterThanEqual(mathList));
    }
    {   //Test all errors thrown for improper type & number of argumetns
        std::vector<expressionList> programs = {logicList, {},
                                symbolList};
        for(auto s : programs){
            REQUIRE_THROWS_AS(greaterThanEqual(logicList), 
                        InterpreterSemanticError);
        }
    }
}

TEST_CASE( "Test '=' operator", "[environment]" ) {
    std::string word = "dummy";
    expressionList logicList = {Expression(true), Expression(true)};
    expressionList mathList = {Expression(5.0), Expression(5.0)};
    expressionList lessThanList = {Expression(2.0), Expression(3.0)};
    expressionList symbolList = {Expression(word), Expression(word)};
    {   //Successful =, true
        REQUIRE(equal(mathList));
    }
    {   //Successful =, false
        REQUIRE(!equal(lessThanList));
    }
    {   //Test all errors thrown for improper type & number of argumetns
        std::vector<expressionList> programs = {logicList, {},
                                symbolList};
        for(auto s : programs){
            REQUIRE_THROWS_AS(equal(logicList), 
                        InterpreterSemanticError);
        }
    }
}

TEST_CASE( "Test logicNot operator", "[environment]" ) {
    std::string word = "dummy";
    expressionList logicList = {Expression(true)};
    expressionList falseList = {Expression(false)};
    expressionList mathList = {Expression(5.0), Expression(5.0)};
    expressionList lessThanList = {Expression(2.0), Expression(3.0)};
    expressionList symbolList = {Expression(word)};
    {   //Successful =, true
        REQUIRE(!logicNot(logicList));
    }
    {   //Successful =, false
        REQUIRE(logicNot(falseList));
    }
    {   //Test all errors thrown for improper type & number of argumetns
        std::vector<expressionList> programs = {mathList, {},
                                symbolList};
        for(auto s : programs){
            REQUIRE_THROWS_AS(logicNot(mathList), 
                        InterpreterSemanticError);
        }
    }
}



