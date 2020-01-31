#include <iostream>
#include <fstream>
#include <string>
#include <string>
#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <math.h>
#include <ctime>

using namespace std;

struct myKrust
{
	int weight;
	int x;
	int y;
};

void generateGraph()
{
	int* theList = NULL;
	int size = 0, n = 0, density = 5;
	int eDex = 0, sDex = 0;
	double startTime, endTime, totalTime = 0.0;
	int runNumber = 0;
	string saveName = "";
	cout << "How big would you a side to be? ";
	cin >> size;
	cout << "Range Size? (1 - n) ";
	cin >> n;
	while(true)
	{
		cout << "Please select a density between 1 and 10 (1 = sparse, 10 = dense) ";
		cin >> density;
		if(density > 0 && density < 11)
			break;
	}	
	cout << "\nGenerating Random List of Size " << size << " with elements ranging from 1 - " << n << "..." << endl;
	theList = new int[size*size];	/*	Applying new max_size to array	*/

	switch(density)
	{
		case 1:
			for(int x,y,z = 0;z < size; z++)
			{
				x = int(rand()%(size-1) + 1);
                		y = int(rand()%x);
                		theList[(y*size)+x] = (rand() % n) + 1;
			}
			break;
		case 2:
		case 3:		
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			for(int x,y,z = 0; z <= ((density*(size*size))/ 10); z++)
			{
				x = int(rand()%(size-1) + 1);
				y = int(rand()%x);
				theList[(y*size)+x] = (rand()% n) + 1;
			}	
			break;
		case 10:
			for(int x = 0; x < (size*size); x++) //fill the matrix with random variables
				theList[x] = (rand() % n) + 1;
			break;
	}


	
	cout << "\nWhat name would you like to save the file as (DO NOT include extension)? ";
	cin >> saveName;
	saveName.append(".txt");

	ofstream outFile(saveName.c_str());

	outFile << "---- " << size << " " << endl;
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			outFile << theList[(i*size) + j] << " ";
		}
		outFile << endl;
	}
	outFile.close();
}

/* MA CODE FOR PRIMS */

void runPrim(int dims, int* myArray, string fileName)
{
	string writeOutName = fileName;
	fileName.append(".PRIMS.RESULTS.txt");
	bool* visitedArr; // Boolean visited array...true == visited, false == not visited.
	float startTime = 0.0, endTime = 0.0, totalTime = 0.0;
	int* mstArr = NULL;
	int min = 10000000;
	int cost = 0;
	int vert;
	mstArr = new int[dims*dims];
	visitedArr = new bool[dims];
	ofstream outFile(fileName.c_str());
	outFile << "---- Array Size: " << dims << " ----" << endl;
	startTime = clock();
	for(int i = 0; i < dims; i++)
	{
		for(int j = 0; j < dims; j++)
		{
			if((visitedArr[j] == false) && (myArray[(i*dims) + j] < min))
			{
				if(myArray[(i*dims) + j] != 0) // If the element in myArray[i][j] position is 0, go to the next element.
				{
					min = myArray[(i*dims) + j]; // Set the distance of myArray[i][j] as the min.
					mstArr[(i*dims) + j] = min; // Place the min in the mstArr[i][j]
					outFile << "From " << i << " to " << j << " = " << min << endl;
					vert = j; // Set vertex to index j value.
				}
			}
		}
		visitedArr[vert] = true; // Set visited vertex array to true.
		cost += min; // Add minimum distance to the cost.
		outFile << "Cost = " << cost << endl;
	}
	endTime = clock();
	totalTime = endTime - startTime;
	cout << "Total time taken: " << totalTime << endl;
	outFile << "Total time taken: " << totalTime << endl;
	outFile << endl;
	outFile.close();
}

/* AND NOW FOR SOMETHING COMPLETELY DIFFERENT (AKA KRUSKALS) */

void doTheCombin(int x, int y, int* anArray)
{
	if( x > y)
		anArray[y] = x;
	else
		anArray[x] = y;
}

int findset(int x, int *parent)
{
 	if(x != parent[x])
        	parent[x] = findset(parent[x], parent);
    	return parent[x];
}

void runKruskal(int dims, int* myArray, string fileName)
{
	double startTime = 0.0, endTime = 0.0, totalTime = 0.0;
	myKrust* thisArray = new myKrust[dims*dims];
	int theMST[dims][2];
	int* anArray = new int[dims];
	int i = 0, j = 0, t = 0, sum = 0;
      	myKrust tmp;
	bool swapped = true;
	string writeOutName = fileName;
	fileName.append(".KRUSKAL.RESULTS.txt");
	//have to sort first by weight
	for(i = 0; i < dims;i++)
	{
		theMST[i][0] = 0;
		theMST[i][1] = 0;
		theMST[i][2] = 0;
		anArray[i] = i;
		for(j = 0; j < dims; j++)
		{
			thisArray[(i * dims) + j].weight = myArray[(i * dims) + j];
			thisArray[(i * dims) + j].x = i;
			thisArray[(i * dims) + j].y = j;			
		}
	}

      	j = 0;
	cout << "Sorting... please wait... this may take a few minutes if matrix is large." << endl;
      	while (swapped) 
	{
		swapped = false;
		j++;
		for (int i = 0; i < (dims*dims) - j; i++) 
		{
              	if (thisArray[i].weight > thisArray[i + 1].weight) 
			{
                        	tmp = thisArray[i];
			//	cout << "swapping" << endl;
                        	thisArray[i] = thisArray[i + 1];
                        	thisArray[i + 1] = tmp;
                        	swapped = true;
				
                  	}
            	}
      	}
	ofstream outFile(fileName.c_str());
	outFile << "---- Array Size: " << dims << " ----" << endl;
	cout << "-----" << endl;
	startTime = clock();
	for(int x = 0; x < (dims*dims); x++)
	{
		i = findset(thisArray[x].x, anArray);
		j = findset(thisArray[x].y, anArray);
		if(thisArray[x].weight != 0 && i != j)
		{
			theMST[t][0] = thisArray[x].x;
			theMST[t][1] = thisArray[x].y;
			theMST[t][2] = thisArray[x].weight;
			sum += thisArray[x].weight;
			outFile << "MST[" << theMST[t][0] << "][" << theMST[t][1] << "] = " << theMST[t][2] << endl;
			anArray[i] = anArray[j];
			t++;
		}
	}
	endTime = clock();
	totalTime = endTime - startTime;
	cout << "Sum = " << sum << endl;
	outFile << "Sum = " << sum << endl;
	cout << "Total time taken: " << totalTime << endl;
	outFile << "Total time taken: " << totalTime << endl;
	outFile << endl;
	outFile.close();
}

void readInFile(int mode)
{
	int* myArray = NULL;
	int dims = 0, i = 0, j = 0;
	string fileName = "";
	string parameterName = "";
	string word = "";
	cout << "Please name the file you would like to open. DO NOT include extension. " << endl;
	cin >> fileName;
	parameterName = fileName;
	fileName.append(".txt");
	ifstream file;
	file.open(fileName.c_str()); // Read in text file.
	if(!file) // If the file cannot be read, then terminate the program.
	{
		cerr << "Error: Cannot open file. Quitting program..." << endl;
		exit(1);
	}

	while(file.good())
	{
		while(getline(file, word, ' '))
		{
			if(word == "----") // If the string word starts with "----", then the string word after it would be converted to an int for the size, dims, of the myArray.
			{
				i = 0;
				j = 0;
				myArray = NULL;
				getline(file, word, ' ');
				dims = atoi(word.c_str());	
				myArray = new int[dims*dims];
				cout << "Matrix Size = " << dims << endl;
			}
			else // Otherwise, convert next word to int and place in myArray.
			{
				myArray[(i*dims) + j] = atoi(word.c_str());
				//cout << myArray[(i*dims) + j] << " "; // Prints out array for cool debugging
				j++;			
				if(j >= dims)
				{
					j = 0;
					i++;
					//cout << endl;
					if(i >= dims)
						i = 0;
				}
			}
		}
	}

	switch(mode)
	{
		case 0:
			runPrim(dims, myArray, parameterName);
			break;
		case 1:
			runKruskal(dims, myArray, parameterName);
			break;
		case 2:
			break;
	}
}

int main()
{
	double startTime, endTime, totalTime = 0.0; 
    double totalTimeTaken;
	string word = "";
	int dims = 0;

	int* arrayINIT = NULL; // Initial array where the graph file gets read into.
	bool* arrayVISITED = NULL; // Boolean visited array...true == visited, false == not visited.
	int* arrayMST = NULL; // Minium spanning tree array.

	int i = 0, j = 0;
	int cost = 0;
	int vert = 0;
	int min = 100000; // Setting min to a random number.
	int option = 0;
	string strOption = "";
	size_t found;

	bool mainLoop = true;
	bool tryPass = false;
	cout << "Welcome to Philpot's Algorithm Project.\n" << endl;
	while(mainLoop)
	{
		cout << "---- MAIN MENU ----\nWhat would you like to do?" << endl;
		cout << "(1)Generate Graph" << endl;
		cout << "(2)Test Prim's" << endl;
		cout << "(3)Test Kruskal's" << endl;
		cout << "(4)Test Both" << endl;
		cout << "(5)Exit" << endl;
		cin >> strOption;
		//toLowerCase(strOption);
		try
		{
			option = atoi(strOption.c_str());
		}
		catch(int i)
		{		
			cout << "TryParse Failed" << endl;
		}

		if(strOption.find("generate") != string::npos || option == 1)
		{
			generateGraph();
		}
		else if(strOption.find("prim") != string::npos || option == 2)
		{
			readInFile(0);
			//runPrim();
		}
		else if(strOption.find("kruskal") != string::npos || option == 3)
		{
			readInFile(1);
			//runKruskal();
		}
		else if(strOption.find("both") != string::npos || option == 4)
		{
			readInFile(2);
			//runBoth();
		}
		else if(strOption.find("exit") != string::npos || option == 5)
		{
			mainLoop = false;
			cout << "Goodbye, Mr. Anderson" << endl;
			break;
		}		
	}
}

