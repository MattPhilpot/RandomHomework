/*
 *  calculator_main.cpp
 *
 *
 *  Created by Matthew Philpot on 1/28/10.
 *
 */

#include <iostream>
#include "string"
using namespace std;

int main () 
{
	string name;
	cout << "\nEnter your name" << endl;
	getline (cin, name);
	
	cout << "\nMy name is " << name << endl;
	return 1;
}
