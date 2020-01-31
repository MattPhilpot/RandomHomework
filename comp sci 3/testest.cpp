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
	char * str1 = "hi ";
	char * str2 = "fren ";
	char * str3;
	str3 = *str1 + *str2;
	cout << str3;
	return 1;
}
