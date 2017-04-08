#ifndef EXCEPTIONS_HEADER
#define EXCEPTIONS_HEADER

#include <exception> //std::exception

class EquationNotWellFormed : public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "Equation not properly formed.";
	}
} equationNotWellFormed;

class EquationContainsInvalidCharacter : public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "Equation not properly formed.";
	}
} equationContainsInvalidCharacter;

#endif