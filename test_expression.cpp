#include "catch.hpp"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "expression.hpp"
#include "test_config.hpp"

TEST_CASE( "Test Default Expression constructor", "[expression]" ) {

  Expression express = Expression();

  REQUIRE(express.type == None);
  REQUIRE(express.number == -0.0);
  REQUIRE(express.stringValue == "None");
  REQUIRE(!express.boolean);
  REQUIRE(express.start == std::make_tuple(-0.0,-0.0));
  REQUIRE(express.centEnd == std::make_tuple(-0.0,-0.0));
  REQUIRE(express.angle == -0.0);
  REQUIRE(express.children.size() == 0);
}

TEST_CASE( "Test Boolean constructor", "[expression]" ) {
  {
    Expression express = Expression(true);

    REQUIRE(express.type == Boolean);
    REQUIRE(express.number == 0.0);
    REQUIRE(express.stringValue == "True");
    REQUIRE(express.boolean);
    REQUIRE(express.start == std::make_tuple(-0.0,-0.0));
    REQUIRE(express.centEnd == std::make_tuple(-0.0,-0.0));
    REQUIRE(express.angle == -0.0);
    REQUIRE(express.children.size() == 0);
  }
  {
    Expression express = Expression(false);

    REQUIRE(express.type == Boolean);
    REQUIRE(express.number == -0.0);
    REQUIRE(express.stringValue == "False");
    REQUIRE(!express.boolean);
    REQUIRE(express.start == std::make_tuple(-0.0,-0.0));
    REQUIRE(express.centEnd == std::make_tuple(-0.0,-0.0));
    REQUIRE(express.angle == -0.0);
    REQUIRE(express.children.size() == 0);
  }
}

TEST_CASE( "Test Double constructor", "[expression]" ) {

  {
    Expression express = Expression(4.5);

    REQUIRE(express.type == Number);
    REQUIRE(express.number == 4.5);
    REQUIRE(express.stringValue == "4.5");
    REQUIRE(!express.boolean);
    REQUIRE(express.start == std::make_tuple(-0.0,-0.0));
    REQUIRE(express.centEnd == std::make_tuple(-0.0,-0.0));
    REQUIRE(express.angle == -0.0);
    REQUIRE(express.children.size() == 0);
  }
}

TEST_CASE( "Test String constructor", "[expression]" ) {

  {
    std::string name= "Faker";
    Expression express = Expression(name);

    REQUIRE(express.type == Symbol);
    REQUIRE(express.number == -0.0);
    REQUIRE(express.stringValue == "Faker");
    REQUIRE(!express.boolean);
    REQUIRE(express.start == std::make_tuple(-0.0,-0.0));
    REQUIRE(express.centEnd == std::make_tuple(-0.0,-0.0));
    REQUIRE(express.angle == -0.0);
    REQUIRE(express.children.size() == 0);
  }
}

TEST_CASE( "Test Point constructor", "[expression]" ) {

  {
    Expression express = Expression(std::make_tuple(5.0,10.0));

    REQUIRE(express.type == Point);
    REQUIRE(express.number == -0.0);
    REQUIRE(express.stringValue == "5,10");
    REQUIRE(!express.boolean);
    REQUIRE(express.start == std::make_tuple(5.0,10.0));
    REQUIRE(express.centEnd == std::make_tuple(-0.0,-0.0));
    REQUIRE(express.angle == -0.0);
    REQUIRE(express.children.size() == 0);
  }
}

TEST_CASE( "Test Line constructor", "[expression]" ) {

  {
    Expression express = Expression(std::make_tuple(5.0,10.0),std::make_tuple(1.0,-1.0));

    REQUIRE(express.type == Line);
    REQUIRE(express.number == -0.0);
    REQUIRE(express.stringValue == "(5,10)(1,-1)");
    REQUIRE(!express.boolean);
    REQUIRE(express.start == std::make_tuple(5.0,10.0));
    REQUIRE(express.centEnd == std::make_tuple(1.0,-1.0));
    REQUIRE(express.angle == -0.0);
    REQUIRE(express.children.size() == 0);
  }
}

TEST_CASE( "Test Arc constructor", "[expression]" ) {

  {
    Expression express = Expression(std::make_tuple(5.0,10.0),std::make_tuple(1.0,-1.0), 1.5);

    REQUIRE(express.type == typeArc);
    REQUIRE(express.number == -0.0);
    REQUIRE(express.stringValue == "(5,10)(1,-1) 1.5");
    REQUIRE(!express.boolean);
    REQUIRE(express.start == std::make_tuple(1.0,-1.0));
    REQUIRE(express.centEnd == std::make_tuple(5.0,10.0));
    REQUIRE(express.angle == 1.5);
    REQUIRE(express.children.size() == 0);
  }
}

TEST_CASE( "Test == when true", "[expression]" ) {
  {
    std::string name= "Faker";
    Expression express = Expression(name);
    Expression second = Expression(name);

    bool compare = (express == second);
  
    REQUIRE(compare);
  }
}

TEST_CASE( "Test == in all false cases", "[expression]" ) {
  {
    std::string name= "Faker";
    Expression express = Expression(name);
    Expression* child = new Expression(true);
    express.children.push_back(child);
    Expression second = Expression(name);

    bool compare = (express == second);
  
    REQUIRE(!compare);
    delete child;
  }
  {
    std::string firstString = "Faker is";
    std::string secondString = "The best";
    Expression express = Expression(firstString);
    Expression second = Expression(secondString);

    bool compare = (express == second);
  
    REQUIRE(!compare);
  }
  {
    Expression express = Expression(true);
    Expression second = Expression(false);

    bool compare = (express == second);
  
    REQUIRE(!compare);
  }
  {
    Expression express = Expression(4.55);
    Expression second = Expression(5.6);

    bool compare = (express == second);
  
    REQUIRE(!compare);
  }
}


TEST_CASE( "test the formatting function with double", "[expression]" ) {
    double unformatted = 1.21000000;
    std::string formatted = format(unformatted);
    REQUIRE (formatted == "1.21");
}

TEST_CASE( "test the formatting function with int", "[expression]" ) {
    double unformatted = 1.00000000;
    std::string formatted = format(unformatted);
    REQUIRE (formatted == "1");
}