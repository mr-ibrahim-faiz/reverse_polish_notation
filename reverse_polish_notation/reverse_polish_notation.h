#pragma once

#include<string>
using std::string;

#include<vector>
using std::vector;

// gets expression from input
vector<string> get_expression();

// clears expression
void clear_expression(vector<string>&) noexcept;

// checks if a char is a representation of a digit
bool is_a_digit(const char&) noexcept;

// checks if a char is a valid operator
bool is_an_operator(const char&) noexcept;

// checks if a char is a valid unary operator + or -
bool is_unary_plus_or_minus(const char&) noexcept;

// checks if a character is allowed in an expression
bool is_allowed_in_expression(const char&) noexcept;

// checks if an expression is valid
bool is_valid(const vector<string>&) noexcept;

// calculates an expression and returns the result
double calculate(const double&, const double&, const char&);

// computes expression
double compute_expression(const vector<string>&);