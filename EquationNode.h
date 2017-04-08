#ifndef EQUATION_NODE_HEADER
#define EQUATION_NODE_HEADER

#include "Operators.h" //Operator
#include <string>      //std::string

enum class Type { NONE, OPERATOR, NUMBER, VARIABLE };

struct EquationNode
{
	Type type = Type::NONE;

	Operator operator_ = Operator::NONE;
	double number = 0;
	std::string variable;

	EquationNode * left = nullptr;
	EquationNode * right = nullptr;
};

#endif