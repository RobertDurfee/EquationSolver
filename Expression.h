#pragma once
#include <vector>
#include <sstream>
using namespace std;

//All supported functions and their string equivalents
string arrFunctions[] = { "root(", "log(", "ln(", "log10(", "sin(", "cos(", "tan(", "csc(", "sec(", "cot(", "abs(", "asin(", "acos(", "atan(", "acsc(", "asec(", "acot(", "+-" };
//Binary or Unary:    	   Bi-	    Bi-     Un-    Un-       Un-     Un-     Un-     Un-     Un-     Un-     Un-     Un-      Un-      Un-      Un-      Un-      Un-      Un-

#define LENGTH			18
#define UNARY_START		2

#define ROOT			0
#define LOG				1
#define LN				2
#define LOG10			3
#define SIN				4
#define COS				5
#define TAN				6
#define CSC				7
#define SEC				8
#define COT				9
#define ABS				10
#define ASIN			11
#define ACOS			12
#define ATAN			13
#define ACSC			14
#define ASEC			15
#define ACOT			16
#define POS_NEG			17

#define LEFT_STACK		0
#define RIGHT_STACK		1
#define	STACK			2

#define E				"2.718281828459045235360287471352662497757"
#define PI				"3.141592653589793238462643383279502884197"

//Side that any variables are located in an equation
enum Side { RIGHT, LEFT, BOTH, NONE, UNINITIALIZED };

//Type of an equation
enum Type { POLYNOMIAL, RATIONAL, TRIGONOMETRIC, RADICAL, EXPONENTIAL, LOGARITHMIC, ABSOLUTE_VALUE };

//Hold necessary information about elements of an equation
struct EquationElement
{
	//If Input is a string
	EquationElement(string org_strInput)
	{
		strValue = org_strInput;
		intFunction = -1;
		chrOperator = 0;
		chrVariable = 0;
	}
	//If input is an operator
	EquationElement(char org_chrInput)
	{
		strValue = "";
		intFunction = -1;
		chrOperator = org_chrInput;
		chrVariable = 0;
	}
	//If input is a function
	EquationElement(int org_intInput, string org_strInput)
	{
		strValue = org_strInput;
		intFunction = org_intInput;
		chrOperator = 0;
		chrVariable = 0;
	}
	//String value equivalent
	string strValue;
	//Function number
	int intFunction;
	//Binary operator
	char chrOperator;
	//Variable
	char chrVariable;
};

//Locates the closing parenthese of a string given the current parethese
int GetClosingParenthese(string& org_strInput, int org_intIndex)
{
	int intNumberOfParentheses = 1;

	for (int i = org_intIndex + 1; i < org_strInput.length(); i++)
	{
		if (org_strInput[i] == '(')
			intNumberOfParentheses++;

		else if (org_strInput[i] == ')')
			intNumberOfParentheses--;

		if (intNumberOfParentheses == 0)
			return i;
	}
	return -1;
}

//Locates the lowest priority operator in a string
int GetOperatorIndex(string org_strInput)
{
	char chrOperators[] = { '+', '-', '*', '/', '^', '^' };
	for (int i = 0; i < 6; i += 2)
	{
		int intParentheseCount = 0;
		for (int j = org_strInput.length() - 1; j >= 0; j--)
		{
			if (org_strInput[j] == ')')
				intParentheseCount++;
			else if (org_strInput[j] == '(')
				intParentheseCount--;
			else if (intParentheseCount == 0 && (org_strInput[j] == chrOperators[i] || org_strInput[j] == chrOperators[i + 1]))
			{
				if ((org_strInput[j] != '+' && org_strInput[j] != '-') || (j != 0 && (org_strInput[j - 1] != '(' || org_strInput[j - 1] != '+' || org_strInput[j - 1] != '-' || org_strInput[j - 1] != '*' || org_strInput[j - 1] != '/' || org_strInput[j - 1] != '^')))
					return j;
			}
		}
	}
	return -1;
}

//Locates the comma operator in a string
int GetCommaIndex(string org_strInput)
{
	int intParentheseCount = -1;
	for (int j = org_strInput.length() - 1; j >= 0; j--)
	{
		if (org_strInput[j] == ')')
			intParentheseCount++;
		else if (org_strInput[j] == '(')
			intParentheseCount--;
		else if (intParentheseCount == 0 && org_strInput[j] == ',')
		{
			if ((org_strInput[j] != '+' && org_strInput[j] != '-') || (j != 0 && (org_strInput[j - 1] != '(' || org_strInput[j - 1] != '+' || org_strInput[j - 1] != '-' || org_strInput[j - 1] != '*' || org_strInput[j - 1] != '/' || org_strInput[j - 1] != '^')))
				return j;
		}
	}
	return -1;
}

//Locates the second node of a binary operator in a stack
int GetBinarySecondNode(int org_intIndex, vector<EquationElement*> org_vecStack)
{
	int intNodes = 0;
	for (int i = org_intIndex; i < (int)org_vecStack.size(); i++)
	{
		if (org_vecStack[i]->chrOperator != 0)
			intNodes += 1;
		else if (org_vecStack[i]->chrOperator == 0 && intNodes != 0)
			intNodes--;
		else if (intNodes == 0)
			return i;
	}
}

//Locates the location of the first variable in a node of a stack
int FindVariableInNode(int org_intNode, int org_intIndex)
{
	return -1;
}

//Holds and performs operatations on an equation
class Equation
{
public:
	Equation(string org_strInput);
	void Solve();
	void Simplify();
	string String();
	void Differentiate();
	void Integrate();
	string strValue;
	//void Extrema();
	//Bitmap Graph();
	//double NumericalDerivative(double org_dblPoint);
	//double NumericalIntegral(double org_dblPoint);
	//void Factor();
	//void Expand();
	//double Limit(double org_dblPoint);

protected:
	vector<EquationElement*> arrStacks[3];
	Side enuSide;
	bool booTwoSided;
	vector<Type> vecEquationTypes;
	int intVariableFrequency;

	bool StackContainsVariables();
	void FillStack();
	void Optimize(string& org_strInput);
	void IdentifyVariables();
	void IdentifyEquationType();
	void GenerateString();
};

//Constructor performing initial operations on equation
Equation::Equation(string org_strInput)
{
	this->enuSide = Side::UNINITIALIZED;

	this->strValue = org_strInput;

	Optimize(this->strValue);

	this->FillStack();

	this->IdentifyVariables();

	this->IdentifyEquationType();

	this->GenerateString();
}

//Locates side of equation with variables
void Equation::IdentifyVariables()
{
	this->intVariableFrequency = 0;
	for (int intStackIndex = 0; intStackIndex < 3; intStackIndex++)
	{
		for (int i = 0; i < (int)this->arrStacks[intStackIndex].size(); i++)
		{
			if (this->arrStacks[intStackIndex][i]->strValue.length() == 1 && this->arrStacks[intStackIndex][i]->strValue.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == -1)
			{
				this->intVariableFrequency++;
				this->arrStacks[intStackIndex][i]->chrVariable = this->arrStacks[intStackIndex][i]->strValue[0];
				switch (intStackIndex)
				{
				case STACK:
					this->enuSide = Side::BOTH;
					break;
				case LEFT_STACK:
					this->enuSide = Side::LEFT;
					break;
				case RIGHT_STACK:
					this->enuSide = (this->enuSide == Side::LEFT) ? Side::BOTH : Side::RIGHT;
					break;
				}
			}
		}
	}
	enuSide = (enuSide == Side::UNINITIALIZED) ? Side::NONE : enuSide;
}

//Determines equation type
void Equation::IdentifyEquationType()
{
	this->vecEquationTypes.clear();
	for (int intStackIndex = 0; intStackIndex < 3; intStackIndex++)
	{
		for (int i = 0; i < (int)this->arrStacks[intStackIndex].size(); i++)
		{
			switch (this->arrStacks[intStackIndex][i]->intFunction)
			{
			case ROOT:
				//Radical
				for (int j = 0; j <= (int)this->vecEquationTypes.size(); j++)
					if (j == 0 || this->vecEquationTypes[j] != Type::RADICAL)
					{
						this->vecEquationTypes.push_back(Type::RADICAL);
						break;
					}
				break;
			case LOG: case LN: case LOG10:
				//Logarithmic
				for (int j = 0; j <= (int)this->vecEquationTypes.size(); j++)
					if (j == 0 || this->vecEquationTypes[j] != Type::LOGARITHMIC)
					{
						this->vecEquationTypes.push_back(Type::LOGARITHMIC);
						break;
					}
				break;
			case SIN: case COS: case TAN: case CSC: case SEC: case COT: case ASIN: case ACOS: case ATAN: case ACSC: case ASEC: case ACOT:
				//Trigonometric
				for (int j = 0; j <= (int)this->vecEquationTypes.size(); j++)
					if (j == 0 || this->vecEquationTypes[j] != Type::TRIGONOMETRIC)
					{
						this->vecEquationTypes.push_back(Type::TRIGONOMETRIC);
						break;
					}
				break;
			case ABS:
				//Absolute Value
				for (int j = 0; j <= (int)this->vecEquationTypes.size(); j++)
					if (j == 0 || this->vecEquationTypes[j] != Type::ABSOLUTE_VALUE)
					{
						this->vecEquationTypes.push_back(Type::ABSOLUTE_VALUE);
						break;
					}
				break;
			}
			//Exponential
			if (this->arrStacks[intStackIndex][i]->chrOperator == '^' && FindVariableInNode(1, i) != -1)
				for (int j = 0; j <= (int)this->vecEquationTypes.size(); j++)
					if (j == 0 || this->vecEquationTypes[j] != Type::EXPONENTIAL)
					{
						this->vecEquationTypes.push_back(Type::EXPONENTIAL);
						break;
					}
			//Rational
			if (this->arrStacks[intStackIndex][i]->chrOperator == '/' && FindVariableInNode(1, i) != -1)
				for (int j = 0; j <= (int)this->vecEquationTypes.size(); j++)
					if (j == 0 || this->vecEquationTypes[j] != Type::RATIONAL)
					{
						this->vecEquationTypes.push_back(Type::RATIONAL);
						break;
					}
		}
	}
	//If there are no special functions, the equation is polynomial
	if (this->vecEquationTypes.size() == 0)
		this->vecEquationTypes.push_back(Type::POLYNOMIAL);
}

//Performs operators to operands wherever possible
void Equation::Simplify()
{
	for (int intStackIndex = 0; intStackIndex < 3; intStackIndex++)
	{
		for (int i = (int)this->arrStacks[intStackIndex].size() - 1; i >= 0; i--)
		{
			if (this->arrStacks[intStackIndex][i]->chrOperator != 0 && this->arrStacks[intStackIndex][i + 1]->chrOperator == 0 && this->arrStacks[intStackIndex][i + 1]->chrVariable == 0 && this->arrStacks[intStackIndex][i + 2]->chrOperator == 0 && this->arrStacks[intStackIndex][i + 2]->chrVariable == 0)
			{
				double num1, num2, answer;
				stringstream(this->arrStacks[intStackIndex][i + 2]->strValue) >> num1;
				stringstream(this->arrStacks[intStackIndex][i + 1]->strValue) >> num2;
				switch (this->arrStacks[intStackIndex][i]->chrOperator)
				{
				case '+':   answer = num1 + num2;   break;
				case '-':   answer = num1 - num2;   break;
				case '*':   answer = num1 * num2;   break;
				case '/':   answer = num1 / num2;   break;
				case '^': answer = pow(num1, num2); break;
				}
				this->arrStacks[intStackIndex][i]->strValue = to_string((long double)answer);
				this->arrStacks[intStackIndex][i]->chrOperator = 0;
				this->arrStacks[intStackIndex].erase(this->arrStacks[intStackIndex].begin() + i + 2);
				this->arrStacks[intStackIndex].erase(this->arrStacks[intStackIndex].begin() + i + 1);
			}
			else if (this->arrStacks[intStackIndex][i]->intFunction >= UNARY_START && this->arrStacks[intStackIndex][i + 1]->chrOperator == 0 && this->arrStacks[intStackIndex][i + 1]->chrVariable == 0)
			{
				double num1, answer;
				stringstream(this->arrStacks[intStackIndex][i + 1]->strValue) >> num1;
				switch (this->arrStacks[intStackIndex][i]->intFunction)
				{
				case LN: answer = log(num1);		break;
				case LOG10: answer = log10(num1);	break;
				case SIN: answer = sin(num1);		break;
				case COS: answer = cos(num1);		break;
				case TAN: answer = tan(num1);		break;
				case CSC: answer = 1 / sin(num1);   break;
				case SEC: answer = 1 / cos(num1);   break;
				case COT: answer = 1 / tan(num1);   break;
				case ABS: answer = abs(num1);	    break;
				case ASIN: answer = asin(num1);  	break;
				case ACOS: answer = acos(num1); 	break;
				case ATAN: answer = atan(num1); 	break;
				case ACSC: answer = asin(1 / num1);	break;
				case ASEC: answer = acos(1 / num1);	break;
				case ACOT: answer = atan(1 / num1);	break;
				case POS_NEG: continue;
				}
				this->arrStacks[intStackIndex][i]->strValue = to_string((long double)answer);
				this->arrStacks[intStackIndex][i]->intFunction = -1;
				this->arrStacks[intStackIndex].erase(this->arrStacks[intStackIndex].begin() + i + 1);
			}
			else if (this->arrStacks[intStackIndex][i]->intFunction >= 0 && this->arrStacks[intStackIndex][i]->intFunction < UNARY_START && this->arrStacks[intStackIndex][i + 1]->chrOperator == 0 && this->arrStacks[intStackIndex][i + 1]->chrVariable == 0 && this->arrStacks[intStackIndex][i + 2]->chrOperator == 0 && this->arrStacks[intStackIndex][i + 2]->chrVariable == 0)
			{
				double num1, num2, answer;
				stringstream(this->arrStacks[intStackIndex][i + 2]->strValue) >> num1;
				stringstream(this->arrStacks[intStackIndex][i + 1]->strValue) >> num2;
				switch (this->arrStacks[intStackIndex][i]->intFunction)
				{
				case ROOT: answer = pow(num1, 1 / num2); break;
				case LOG: answer = log(num1) / log(num2); break;
				}
				this->arrStacks[intStackIndex][i]->strValue = to_string((long double)answer);
				this->arrStacks[intStackIndex][i]->intFunction = -1;
				this->arrStacks[intStackIndex].erase(this->arrStacks[intStackIndex].begin() + i + 2);
				this->arrStacks[intStackIndex].erase(this->arrStacks[intStackIndex].begin() + i + 1);
			}
		}
	}
	this->GenerateString();
}

//Solves an equation with one instance of a variable
void Equation::Solve()
{
	this->Simplify();

	int intStackIndex;
	switch (this->enuSide)
	{
	case Side::LEFT:	intStackIndex = LEFT_STACK;		break;
	case Side::RIGHT:	intStackIndex = RIGHT_STACK;	break;
	case Side::NONE:	return;							break;
	case Side::BOTH:	return;							break;
	}

	if (this->intVariableFrequency > 1)
		return;

	for (int i = 0; i < (int)this->arrStacks[intStackIndex].size(); i++)
	{
		//If operand is after the operator
		if (this->arrStacks[intStackIndex][i]->chrOperator != 0 && this->arrStacks[intStackIndex][i + 1]->chrOperator == 0 && this->arrStacks[intStackIndex][i + 1]->intFunction == -1 && this->arrStacks[intStackIndex][i + 1]->chrVariable == 0)
		{
			switch (this->arrStacks[intStackIndex][i]->chrOperator)
			{
			case '+': this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin(), new EquationElement('-'));			break;
			case '-': this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin(), new EquationElement('+'));			break;
			case '*': this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin(), new EquationElement('/'));			break;
			case '/': this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin(), new EquationElement('*'));			break;
			case '^': this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin(), new EquationElement(ROOT, "root()")); break;
			}
			this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin() + 1, this->arrStacks[intStackIndex][i + 1]);
			this->arrStacks[intStackIndex].erase(this->arrStacks[intStackIndex].begin() + i + 1);
			this->arrStacks[intStackIndex].erase(this->arrStacks[intStackIndex].begin() + i);
			i--;
		}
		//If operand is before the operator
		else if (this->arrStacks[intStackIndex][i]->chrOperator != 0 && this->arrStacks[intStackIndex][GetBinarySecondNode(i, this->arrStacks[intStackIndex])]->chrOperator == 0 && this->arrStacks[intStackIndex][GetBinarySecondNode(i, this->arrStacks[intStackIndex])]->intFunction == -1 && this->arrStacks[intStackIndex][GetBinarySecondNode(i, this->arrStacks[intStackIndex])]->chrVariable == 0)
		{
			switch (this->arrStacks[intStackIndex][i]->chrOperator)
			{
			case '+': this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin(), new EquationElement('-'));			break;
			case '-':
				this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin(), new EquationElement('-'));
				this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin() + 1, this->arrStacks[intStackIndex][GetBinarySecondNode(i, this->arrStacks[intStackIndex])]);
				this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin(), new EquationElement('*'));
				this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin() + 1, new EquationElement("-1"));
				this->arrStacks[intStackIndex].erase(this->arrStacks[intStackIndex].begin() + GetBinarySecondNode(i, this->arrStacks[intStackIndex]));
				this->arrStacks[intStackIndex].erase(this->arrStacks[intStackIndex].begin() + i);
				i--;
				continue;
			case '*': this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin(), new EquationElement('/'));			break;
			case '/':
				this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin(), new EquationElement('/'));
				this->arrStacks[!intStackIndex].push_back(this->arrStacks[intStackIndex][GetBinarySecondNode(i, this->arrStacks[intStackIndex])]);
				this->arrStacks[intStackIndex].erase(this->arrStacks[intStackIndex].begin() + GetBinarySecondNode(i, this->arrStacks[intStackIndex]));
				this->arrStacks[intStackIndex].erase(this->arrStacks[intStackIndex].begin() + i);
				i--;
				continue;
			case '^': this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin(), new EquationElement(LOG, "log()"));	break;
			}
			this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin() + 1, this->arrStacks[intStackIndex][GetBinarySecondNode(i, this->arrStacks[intStackIndex])]);
			this->arrStacks[intStackIndex].erase(this->arrStacks[intStackIndex].begin() + GetBinarySecondNode(i, this->arrStacks[intStackIndex]));
			this->arrStacks[intStackIndex].erase(this->arrStacks[intStackIndex].begin() + i);
			i--;
		}
		//If Function is Unary
		else if (this->arrStacks[intStackIndex][i]->intFunction >= UNARY_START)
		{
			switch (this->arrStacks[intStackIndex][i]->intFunction)
			{
			case LN:
				this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin(), new EquationElement('^'));
				this->arrStacks[!intStackIndex].push_back(new EquationElement(E));
				break;
			case LOG10:
				this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin(), new EquationElement('^'));
				this->arrStacks[!intStackIndex].push_back(new EquationElement("10"));
				break;
			case SIN:  this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin(), new EquationElement(ASIN, "asin()"));	break;
			case COS:  this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin(), new EquationElement(ACOS, "acos()"));	break;
			case TAN:  this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin(), new EquationElement(ATAN, "atan()"));	break;
			case CSC:  this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin(), new EquationElement(ACSC, "acsc()"));	break;
			case SEC:  this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin(), new EquationElement(ASEC, "asec()"));	break;
			case COT:  this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin(), new EquationElement(ACOT, "acot()"));	break;
			case ABS:  this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin(), new EquationElement(POS_NEG, "+-"));		break;
			}
			this->arrStacks[intStackIndex].erase(this->arrStacks[intStackIndex].begin() + i);
		}
		//If Function is Binary
		else if (this->arrStacks[intStackIndex][i]->intFunction >= 0 && this->arrStacks[intStackIndex][i]->intFunction < UNARY_START && this->arrStacks[intStackIndex][i + 1]->chrOperator == 0 && this->arrStacks[intStackIndex][i + 1]->intFunction == -1 && this->arrStacks[intStackIndex][i + 1]->chrVariable == 0)
		{
			switch (this->arrStacks[intStackIndex][i]->intFunction)
			{
			case ROOT:
				this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin(), new EquationElement('^'));
				this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin() + 1, this->arrStacks[intStackIndex][i + 1]);
				break;
			case LOG:
				this->arrStacks[!intStackIndex].insert(this->arrStacks[!intStackIndex].begin(), new EquationElement('^'));
				this->arrStacks[!intStackIndex].push_back(this->arrStacks[intStackIndex][i + 1]);
				break;
			}
			this->arrStacks[intStackIndex].erase(this->arrStacks[intStackIndex].begin() + i + 1);
			this->arrStacks[intStackIndex].erase(this->arrStacks[intStackIndex].begin() + i);
		}
	}

	if (this->StackContainsVariables())
		this->Solve();

	this->Simplify();
}

//Determines the indefinite derivative of a function, as a function
void Equation::Differentiate()
{

}

//Determines the indefinite integral of a function, as a function
void Equation::Integrate()
{

}

//Fills and parses the equation stack
void Equation::FillStack()
{
	int intStackIndex, intMaxStackIndex;
	if (this->strValue.find('=') == -1)
	{
		intStackIndex = 2;
		intMaxStackIndex = 3;
		this->booTwoSided = false;
		this->arrStacks[STACK].push_back(new EquationElement(this->strValue));
	}
	else
	{
		intStackIndex = 0;
		intMaxStackIndex = 2;
		this->booTwoSided = true;
		this->arrStacks[LEFT_STACK].push_back(new EquationElement(this->strValue.substr(0, this->strValue.find('='))));
		this->arrStacks[RIGHT_STACK].push_back(new EquationElement(this->strValue.substr(this->strValue.find('=') + 1)));
	}
	for (intStackIndex; intStackIndex < intMaxStackIndex; intStackIndex++)
	{
		for (int i = 0; i < (int)this->arrStacks[intStackIndex].size(); i++)
		{
			string strExpression = this->arrStacks[intStackIndex][i]->strValue;
			Optimize(strExpression);
			int intOperatorIndex = GetOperatorIndex(strExpression);
			if (intOperatorIndex != -1)
			{
				this->arrStacks[intStackIndex][i]->chrOperator = strExpression[intOperatorIndex];
				this->arrStacks[intStackIndex].insert(this->arrStacks[intStackIndex].begin() + i + 1, new EquationElement(strExpression.substr(intOperatorIndex + 1)));
				this->arrStacks[intStackIndex].insert(this->arrStacks[intStackIndex].begin() + i + 2, new EquationElement(strExpression.substr(0, intOperatorIndex)));
				this->arrStacks[intStackIndex][i]->strValue = "";
			}
			else
			{
				int intCommaIndex = GetCommaIndex(strExpression);
				for (int j = UNARY_START; j < LENGTH; j++)
				{
					if (strExpression.find(arrFunctions[j]) != -1)
					{
						this->arrStacks[intStackIndex][i]->intFunction = j;
						this->arrStacks[intStackIndex].insert(this->arrStacks[intStackIndex].begin() + i + 1, new EquationElement(strExpression.substr(strExpression.find(arrFunctions[j]) + arrFunctions[j].length(), strExpression.length() - (strExpression.find(arrFunctions[j]) + arrFunctions[j].length()) - 1)));
						this->arrStacks[intStackIndex][i]->strValue = arrFunctions[j] + ")";
					}
				}
				for (int j = 0; j < UNARY_START; j++)
				{
					if (strExpression.find(arrFunctions[j]) != -1)
					{
						this->arrStacks[intStackIndex][i]->intFunction = j;
						this->arrStacks[intStackIndex].insert(this->arrStacks[intStackIndex].begin() + i + 1, new EquationElement(strExpression.substr(strExpression.find(arrFunctions[j]) + arrFunctions[j].length(), intCommaIndex - (strExpression.find(arrFunctions[j]) + arrFunctions[j].length()))));
						this->arrStacks[intStackIndex].insert(this->arrStacks[intStackIndex].begin() + i + 2, new EquationElement(strExpression.substr(intCommaIndex + 1, strExpression.length() - intCommaIndex - 2)));
						this->arrStacks[intStackIndex][i]->strValue = arrFunctions[j] + ")";
					}
				}
			}
		}
	}
}

//Optimizes a string input for initial tasks
void Equation::Optimize(string& org_strInput)
{
	//Get Length For Testing if the String Changed Later
	int org_intLength = org_strInput.length();

	for (int i = 0; i < org_strInput.length(); i++)
	{
		//Replace "+-" With "-"
		if (org_strInput[i] == '+' && i < org_strInput.length() - 1)
			if (org_strInput[++i] == '-')
				org_strInput.erase(i - 1, 1);
		//Replace "--" With "+" Or ""
			else if (org_strInput[i] == '-' && i < org_strInput.length() - 1)
			{
				if (org_strInput[++i] == '-' && (i - 1 == 0 || (org_strInput[i - 2] == '(' || org_strInput[i - 2] == '+' || org_strInput[i - 2] == '-' || org_strInput[i - 2] == '*' || org_strInput[i - 2] == '/' || org_strInput[i - 2] == '^')))
					org_strInput.erase(--i, 2);
				else if (org_strInput[i] == '-')
				{
					org_strInput.erase(i, 1);
					org_strInput.replace(--i, 1, "+");
				}
			}
	}

	//Replace ((...)) with (...)
	int i = -1;
	while ((i = org_strInput.find("((", i + 1)) != -1)
		if (org_strInput[GetClosingParenthese(org_strInput, i + 1) + 1] == ')')
		{
			org_strInput.erase(GetClosingParenthese(org_strInput, i + 1), 2);
			org_strInput.erase(i, 2);
		}

	//Remove Any "*1"
	i = -1;
	while ((i = org_strInput.find("*1", i + 1)) != -1)
		if (i + 2 == org_strInput.length() || (org_strInput[i + 2] == '+' || org_strInput[i + 2] == '-' || org_strInput[i + 2] == '*' || org_strInput[i + 2] == '('))
			org_strInput.erase(i, 2);
	//Remove Any "1*"
	i = -1;
	while ((i = org_strInput.find("1*", i + 1)) != -1)
		if (i == 0 || (org_strInput[i - 1] == '+' || org_strInput[i - 1] == '-' || org_strInput[i - 1] == '*' || org_strInput[i - 1] == '('))
			org_strInput.erase(i, 2);

	//Remove Any "^1"
	i = -1;
	while ((i = org_strInput.find("^1", i + 1)) != -1)
		if (i + 2 == org_strInput.length() || (org_strInput[i + 2] == '+' || org_strInput[i + 2] == '-' || org_strInput[i + 2] == '*' || org_strInput[i + 2] == '('))
			org_strInput.erase(i, 2);

	//Remove Unneeded Parentheses
	i = 0;
	while ((i = org_strInput.find("(", i)) != -1)
	{
		//If The Parenthese is the Beginning of a Function
		if (i > 0 && (org_strInput[i - 1] == 'n' || org_strInput[i - 1] == 's' || org_strInput[i - 1] == 'c' || org_strInput[i - 1] == 't' || org_strInput[i - 1] == 'h' || org_strInput[i - 1] == 'g' || org_strInput[i - 1] == '0'))
		{
			i++;
			continue;
		}

		int intCloseIndex = GetClosingParenthese(org_strInput, i);

		if ((i == 0 && intCloseIndex == org_strInput.length() - 1) || (intCloseIndex - i == 1) || (org_strInput.substr(i + 1, (intCloseIndex - i) - 1).find_first_not_of("0123456789") == -1))
		{
			org_strInput.erase(intCloseIndex, 1);
			org_strInput.erase(i, 1);
		}
		else
			i++;
	}

	//If The String Changed, Recurse
	if (org_intLength != org_strInput.length())
		Optimize(org_strInput);
}

//Returns string value of equation
string Equation::String()
{
	this->GenerateString();
	return this->strValue;
}

//Determines if stack contains operators
bool Equation::StackContainsVariables()
{
	for (int intStackIndex = 0; intStackIndex < 3; intStackIndex++)
		for (int i = 0; i < (int)this->arrStacks[intStackIndex].size(); i++)
			if (this->arrStacks[intStackIndex][i]->chrOperator != '\0')
				return true;
	return false;
}

//Generates the string value of equation
void Equation::GenerateString()
{
	this->strValue = "";

	for (int intStackIndex = 0; intStackIndex < 3; intStackIndex++)
	{
		for (int i = 0; i < (int)this->arrStacks[intStackIndex].size(); i++)
		{
			if (intStackIndex == RIGHT_STACK && i == 0)
				this->strValue += "=";
			if (this->arrStacks[intStackIndex][i]->strValue == "")
			{
				stringstream ss;
				ss << this->arrStacks[intStackIndex][i]->chrOperator;
				this->strValue += ss.str();
			}
			else
				this->strValue += this->arrStacks[intStackIndex][i]->strValue;
		}
	}
}