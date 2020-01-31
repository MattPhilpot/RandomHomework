//Created and Written by
//
//Matthew Philpot
//
//HW1: Calculator

#include <iostream>
#include <string>
using namespace std;


class Calculator
{

public:
	double add(double x, double y)
	{
		return x+y;
	}

	double subtract(double x, double y)
	{
		return x-y;
	}
	
	double multi(double x, double y)
	{
		return x*y;
	}
	
	double divide(double x, double y)
	{
		x = (double)x;
		y = (double)y;
		return x/y;
	}

	int modulo(int x, int y)
	{
		return x%y;
	}

	double exponent(double x, double y)
	{
		double w = x;
		for(double z = 0;z<y;z++)
		{
			w*=x;
		}
		return w;
	}

	double factorial(double i)
	{
		if (i <= 1)
	        return i;
	    return (i * factorial(i - 1));
	}
};

string StringToLower(string strToConvert)
{
	for(unsigned int i=0;i<strToConvert.length();i++)
	{
		strToConvert[i] = tolower(strToConvert[i]);
	}
		return strToConvert;
}

int main()
{
	cout << "Welcome to Matthew's fantastic calculating machine!" << endl;
	Calculator Calc;
	double x,y;
	int z;
	string w;
	bool it = true;
	while(it)
	{
		cout << "Please enter two numbers...\nFirst Number: ";
		cin >> x;
		cout << "Second Number: ";
		cin >> y;
		bool smallit = true;
		while(smallit)
		{
			cout << "\n\nX is set to " << x << " and Y is set to " << y << "." << endl;
			cout << "Please select which operation you would like to complete." << endl;
			cout << "1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\n5. Modulo\n6. Exponent\n7. Factorial\n8. Exit" << endl;
			cin >> z;
			switch(z)
			{
			case 1: cout << "\nThe result is: " << Calc.add(x,y);break;
			case 2: cout << "\nThe result is: " << Calc.subtract(x,y);break;
			case 3: cout << "\nThe result is: " << Calc.multi(x,y);break;
			case 4: cout << "\nThe result is: " << Calc.divide(x,y);break;
			case 5: cout << "\nThe result is: " << Calc.modulo(x,y);break;
			case 6: cout << "\nThe result is: " << Calc.exponent(x,y);break;
			case 7: 
				cout << "\nThe result of X is: " << Calc.factorial(x) <<endl;
				cout << "The result of Y is : " << Calc.factorial(y);
				break;
			default:
			case 8: 
				cout << "Would you like to use new numbers? Yes or No" << endl;
				cin >> w;
				if(StringToLower(w)=="yes")
					smallit=false;
				else
				{
					smallit=false;
					it=false;
				}
			}
		}
	}
	cout << "\n\ngoodbye\n\n";
}