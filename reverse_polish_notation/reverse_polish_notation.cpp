#include "reverse_polish_notation.h"

#include<iostream>
using std::cin;
using std::ws;

#include<stack>
using std::stack;

#include<string>
using std::stod;

#include<stdexcept>
using std::runtime_error;

// gets expression from input
vector<string> get_expression()
// gets expression and tokenizes it
// returns a vector of string containing the expression token (values, operators, etc)
{
	vector<string> expression;

	// peeks at the next character to see if we're at the end of the expression
	for (string token; cin.peek() != '\n';) {
		cin >> token;

		if (!token.empty())
			expression.push_back(token);

		// ignores whitespaces (especially at the end of the input)
		while (isspace(cin.peek()) && cin.peek() != '\n') // pseudo equivalent to: while(cin.peek() == ' ')
			cin.ignore(1, ' ');
	}

	// deals with the newline left in cin
	getchar();

	return expression;
}

// clears expression
void clear_expression(vector<string>& expression) noexcept
// clears expression's tokens by changing 'x' to '*' and ':' unto '/'
{
	for (string& token : expression) {

		// replace ':', 'x' by '/' and '*'
		for (size_t i = 0; i < token.size(); ++i) {
			switch (token[i]) {
			case 'x':
				token[i] = '*';
				break;
			case ':':
				token[i] = '/';
				break;
			default:
				break;
			}
		}

	}
}

// checks if a char is a representation of a digit
bool is_a_digit(const char& c) noexcept
// checks if the argument is the representation of a digit [0, 10)
// returns true if the argument is the representation of a digit
{
	switch (c)
	{
	case '0': case '1': case '2': case '3': case '4': case '5':
	case '6': case '7': case '8': case '9':
		return true;
	default:
		return false;
	}
}

// checks if a char is a valid operator
bool is_an_operator(const char& c) noexcept
// checks if the argument is the representation of a valid operator +, -, * / or ^
// returns true if it is the case
{
	switch (c)
	{
	case '+': case '-': case '*': case '/': case '^':
		return true;
	default:
		return false;
	}
}

// checks if a char is a valid unary operator + or -
bool is_unary_plus_or_minus(const char& c) noexcept
// checks if the argument is the representation of a valid unary operator +, or -
// returns true if it is the case
{
	switch (c)
	{
	case '+': case '-':
		return true;
	default:
		return false;
	}
}

// checks if a character is allowed in an expression
bool is_allowed_in_expression(const char& c) noexcept
// checks if the character passed as argument is allowed in an expression
// returns true if it is the case
{
	if (is_a_digit(c) || is_unary_plus_or_minus(c) || c == '.' || c == 'e')
		return true;
	return false;
}

// checks if an expression is valid
bool is_valid(const vector<string>& expression) noexcept
// checks if expression tokens are valid by using a set of rules
// i.e. number of tokens, invalid characters in tokens, etc
// returns true if everything is fine according to these rules
{
	// size of the expression
	size_t expression_size = expression.size();

	// this variable is used to track the numbers of operand and operators
	// it must never be less or equal to 0
	int validation = 0;

	// checks if the number of tokens is even or less than 3
	// returns false if it's the case
	if (expression_size % 2 && expression_size > 2);
	else
		return false;

	// checks if the tokens are valid numbers or operators
	for (string token : expression) {
		// length of the token
		size_t token_size = token.size();

		// counts 'e'
		size_t power_ten_count = 0;

		// counts '.'
		size_t point_count = 0;

		if (token_size == 1) {
			if (!is_a_digit(token[0]) && !is_an_operator(token[0]))
				return false;

			// validation
			if (is_a_digit(token[0]))
				++validation;
			else if (is_an_operator(token[0]))
				--validation;
		}
		else if (token_size > 1) {
			for (size_t i = 0; i < token_size; ++i) {
				if (!is_allowed_in_expression(token[i]))
					return false;
				else {

					switch (token[i]) {

					case '+': case '-':
						if (i == 0) {
							if (!is_a_digit(token[i + 1]) && token[i + 1] != '.')
								return false;
						}
						else if (i == token_size - 1)
							return false;
						else {
							if (token[i - 1] != 'e' 
								|| (!is_a_digit(token[i + 1]) && token[i + 1] != '.'))
								return false;
						}
						break;

					case 'e':
						++power_ten_count;
						point_count = 0;

						if (power_ten_count > 1)
							return false;
						else if (i == 0 || i == token_size - 1)
							return false;
						else
							if (!is_a_digit(token[i - 1]) && token[i - 1] != '.'
								|| (!is_a_digit(token[i + 1]) && !is_unary_plus_or_minus(token[i + 1]) && token[i + 1] != '.'))
								return false;
						break;

					case '.':
						++point_count;

						if (point_count > 1)
							return false;
						else if (i == 0) {
							if (!is_a_digit(token[i + 1]))
								return false;
						}
						else if (i == token_size - 1) {
							if (!is_a_digit(token[i - 1]))
								return false;
						}
						else
							if (is_unary_plus_or_minus(token[i - 1]) && token[i + 1] == 'e')
								return false;
							else if (!is_a_digit(token[i - 1]) && !is_unary_plus_or_minus(token[i - 1]) && token[i - 1] != 'e' 
								|| !is_a_digit(token[i + 1]) && token[i + 1] != 'e')
								return false;
						break;

					default:
						break;
					}
				}
			}

			// checks validation variable
			++validation;
		}
		else
			return false;

		// checks validation variable
		if (validation <= 0)
			return false;
	}

	// checks validation variable
	if (validation != 1)
		return false;

	return true;
}

// calculates an expression and returns the result
double calculate(const double& first, const double& second, const char& op)
// calculates an expression and returns the result
// supports only the operators +, -, /, *, e and ^
// throws a division by zero exception when detected
{
	switch (op) {
	case '+':
		return first + second;
	case '-':
		return first - second;
	case '*':
		return first * second;
	case '/':
		if (second == 0)
			throw runtime_error("division by zero.");
		return first / second;
	case 'e':
		// TODO: check first and second before computing first*pow(10, second)
		return first*pow(10, second);
	case '^':
		// TODO: check first and second before computing pow(first, second)
		return pow(first, second);
	default:
		throw runtime_error("unsupported operator.");
	}
}

// computes token
double compute_token(const string& token)
// computes token if contains specific operators
// returns the computed value of the token
{
	// size of the token
	size_t token_size = token.size();

	// searches for the power ten operator 'e'
	size_t found = token.find('e');

	// if it finds the power ten operator
	// identifies operands a and b, computes and returns a*10^b
	if (found != string::npos) {
		string a { "" }, b { "" };

		for (size_t i = 0; i < found; ++i)
			a.push_back(token[i]);
		for (size_t i = found + 1; i < token_size; ++i)
			b.push_back(token[i]);

		return calculate(stod(a), stod(b), 'e');
	}
	else
		return stod(token);
}

// computes expression
double compute_expression(const vector<string>& expression)
// computes the postfix expression passed as argument, 
// parses and calcultates expression from left to right
// returns the result as a string ? double ?
{
	stack<double> result;

	for (string token : expression) {
		if (token.size() == 1 && is_an_operator(token[0])) {
			double b = result.top();
			result.pop();
			double a = result.top();
			result.pop();
			result.push(calculate(a, b, token[0]));
		}
		else
			result.push(compute_token(token));
	}
	return result.top();
}