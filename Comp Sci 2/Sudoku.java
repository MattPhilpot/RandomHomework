public class Sudoku
{
	int[][] sudoku_main = new int[9][9];
	boolean next_method = true;
	public Sudoku(int[][] k)
	{
		sudoku_main = k;
	}
	
	void solve_main()
	{
		for(int i = 0;i<9;i++);
		{
			for(int j = 0;j<9;j++)
			{
				if(sudoku_main[i][j]==0)
				{
					solve_methods(i, j);
				}
			}
		}
	}
	
	void solve_methods(int i, int j)
	{
		if(next_method==true) //how does solve_methods decide?
		{
			single_option(i,j);
		}
		
	}
	
	void single_option(int i, int j)
	{
		int[] x_row = {1,2,3,4,5,6,7,8,9};
		int[] y_row = {1,2,3,4,5,6,7,8,9};
		for(int x=0;x<9;x++)
		{
			if(sudoku_main[x][y]!=0)
			{
				x_row = remove_int(sudoku_main[x][y], x_row);
			}
		}
		for(int y=0;y<9;y++)
		{
			if(sudoku_main[x][y]!=0)
			{
				y_row = remove_int(sudoku_main[x][y], x_row);
			}
		}
	}
	
	static int remove_int(int x, int[] array)
	{
		int i = 0;
		int temp[] = new int[array.length-1];
		while(i<array.length)
		{
			if(array[i]!=x)
				temp[i]=array[i];
			if(array[i]==x)
				i--;
			i++;
		}
		return temp[];
	}
	
	void display()
	{
		for(int i = 0;i<9;i++)
		{
			for(int j = 0;j<9;j++)
			{
				if(sudoku_main[i][j]==0)
					System.out.print("  ");
				if(j==2 || j==5)
					System.out.print(" |");
				if(j==8)
					System.out.println();
			}
			if(i==2 || i==5)
				System.out.println("---------------------------");
		}
	}
}