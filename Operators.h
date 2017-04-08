#ifndef OPERATORS_HEADER
#define OPERATORS_HEADER

#include <string> //std::string

#define NUMBER_OF_OPERATORS 24

const std::string OperatorString[] =
{
	"",
	"=",
	"+",
	"-",
	"*",
	"/",
	"^",
	"sqrt",
	"ln",
	"lg",
	"sin",
	"cos",
	"tan",
	"csc",
	"sec",
	"cot",
	"asin",
	"acos",
	"atan",
	"acsc",
	"asec",
	"acot",
	"abs",
	"neg"
};

enum class Operator
{
	NONE,
	EQUALS,
	ADDITION,
	SUBTRACTION,
	MULTIPLICATION,
	DIVISION,
	POWER,
	SQUARE_ROOT,
	NATURAL_LOGARITHM,
	COMMON_LOGARITHM,
	SINE,
	COSINE,
	TANGENT,
	COSECANT,
	SECANT,
	COTANGENT,
	INVERSE_SINE,
	INVERSE_COSINE,
	INVERSE_TANGENT,
	INVERSE_COSECANT,
	INVERSE_SECANT,
	ABSOLUTE_VALUE,
	NEGATE
};

double ADDITION(double left, double right)
{
	return left + right;
}
double SUBTRACTION(double left, double right)
{
	return left - right;
}
double MULTIPLICATION(double left, double right)
{
	return left * right;
}
double DIVISION(double left, double right)
{
	return left / right;
}
double POWER(double left, double right)
{
	return pow(left, right);
}
double SQUARE_ROOT(double left, double right)
{
	return sqrt(right);
}
double NATURAL_LOGARITHM(double left, double right)
{
	return log(right);
}
double COMMON_LOGARITHM(double left, double right)
{
	return log10(right);
}
double SINE(double left, double right)
{
	return sin(right);
}
double COSINE(double left, double right)
{
	return cos(right);
}
double TANGENT(double left, double right)
{
	return tan(right);
}
double COSECANT(double left, double right)
{
	return 1 / sin(right);
}
double SECANT(double left, double right)
{
	return 1 / cos(right);
}
double COTANGENT(double left, double right)
{
	return 1 / tan(right);
}
double INVERSE_SINE(double left, double right)
{
	return asin(right);
}
double INVERSE_COSINE(double left, double right)
{
	return acos(right);
}
double INVERSE_TANGENT(double left, double right)
{
	return atan(right);
}
double INVERSE_COSECANT(double left, double right)
{
	return asin(1 / right);
}
double INVERSE_SECANT(double left, double right)
{
	return acos(1 / right);
}
double INVERSE_COTANGENT(double left, double right)
{
	return atan(1 / right);
}
double ABSOLUTE_VALUE(double left, double right)
{
	return abs(right);
}
double NEGATE(double left, double right)
{
	return -right;
}

typedef double(*OperatorRoutinePointer)(double left, double right);

const OperatorRoutinePointer OperatorRoutine[] =
{
	nullptr,
	nullptr,
	&ADDITION,
	&SUBTRACTION,
	&MULTIPLICATION,
	&DIVISION,
	&POWER,
	&SQUARE_ROOT,
	&NATURAL_LOGARITHM,
	&COMMON_LOGARITHM,
	&SINE,
	&COSINE,
	&TANGENT,
	&COSECANT,
	&SECANT,
	&COTANGENT,
	&INVERSE_SINE,
	&INVERSE_COSINE,
	&INVERSE_TANGENT,
	&INVERSE_COSECANT,
	&INVERSE_SECANT,
	&INVERSE_COTANGENT,
	&ABSOLUTE_VALUE,
	&NEGATE
};

#endif