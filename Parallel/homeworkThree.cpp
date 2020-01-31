#include <iostream>
#include <ctime>
#include <math.h>
#include <iso646.h>
using namespace std;

int main()
{
	unsigned long a = 13, b = 22, c = 43, d = 64, e = 99;
	unsigned long theArray[] = {13,22,43,64,99};
	unsigned long temp = 0;
	cout << "Given the integers: " << a << ", " << b << ", " << c << ", " << d << ", " << e << endl << endl;
	cout << "Addition: " << (a+b+c+d+e) << endl << endl;
	cout << "Multiplication: " << (a*b*c*d*e) << endl << endl;

	for(int x = 0; x < 5; x++)
	{
		if(theArray[x] > temp)
			temp = theArray[x];
	}
	cout << "Maximum: " << temp << endl << endl;

	temp = theArray[0];
	for(int x = 0; x < 5; x++)
	{
		if(theArray[x] < temp)
			temp = theArray[x];
	}
	cout << "Minimum: " << temp << endl << endl;

	cout << "Bitwise OR: " << dec << ( a ^ b ^ c ^ d ^ e) << endl << endl;
	cout << "Bitwise AND: " << dec << (a & b & c & d & e) << endl << endl;
	cout << "Logical OR: " << dec << ( a || b || c || d || e) << endl << endl;
	cout << "Logical AND: " << dec << (a && b && c && d && e) << endl << endl;
	return 0;
}
