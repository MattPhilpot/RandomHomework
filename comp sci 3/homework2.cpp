// Matthew Philpot
// Computer Science 3
// 3.21.10

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Operations
{

public:
	void digits(string AintNoThang, int total)
	{
		string rawr;
		int test = 0;
		if(!AintNoThang.empty())
		{
			rawr = AintNoThang[0];
			istringstream buffer(rawr);
			buffer >> test;
			total += test;
			if(AintNoThang.length()>1)
			{
				cout << test << " + ";
				AintNoThang.erase(0,1);
				digits(AintNoThang, total);
			}
			else
			{
				cout << test << " = " << total << "\n" << endl;
			}
		}
	}

	void reverse(char* s)
	{
		if(*s != '\0')
			reverse(s+1);
		cout<<*(s);
	}
};

int main()
{
	Operations doIt;
	string option;
	bool exit = true;
	cout << "Hi! Please... Come in!" << endl;
	while(exit)
	{
		cout << "\nSelect one of {s}um of digits, {r}everse order, or {e}xit" << endl;
		cin >> option;
		if(option == "s")
		{
			string digits;
			cout << "Enter digits" << endl;
			cin >> digits;
			doIt.digits(digits,0);
		}

		if(option == "r")
		{
			string reverseIT;
			cout << "Enter phrase: ";
			do
			{
				getline(cin,reverseIT);
			}
			while(reverseIT.length()==0);
			cout << "The phrase is reversed: ";
			char *buff;
			buff = new char[reverseIT.length()];
			strcpy(buff, reverseIT.c_str());
			doIt.reverse(buff);
			cout << "" << endl;
		}
		if(option == "e")
		{
			exit = false;
		}
	}
}