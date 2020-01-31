//Matthew Philpot
//Computer Science 3
//Radix Sort

#include <iostream>
#include <fstream>
using namespace std;

class Radix_Sort
{	
public:
	void sorting(int base, int Array[1000], int temp[1000], int length) //sorting algorithm
	{
//		cout << "PASS " << base << ": ";
//		for(int x = 0; x<1000;x++)
//		{
//			cout << Array[x] << " ";
//		}
		//this bit of code was used for testing purposes, but I decided to include it. 
		cout << endl;
		int tempcount = 0;
		for(int x = 0; x<10; x++) //this radix sort uses the temp array as a bucket to sort the list.
		{						  //it saves on resources and is faster.
			for(int y = 0;y<length;y++)
			{
				int l = Array[y];
				if(baseInt(l,base) == x)// THIS IS THE MOST IMPORTANT PART... GO TO baseINT
				{
					temp[tempcount]= Array[y];
					tempcount++;
				}
			}
		}
		cout << endl << endl;
		if(base!=5)
		{
			base++;
			sorting(base,temp,Array,1000);
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

	int baseInt(int num, int base) //this returns whatever place value you are looking for
	{							   //so one's, ten's, hundred's, thousands, etc.. 
							       //this function takes care of that so that the sorting
		int temp = 0;			   //can take place
		switch(base)
		{
		case 0: 
			temp = num % 10;//1's place
			return temp;
			break;
		case 1:
			temp = (num%100)-(num%10);//10's place
			return temp/10;
			break;
		case 2:
			temp = (num%1000)-(num%100);//100's place
			return temp/100;
			break;
		case 3:
			temp = (num%10000)-(num%1000);//1000's place
			return temp/1000;
			break;
		case 4:
			temp = (num%100000)-(num%10000);//10000's place (note, only one 5 digit number in all of array)
			return temp/10000;
			break;
		}
	}
};


int main() //main
{
	ifstream infile("data_Lab9.txt");
	Radix_Sort sorting;
	int Arrayone[1000];
	int Arraytwo[1000];
	for(int x=0; x<1000;x++)
	{
		infile >> Arrayone[x];
		Arraytwo[x]=0;
		
	}
	sorting.sorting(0,Arrayone,Arraytwo,1000);
	
}