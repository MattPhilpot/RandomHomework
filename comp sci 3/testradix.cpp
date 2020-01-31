//Matthew Philpot
//Computer Science 3
//Radix Sort

#include <iostream>
#include <fstream>
using namespace std;

class Radix_Sort
{	
public:
	void sorting(int base, int Array[1000], int length)
	{
//		cout << "PASS " << base << ": ";
//		for(int x = 0; x<1000;x++)
//		{
//			cout << Array[x] << " ";
//		}
		//this bit of code was used for testing purposes, but I decided to include it. 
		cout << endl;
		int temp = 0;
		for(int x = 0; x<length; x++)
		{
			for(int y = 0;y<length-1;y++)
			{
				int l = Array[y];
				int k = Array[y+1];
				if(baseInt(l,base) < baseInt(k,base))
				{
//					cout << "Swapping " << baseInt(l,base) << " with " << baseInt(k,base) << endl;
					//this last line is optional
					//the reason I included it was so you can see
					//which numbers are beings swapped, and to make sure
					//that is doing it by the ones, tens, hundreds, etc.
					temp = Array[y];
					Array[y] = Array[y+1];
					Array[y+1] = temp;
				}
			}
		}
		cout << endl << endl;
		if(base!=5)
		{
			base++;
			sorting(base,Array,1000);
		}
		else
		{
			cout << "Final Array Sorted: ";
			for(int x = 0; x<1000;x++)
			{
				cout << Array[x] << " ";
			}
			cout << endl << endl;
		}
	}

	int baseInt(int num, int base)
	{
		int temp = 0;
		switch(base)
		{
		case 0: 
			temp = num % 10;
			return temp;
			break;
		case 1:
			temp = (num%100)-(num%10);
			return temp;
			break;
		case 2:
			temp = (num%1000)-(num%100);
			return temp;
			break;
		case 3:
			temp = (num%10000)-(num%1000);
			return temp;
			break;
		case 4:
			temp = (num%100000)-(num%10000);
			return temp;
			break;
		}
	}
};


int main() //main
{
	ifstream infile("data_Lab9.txt");
	Radix_Sort sorting;
	int Arrayone[1000];
	for(int x=0; x<1000;x++)
	{
		infile >> Arrayone[x];
		
	}
	sorting.sorting(0,Arrayone,1000);
	
}