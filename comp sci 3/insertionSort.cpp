//Matthew Philpot
//Computer Science 3

#include <iostream>
#include <time.h>
#include <fstream>
using namespace std;

void insertion_sort (int Array[1000], int length)
{
	clock_t sTime;
	srand((unsigned)clock());
	sTime = clock(); //ready, set, GOGOGOGOGOGO!!!!	
	int temp1,temp2;
	for(int x = 2; x<length-1;x++)
	{
		temp1 = Array[x];
		for(int y=0;y<x; y++)
		{
			if(Array[x] < Array[y])
			{
				temp2 = Array[y];
				Array[y] = Array[x];
				Array[x] = temp2;
				temp2 = 0;
			}
		}
	}

	for(int x = 0; x < 1000 - 1; x++)
	{
		cout << Array[x] << " ";
	}
	double time = (double) (clock()-sTime)/CLOCKS_PER_SEC; //clock
	cout << "\nTotal time until Insertion Sort completion (Array Length: 1000): " << time << " seconds" << endl; 
}

int main() //main
{
	ifstream infile("data_Lab9.txt");
	int Arrayone[1000];
	for(int x=0; x<1000;x++)
	{
		infile >> Arrayone[x];
		
	}
	insertion_sort(Arrayone, 1000);
}