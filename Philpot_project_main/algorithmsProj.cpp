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

void generateGraph()
{
	int* theList = NULL; //initial array
	int size = 0, n = 0, density = 5; //variables
	int eDex = 0, sDex = 0;
	int runNumber = 0;
	string saveName = "";
	cout << "How big would you a side to be? "; //how big
	cin >> size;
	cout << "Range Size? (1 - n) "; //range, just because
	cin >> n;
	while(true)
	{
		cout << "Please select a density between 1 and 10 (1 = sparse, 10 = dense) ";
		cin >> density; //select density
		if(density > 0 && density < 11)
			break;
	}	
	cout << "\nGenerating Random List of Size " << size << " with elements ranging from 1 - " << n << "..." << endl;
	theList = new int[size*size];	/*	Applying new max_size to array	*/

	for(int i = 0; i < (size*size); i++)
	{
		theList[i] = 0;
	}

	switch(density)
	{
		case 1:
			for(int x,y,z = 0;z < size; z++)
			{
				x = int(rand()%(size-1) + 1); //only for 1
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
			for(int x,y,z = 0; z <= ((density*(size*size))/ 10); z++) //for 2 - 9, it works!
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


	
	cout << "\nWhat name would you like to save the file as (DO NOT include extension)? "; //save as what name?
	cin >> saveName;
	saveName.append(".txt"); //append with .txt

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

void runPrim(int dims, int* primRayMan, string fileName)
{
	string writeOutName = fileName;
	fileName.append(".PRIMS.RESULTS.txt");
	bool* visitedNodes; // Boolean visited array...true == visited, false == not visited.
	time_t startTime, endTime; //time variables
	double totalTime;
	int* mstArr = NULL;
	int min = 1000000; //minimump for prims
	int cost = 0, numZero = 0;
	int vert;
	mstArr = new int[dims*dims];
	visitedNodes = new bool[dims];
	for(int x = 0; x < dims; x++)
	{
		visitedNodes[x] = false; //set visited nodes to false
	}
	visitedNodes[0] = true; //first one set to true... obviously
	ofstream outFile(fileName.c_str());
	outFile << "---- Array Size: " << dims << " ----" << endl;
	cout << "Starting Prims!" << endl;
	startTime = clock();

	while(numZero < (dims-1))
	{
		for(int i = 0; i < dims; i++) //first dimension
		{
			min = 1000000; //reset minium
			if(visitedNodes[i] == true) //check if vertex has already been visited
			{
				for(int j = 1; j < dims; j++) //2nd goodness
				{
					if((visitedNodes[j] == false) && primRayMan[(i*dims) + j] < min && primRayMan[(i*dims) + j] != 0)
					{
						min = primRayMan[(i*dims) + j]; // Set the weight at i,j as min
						outFile << "From " << i << " to " << j << " = " << min << endl;
						vert = j; // GIVE ME that vertex
					}
				}
				visitedNodes[vert] = true; // Set visited vertex array to true.
				if(min != 1000000)
					cost += min; // Finding length of MST'ish
				outFile << "Cost = " << cost << endl; //output cost to file
				numZero++; //I don't know why I named this 'numZero'
			}
		}
	}
	
	endTime = clock();
	totalTime = endTime - startTime;
	cout << "Total cost: " << cost << endl;
	cout << "Total time taken: " << totalTime/1000000.00 << " seconds " << endl; //out the stuff to the screen and file
	outFile << "Total cost: " << cost << endl;
	outFile << "Total time taken: " << totalTime/1000000.00 << " seconds " << endl;
	outFile << endl;
	outFile.close(); //then save result file!
}

/* AND NOW FOR SOMETHING COMPLETELY DIFFERENT (AKA KRUSKALS) */

int findset(int x, int *parent)
{
 	if(x != parent[x])
        parent[x] = findset(parent[x], parent);
    return parent[x];
}

void doTheMath(int** theList, int sDex, int eDex) //quicksortFunction
{
	int i = sDex, j = eDex;
	int pivot = theList[(sDex + eDex) / 2][2];
	int x  = 0, y = 0, z = 0;

	while(i <= j)
	{
		while(theList[i][2] < pivot) //quicksorting all over the place
			i++;
		while(theList[j][2] > pivot)
			j--;
		if(i <= j)
		{
			x = theList[i][0];// I love me
			y = theList[i][1];// some quicksort
			z = theList[i][2];//but.. I really like
			theList[i][0] = theList[j][0];//radix sort way
			theList[i][1] = theList[j][1];//more
			theList[i][2] = theList[j][2];
			theList[j][0] = x;
			theList[j][1] = y;
			theList[j][2] = z;
			i++;
			j--;
		}
	}

	if(sDex < j)
		doTheMath(theList, sDex, j);
	if(j < eDex)
		doTheMath(theList, i, eDex);
}

void runKruskal(int dims, int* KrusRayMan, string fileName)
{
	double startTime = 0.0, endTime = 0.0, totalTime = 0.0; //time variables
	int** thisArray = NULL;
	thisArray = new int*[dims*dims]; //the main man array
	int theMST[dims][2];//keeps track of MST
	int* anArray = new int[dims]; //this is just an array
	int i = 0, j = 0, t = 0, sum = 0, a = 0, b = 0, c = 0; //I need to get away from generice variable names...
	bool swapped = true;
	string writeOutName = fileName;
	fileName.append(".KRUSKAL.RESULTS.txt"); //creating file
	for(i = 0; i < dims;i++)
	{
		theMST[i][0] = 0;
		theMST[i][1] = 0; //writing matrix to this array, while keeping which weight is connected to i/j intact.
		theMST[i][2] = 0; // that's the important part!
		anArray[i] = i;
		for(j = 0; j < dims; j++)
		{
			thisArray[(i * dims) + j] = new int[3];
			thisArray[(i * dims) + j][0] = i;
			thisArray[(i * dims) + j][1] = j;	
			thisArray[(i * dims) + j][2]= KrusRayMan[(i * dims) + j];		
		}
	}
	startTime = clock();
      	j = 0;
	cout << "Starting Kruskals!" << endl;
	cout << "Sorting... please wait..." << endl;
	doTheMath(thisArray, 0, (dims*dims)-1); //quicksorting by weight
	ofstream outFile(fileName.c_str());
	outFile << "---- Array Size: " << dims << " ----" << endl;

	for(int x = 0; x < (dims*dims); x++) //this is where the magic happens, oh yea...
	{
		i = findset(thisArray[x][0], anArray);
		j = findset(thisArray[x][1], anArray);
		if(thisArray[x][2] != 0 && i != j)
		{
			theMST[t][0] = thisArray[x][0];
			theMST[t][1] = thisArray[x][1];
			theMST[t][2] = thisArray[x][2];
			sum += thisArray[x][2];
			outFile << "MST[" << theMST[t][0] << "][" << theMST[t][1] << "] = " << theMST[t][2] << endl; //out selected weights to file
			anArray[i] = anArray[j];
			t++;
		}
	}
	endTime = clock();
	totalTime = endTime - startTime;
	cout << "Total Cost = " << sum << endl;
	outFile << "Total Cost = " << sum << endl;
	cout << "Total time taken: " << totalTime/1000000.00 << " seconds " <<endl; //put the time and cost in file
	outFile << "Total time taken: " << totalTime/1000000.00 << " seconds " << endl;
	outFile << endl;
	outFile.close(); // and save
}

void readInFile(int mode)
{
	int* primRayMan = NULL;
	int dims = 0, i = 0, j = 0;
	string fileName = "";
	string parameterName = "";
	string word = "";
	cout << "Please name the file you would like to open(DO NOT include extension): ";
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
	cout << "\nOpening " << fileName << endl;
	while(file.good())
	{
		while(getline(file, word, ' '))
		{
			if(word == "----") // If the string word starts with "----", then the string word after it would be converted to an int for the size, dims, of the primRayMan.
			{
				i = 0;
				j = 0;
				primRayMan = NULL;
				getline(file, word, ' ');
				dims = atoi(word.c_str());	
				primRayMan = new int[dims*dims];
				cout << "Reading Matrix Size: " << dims << endl << endl;
			}
			else // Otherwise, convert next word to int and place in primRayMan.
			{
				primRayMan[(i*dims) + j] = atoi(word.c_str());
				//cout << primRayMan[(i*dims) + j] << " "; // Prints out array for cool debugging
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
			runPrim(dims, primRayMan, parameterName);
			break;
		case 1:
			runKruskal(dims, primRayMan, parameterName);
			break;
		case 2:
			runPrim(dims, primRayMan, parameterName);
			cout << "\n---------\n" << endl;
			runKruskal(dims, primRayMan, parameterName);
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
	cout << "Welcome to Philpot's Algorithm Project." << endl;
	while(mainLoop)
	{
		cout << "\n---- MAIN MENU ----\nWhat would you like to do?" << endl;
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

