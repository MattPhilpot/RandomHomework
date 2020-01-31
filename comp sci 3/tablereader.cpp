#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <cstring>
#include <math.h>
#include <vector>
#include <sstream>
#include <stdlib.h> 
#include <cstdlib>
using namespace std;

class Table
{
	int row;
	int col;
public:
	

	int rows()
	{
		return row;
	}

	int cols()
	{
		return col;
	}

	void Deminsion()
	{
		row = 0;
		col = 0;
		string line;
		string dataFile = "data.txt";

		ifstream myfile(dataFile);
		if(myfile.is_open())
		{
			while(!myfile.eof())
			{
				string buf;
				stringstream ss(line);
				vector<string> tokens;
				getline(myfile,line);
				row++;
				
				int* Array;
				Array = new int(line.size()/4);
				int length = line.size()/4;
				cout << "length is " << length << endl;
				for(int x = 0;x<length;x++)
				{
					Array[x] = 0;
					cout << "test";
				}
				int i = 0;
				while (ss >> buf)
				{
					tokens.push_back(buf);
					int tempInt = atoi(buf.c_str());
					Array[i]=tempInt;
					i++;
					
				}
				ss.seekp(0);
				ss.clear();
				ss.str("");
				buf.clear();
				int counter = 0;
				for(int x = 0; x<length;x++)
				{
					if(Array[x]==0)
					{
						counter++;
						
					}
						
				}
				int* newArray;
				length -= counter;
				newArray = new int(length);
				for(int x = 0; x<length;x++)
				{
					newArray[x]=Array[x];
					if(length>row)
					{
						col = length;
					}
				}
				for(int x = 0; x<length;x++)
				{
					
				}
			}
			myfile.close();
		}
	}

	void certainNum(int number)
	{
		string line;
		int temprow = 0;
		int Found = 0;
		ifstream myfile("data.txt");
		if(myfile.is_open())
		{
			while(!myfile.eof())
			{
				getline(myfile,line);
				temprow++;
				char *a=new char[line.size()+1];
				a[line.size()]=0;
				memcpy(a,line.c_str(),line.size());
				for(int x=0;x<(int)strlen(a);x++)
				{
					if(a[x] == number)
					{
						cout << "Found at: Row " << temprow << ", Column " << x << endl;
						Found++;
					}
				}
			}
			cout << "Found " << Found << " instances of the number " << number << "." << endl;
		}
	}

	void rowElement(int temprow, int size) //1 means largest, 0 smallest
	{
		string line;
		int temprows = 0;
		int number;
		int colnum = 0;
		ifstream myfile("data.txt");
		if(myfile.is_open())
		{
			while(!myfile.eof())
			{
				getline(myfile,line);
				temprows++;
				if(temprows = temprow)
				{
					char *a=new char[line.size()+1];
					a[line.size()]=0;
					memcpy(a,line.c_str(),line.size());
					number = a[0];
					if(size==1)
					{
						for(int x=0;x<(int)strlen(a);x++)
						{
							if(a[x]>number)
							{
								number=a[x];
								colnum = x;
							}
								
						}
					}
					if(size==0)
					{
						for(int x=0;x<(int)strlen(a);x++)
						{
							if(a[x]<number)
							{
								number=a[x];
								colnum = x;
							}
								
						}
					}
				}
			}
		}
		switch(size)
		{
		case 0: 
			cout << "The smallest number in row " << temprow << " is " << number << "." << endl;
			cout << "It is located in column " << colnum << "." << endl; break;

		case 1:
			cout << "The largest number in row " << temprow << " is " << number << "." << endl;
			cout << "It is located in column " << colnum << "." << endl; break;
		}
	}

	void colElement(int tempcol, int size) //1 means largest, 0 smallest
	{
		string line;
		int number;
		int temprow = 0;
		int rownum = 1;
		ifstream myfile("data.txt");
		if(myfile.is_open())
		{
			while(!myfile.eof())
			{
				getline(myfile,line);
				temprow++;
				char *a=new char[line.size()+1];
				a[line.size()]=0;
				memcpy(a,line.c_str(),line.size());
				if(temprow==1)
				{
					number = a[tempcol];
				}
				if(size==1 && a[tempcol] > number)
				{
					number=a[tempcol];
					rownum = temprow;
				}
				if(size==0 && a[tempcol] < number)
				{
					number=a[tempcol];
					rownum = temprow;
				}
			}
		}
		switch(size)
		{
		case 0: 
			cout << "The smallest number in column " << tempcol << " is " << number << "." << endl;
			cout << "It is located in row " << rownum << "." << endl; break;

		case 1:
			cout << "The largest number in column " << tempcol << " is " << number << "." << endl;
			cout << "It is located in row " << rownum << "." << endl; break;
		}
	}

	void numbersize(int size) //1 means largest, 0 smallest
	{
		string line;
		int temprow = 0;
		int rownum = 1;
		int colnum = 0;
		int thenumber;
		ifstream myfile("data.txt");
		if(myfile.is_open())
		{
			while(!myfile.eof())
			{
				getline(myfile,line);
				temprow++;
				char *a=new char[line.size()+1];
				a[line.size()]=0;
				memcpy(a,line.c_str(),line.size());
				if(rownum==1)
				{
					thenumber = a[0];
				}
				for(int x=0;x<(int)strlen(a);x++)
				{
					if(size==1 && a[x] > thenumber)
					{
						thenumber=a[x];
						rownum = temprow;
						colnum = x;
					}
					if(size==0 && a[x] < thenumber)
					{
						thenumber=a[x];
						rownum = temprow;
						colnum = x;
					}
				}
			}
		}
		switch(size)
		{
		case 0: 
			cout << "The smallest number is in row " << rownum << " and is " << thenumber << "." << endl;
			cout << "It is located in column " << colnum << "." << endl; break;

		case 1:
			cout << "The largest number is in row " << rownum << " and is " << thenumber << "." << endl;
			cout << "It is located in column " << colnum << "." << endl; break;
		}
	}

};


int main()
{
	Table rawr;
	rawr.Deminsion();
	cout << "There are " << rawr.rows() << " rows." <<endl;
	cout << "There are " << rawr.cols() << " columns." << endl;
	//rawr.certainNum(1028);
	//rawr.numbersize(1);

	return 0;
}