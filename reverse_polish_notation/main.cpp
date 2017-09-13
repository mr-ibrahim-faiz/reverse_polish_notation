#include "reverse_polish_notation.h"

#include<iostream>
using std::cin;
using std::cerr;
using std::cout;
using std::endl;

#include<stdexcept>
using std::exception;
using std::runtime_error;

int main()
try
{

	vector<string> expression;

	while (true)
	{
		// gets expression from input
		cout << "> ";
		expression = get_expression();

		// checks if the user wants to quit the program
		// exits if the user enters "exit"
		if (expression.size() == 1 && expression[0] == "exit")
			break;

		// clears expression
		clear_expression(expression);

		try {
			// check if the expression is valid before computing it
			if (is_valid(expression)) {
				// computes and display expression result
				cout << compute_expression(expression) << endl;
				cout << endl;
			}
			else {
				cout << "Error: invalid postfix expression." << endl;
				cout << endl;
			}
		}
		catch (runtime_error& e) {
			cerr << "Error: " << e.what() << endl;
			cerr << endl;
		}

	}

	cout << "\nGoodbye !" << endl;
	return 0;
}
catch (exception& e) {
	cerr << "Error: " << e.what() << endl;
}
catch (...) {
	cerr << "Error: unknown exception caught." << endl;
}