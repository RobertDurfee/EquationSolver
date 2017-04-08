#ifndef EQUATION_HEADER
#define EQUATION_HEADER

#include "Operators.h"    //Operator, OperatorString, OperatorRoutine
#include "EquationNode.h" //EquationNode, Type
#include "Exceptions.h"   //EquationNotWellFormedException

#include <string>         //std::string
#include <stack>          //std::stack

class Equation
{
public:
	Equation(std::string equationString);

	void Simplify();

private:
	EquationNode * equationTree = nullptr;

	bool IsWellFormed(std::string equationString);
	bool HasInvalidCharacters(std::string equationString);
	void RemoveSurroundingParentheses(std::string * equationString);
	void RemoveSpaces(std::string * equationString);

	EquationNode * Parse(std::string equationString);

	void SimplifyRecursive(EquationNode * equationTree);
};

Equation::Equation(std::string equationString)
{
	if (IsWellFormed(equationString))
	{
		if (!HasInvalidCharacters(equationString))
		{
			RemoveSpaces(&equationString);

			equationTree = Parse(equationString);
		}
		else
			throw equationContainsInvalidCharacter;
	}
	else
		throw equationNotWellFormed;
}

void Equation::Simplify()
{
	SimplifyRecursive(this->equationTree);
}

bool Equation::IsWellFormed(std::string equationString)
{
	std::stack<int> parentheses;

	std::string opening = "({[", closing = ")}]";

	for (unsigned int index = 0; index < equationString.length(); index++)
	{
		int openingType, closingType;

		if ((openingType = opening.find(equationString[index])) != -1)
			parentheses.push(openingType);

		else if ((closingType = closing.find(equationString[index])) != -1)
		{
			if (parentheses.size() != 0 && closingType == parentheses.top())
				parentheses.pop();
			else
				return false;
		}
	}

	return (parentheses.size() == 0);
}
bool Equation::HasInvalidCharacters(std::string equationString)
{
	if (equationString.find_first_not_of(" ()*+-./0123456789=ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^abcdefghijklmnopqrstuvwxyz{}") != -1)
		return true;
	else
		return false;
}
void Equation::RemoveSurroundingParentheses(std::string * equationString)
{
	int numberOfParentheses = 0;

	std::string opening = "({[", closing = ")}]";

	if (opening.find((*equationString)[0]) != -1)
		numberOfParentheses++;
	else
		return;

	for (unsigned int index = 1; index < equationString->length() - 1; index++)
	{
		if (opening.find((*equationString)[index]) != -1)
			numberOfParentheses++;
		else if (closing.find((*equationString)[index]) != -1)
			numberOfParentheses--;

		if (numberOfParentheses == 0)
			return;
	}

	*equationString = equationString->substr(1, equationString->length() - 2);

	RemoveSurroundingParentheses(equationString);
}
void Equation::RemoveSpaces(std::string * equationString)
{
	for (unsigned int index = 0; index < equationString->length(); index++)
		if ((*equationString)[index] == ' ')
			equationString->erase(index--, 1);
}

EquationNode * Equation::Parse(std::string equationString)
{
	EquationNode * equationTree = new EquationNode;

	if (equationString.length() > 0)
	{
		RemoveSurroundingParentheses(&equationString);

		std::string opening = "({[", closing = ")}]";

		int numberOfParentheses = 0;

		for (int operator_ = 1; operator_ < NUMBER_OF_OPERATORS; operator_++)
		{
			for (int index = 0; index < equationString.length(); index++)
			{
				if (opening.find(equationString[index]) != -1)
					numberOfParentheses++;

				else if (closing.find(equationString[index]) != -1)
					numberOfParentheses--;

				else
					if (numberOfParentheses == 0 && equationString.substr(index).find(OperatorString[operator_]) == 0)
					{
						equationTree->type = Type::OPERATOR;

						equationTree->operator_ = (Operator)operator_;

						equationTree->left = Parse(equationString.substr(0, index));
						equationTree->right = Parse(equationString.substr(index + OperatorString[operator_].length()));

						return equationTree;
					}
			}
		}

		try //I should probably implement a better solution to this...
		{
			equationTree->number = std::stod(equationString);
			equationTree->type = Type::NUMBER;
		}
		catch (std::invalid_argument)
		{
			equationTree->variable = equationString;
			equationTree->type = Type::VARIABLE;
		}
	}

	return equationTree;
}

void Equation::SimplifyRecursive(EquationNode * equationTree)
{
	if (equationTree->type == Type::OPERATOR)
	{
		SimplifyRecursive(equationTree->left);
		SimplifyRecursive(equationTree->right);

		if ((equationTree->left->type == Type::NUMBER || equationTree->left->type == Type::NONE) && equationTree->right->type == Type::NUMBER && equationTree->operator_ > Operator::EQUALS)
		{
			equationTree->number = (*OperatorRoutine[(int)equationTree->operator_])(equationTree->left->number, equationTree->right->number);

			equationTree->operator_ = Operator::NONE;

			equationTree->type = Type::NUMBER;
			
			delete equationTree->left;
			delete equationTree->right;

			equationTree->left = nullptr;
			equationTree->right = nullptr;
		}
	}
}

#endif