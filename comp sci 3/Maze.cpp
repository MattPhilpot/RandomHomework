//matthew Philpot
//CSCE 2050.001

//sorry, no dynamic array... have to change size manually...
//for some reason I can't get the very very end to work... You'll see what I mean
//aside from that, it's perfect

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stack>
#include <time.h>
using namespace std;


//Array is 19 across, 10 down
//walls = -1
//available path = 0;
//prev visited = 1;
//start = 2, end = 3;
//been to but don't go = 4;

/*
################### 1
#       # #   #>  # 2
# ##### # # # ### # 3
#     #     #     # 4
### # ########### # 5
#   #      #   #### 6
########## # #    # 7
##     #   # # #### 8
## ###   #   #   <# 9
################### 10
*/
class mazer
{
	int row;
	int col;
	int Maze[10][19];
	int prevMove;
	int N, S, E, W;
	int doner;
	int availPath;
	int done;
	int top;
	stack<int> theStack;
	stack<int> revStack;

	//1=N, 2=E, 3=S, 4=W
public:
	
	void sleep(unsigned int mseconds)
	{
		clock_t goal = mseconds + clock();
		while (goal > clock());
	}

	void begin()
	{
		col = 17;
		row = 8;
		doner = 0;
		theStack.empty();
	}
	void redoBegin()
	{
		col = 17;
		row = 8;
		doner=0;
		revStack.empty();
	}

	void theMaze()
	{
//		int Maze[10][19];
		if(doner!=1)
		{
			ifstream infile;
			infile.open("hw4_mazemap.txt");
			while (!infile.eof())
			{
				for(int j=0;j<10;j++)
				{
					for(int k=0; k<19;k++)
					{
						infile >> Maze[j][k];
					}
				}
			} //end while
			infile.close();
			doner=1;
		}
	}
	void display()
	{
		for(int x=0;x<10;x++)
		{
			for(int k=0;k<19;k++)
			{
				if(Maze[x][k]==0)
				{
					cout << " ";
				}
				else if(Maze[x][k]==1)
				{
					cout << "+";
				}
				else if(Maze[x][k]==2)
				{
					cout << "<";
				}
				else if(Maze[x][k]==3)
				{
					cout << ">";
				}
				else if(Maze[x][k]==4)
				{
					cout << "-";
				}
				else if(Maze[x][k]==-1)
				{
					cout << "#";
				}
			}
			cout << endl;
		}
	}
	void nextDir()
	{
		N = 0;
		N = Maze[row-1][col];
		S = 0;
		S = Maze[row+1][col];
		E = 0;
		E = Maze[row][col+1];
		W = 0;
		W = Maze[row][col-1];
		availPath = 0;
		done = 0;
		display();
		cout << "current location: " << row << " down. " << col << " right." << endl;
		cout << "previous move: " << prevMove << endl;
		if(N==0)
		{
			availPath++;
		}
		if(S==0)
		{
			availPath++;
		}
		if(E==0)
		{
			availPath++;
		}
		if(W==0)
		{
			availPath++;
		}
		cout << "available moves: " << availPath << endl << endl;
//		system("PAUSE");
		sleep(1000000);

		if(availPath==0 && done==0)
		{
			if(N==1)
			{
				Maze[row][col] = 4;
				row--;
				prevMove = 1;
				theStack.pop();
			}
			else if(S==1)
			{
				Maze[row][col] = 4;
				row++;
				prevMove = 3;
				theStack.pop();
			}
			else if(E==1)
			{
				Maze[row][col] = 4;
				col++;
				prevMove = 2;
				theStack.pop();
			}
			else if(W==1)
			{
				Maze[row][col] = 4;
				col--;
				prevMove = 4;
				theStack.pop();
			}
			//end of maze
			if(N==3)
			{
				Maze[row][col] = 1;
				row--;
				prevMove = 1;
				theStack.push(1);
				done = 1;
			}
			else if(S==3)
			{
				Maze[row][col] = 1;
				row++;
				prevMove = 3;
				theStack.push(3);
				done = 1;
			}
			else if(E==3)
			{
				Maze[row][col] = 1;
				col++;
				prevMove = 2;
				theStack.push(2);
				done = 1;
			}
			else if(W==3)
			{
				Maze[row][col] = 1;
				col--;
				prevMove = 4;
				theStack.push(4);
				done = 1;
			}
		} //end avail=0 if
		else if(availPath==1 && done==0)
		{
			if(N==0)
			{
				Maze[row][col] = 1;
				row--;
				prevMove = 1;
				theStack.push(1);
			}
			else if(S==0)
			{
				Maze[row][col] = 1;
				row++;
				prevMove = 3;
				theStack.push(3);
			}
			else if(E==0)
			{
				Maze[row][col] = 1;
				col++;
				prevMove = 2;
				theStack.push(2);
			}
			else if(W==0)
			{
				Maze[row][col] = 1;
				col--;
				prevMove = 4;
				theStack.push(4);
			}
		}//end avail=1 if 

		else if(availPath==2 && done==0)
		{
			if(prevMove==1)
			{
				if(W==0)
				{
					Maze[row][col] = 1;
					col--;
					prevMove = 4;
					theStack.push(4);
				}
				else if(N==0)
				{
					Maze[row][col] = 1;
					row--;
					prevMove = 1;
					theStack.push(1);
				}
				else if(E==0)
				{
					Maze[row][col] = 1;
					col++;
					prevMove = 2;
					theStack.push(2);
				}
			} //end prevMove = North
			
			else if(prevMove==2)
			{
				if(N==0)
				{
					Maze[row][col] = 1;
					row--;
					prevMove = 1;
					theStack.push(1);
				}
				else if(E==0)
				{
					Maze[row][col] = 1;
					col++;
					prevMove = 2;
					theStack.push(2);
				}
				else if(S==0)
				{
					Maze[row][col] = 1;
					row++;
					prevMove = 3;
					theStack.push(3);
				}
			} //end prevMove = East
			else if(prevMove==3)
			{
				if(E==0)
				{
					Maze[row][col] = 1;
					col++;
					prevMove = 2;
					theStack.push(2);
				}
				else if(S==0)
				{
					Maze[row][col] = 1;
					row++;
					prevMove = 3;
					theStack.push(3);
				}
				else if(W==0)
				{
					Maze[row][col] = 1;
					col--;
					prevMove = 4;
					theStack.push(4);
				}
			} //end prevMove = South
			else if(prevMove==4)
			{
				if(S==0)
				{
					Maze[row][col] = 1;
					row++;
					prevMove = 3;
					theStack.push(3);
				}
				else if(W==0)
				{
					Maze[row][col] = 1;
					col--;
					prevMove = 4;
					theStack.push(4);
				}
				else if(N==0)
				{
					Maze[row][col] = 1;
					row--;
					prevMove = 1;
					theStack.push(1);
				}
			} //end prevMove = West
		}//end avail>=2 if
		if(done==0)
		{
			nextDir();
		}
		else
		{
			display();
			cout << "Hurray, You Finished!!!" << endl;
		}
	}

//Array is 19 across, 10 down
//walls = -1
//available path = 0;
//prev visited = 1;
//start = 2, end = 3;
//been to but don't go = 4;

	void redoStack()
	{
		while(!theStack.empty())
		{
			revStack.push(theStack.top());
			theStack.pop();
		}
	}
	
	void redoMaze()
	{
		int done = 0;
		theMaze();
		display();
//		system("PAUSE");
		sleep(1000000);
		int top = revStack.top();
		if(revStack.empty() && revStack.size()==0)
		{
			done = 1;
		}
		else if(top==1)
		{
			Maze[row][col]=1;
			row--;
			revStack.pop();
		}
		else if(top==2)
		{
			Maze[row][col]=1;
			col++;
			revStack.pop();
		}
		else if(top==3)
		{
			Maze[row][col]=1;
			row++;
			revStack.pop();
		}
		else if(top==4)
		{
			Maze[row][col]=1;
			col--;
			revStack.pop();
		}

		
		if(done==0)
		{
			redoMaze();
		}
		else
		{
			display();
			cout << "Hurray, You Finished!!!" << endl;
		}

	}

};

int main()
{
	mazer MyMaze;
	MyMaze.begin();
	MyMaze.theMaze();
	MyMaze.nextDir();
	MyMaze.redoBegin();
	MyMaze.sleep(2500);
	MyMaze.redoStack();
	MyMaze.redoMaze();
	return 1;
}