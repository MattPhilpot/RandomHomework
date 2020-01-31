import javax.swing.*;
import javax.swing.table.*;
import java.awt.event.*;
import java.awt.*;
import java.util.*;
import java.io.*;

class KTimer extends JTextField implements Runnable
{
	MainTable mt;
	int minutes;
	int seconds;
	
	boolean start;
	
	KTimer(MainTable mt)
	{
		super(4);
		this.mt = mt;
		minutes = 0;
		seconds = 0;
		start = false;
		Font f = new Font("Times New Roman", Font.BOLD, 18);
		setFont(f);
		setEditable(false);
		setHorizontalAlignment(JTextField.RIGHT);
		String textToSet = "";
		if (minutes < 10)
		{
			textToSet = textToSet + "0";
		}
		textToSet = textToSet + minutes + ":";
		if (seconds < 10)
		{
			textToSet = textToSet + "0";
		}
		textToSet = textToSet + seconds;
		setText(textToSet);
	}
	
	public void run()
	{
		while (Thread.currentThread().isAlive())
		{
			try
			{
				Thread.sleep(100);
			}
			catch (Exception e){};
			
			while(start)
			{
				String textToSet = "";
				if (minutes < 10)
				{
					textToSet = textToSet + "0";
				}
				textToSet = textToSet + minutes + ":";
				if (seconds < 10)
				{
					textToSet = textToSet + "0";
				}
				textToSet = textToSet + seconds;
				setText(textToSet);
				
				try
				{
					Thread.sleep(1000);
				}
				catch (Exception e){};
				
				if (seconds == 59)
				{
					minutes++;
					seconds = 0;
				}
				else
				{
					seconds++;
				}
				
				if (!mt.hasEmptySlots())
				{
					stop();
					mt.validateSolve();
					mt.repaint();
				}
				
				if (mt.isEmpty())
				{
					reset();
				}
			}
		}
	}
	
	void start()
	{
		start = true;
	}
	
	void stop()
	{
		Thread.currentThread().interrupt();
		start = false;
	}
	
	void reset()
	{
		setText("00:00");
		start = false;
		seconds = 0;
		minutes = 0;
	}
	
	boolean tryAgain()
	{
		return seconds > 20;
	}
}
class KSector
{
	int[][] rowSecs;
	int[][] colSecs;
	int mode;
		
	KSector(int mode)
	{
		this.mode = mode;
		
		switch (mode)
		{
			case 3:
				rowSecs = new int[9][3];
				
				rowSecs[0][0] = 1;
				rowSecs[0][1] = 2;
				rowSecs[0][2] = 3;
				rowSecs[1][0] = 1;
				rowSecs[1][1] = 2;
				rowSecs[1][2] = 3;
				rowSecs[2][0] = 1;
				rowSecs[2][1] = 2;
				rowSecs[2][2] = 3;
				rowSecs[3][0] = 4;
				rowSecs[3][1] = 5;
				rowSecs[3][2] = 6;
				rowSecs[4][0] = 4;
				rowSecs[4][1] = 5;
				rowSecs[4][2] = 6;
				rowSecs[5][0] = 4;
				rowSecs[5][1] = 5;
				rowSecs[5][2] = 6;
				rowSecs[6][0] = 7;
				rowSecs[6][1] = 8;
				rowSecs[6][2] = 9;
				rowSecs[7][0] = 7;
				rowSecs[7][1] = 8;
				rowSecs[7][2] = 9;
				rowSecs[8][0] = 7;
				rowSecs[8][1] = 8;
				rowSecs[8][2] = 9;
				
				colSecs = new int[9][3];
				
				colSecs[0][0] = 1;
				colSecs[0][1] = 4;
				colSecs[0][2] = 7;
				colSecs[1][0] = 1;
				colSecs[1][1] = 4;
				colSecs[1][2] = 7;
				colSecs[2][0] = 1;
				colSecs[2][1] = 4;
				colSecs[2][2] = 7;
				colSecs[3][0] = 2;
				colSecs[3][1] = 5;
				colSecs[3][2] = 8;
				colSecs[4][0] = 2;
				colSecs[4][1] = 5;
				colSecs[4][2] = 8;
				colSecs[5][0] = 2;
				colSecs[5][1] = 5;
				colSecs[5][2] = 8;
				colSecs[6][0] = 3;
				colSecs[6][1] = 6;
				colSecs[6][2] = 9;
				colSecs[7][0] = 3;
				colSecs[7][1] = 6;
				colSecs[7][2] = 9;
				colSecs[8][0] = 3;
				colSecs[8][1] = 6;
				colSecs[8][2] = 9;
			break;
			
			case 4:
				rowSecs = new int[16][4];
				
				rowSecs[0][0] = 1;
				rowSecs[0][1] = 2;
				rowSecs[0][2] = 3;
				rowSecs[0][3] = 4;
				rowSecs[1][0] = 1;
				rowSecs[1][1] = 2;
				rowSecs[1][2] = 3;
				rowSecs[1][3] = 4;
				rowSecs[2][0] = 1;
				rowSecs[2][1] = 2;
				rowSecs[2][2] = 3;
				rowSecs[2][3] = 4;
				rowSecs[3][0] = 1;
				rowSecs[3][1] = 2;
				rowSecs[3][2] = 3;
				rowSecs[3][3] = 4;
				rowSecs[4][0] = 5;
				rowSecs[4][1] = 6;
				rowSecs[4][2] = 7;
				rowSecs[4][3] = 8;
				rowSecs[5][0] = 5;
				rowSecs[5][1] = 6;
				rowSecs[5][2] = 7;
				rowSecs[5][3] = 8;
				rowSecs[6][0] = 5;
				rowSecs[6][1] = 6;
				rowSecs[6][2] = 7;
				rowSecs[6][3] = 8;
				rowSecs[7][0] = 5;
				rowSecs[7][1] = 6;
				rowSecs[7][2] = 7;
				rowSecs[7][3] = 8;
				rowSecs[8][0] = 9;
				rowSecs[8][1] = 10;
				rowSecs[8][2] = 11;
				rowSecs[8][3] = 12;
				rowSecs[9][0] = 9;
				rowSecs[9][1] = 10;
				rowSecs[9][2] = 11;
				rowSecs[9][3] = 12;
				rowSecs[10][0] = 9;
				rowSecs[10][1] = 10;
				rowSecs[10][2] = 11;
				rowSecs[10][3] = 12;
				rowSecs[11][0] = 9;
				rowSecs[11][1] = 10;
				rowSecs[11][2] = 11;
				rowSecs[11][3] = 12;
				rowSecs[12][0] = 13;
				rowSecs[12][1] = 14;
				rowSecs[12][2] = 15;
				rowSecs[12][3] = 16;
				rowSecs[13][0] = 13;
				rowSecs[13][1] = 14;
				rowSecs[13][2] = 15;
				rowSecs[13][3] = 16;
				rowSecs[14][0] = 13;
				rowSecs[14][1] = 14;
				rowSecs[14][2] = 15;
				rowSecs[14][3] = 16;
				rowSecs[15][0] = 13;
				rowSecs[15][1] = 14;
				rowSecs[15][2] = 15;
				rowSecs[15][3] = 16;
				
				colSecs = new int[16][4];
				
				colSecs[0][0] = 1;
				colSecs[0][1] = 5;
				colSecs[0][2] = 9;
				colSecs[0][3] = 13;
				colSecs[1][0] = 1;
				colSecs[1][1] = 5;
				colSecs[1][2] = 9;
				colSecs[1][3] = 13;
				colSecs[2][0] = 1;
				colSecs[2][1] = 5;
				colSecs[2][2] = 9;
				colSecs[2][3] = 13;
				colSecs[3][0] = 1;
				colSecs[3][1] = 5;
				colSecs[3][2] = 9;
				colSecs[3][3] = 13;
				colSecs[4][0] = 2;
				colSecs[4][1] = 6;
				colSecs[4][2] = 10;
				colSecs[4][3] = 14;
				colSecs[5][0] = 2;
				colSecs[5][1] = 6;
				colSecs[5][2] = 10;
				colSecs[5][3] = 14;
				colSecs[6][0] = 2;
				colSecs[6][1] = 6;
				colSecs[6][2] = 10;
				colSecs[6][3] = 14;
				colSecs[7][0] = 2;
				colSecs[7][1] = 6;
				colSecs[7][2] = 10;
				colSecs[7][3] = 14;
				colSecs[8][0] = 3;
				colSecs[8][1] = 7;
				colSecs[8][2] = 11;
				colSecs[8][3] = 15;
				colSecs[9][0] = 3;
				colSecs[9][1] = 7;
				colSecs[9][2] = 11;
				colSecs[9][3] = 15;
				colSecs[10][0] = 3;
				colSecs[10][1] = 7;
				colSecs[10][2] = 11;
				colSecs[10][3] = 15;
				colSecs[11][0] = 3;
				colSecs[11][1] = 7;
				colSecs[11][2] = 11;
				colSecs[11][3] = 15;
				colSecs[12][0] = 4;
				colSecs[12][1] = 8;
				colSecs[12][2] = 12;
				colSecs[12][3] = 16;
				colSecs[13][0] = 4;
				colSecs[13][1] = 8;
				colSecs[13][2] = 12;
				colSecs[13][3] = 16;
				colSecs[14][0] = 4;
				colSecs[14][1] = 8;
				colSecs[14][2] = 12;
				colSecs[14][3] = 16;
				colSecs[15][0] = 4;
				colSecs[15][1] = 8;
				colSecs[15][2] = 12;
				colSecs[15][3] = 16;
			break;
		}
	}
	
	int[] getSectorsOfRow(int row)
	{
		int[] temp = new int[0];
		
		for (int i = 0; i < mode; i++)
		{
			temp = Logic.addInt(temp, rowSecs[row][i]);
		}
		
		return temp;
	}
	
	int[] getSectorsOfColumn(int col)
	{
		int[] temp = new int[0];
		
		for (int i = 0; i < mode; i++)
		{
			temp = Logic.addInt(temp, colSecs[col][i]);
		}
		
		return temp;
	}
	
	boolean rowContainsSector(int row, int sector)
	{
		for (int i = 0; i < mode; i++)
		{
			if (rowSecs[row][i] == sector)
			{
				return true;
			}
		}
		
		return false;
	}
	
	boolean columnContainsSector(int col, int sector)
	{
		for (int i = 0; i < mode; i++)
		{
			if (colSecs[col][i] == sector)
			{
				return true;
			}
		}
		
		return false;
	}
}
class KD
{
	int x;
	int y;

	KD(int i, int j)
	{
		x = i;
		y = j;
	}

	int getX()
	{
		return x;
	}

	int getY()
	{
		return y;
	}
}
class CustomCellEditor extends DefaultCellEditor implements TableCellEditor
{
	JTextField j;
	KTimer kt;
	KTable parent;
	
	public CustomCellEditor(KTable p)
	{
		super(new JTextField());
		j = new JTextField();
		j.setFont(new Font("Serif", Font.BOLD, 20));
		j.setHorizontalAlignment(JTextField.CENTER);
		parent = p;
	}
	
	public Component getTableCellEditorComponent(JTable table, Object value, boolean isSelected, int row, int column)
	{
		parent.resetColor(row, column);
		
		if (j.isEditable())
		{
			j.setText("");
		}
		else
		{
			j.setText((String)value);
		}
		
		return j;
	}
	
	public Object getCellEditorValue()
	{
		String s = j.getText();
		String toReturn = "";
		
		for (int i = 0; i < s.length(); i++)
		{
			if (s.charAt(i) != ' ')
			{
				toReturn = toReturn + s.toUpperCase().charAt(i);
				break;
			}
		}
		
		kt.start();
		return toReturn;
	}
	
	void setEditable(boolean b)
	{
		j.setEditable(b);
	}
	
	void setTimer(KTimer kt)
	{
		this.kt = kt;
	}
}
class CustomCellRender extends DefaultTableCellRenderer implements TableCellRenderer
{
	char[] allow;
	Color[][] fontcolor;
	
    public CustomCellRender(char[] allow, Color[][] fontcolor)
    {
    	super();
    	this.allow = allow;
    	this.fontcolor = fontcolor;
    }

	public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int column)
	{
		String s = (String)value;
		s = s.replaceAll(" ", "");
		
		if (s.length() > 0)
		{
			if (!Logic.arrayContains(allow, s.charAt(0)))
			{
				setBackground(Color.red);
				setForeground(Color.black);
			}
			else
			{
				setBackground(Color.white);
				setForeground(fontcolor[row][column]);
			}
		}
		else
		{
			setBackground(Color.white);
			setForeground(fontcolor[row][column]);
		}
		
		JLabel toReturn = (JLabel)super.getTableCellRendererComponent(table, value, isSelected, hasFocus, row, column);
		toReturn.setFont(new Font("Serif", Font.BOLD, 20));
		toReturn.setHorizontalAlignment(SwingConstants.CENTER);
		
		return toReturn;           
	}
}
class KTable extends JTable
{
	JTextField[][] values;
	Color[][] fontcolors;
	CustomCellRender ccr;
	CustomCellEditor cce;
	int sector;
	int dim;
	Color defaultFontColor = Color.red;

	KTable(int i, int i2, char[] allow)
	{
		super(i2, i2);
		
		fontcolors = new Color[i2][i2];
		
		for (int x = 0; x < i2; x++)
		{
			for (int j = 0; j < i2; j++)
			{
				fontcolors[x][j] = Color.red;
			}
		}
		
		ccr = new CustomCellRender(allow, fontcolors);
		setDefaultRenderer(Object.class, ccr);
		cce = new CustomCellEditor(this);
		setDefaultEditor(Object.class, cce);
		setGridColor(Color.blue);
		dim = i2;
		sector = i;
		
		addFocusListener(new java.awt.event.FocusAdapter()
		{
			public void focusLost(FocusEvent evt)
			{
				cce.stopCellEditing();
			}
		});
		
		for (int t2 = 0; t2 < i2; t2++)
		{
			getColumnModel().getColumn(t2).setPreferredWidth(33);
			
			for (int t3 = 0; t3 < i2; t3++)
			{
				
				setValueAt("", t2, t3);
			}
		}
		
		setRowHeight(33);
	}
	
	void resetColor(int i, int j)
	{
		fontcolors[i][j] = defaultFontColor;
	}
	
	public void setForeground(Color c)
	{
		for (int x = 0; x < dim; x++)
		{
			for (int j = 0; j < dim; j++)
			{
				fontcolors[x][j] = c;
			}
		}
	}
	
	void setValueAt(String s, int row, int col)
	{
		fontcolors[row][col] = Color.red;
		super.setValueAt(s, row, col);
	}
	
	void setValueAt(Color c, String s, int row, int col)
	{
		fontcolors[row][col] = c;
		super.setValueAt(s, row, col);
	}
	
	void setEditable(boolean b)
	{
		cce.setEditable(b);
	}
	
	void setTimer(KTimer kt)
	{
		cce.setTimer(kt);
	}

	int getSector()
	{
		return sector;
	}

	char[] returnValues()
	{
		char[] temp = new char[0];

		for (int i = 0; i < dim; i++)
		{
			for (int j = 0; j < dim; j++)
			{
				String s = (String)getValueAt(i, j);
				s = s.replaceAll(" ", "");
				
				if (s.length() > 0)
				{
					temp = Logic.addChar(temp, s.charAt(0));
				}
			}
		}

		return temp;
	}

	char[] returnValuesOfRow(int i)
	{
		char[] temp = new char[0];

		try
		{
			for (int j = 0; j < dim; j++)
			{
				String s = (String)getValueAt(i, j);
				s = s.replaceAll(" ", "");
				
				if (s.length() > 0)
				{
					temp = Logic.addChar(temp, s.charAt(0));
				}
			}
		}
		catch (Exception e)
		{

		}
		finally
		{
			return temp;
		}
	}

	char[] returnValuesOfColumn(int i)
	{
		char[] temp = new char[0];

		try
		{
			for (int j = 0; j < dim; j++)
			{
				String s = (String)getValueAt(j, i);
				s = s.replaceAll(" ", "");
				
				if (s.length() > 0)
				{
					temp = Logic.addChar(temp, s.charAt(0));
				}
			}
		}
		catch (Exception e)
		{

		}
		finally
		{
			return temp;
		}
	}
}
class Logic
{
	static MainTable[] addMT(MainTable[] array, MainTable i)
	{
		MainTable[] temp = new MainTable[array.length + 1];

		for (int x = 0; x < array.length; x++)
		{
			temp[x] = array[x];
		}

		temp[array.length] = i;

		return temp;
	}
	
	static int[] addInt(int[] array, int i)
	{
		int[] temp = new int[array.length + 1];

		for (int x = 0; x < array.length; x++)
		{
			temp[x] = array[x];
		}

		temp[array.length] = i;

		return temp;
	}
	
	static char[] addChar(char[] array, char[] i)
	{
		char[] temp = new char[array.length + i.length];

		for (int x = 0; x < array.length; x++)
		{
			temp[x] = array[x];
		}

		for (int x = array.length; x < array.length + i.length; x++)
		{
			temp[x] = i[x - array.length];
		}

		return temp;
	}
	
	static char[] addChar(char[] array, char i)
	{
		char[] temp = new char[array.length + 1];

		for (int x = 0; x < array.length; x++)
		{
			temp[x] = array[x];
		}

		temp[array.length] = i;

		return temp;
	}
	
	static char[] removeChar(char[] array, char i)
	{
		char[] temp = new char[0];

		for (int x = 0; x < array.length; x++)
		{
			if (array[x] != i)
			{
				temp = Logic.addChar(temp, array[x]);
			}
		}

		return temp;
	}

	static boolean arrayContains(char[] original, char checkAgainst)
	{
		for (int x = 0; x < original.length; x++)
		{
			if (original[x] == checkAgainst)
			{
				return true;
			}
		}

		return false;
	}

	static KD findSingleTrue(boolean[][] array)
	{
		KD toReturn = null;
		int count = 0;
		
		for (int x = 0; x < array[0].length; x++)
		{
			for (int y = 0; y < array[0].length; y++)
			{
				if (array[x][y] == true)
				{
					toReturn = new KD(x, y);
					count++;
				}
			}
		}
		
		if (count != 1)
		{
			toReturn = null;
		}
		
		return toReturn;
	}
	
	static int findSinglePossibleRow(boolean[][] array, int sector)
	{
		int rowsWithTrue = 0;
		int row = -1;
		
		for (int i = 0; i < array[0].length; i++)
		{
			boolean tri = false;
			
			for (int j = 0; j < array[0].length; j++)
			{
				if (array[i][j] == true)
				{
					tri = true;
					row = i;
				}
			}
			
			if (tri)
			{
				rowsWithTrue++;
			}
		}
		
		if (rowsWithTrue == 1)
		{
			switch (array[0].length)
			{
				case 3:
					switch (sector)
					{
						case 4:
						case 5:
						case 6:
							row += 3;
						break;
						case 7:
						case 8:
						case 9:
							row += 6;
						break;
					}
				break;
				
				case 4:
				break;
			}
		}
		else
		{
			row = -1;
		}
		
		return row;
	}
	
	static int findSinglePossibleCol(boolean[][] array, int sector)
	{
		int colsWithTrue = 0;
		int col = -1;
		
		for (int i = 0; i < array[0].length; i++)
		{
			boolean tri = false;
			
			for (int j = 0; j < array[0].length; j++)
			{
				if (array[j][i] == true)
				{
					tri = true;
					col = i;
				}
			}
			
			if (tri)
			{
				colsWithTrue++;
			}
		}
		
		if (colsWithTrue == 1)
		{
			switch (array[0].length)
			{
				case 3:
				switch (sector)
				{
					case 4:
					case 5:
					case 6:
						col += 3;
					break;
					case 7:
					case 8:
					case 9:
						col += 6;
					break;
				}
				break;
				
				case 4:
				break;
			}
		}
		else
		{
			col = -1;
		}
		
		return col;
	}
	
	static char findChar(String s)
	{
		s = s.replaceAll(" ", "");
		
		if (s.length() > 0)
		{
			return s.charAt(0);
		}
		
		return 'z';
	}
	
	static int findSingleTrue(boolean[] array)
	{
		int toReturn = -1;
		int count = 0;
		
		for (int x = 0; x < array.length; x++)
		{
			if (array[x] == true)
			{
				toReturn = x;
				count++;
			}
		}
		
		if (count != 1)
		{
			toReturn = -1;
		}
		
		return toReturn;
	}
	
	static boolean checkRepeatingValues(char[] array)
	{
		char[] temp = new char[0];
		
		for (int x = 0; x < array.length; x++)
		{
			if (arrayContains(temp, array[x]))
			{
				return true;
			}
			else
			{
				temp = addChar(temp, array[x]);
			}
		}
		
		return false;
	}
	
	static void display(boolean[][] ar)
	{
		for (int i = 0; i < ar[0].length; i++)
		{
			for (int j = 0; j < ar[0].length; j++)
			{
				System.out.print(ar[i][j] + " ");
			}
			
			System.out.println();
		}
	}
}
class HelpFrame extends JFrame implements ActionListener, Runnable
{
	JMenuBar jmb;
	JButton about;
	JButton help;
	
	JTextArea jt;
	JScrollPane jsp;
	String[] abouttext;
	String[] helptext;
	
	HelpFrame()
	{
		
	}
	
	public void run()
	{
		jmb = new JMenuBar();
		about = new JButton("About");
		about.addActionListener(this);
		help = new JButton("Help");
		help.addActionListener(this);
		
		String[] ta = {"Written by Matthew Philpot and Preston Henninger\n\n",
					   "Special thanks to Kyle Chamberlain for coding help!"};
		abouttext = ta;
		
		String[] ha = {"~~~~~~~~~~~What is a sudoku puzzle?~~~~~~~~~~~\n",
					   "A sudoku is a japanese number puzzle.  Within\n",
					   "each row, each column, and each 3x3 square\n",
					   "there are the numbers 1 - 9.  They don't repeat,\n",
					   "and they are all there.  Your job as the solver\n",
					   "is to fill in the missing numbers.\n",
					   "\n",
					   "This utility is designed to solve any sudoku \n",
					   "puzzle (including a blank one!).  It also\n",
					   "provides you with an environment to solve your\n",
					   "own puzzles.\n",
					   "\n",
					   "\n",
					   "~~~~~~~~~~~How to use this program~~~~~~~~~~~~\n",
					   "File\n",
					   "----\n",
					   "The two options here are loading and saving\n",
					   "files.  This lets you save a puzzle you are\n",
					   "working on if you have to stop in the middle.\n",
					   "\n",
					   "Actions\n",
					   "-------\n",
					   "This is where you'll find all the tools at your\n",
					   "disposal for solving and manipulating puzzles.\n",
					   "The attempt to solve menu is where you will find\n",
					   "the logical methods for solving puzzles.  Check\n",
					   "the ones you would like to use, then click solve.\n",
					   "The solver will use the logical methods in order\n",
					   "from top to bottom on the menu.\n",
					   "The details of each solving method will not be\n",
					   "divulged in this help document.\n",
					   "\n",
					   "The 'Give me a hint' button uses only the logic\n",
					   "that you have checked.  If no buttons are\n",
					   "checked, no hints will be given.\n",
					   "\n",
					   "There are not many puzzles that can be solved\n",
					   "by only one logical method.  Some puzzles cannot\n",
					   "be solved by solid logic at all.  Dynamic number\n",
					   "allocation will solve any puzzle, but in contrast\n",
					   "is by far the slowest method.\n",
					   "\n",
					   "Puzzles\n",
					   "-------\n",
					   "This menu is pretty self explanatory.  There are\n",
					   "30 saved puzzles per sudoku mode, and this program\n",
					   "has the capability to generate puzzles.\n",
					   "\n",
					   "Options\n",
					   "-------\n",
					   "The speed option will let you slow down the solving\n",
					   "of a puzzle so you can see exactly where it is\n",
					   "putting numbers.  The number in the field is the\n",
					   "amount of miliseconds the puzzle will wait between\n",
					   "filled in numbers.  (1000 in the field will put a\n",
					   "1 second timer between filled in numbers).\n",
					   "The color option is pretty self-explanatory.  You can\n",
					   "customize the screen to fit your artistic whims.\n",
		};
		helptext = ha;
		
		jt = new JTextArea();
		
		for (int i = 0; i < abouttext.length; i++)
		{
			jt.append(abouttext[i]);
		}
		
		jsp = new JScrollPane(jt);
		
		getContentPane().setLayout(new BorderLayout());
		getContentPane().add(jsp, BorderLayout.CENTER);
		
		jmb.add(about);
		jmb.add(help);
		
		setJMenuBar(jmb);
		setTitle("About");
		setSize(320, 340);
		setResizable(false);
		setLocation(400, 200);
		setVisible(true);
		
	}
	
	public void actionPerformed(ActionEvent evt)
	{
		jt.setText("");
		
		if (evt.getActionCommand().equals("About"))
		{
			for (int i = 0; i < abouttext.length; i++)
			{
				jt.append(abouttext[i]);
			}
		}
		if (evt.getActionCommand().equals("Help"))
		{
			for (int i = 0; i < helptext.length; i++)
			{
				jt.append(helptext[i]);
			}
		}
		
		jt.setCaretPosition(0);
	}
}
class SolveFrame extends JFrame implements ActionListener
{
	JMenuBar jmb;
	JMenu file;
	JMenu action;
	JMenu puzzles;
	JMenu modeMenu;
	JMenu options;
	JMenu normalEasy;
	JMenu normalMed;
	JMenu normalHard;
	JMenu hexEasy;
	JMenu hexMed;
	JMenu hexHard;
	JMenu solve;
	JMenu colors;
	JMenu speed;
	JCheckBox logic1;
	JCheckBox logic2;
	JCheckBox logic3;
	JCheckBox logic4;
	JCheckBox logic5;
	JCheckBox logicfailsafe;
	JTextField sleep;
	JMenuItem execute;
	JMenuItem hintButton;
	JMenuItem stopSolving;
	JMenuItem importPuz;
	JMenuItem exportPuz;
	JMenuItem clear;
	JMenuItem[] normalEasyPuzs;
	JMenuItem[] normalMedPuzs;
	JMenuItem[] normalHardPuzs;
	JMenuItem[] hexEasyPuzs;
	JMenuItem[] hexMedPuzs;
	JMenuItem[] hexHardPuzs;
	JMenuItem generate;
	JMenuItem help;
	JMenuItem mode3;
	JMenuItem mode4;
	JMenuItem backcolor;
	JMenuItem gridcolor;
	JPanel buttonMenu;
	JButton clearAll;
	JButton setAll;
	JProgressBar jpb;
	JPanel tables;
	KTimer timer;
	Thread t;
	MainTable mt;
	PuzzleSolver ps;
	PuzzleGenerator pg;
	
	boolean operationConfirm;
	boolean fastLogic;
	
	int mode;

	SolveFrame(int mode)
	{
		jmb = new JMenuBar();
		file = new JMenu("File");
		action = new JMenu("Actions");
		puzzles = new JMenu("Puzzles");
		modeMenu = new JMenu("Mode");
		options = new JMenu("Options");
		speed = new JMenu("Speed");
		colors = new JMenu("Colors");
		normalEasy = new JMenu("Easy");
		normalMed = new JMenu("Medium");
		normalHard = new JMenu("Hard");
		hexEasy = new JMenu("Easy");
		hexMed = new JMenu("Medium");
		hexHard = new JMenu("Hard");
		solve = new JMenu("Solve With");
		stopSolving = new JMenuItem("Stop solving");
		stopSolving.addActionListener(this);
		stopSolving.setActionCommand("stop");
		logic1 = new JCheckBox("Single cell possibility logic");
		logic2 = new JCheckBox("Sector elimination logic");
		logic3 = new JCheckBox("Row elimination logic");
		logic4 = new JCheckBox("Column elimination logic");
		logic5 = new JCheckBox("Phantom number placement");
		logicfailsafe = new JCheckBox("Dynamic number allocation");
		sleep = new JTextField(5);
		sleep.setText("0");
		buttonMenu = new JPanel();
		clearAll = new JButton("Clear All");
		clearAll.addActionListener(this);
		clearAll.setActionCommand("clearAll");
		setAll = new JButton("Select All");
		setAll.addActionListener(this);
		setAll.setActionCommand("setAll");
		execute = new JMenuItem("Solve!");
		execute.addActionListener(this);
		execute.setActionCommand("solve");
		hintButton = new JMenuItem("Give me a hint!");
		hintButton.addActionListener(this);
		hintButton.setActionCommand("hint");
		importPuz = new JMenuItem("Load Puzzle");
		importPuz.addActionListener(this);
		importPuz.setActionCommand("loadpuz");
		exportPuz = new JMenuItem("Save Puzzle");
		exportPuz.addActionListener(this);
		exportPuz.setActionCommand("save");
		clear = new JMenuItem("Clear puzzle");
		clear.addActionListener(this);
		clear.setActionCommand("clear");
		normalEasyPuzs = new JMenuItem[10];
		normalMedPuzs = new JMenuItem[10];
		normalHardPuzs = new JMenuItem[10];
		hexEasyPuzs = new JMenuItem[10];
		hexMedPuzs = new JMenuItem[10];
		hexHardPuzs = new JMenuItem[10];
		mode3 = new JMenuItem("Normal");
		mode3.addActionListener(this);
		mode3.setActionCommand("mode3");
		mode4 = new JMenuItem("Hexadecimal");
		mode4.addActionListener(this);
		mode4.setActionCommand("mode4");
		backcolor = new JMenuItem("Background");
		backcolor.addActionListener(this);
		gridcolor = new JMenuItem("Grid");
		gridcolor.addActionListener(this);
		jpb = new JProgressBar();
		help = new JMenuItem("Help");
		help.addActionListener(this);
		generate = new JMenuItem("Generate random puzzle");
		generate.addActionListener(this);
		generate.setActionCommand("gen");
		
		for (int x = 0; x < 10; x++)
		{
			normalEasyPuzs[x] = new JMenuItem("Easy Puzzle " + (x + 1));
			normalEasyPuzs[x].addActionListener(this);
			normalEasyPuzs[x].setActionCommand("puzeasy" + x);
		}
		
		for (int x = 0; x < 10; x++)
		{
			normalMedPuzs[x] = new JMenuItem("Medium Puzzle " + (x + 1));
			normalMedPuzs[x].addActionListener(this);
			normalMedPuzs[x].setActionCommand("puzmed" + x);
		}

		for (int x = 0; x < 10; x++)
		{
			normalHardPuzs[x] = new JMenuItem("Hard Puzzle " + (x + 1));
			normalHardPuzs[x].addActionListener(this);
			normalHardPuzs[x].setActionCommand("puzhard" + x);
		}
		
		for (int x = 0; x < 10; x++)
		{
			hexEasyPuzs[x] = new JMenuItem("Easy Puzzle " + (x + 1));
			hexEasyPuzs[x].addActionListener(this);
			hexEasyPuzs[x].setActionCommand("puzhexeasy" + x);
		}
		
		for (int x = 0; x < 10; x++)
		{
			hexMedPuzs[x] = new JMenuItem("Medium Puzzle " + (x + 1));
			hexMedPuzs[x].addActionListener(this);
			hexMedPuzs[x].setActionCommand("puzhexmed" + x);
		}
		
		for (int x = 0; x < 10; x++)
		{
			hexHardPuzs[x] = new JMenuItem("Hard Puzzle " + (x + 1));
			hexHardPuzs[x].addActionListener(this);
			hexHardPuzs[x].setActionCommand("puzhexhard" + x);
		}
		
		buttonMenu.setLayout(new GridLayout(0, 1));
		buttonMenu.add(setAll);
		buttonMenu.add(clearAll);
		solve.add(logic1);
		solve.add(logic2);
		solve.add(logic3);
		solve.add(logic4);
		solve.add(logic5);
		solve.add(logicfailsafe);
		solve.addSeparator();
		solve.add(buttonMenu);
		solve.addSeparator();
		solve.add(execute);
		file.add(importPuz);
		file.add(exportPuz);
		action.add(solve);
		action.add(hintButton);
		action.add(stopSolving);
		action.add(clear);
		modeMenu.add(mode3);
		modeMenu.add(mode4);
		colors.add(backcolor);
		colors.add(gridcolor);
		speed.add(sleep);
		options.add(speed);
		options.add(colors);
		puzzles.add(generate);

		for (int x = 0; x < 10; x++)
		{
			normalEasy.add(normalEasyPuzs[x]);
		}
		for (int x = 0; x < 10; x++)
		{
			normalMed.add(normalMedPuzs[x]);
		}
		for (int x = 0; x < 10; x++)
		{
			normalHard.add(normalHardPuzs[x]);
		}
		for (int x = 0; x < 10; x++)
		{
			hexEasy.add(hexEasyPuzs[x]);
		}
		for (int x = 0; x < 10; x++)
		{
			hexMed.add(hexMedPuzs[x]);
		}
		for (int x = 0; x < 10; x++)
		{
			hexHard.add(hexHardPuzs[x]);
		}
		
		jmb.add(file);
		jmb.add(action);
		jmb.add(puzzles);
		jmb.add(modeMenu);
		jmb.add(options);
		jmb.add(help);
		
		setTitle("Sudoku Solver");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setJMenuBar(jmb);
		setLocation(400, 200);
		setResizable(false);
		
		getContentPane().setLayout(new BorderLayout());
		getContentPane().add(jpb, BorderLayout.SOUTH);
		initializePuzzle(mode);
		setVisible(true);
	}
	
	void initializePuzzle(int i)
	{
		if (mode != i)
		{
			mode = i;
			setSize(i * (i * 33 + 10) + 5, i * (i * 33 + 10) + 65);
			
			mt = new MainTable(i);
			
			if (timer != null)
			{
				jmb.remove(timer);
			}
			
			timer = new KTimer(mt);
			new Thread(timer).start();
			mt.setTimer(timer);
			
			jmb.add(timer);
			
			if (tables != null)
			{
				getContentPane().remove(tables);
			}
			
			tables = new JPanel();
			tables.setBackground(Color.gray);
			tables.setLayout(new FlowLayout());
				
			for (int x = 0; x < i; x++)
			{
				for (int y = 0; y < i; y++)
				{
					tables.add(mt.getTable(x, y));
				}
			}
			
			getContentPane().add(tables, BorderLayout.CENTER);
			
			if (mode == 3)
			{
				puzzles.remove(hexEasy);
				puzzles.remove(hexMed);
				puzzles.remove(hexHard);
				puzzles.add(normalEasy);
				puzzles.add(normalMed);
				puzzles.add(normalHard);
			}
			else
			{
				puzzles.remove(normalEasy);
				puzzles.remove(normalMed);
				puzzles.remove(normalHard);
				puzzles.add(hexEasy);
				puzzles.add(hexMed);
				puzzles.add(hexHard);
			}
			
			repaint();
		}
	}

	public void actionPerformed(ActionEvent evt)
	{
		if (evt.getActionCommand().equals("Background"))
		{
			tables.setBackground(new JColorChooser().showDialog(this, "Background Color", Color.gray));
		}
		if (evt.getActionCommand().equals("Grid"))
		{
			mt.setGrid(new JColorChooser().showDialog(this, "Background Color", Color.blue));
		}
		if (evt.getActionCommand().equals("gen"))
		{
			operationStart();
			mt.clear();
			pg = new PuzzleGenerator(mt, jpb, timer);
			t = new Thread(pg);
			t.start();
		}
		if (evt.getActionCommand().equals("stop"))
		{
			jpb.setIndeterminate(false);
			
			if (ps != null)
			{
				ps.interrupt();
			}
			
			if (pg != null)
			{
				pg.cancelGen();
			}
		}
		if (evt.getActionCommand().equals("hint"))
		{
			ps = new PuzzleSolver(mt, logic1.isSelected(), logic2.isSelected(), logic3.isSelected(), logic4.isSelected(), logic5.isSelected(), logicfailsafe.isSelected(), false, jpb, "hint", 0);
			t = new Thread(ps);
			t.start();
		}
		if (evt.getActionCommand().equals("mode3"))
		{
			initializePuzzle(3);
		}
		if (evt.getActionCommand().equals("mode4"))
		{
			initializePuzzle(4);
		}
		if (evt.getActionCommand().equals("clearAll"))
		{
			logic1.setSelected(false);
			logic2.setSelected(false);
			logic3.setSelected(false);
			logic4.setSelected(false);
			logicfailsafe.setSelected(false);
		}
		if (evt.getActionCommand().equals("setAll"))
		{
			logic1.setSelected(true);
			logic2.setSelected(true);
			logic3.setSelected(true);
			logic4.setSelected(true);
			logicfailsafe.setSelected(true);
		}
		if (evt.getActionCommand().equals("Help"))
		{
			HelpFrame hf = new HelpFrame();
			Thread helpthread = new Thread(hf);
			helpthread.start();
		}
		if (evt.getActionCommand().equals("solve"))
		{
			int secondsToSleep = 0;
			
			try
			{
				secondsToSleep = Integer.parseInt(sleep.getText());
			}
			catch (Exception e)
			{
				JOptionPane.showMessageDialog(this, "Please enter a valid sleep number");
				return;
			}
			
			timer.start();
			ps = new PuzzleSolver(mt, logic1.isSelected(), logic2.isSelected(), logic3.isSelected(), logic4.isSelected(), logic5.isSelected(), logicfailsafe.isSelected(), false, jpb, "solve", secondsToSleep);
			t = new Thread(ps);
			t.start();
		}
		if (evt.getActionCommand().equals("loadpuz"))
		{
			try
			{
				PuzzleIO.loadPuzzle(mt);
			}
			catch (Exception e){}
		}
		if (evt.getActionCommand().equals("save"))
		{
			try
			{
				PuzzleIO.savePuzzle(mt);
			}
			catch (Exception e){}
		}
		if (evt.getActionCommand().equals("clear"))
		{
			timer.reset();
			clearPuzzle();
		}
		if (evt.getActionCommand().substring(0, 3).equals("puz"))
		{
			timer.reset();
			try
			{
				loadPuzzle(evt.getActionCommand());
			}
			catch (Exception e){}
		}
	}
	
	private void loadPuzzle(String puzname) throws Exception
	{
		Scanner stdin = new Scanner(getClass().getResourceAsStream(puzname + ".txt"));

		String[] s;

		for (int x = 0; x < mode * mode; x++)
		{
			s = stdin.nextLine().split(",");

			for (int y = 0; y < mode * mode; y++)
			{
				if (s[y].equals("-"))
				{
					mt.setValueAt(x, y, "");
				}
				else
				{
					mt.setValueAt(x, y, "" + s[y].toUpperCase(), Color.black);
				}
			}
		}
	}

	public void clearPuzzle()
	{
		for (int x = 0; x < mode * mode; x++)
		{
			for (int y = 0; y < mode * mode; y++)
			{
				mt.setValueAt(x, y, "");
			}
		}
	}
	
	void operationStart()
	{
		timer.reset();
		timer.start();
		jpb.setIndeterminate(true);
	}
}
class PuzzleIO
{
	static File f;
	
	public static void savePuzzle(MainTable mt) throws Exception
	{
		JFileChooser jf = new JFileChooser();
		jf.setCurrentDirectory(new File("C:\\"));
		File t = null;
		int confirm = 50;
		
		do
		{
			if (jf.showSaveDialog(new JFrame()) == JFileChooser.CANCEL_OPTION)
			{
				return;
			}
			
			t = new File(jf.getSelectedFile().getPath() + ".txt");
			
			if (t.exists())
			{
				confirm = JOptionPane.showConfirmDialog(new JFrame(), "This file already exists, do you wish to overwrite?", "Overwrite?", 2);
			}
		}
		while (confirm == JOptionPane.CANCEL_OPTION);
		
		FileWriter fw = new FileWriter(t);
		
		for (int x = 0; x < mt.dim() * mt.dim(); x++)
		{
			for (int y = 0; y < mt.dim() * mt.dim(); y++)
			{
				String s = (String)mt.getValueAt(x, y);
				
				if (s.equals(""))
				{
					fw.write("-");
				}
				else
				{
					fw.write(s.replaceAll(" ", ""));
				}
				
				if (y != mt.dim() * mt.dim() - 1)
				{
					fw.write(",");
				}
			}
			
			fw.write("\r\n");
		}
		
		fw.close();
		JOptionPane.showMessageDialog(new JFrame(), "Puzzle saved successfully!");
	}
	
	public static void loadPuzzle(MainTable mt) throws Exception
	{
		JFileChooser jf = new JFileChooser();
		jf.setCurrentDirectory(new File("C:\\"));
		jf.showDialog(new JFrame(), "Sudoku!");
		Scanner stdin = new Scanner(jf.getSelectedFile());

		String[] s;

		for (int x = 0; x < 16; x++)
		{
			s = stdin.nextLine().split(",");

			for (int y = 0; y < s.length; y++)
			{
				if (s[y].equals("-"))
				{
					mt.setValueAt(x, y, "");
				}
				else
				{
					mt.setValueAt(x, y, "" + s[y], Color.black);
				}
			}
		}
	}
	
	public static void savePuzzle(MainTable mt, String puzname) throws Exception
	{
		FileWriter fw = new FileWriter(new File(puzname + ".txt"));
		
		for (int x = 0; x < mt.dim() * mt.dim(); x++)
		{
			for (int y = 0; y < mt.dim() * mt.dim(); y++)
			{
				String s = (String)mt.getValueAt(x, y);
				
				if (s.equals(""))
				{
					fw.write("-");
				}
				else
				{
					fw.write(s.replaceAll(" ", ""));
				}
				
				if (y != mt.dim() * mt.dim() - 1)
				{
					fw.write(",");
				}
			}
			
			fw.write("\r\n");
		}
		
		fw.close();
	}
}
class PuzzleGenerator implements Runnable
{
	JProgressBar jpb;
	KTimer timer;
	PuzzleSolver ps;
	MainTable mt;
	MainTable temp;
	Thread t;
	
	boolean stop;
	
	PuzzleGenerator(MainTable mt, JProgressBar jpb, KTimer timer)
	{
		this.mt = mt;
		this.jpb = jpb;
		this.timer = timer;
		stop = false;
	}
	
	public void run()
	{
		jpb.setIndeterminate(true);
		temp = new MainTable(mt.dim());
		ps = new PuzzleSolver(temp, false, false, false, false, false, true, true, jpb, "solve", 0);
		t = new Thread(ps);
		t.start();
		
		while (t.isAlive() && !stop)
		{
			try
			{
				Thread.sleep(100);
			}
			catch (Exception e){};
			
			if (timer.tryAgain())
			{
				ps = new PuzzleSolver(temp, false, false, false, false, false, true, true, jpb, "solve", 0);
				t = new Thread(ps);
				t.start();
				timer.reset();
			}
		}
		
		if (!stop)
		{
			for (int i = 0; i < 60; i++)
			{
				int x = new Random().nextInt(9);
				int y = new Random().nextInt(9);
				temp.setValueAt(x, y, "");
			}
			
			for (int i = 0; i < mt.dim() * mt.dim(); i++)
			{
				for (int j = 0; j < mt.dim() * mt.dim(); j++)
				{
					mt.setValueAt(i, j, temp.getValueAt(i, j), Color.black);
				}
			}
		}
		
		jpb.setIndeterminate(false);
		timer.stop();
	}
	
	void cancelGen()
	{
		stop = true;
	}
}
class PuzzleSolver implements Runnable
{
	JProgressBar jpb;
	MainTable mt;
	MainTable[] save;
	int mode;
	int timer;
	
	boolean logic1;
	boolean logic2;
	boolean logic3;
	boolean logic4;
	boolean logic5;
	boolean logicfailsafe;
	
	boolean hidden;
	boolean operationConfirm;
	String command;
	
	boolean stop;
	int depth;
	int count;
	
	PuzzleSolver(MainTable m, boolean logic1, boolean logic2, boolean logic3, boolean logic4, boolean logic5, boolean logicfailsafe, boolean hidden, JProgressBar jpb, String command, int timer)
	{
		this.jpb = jpb;
		mt = m;
		mode = mt.dim();
		save = new MainTable[0];
		this.logic1 = logic1;
		this.logic2 = logic2;
		this.logic3 = logic3;
		this.logic4 = logic4;
		this.logic5 = logic5;
		this.logicfailsafe = logicfailsafe;
		this.timer = timer;
		stop = false;
		this.command = command;
		this.hidden = hidden;
	}
	
	public void run()
	{
		if (command.equals("hint"))
		{
			hint();
		}
		else
		if (command.equals("solve"))
		{
			if (noneSelected())
			{
				JOptionPane.showMessageDialog(new JFrame(), "Please select a solving method");
				return;
			}
			
			if (!mt.isSolvable())
			{
				JOptionPane.showMessageDialog(new JFrame(), "This puzzle is not solvable");
				return;
			}
			
			jpb.setIndeterminate(true);
			mt.setEditable(false);
			String returned = solvePuzzle(false, true);
			
			if (returned.equals("pass"))
			{
				jpb.setIndeterminate(false);
				
				if (!hidden)
				{
					JOptionPane.showMessageDialog(new JFrame(), "Puzzle Solved!");
					mt.setForeground(Color.blue);
					mt.repaint();
				}
			}
			else
			if (returned.equals("fail"))
			{
				jpb.setIndeterminate(false);
				
				if (!hidden)
				{
					JOptionPane.showMessageDialog(new JFrame(), "Puzzle Unsolvable");
				}
			}
			else
			{
				jpb.setIndeterminate(false);
			}
		}
		
		mt.setEditable(true);
		
		return;
	}
	
	public void interrupt()
	{
		stop = true;
	}
	
	private void tempSave(int count)
	{
		if (count >= save.length)
		{
			save = Logic.addMT(save, new MainTable(mode));
		}
		
		for (int x = 0; x < mode * mode; x++)
		{
			for (int y = 0; y < mode * mode; y++)
			{
				save[count].setValueAt(x, y, mt.getValueAt(x, y));
			}
		}
	}
	
	private void tempLoad(int count)
	{
		for (int x = 0; x < mode * mode; x++)
		{
			for (int y = 0; y < mode * mode; y++)
			{
				Color c;
				
				if (save[0].getValueAt(x, y).replaceAll(" ", "").equals(""))
				{
					c = Color.red;
				}
				else
				{
					c = Color.black;
				}
				
				mt.setValueAt(x, y, save[count].getValueAt(x, y), c);
			}
		}
	}
	
	public boolean noneSelected()
	{
		if (logic1)
			return false;
		if (logic2)
			return false;
		if (logic3)
			return false;
		if (logic4)
			return false;
		if (logic5)
			return false;
		if (logicfailsafe)
			return false;
			
		return true;
	}
	
	public void hint()
	{
		if (logic1)
		{
			if (logicOne(true).equals("stop"))
			{
				return;
			}
		}
		
		if (logic2)
		{
			if (logicTwo(true).equals("stop"))
			{
				return;
			}
		}
		
		if (logic3)
		{
			if (logicThree(true).equals("stop"))
			{
				return;
			}
		}
		
		if (logic4)
		{
			if (logicFour(true).equals("stop"))
			{
				return;
			}
		}
		
		if (logic5)
		{
			if (logicFive(true).equals("stop"))
			{
				return;
			}
		}
		
		jpb.setIndeterminate(false);
		JOptionPane.showMessageDialog(new JFrame(), "No hints are available");
	}
	
	public String solvePuzzle(boolean override, boolean exception)
	{
		operationConfirm = false;
			
		do
		{
			operationConfirm = false;
			
			if (logic1 || override)
			{
				String returned = logicOne(false);
				
				if (returned.equals("pass"))
				{
					return "pass";
				}
				else
				if (returned.equals("stop"))
				{
					return "stop";
				}
			}
			
			if (logic2 || override)
			{
				String returned = logicTwo(false);
				
				if (returned.equals("pass"))
				{
					return "pass";
				}
				else
				if (returned.equals("stop"))
				{
					return "stop";
				}
			}
			
			if (logic3 || override)
			{
				String returned = logicThree(false);
				
				if (returned.equals("pass"))
				{
					return "pass";
				}
				else
				if (returned.equals("stop"))
				{
					return "stop";
				}
			}
			
			if (logic4 || override)
			{
				String returned = logicFour(false);
				
				if (returned.equals("pass"))
				{
					return "pass";
				}
				else
				if (returned.equals("stop"))
				{
					return "stop";
				}
			}
			
			if (logic5 || override)
			{
				String returned = logicFive(false);
				
				if (returned.equals("pass"))
				{
					return "pass";
				}
				else
				if (returned.equals("stop"))
				{
					return "stop";
				}
			}
		}
		while (operationConfirm);
		
		if (logicfailsafe && exception)
		{
			count = 0;
			depth = 1;
			tempSave(0);
			
			if (logicFailSafe(hidden).equals("stop"))
			{
				return "stop";
			}
			
			return "pass";
		}
		else
		if (stop)
		{
			return "stop";
		}
		
		return "fail";
	}
	
	private void fillIn(int x, int y, String s)
	{
		mt.setValueAt(x, y, s);
		
		try
		{
			Thread.sleep(timer);
		}
		catch (Exception e){}
	}
	
	private void fillIn(int x, KD y, String s)
	{
		mt.setValueAt(x, y, s);
		
		try
		{
			Thread.sleep(timer);
		}
		catch (Exception e){}
	}

	String logicOne(boolean hint)
	{
		boolean somethingChanged = false;

		do
		{
			somethingChanged = false;

			for (int i = 0; i < mode * mode; i++)
			{
				for (int j = 0; j < mode * mode; j++)
				{
					if (mt.getValueAt(i, j).replaceAll(" ", "").equals(""))
					{
						char[] ops = mt.findOptions(i, j, mode);
						
						if (ops.length == 1)
						{
							fillIn(i, j, "" + ops[0]);
							somethingChanged = true;
							operationConfirm = true;
							
							if (hint || stop)
							{
								return "stop";
							}
						}
					}
				}
			}
			
			if (hint)
			{
				return "fail";
			}
		}
		while (mt.hasEmptySlots() && somethingChanged);

		if (mt.hasEmptySlots())
		{
			return "fail";
		}
		else
		{
			return "pass";
		}
	}
	
	String logicTwo(boolean hint)
	{
		boolean somethingChanged = false;

		do
		{
			somethingChanged = false;
			
			switch (mode)
			{
				case 3:
					for (char c = '1'; c <= '9'; c++)
					{
						for (int sector = 1; sector <= 9; sector++)
						{
							boolean[][] possibles = new boolean[3][3];
							
							for (int i = 0; i < 3; i++)
							{
								for (int j = 0; j < 3; j++)
								{
									if (((String)mt.getTable(mt.findCoordsOfSector(sector)).getValueAt(i, j)).replaceAll(" ", "").equals(""))
									{
										possibles[i][j] = true;
									}
									else
									{
										possibles[i][j] = false;
									}
								}
							}
							
							KD secCoords = mt.findCoordsOfSector(sector);
							char[] vals = mt.getTable(secCoords).returnValues();
							
							if (Logic.arrayContains(vals, c))
							{
								for (int i = 0; i < 3; i++)
								{
									for (int j = 0; j < 3; j++)
									{
										possibles[i][j] = false;
									}
								}
							}
							else
							{
								for (int i = 0; i < 9; i++)
								{
									if (mt.rowContainsSector(i, sector))
									{
										if (Logic.arrayContains(mt.getRow(i), c))
										{
											for (int j = 0; j < 3; j++)
											{
												possibles[i % 3][j] = false;
											}
										}
									}
								}
								
								for (int i = 0; i < 9; i++)
								{
									if (mt.columnContainsSector(i, sector))
									{
										if (Logic.arrayContains(mt.getColumn(i), c))
										{
											for (int j = 0; j < 3; j++)
											{
												possibles[j][i % 3] = false;
											}
										}
									}
								}
							}
							
							KD single = Logic.findSingleTrue(possibles);
							
							if (single != null)
							{
								fillIn(sector, single, "" + c);
								somethingChanged = true;
								operationConfirm = true;
								
								if (hint || stop)
								{
									return "stop";
								}
							}
						}
					}
					
					if (hint)
					{
						return "fail";
					}
				break;
				
				case 4:
					for (char c = '1'; c <= '9'; c++)
					{
						for (int sector = 1; sector <= 16; sector++)
						{
							boolean[][] possibles = new boolean[4][4];
							
							for (int i = 0; i < 4; i++)
							{
								for (int j = 0; j < 4; j++)
								{
									if (((String)mt.getTable(mt.findCoordsOfSector(sector)).getValueAt(i, j)).replaceAll(" ", "").equals(""))
									{
										possibles[i][j] = true;
									}
									else
									{
										possibles[i][j] = false;
									}
								}
							}
							
							KD secCoords = mt.findCoordsOfSector(sector);
							char[] vals = mt.getTable(secCoords).returnValues();
							
							if (Logic.arrayContains(vals, c))
							{
								for (int i = 0; i < 4; i++)
								{
									for (int j = 0; j < 4; j++)
									{
										possibles[i][j] = false;
									}
								}
							}
							else
							{
								for (int i = 0; i < 16; i++)
								{
									if (mt.rowContainsSector(i, sector))
									{
										if (Logic.arrayContains(mt.getRow(i), c))
										{
											for (int j = 0; j < 4; j++)
											{
												possibles[i % 4][j] = false;
											}
										}
									}
								}
								
								for (int i = 0; i < 16; i++)
								{
									if (mt.columnContainsSector(i, sector))
									{
										if (Logic.arrayContains(mt.getColumn(i), c))
										{
											for (int j = 0; j < 4; j++)
											{
												possibles[j][i % 4] = false;
											}
										}
									}
								}
							}
							
							KD single = Logic.findSingleTrue(possibles);
							
							if (single != null)
							{
								fillIn(sector, single, "" + c);
								somethingChanged = true;
								operationConfirm = true;
								
								if (hint || stop)
								{
									return "stop";
								}
							}
						}
					}
					
					for (char c = 'A'; c <= 'F'; c++)
					{
						for (int sector = 1; sector <= 16; sector++)
						{
							boolean[][] possibles = new boolean[4][4];
							
							for (int i = 0; i < 4; i++)
							{
								for (int j = 0; j < 4; j++)
								{
									if (((String)mt.getTable(mt.findCoordsOfSector(sector)).getValueAt(i, j)).replaceAll(" ", "").equals(""))
									{
										possibles[i][j] = true;
									}
									else
									{
										possibles[i][j] = false;
									}
								}
							}
							
							KD secCoords = mt.findCoordsOfSector(sector);
							char[] vals = mt.getTable(secCoords).returnValues();
							
							if (Logic.arrayContains(vals, c))
							{
								for (int i = 0; i < 4; i++)
								{
									for (int j = 0; j < 4; j++)
									{
										possibles[i][j] = false;
									}
								}
							}
							else
							{
								for (int i = 0; i < 16; i++)
								{
									if (mt.rowContainsSector(i, sector))
									{
										if (Logic.arrayContains(mt.getRow(i), c))
										{
											for (int j = 0; j < 4; j++)
											{
												possibles[i % 4][j] = false;
											}
										}
									}
								}
								
								for (int i = 0; i < 16; i++)
								{
									if (mt.columnContainsSector(i, sector))
									{
										if (Logic.arrayContains(mt.getColumn(i), c))
										{
											for (int j = 0; j < 4; j++)
											{
												possibles[j][i % 4] = false;
											}
										}
									}
								}
							}
							
							KD single = Logic.findSingleTrue(possibles);
							
							if (single != null)
							{
								fillIn(sector, single, "" + c);
								somethingChanged = true;
								operationConfirm = true;
								
								if (hint || stop)
								{
									return "stop";
								}
							}
						}
					}
					
					if (hint)
					{
						return "fail";
					}
				break;
			}
		}
		while (mt.hasEmptySlots() && somethingChanged);

		if (mt.hasEmptySlots())
		{
			return "fail";
		}
		else
		{
			return "pass";
		}
	}
	
	String logicThree(boolean hint)
	{
		boolean somethingChanged = false;

		do
		{
			somethingChanged = false;
			
			switch (mode)
			{
				case 3:
					for (char c = '1'; c <= '9'; c++)
					{
						for (int row = 0; row < 9; row++)
						{
							boolean[] possibles = new boolean[9];
					
							for (int x = 0; x < 9; x++)
							{
								if (((String)mt.getValueAt(row, x)).replaceAll(" ", "").equals(""))
								{
									possibles[x] = true;
								}
								else
								{
									possibles[x] = false;
								}
							}
							
							for (int x = 0; x < 9; x++)
							{
								char[] vals = mt.getColumn(x);
								vals = Logic.addChar(vals, mt.getTable(mt.findCoordsOfSector(mt.findSector(row, x))).returnValues());
								vals = Logic.addChar(vals, mt.getRow(row));
								
								if (Logic.arrayContains(vals, c))
								{
									possibles[x] = false;
								}
							}
							
							int index = Logic.findSingleTrue(possibles);
							
							if (index != -1)
							{
								fillIn(row, index, "" + c);
								somethingChanged = true;
								operationConfirm = true;
								
								if (hint || stop)
								{
									return "stop";
								}
							}
						}
					}
					
					if (hint)
					{
						return "fail";
					}
				break;
				
				case 4:
					for (char c = '0'; c <= '9'; c++)
					{
						for (int row = 0; row < 16; row++)
						{
							boolean[] possibles = new boolean[16];
							
							for (int x = 0; x < 16; x++)
							{
								if (((String)mt.getValueAt(row, x)).replaceAll(" ", "").equals(""))
								{
									possibles[x] = true;
							}
								else
								{
									possibles[x] = false;
								}
							}
							
							for (int x = 0; x < 16; x++)
							{
								char[] vals = mt.getColumn(x);
								vals = Logic.addChar(vals, mt.getTable(mt.findCoordsOfSector(mt.findSector(row, x))).returnValues());
								vals = Logic.addChar(vals, mt.getRow(row));
								
								if (Logic.arrayContains(vals, c))
								{
									possibles[x] = false;
								}
							}
							
							int index = Logic.findSingleTrue(possibles);
							
							if (index != -1)
							{
								fillIn(row, index, "" + c);
								somethingChanged = true;
								operationConfirm = true;
								
								if (hint || stop)
								{
									return "stop";
								}
							}
						}
					}
					
					for (char c = 'A'; c <= 'F'; c++)
					{
						for (int row = 0; row < 16; row++)
						{
							boolean[] possibles = new boolean[16];
							
							for (int x = 0; x < 16; x++)
							{
								if (((String)mt.getValueAt(row, x)).replaceAll(" ", "").equals(""))
								{
									possibles[x] = true;
							}
								else
								{
									possibles[x] = false;
								}
							}
							
							for (int x = 0; x < 16; x++)
							{
								char[] vals = mt.getColumn(x);
								vals = Logic.addChar(vals, mt.getTable(mt.findCoordsOfSector(mt.findSector(row, x))).returnValues());
								vals = Logic.addChar(vals, mt.getRow(row));
								
								if (Logic.arrayContains(vals, c))
								{
									possibles[x] = false;
								}
							}
							
							int index = Logic.findSingleTrue(possibles);
					
							if (index != -1)
							{
								fillIn(row, index, "" + c);
								somethingChanged = true;
								operationConfirm = true;
								
								if (hint || stop)
								{
									return "stop";
								}
							}
						}
					}
					
					if (hint)
					{
						return "fail";
					}
				break;
			}
		}
		while (mt.hasEmptySlots() && somethingChanged);

		if (mt.hasEmptySlots())
		{
			return "fail";
		}
		else
		{
			return "pass";
		}
	}

	String logicFour(boolean hint)
	{
		boolean somethingChanged = false;
		
		do
		{
			somethingChanged = false;
			
			switch (mode)
			{
				case 3:
					for (char c = '1'; c <= '9'; c++)
					{
						for (int col = 0; col < 9; col++)
						{
							boolean[] possibles = new boolean[9];
					
							for (int x = 0; x < 9; x++)
							{
								if (((String)mt.getValueAt(x, col)).replaceAll(" ", "").equals(""))
								{
									possibles[x] = true;
								}
								else
								{
									possibles[x] = false;
								}
							}
							
							for (int x = 0; x < 9; x++)
							{
								char[] vals = mt.getRow(x);
								vals = Logic.addChar(vals, mt.getTable(mt.findCoordsOfSector(mt.findSector(x, col))).returnValues());
								vals = Logic.addChar(vals, mt.getColumn(col));
								
								if (Logic.arrayContains(vals, c))
								{
									possibles[x] = false;
								}
							}
							
							int index = Logic.findSingleTrue(possibles);
							
							if (index != -1)
							{
								fillIn(index, col, "" + c);
								somethingChanged = true;
								operationConfirm = true;
								
								if (hint || stop)
								{
									return "stop";
								}
							}
						}
					}
					
					if (hint)
					{
						return "fail";
					}
				break;
				
				case 4:
					for (char c = '0'; c <= '9'; c++)
					{
						for (int col = 0; col < 16; col++)
						{
							boolean[] possibles = new boolean[16];
							
							for (int x = 0; x < 16; x++)
							{
								if (((String)mt.getValueAt(x, col)).replaceAll(" ", "").equals(""))
								{
									possibles[x] = true;
							}
								else
								{
									possibles[x] = false;
								}
							}
							
							for (int x = 0; x < 16; x++)
							{
								char[] vals = mt.getRow(x);
								vals = Logic.addChar(vals, mt.getTable(mt.findCoordsOfSector(mt.findSector(x, col))).returnValues());
								vals = Logic.addChar(vals, mt.getColumn(col));
								
								if (Logic.arrayContains(vals, c))
								{
									possibles[x] = false;
								}
							}
							
							int index = Logic.findSingleTrue(possibles);
							
							if (index != -1)
							{
								fillIn(index, col, "" + c);
								somethingChanged = true;
								operationConfirm = true;
								
								if (hint || stop)
								{
									return "stop";
								}
							}
						}
					}
					
					for (char c = 'A'; c <= 'F'; c++)
					{
						for (int col = 0; col < 16; col++)
						{
							boolean[] possibles = new boolean[16];
							
							for (int x = 0; x < 16; x++)
							{
								if (((String)mt.getValueAt(x, col)).replaceAll(" ", "").equals(""))
								{
									possibles[x] = true;
							}
								else
								{
									possibles[x] = false;
								}
							}
							
							for (int x = 0; x < 16; x++)
							{
								char[] vals = mt.getRow(x);
								vals = Logic.addChar(vals, mt.getTable(mt.findCoordsOfSector(mt.findSector(x, col))).returnValues());
								vals = Logic.addChar(vals, mt.getColumn(col));
								
								if (Logic.arrayContains(vals, c))
								{
									possibles[x] = false;
								}
							}
							
							int index = Logic.findSingleTrue(possibles);
					
							if (index != -1)
							{
								fillIn(index, col, "" + c);
								somethingChanged = true;
								operationConfirm = true;
								
								if (hint || stop)
								{
									return "stop";
								}
							}
						}
					}
					
					if (hint)
					{
						return "fail";
					}
				break;
			}
		}
		while (mt.hasEmptySlots() && somethingChanged);
		
		if (mt.hasEmptySlots())
		{
			return "fail";
		}
		else
		{
			return "pass";
		}
	}
	
	String logicFive(boolean hint)
	{
		boolean somethingChanged = false;
		
		do
		{
			somethingChanged = false;
			
			switch (mode)
			{
				case 3:
					for (char c = '1'; c <= '9'; c++)
					{
						for (int sector = 1; sector <= 9; sector++)
						{
							boolean[][] possibles = new boolean[3][3];
							
							for (int i = 0; i < 3; i++)
							{
								for (int j = 0; j < 3; j++)
								{
									if (((String)mt.getTable(mt.findCoordsOfSector(sector)).getValueAt(i, j)).replaceAll(" ", "").equals(""))
									{
										possibles[i][j] = true;
									}
									else
									{
										possibles[i][j] = false;
									}
								}
							}
							
							KD secCoords = mt.findCoordsOfSector(sector);
							char[] vals = mt.getTable(secCoords).returnValues();
							
							if (Logic.arrayContains(vals, c))
							{
								for (int i = 0; i < 3; i++)
								{
									for (int j = 0; j < 3; j++)
									{
										possibles[i][j] = false;
									}
								}
							}
							else
							{
								for (int i = 0; i < 9; i++)
								{
									if (mt.rowContainsSector(i, sector))
									{
										if (Logic.arrayContains(mt.getRow(i), c))
										{
											for (int j = 0; j < 3; j++)
											{
												possibles[i % 3][j] = false;
											}
										}
									}
								}
								
								for (int i = 0; i < 9; i++)
								{
									if (mt.columnContainsSector(i, sector))
									{
										if (Logic.arrayContains(mt.getColumn(i), c))
										{
											for (int j = 0; j < 3; j++)
											{
												possibles[j][i % 3] = false;
											}
										}
									}
								}
							}
							
							int singlePossibilityRow = Logic.findSinglePossibleRow(possibles, sector);
							int singlePossibilityCol = Logic.findSinglePossibleCol(possibles, sector);
							
							if (singlePossibilityRow != -1)
							{
								int[] neighbors = mt.findHorizontalNeighboringSectors(sector, mode);
								
								for (int sec : neighbors)
								{
									boolean[][] possibles2 = new boolean[3][3];
									
									for (int i = 0; i < 3; i++)
									{
										for (int j = 0; j < 3; j++)
										{
											if (((String)mt.getTable(mt.findCoordsOfSector(sec)).getValueAt(i, j)).replaceAll(" ", "").equals(""))
											{
												possibles2[i][j] = true;
											}
											else
											{
												possibles2[i][j] = false;
											}
										}
									}
									
									KD secCoords2 = mt.findCoordsOfSector(sec);
									char[] vals2 = mt.getTable(secCoords2).returnValues();
									
									if (Logic.arrayContains(vals2, c))
									{
										for (int i = 0; i < 3; i++)
										{
											for (int j = 0; j < 3; j++)
											{
												possibles2[i][j] = false;
											}
										}
									}
									else
									{
										for (int i = 0; i < 9; i++)
										{
											if (mt.rowContainsSector(i, sec))
											{
												char[] temp = mt.getRow(i);
												
												if (i == singlePossibilityRow)
												{
													temp = Logic.addChar(temp, c);
												}
												
												if (Logic.arrayContains(temp, c))
												{
														for (int j = 0; j < 3; j++)
													{
														possibles2[i % 3][j] = false;
													}
												}
											}
										}
										
										for (int i = 0; i < 9; i++)
										{
											if (mt.columnContainsSector(i, sec))
											{
												if (Logic.arrayContains(mt.getColumn(i), c))
												{
													for (int j = 0; j < 3; j++)
													{
														possibles2[j][i % 3] = false;
													}
												}
											}
										}
									}
									
									KD single = Logic.findSingleTrue(possibles2);
									
									if (single != null)
									{
										fillIn(sec, single, "" + c);
										somethingChanged = true;
										operationConfirm = true;
										
										if (hint || stop)
										{
											return "stop";
										}
									}
								}
							}
							else
							if (singlePossibilityCol != -1)
							{
								int[] neighbors = mt.findVerticalNeighboringSectors(sector, mode);
								
								for (int sec : neighbors)
								{
									boolean[][] possibles2 = new boolean[3][3];
									
									for (int i = 0; i < 3; i++)
									{
										for (int j = 0; j < 3; j++)
										{
											if (((String)mt.getTable(mt.findCoordsOfSector(sec)).getValueAt(i, j)).replaceAll(" ", "").equals(""))
											{
												possibles2[i][j] = true;
											}
											else
											{
												possibles2[i][j] = false;
											}
										}
									}
									
									KD secCoords2 = mt.findCoordsOfSector(sec);
									char[] vals2 = mt.getTable(secCoords2).returnValues();
									
									if (Logic.arrayContains(vals2, c))
									{
										for (int i = 0; i < 3; i++)
										{
											for (int j = 0; j < 3; j++)
											{
												possibles2[i][j] = false;
											}
										}
									}
									else
									{
										for (int i = 0; i < 9; i++)
										{
											if (mt.rowContainsSector(i, sec))
											{
												if (Logic.arrayContains(mt.getRow(i), c))
												{
														for (int j = 0; j < 3; j++)
													{
														possibles2[i % 3][j] = false;
													}
												}
											}
										}
										
										for (int i = 0; i < 9; i++)
										{
											if (mt.columnContainsSector(i, sec))
											{
												char[] temp = mt.getColumn(i);
												
												if (i == singlePossibilityCol)
												{
													temp = Logic.addChar(temp, c);
												}
												
												if (Logic.arrayContains(temp, c))
												{
													for (int j = 0; j < 3; j++)
													{
														possibles2[j][i % 3] = false;
													}
												}
											}
										}
									}
									
									KD single = Logic.findSingleTrue(possibles2);
									
									if (single != null)
									{
										fillIn(sec, single, "" + c);
										somethingChanged = true;
										operationConfirm = true;
										
										if (hint || stop)
										{
											return "stop";
										}
									}
								}
							}
						}
					}
					
					if (hint)
					{
						return "fail";
					}
				break;
				
				case 4:
					for (char c = '1'; c <= '9'; c++)
					{
						for (int sector = 1; sector <= 16; sector++)
						{
							boolean[][] possibles = new boolean[4][4];
							
							for (int i = 0; i < 4; i++)
							{
								for (int j = 0; j < 4; j++)
								{
									if (((String)mt.getTable(mt.findCoordsOfSector(sector)).getValueAt(i, j)).replaceAll(" ", "").equals(""))
									{
										possibles[i][j] = true;
									}
									else
									{
										possibles[i][j] = false;
									}
								}
							}
							
							KD secCoords = mt.findCoordsOfSector(sector);
							char[] vals = mt.getTable(secCoords).returnValues();
							
							if (Logic.arrayContains(vals, c))
							{
								for (int i = 0; i < 4; i++)
								{
									for (int j = 0; j < 4; j++)
									{
										possibles[i][j] = false;
									}
								}
							}
							else
							{
								for (int i = 0; i < 16; i++)
								{
									if (mt.rowContainsSector(i, sector))
									{
										if (Logic.arrayContains(mt.getRow(i), c))
										{
											for (int j = 0; j < 4; j++)
											{
												possibles[i % 4][j] = false;
											}
										}
									}
								}
								
								for (int i = 0; i < 16; i++)
								{
									if (mt.columnContainsSector(i, sector))
									{
										if (Logic.arrayContains(mt.getColumn(i), c))
										{
											for (int j = 0; j < 4; j++)
											{
												possibles[j][i % 4] = false;
											}
										}
									}
								}
							}
							
							int singlePossibilityRow = Logic.findSinglePossibleRow(possibles, sector);
							int singlePossibilityCol = Logic.findSinglePossibleCol(possibles, sector);
							
							if (singlePossibilityRow != -1)
							{
								int[] neighbors = mt.findHorizontalNeighboringSectors(sector, mode);
								
								for (int sec : neighbors)
								{
									boolean[][] possibles2 = new boolean[4][4];
									
									for (int i = 0; i < 4; i++)
									{
										for (int j = 0; j < 4; j++)
										{
											if (((String)mt.getTable(mt.findCoordsOfSector(sec)).getValueAt(i, j)).replaceAll(" ", "").equals(""))
											{
												possibles2[i][j] = true;
											}
											else
											{
												possibles2[i][j] = false;
											}
										}
									}
									
									KD secCoords2 = mt.findCoordsOfSector(sec);
									char[] vals2 = mt.getTable(secCoords2).returnValues();
									
									if (Logic.arrayContains(vals2, c))
									{
										for (int i = 0; i < 4; i++)
										{
											for (int j = 0; j < 4; j++)
											{
												possibles2[i][j] = false;
											}
										}
									}
									else
									{
										for (int i = 0; i < 16; i++)
										{
											if (mt.rowContainsSector(i, sec))
											{
												char[] temp = mt.getRow(i);
												
												if (i == singlePossibilityRow)
												{
													temp = Logic.addChar(temp, c);
												}
												
												if (Logic.arrayContains(temp, c))
												{
														for (int j = 0; j < 4; j++)
													{
														possibles2[i % 4][j] = false;
													}
												}
											}
										}
										
										for (int i = 0; i < 16; i++)
										{
											if (mt.columnContainsSector(i, sec))
											{
												if (Logic.arrayContains(mt.getColumn(i), c))
												{
													for (int j = 0; j < 4; j++)
													{
														possibles2[j][i % 4] = false;
													}
												}
											}
										}
									}
									
									KD single = Logic.findSingleTrue(possibles2);
									
									if (single != null)
									{
										fillIn(sec, single, "" + c);
										somethingChanged = true;
										operationConfirm = true;
										
										if (hint || stop)
										{
											return "stop";
										}
									}
								}
							}
							else
							if (singlePossibilityCol != -1)
							{
								int[] neighbors = mt.findVerticalNeighboringSectors(sector, mode);
								
								for (int sec : neighbors)
								{
									boolean[][] possibles2 = new boolean[4][4];
									
									for (int i = 0; i < 4; i++)
									{
										for (int j = 0; j < 4; j++)
										{
											if (((String)mt.getTable(mt.findCoordsOfSector(sec)).getValueAt(i, j)).replaceAll(" ", "").equals(""))
											{
												possibles2[i][j] = true;
											}
											else
											{
												possibles2[i][j] = false;
											}
										}
									}
									
									KD secCoords2 = mt.findCoordsOfSector(sec);
									char[] vals2 = mt.getTable(secCoords2).returnValues();
									
									if (Logic.arrayContains(vals2, c))
									{
										for (int i = 0; i < 4; i++)
										{
											for (int j = 0; j < 4; j++)
											{
												possibles2[i][j] = false;
											}
										}
									}
									else
									{
										for (int i = 0; i < 16; i++)
										{
											if (mt.rowContainsSector(i, sec))
											{
												if (Logic.arrayContains(mt.getRow(i), c))
												{
														for (int j = 0; j < 4; j++)
													{
														possibles2[i % 4][j] = false;
													}
												}
											}
										}
										
										for (int i = 0; i < 16; i++)
										{
											if (mt.columnContainsSector(i, sec))
											{
												char[] temp = mt.getColumn(i);
												
												if (i == singlePossibilityCol)
												{
													temp = Logic.addChar(temp, c);
												}
												
												if (Logic.arrayContains(temp, c))
												{
													for (int j = 0; j < 4; j++)
													{
														possibles2[j][i % 4] = false;
													}
												}
											}
										}
									}
									
									KD single = Logic.findSingleTrue(possibles2);
									
									if (single != null)
									{
										fillIn(sec, single, "" + c);
										somethingChanged = true;
										operationConfirm = true;
										
										if (hint || stop)
										{
											return "stop";
										}
									}
								}
							}
						}
					}
					
					if (hint)
					{
						return "fail";
					}
					
					for (char c = 'A'; c <= 'F'; c++)
					{
						for (int sector = 1; sector <= 16; sector++)
						{
							boolean[][] possibles = new boolean[4][4];
							
							for (int i = 0; i < 4; i++)
							{
								for (int j = 0; j < 4; j++)
								{
									if (((String)mt.getTable(mt.findCoordsOfSector(sector)).getValueAt(i, j)).replaceAll(" ", "").equals(""))
									{
										possibles[i][j] = true;
									}
									else
									{
										possibles[i][j] = false;
									}
								}
							}
							
							KD secCoords = mt.findCoordsOfSector(sector);
							char[] vals = mt.getTable(secCoords).returnValues();
							
							if (Logic.arrayContains(vals, c))
							{
								for (int i = 0; i < 4; i++)
								{
									for (int j = 0; j < 4; j++)
									{
										possibles[i][j] = false;
									}
								}
							}
							else
							{
								for (int i = 0; i < 16; i++)
								{
									if (mt.rowContainsSector(i, sector))
									{
										if (Logic.arrayContains(mt.getRow(i), c))
										{
											for (int j = 0; j < 4; j++)
											{
												possibles[i % 4][j] = false;
											}
										}
									}
								}
								
								for (int i = 0; i < 16; i++)
								{
									if (mt.columnContainsSector(i, sector))
									{
										if (Logic.arrayContains(mt.getColumn(i), c))
										{
											for (int j = 0; j < 4; j++)
											{
												possibles[j][i % 4] = false;
											}
										}
									}
								}
							}
							
							int singlePossibilityRow = Logic.findSinglePossibleRow(possibles, sector);
							int singlePossibilityCol = Logic.findSinglePossibleCol(possibles, sector);
							
							if (singlePossibilityRow != -1)
							{
								int[] neighbors = mt.findHorizontalNeighboringSectors(sector, mode);
								
								for (int sec : neighbors)
								{
									boolean[][] possibles2 = new boolean[4][4];
									
									for (int i = 0; i < 4; i++)
									{
										for (int j = 0; j < 4; j++)
										{
											if (((String)mt.getTable(mt.findCoordsOfSector(sec)).getValueAt(i, j)).replaceAll(" ", "").equals(""))
											{
												possibles2[i][j] = true;
											}
											else
											{
												possibles2[i][j] = false;
											}
										}
									}
									
									KD secCoords2 = mt.findCoordsOfSector(sec);
									char[] vals2 = mt.getTable(secCoords2).returnValues();
									
									if (Logic.arrayContains(vals2, c))
									{
										for (int i = 0; i < 4; i++)
										{
											for (int j = 0; j < 4; j++)
											{
												possibles2[i][j] = false;
											}
										}
									}
									else
									{
										for (int i = 0; i < 16; i++)
										{
											if (mt.rowContainsSector(i, sec))
											{
												char[] temp = mt.getRow(i);
												
												if (i == singlePossibilityRow)
												{
													temp = Logic.addChar(temp, c);
												}
												
												if (Logic.arrayContains(temp, c))
												{
														for (int j = 0; j < 4; j++)
													{
														possibles2[i % 4][j] = false;
													}
												}
											}
										}
										
										for (int i = 0; i < 16; i++)
										{
											if (mt.columnContainsSector(i, sec))
											{
												if (Logic.arrayContains(mt.getColumn(i), c))
												{
													for (int j = 0; j < 4; j++)
													{
														possibles2[j][i % 4] = false;
													}
												}
											}
										}
									}
									
									KD single = Logic.findSingleTrue(possibles2);
									
									if (single != null)
									{
										fillIn(sec, single, "" + c);
										somethingChanged = true;
										operationConfirm = true;
										
										if (hint || stop)
										{
											return "stop";
										}
									}
								}
							}
							else
							if (singlePossibilityCol != -1)
							{
								int[] neighbors = mt.findVerticalNeighboringSectors(sector, mode);
								
								for (int sec : neighbors)
								{
									boolean[][] possibles2 = new boolean[4][4];
									
									for (int i = 0; i < 4; i++)
									{
										for (int j = 0; j < 4; j++)
										{
											if (((String)mt.getTable(mt.findCoordsOfSector(sec)).getValueAt(i, j)).replaceAll(" ", "").equals(""))
											{
												possibles2[i][j] = true;
											}
											else
											{
												possibles2[i][j] = false;
											}
										}
									}
									
									KD secCoords2 = mt.findCoordsOfSector(sec);
									char[] vals2 = mt.getTable(secCoords2).returnValues();
									
									if (Logic.arrayContains(vals2, c))
									{
										for (int i = 0; i < 4; i++)
										{
											for (int j = 0; j < 4; j++)
											{
												possibles2[i][j] = false;
											}
										}
									}
									else
									{
										for (int i = 0; i < 16; i++)
										{
											if (mt.rowContainsSector(i, sec))
											{
												if (Logic.arrayContains(mt.getRow(i), c))
												{
														for (int j = 0; j < 4; j++)
													{
														possibles2[i % 4][j] = false;
													}
												}
											}
										}
										
										for (int i = 0; i < 16; i++)
										{
											if (mt.columnContainsSector(i, sec))
											{
												char[] temp = mt.getColumn(i);
												
												if (i == singlePossibilityCol)
												{
													temp = Logic.addChar(temp, c);
												}
												
												if (Logic.arrayContains(temp, c))
												{
													for (int j = 0; j < 4; j++)
													{
														possibles2[j][i % 4] = false;
													}
												}
											}
										}
									}
									
									KD single = Logic.findSingleTrue(possibles2);
									
									if (single != null)
									{
										fillIn(sec, single, "" + c);
										somethingChanged = true;
										operationConfirm = true;
										
										if (hint || stop)
										{
											return "stop";
										}
									}
								}
							}
						}
					}
					
					if (hint)
					{
						return "fail";
					}
				break;
			}
		}
		while (mt.hasEmptySlots() && somethingChanged);
		
		if (mt.hasEmptySlots())
		{
			return "fail";
		}
		else
		{
			return "pass";
		}
	}
	
	String logicFailSafe(boolean hidden)
	{
		for (int x = 0; x < mode * mode; x++)
		{
			for (int y = 0; y < mode * mode; y++)
			{
				String s = (String)mt.getValueAt(x, y);
				
				if (s.equals(""))
				{
					char[] toTry = mt.findOptions(x, y, mode);
					boolean[] alreadyChecked = new boolean[toTry.length];
					
					for (int i = 0; i < alreadyChecked.length; i++)
					{
						alreadyChecked[i] = false;
					}
					
					if (toTry.length == 0)
					{
						return "fail";
					}
					
					tempSave(depth);
					
					for (int i = 0; i < toTry.length; i++)
					{
						int index;
						
						do
						{
							index = new Random().nextInt(toTry.length);
						}
						while (alreadyChecked[index] == true);
						
						fillIn(x, y, "" + toTry[index]);
						alreadyChecked[index] = true;
						tempSave(depth);
						
						if (solvePuzzle(true, false).equals("pass"))
						{
							return "pass";
						}
						else
						{
							tempLoad(depth);
							depth++;
							
							if (logicFailSafe(hidden).equals("pass"))
							{
								return "pass";
							}
							
							depth--;
							tempLoad(depth);
							
							if (stop)
							{
								tempLoad(0);
								return "stop";
							}
						}
					}
					
					tempLoad(depth);
				}
			}
		}
		
		return "fail";
	}
}
class MainTable
{
	KTable[][] grids;
	KSector sectorList;
	int dim;

	MainTable(int dim)
	{
		this.dim = dim;

		grids = new KTable[dim][dim];

		int temp = 1;
		for (int i = 0; i < dim; i++)
		{
			for (int j = 0; j < dim; j++)
			{
				char[] allow;
				
				if (dim == 4)
				{
					allow = new char[16];
					char c = '0';
					
					for (int b = 0; b <= 10; b++)
					{
						allow[b] = c;
						c++;
					}
					
					c = 'A';
					
					for (int b = 10; b < 16; b++)
					{
						allow[b] = c;
						c++;
					}
				}
				else
				{
					allow = new char[9];
					char c = '1';
					
					for (int b = 0; b < 9; b++)
					{
						allow[b] = c;
						c++;
					}
				}
				
				grids[i][j] = new KTable(temp, dim, allow);
				grids[i][j].setColumnSelectionAllowed(false);
				grids[i][j].setRowSelectionAllowed(false);

				temp++;
			}
		}
		
		sectorList = new KSector(dim);
	}
	
	void setGrid(Color c)
	{
		for (int i = 0; i < dim; i++)
		{
			for (int j = 0; j < dim; j++)
			{
				grids[i][j].setGridColor(c);
			}
		}
	}
	
	void setEditable(boolean b)
	{
		for (int i = 0; i < dim; i++)
		{
			for (int j = 0; j < dim; j++)
			{
				grids[i][j].setEditable(b);
			}
		}
	}
	
	void setTimer(KTimer t)
	{
		for (int i = 0; i < dim; i++)
		{
			for (int j = 0; j < dim; j++)
			{
				grids[i][j].setTimer(t);
			}
		}
	}
	
	void setForeground(Color c)
	{
		for (int i = 0; i < dim; i++)
		{
			for (int j = 0; j < dim; j++)
			{
				grids[i][j].setForeground(c);
			}
		}
	}
	
	void repaint()
	{
		for (int i = 0; i < dim; i++)
		{
			for (int j = 0; j < dim; j++)
			{
				grids[i][j].repaint();
			}
		}
	}

	KTable getTable(int i, int j)
	{
		return grids[i][j];
	}

	KTable getTable(KD d)
	{
		return grids[d.x][d.getY()];
	}

	String getValueAt(int row, int col)
	{
		return (String)getTable(findCoordsOfSector(findSector(row, col))).getValueAt(row % dim, col % dim);
	}

	void setValueAt(int row, int col, String val)
	{
		getTable(findCoordsOfSector(findSector(row, col))).setValueAt(val, row % dim, col % dim);
	}
	
	void setValueAt(int row, int col, String val, Color c)
	{
		getTable(findCoordsOfSector(findSector(row, col))).setValueAt(c, val, row % dim, col % dim);
	}
	
	void setValueAt(int sector, KD pos, String val)
	{
		getTable(findCoordsOfSector(sector)).setValueAt(val, pos.getX(), pos.getY());
	}
	
	int dim()
	{
		return dim;
	}

	boolean hasEmptySlots()
	{
		for (int i = 0; i < dim * dim; i++)
		{
			for (int j = 0; j < dim * dim; j++)
			{
				String s = getValueAt(i, j).replaceAll(" ", "");

				if (s.equals(""))
				{
					return true;
				}
			}
		}

		return false;
	}
	
	boolean isEmpty()
	{
		for (int i = 0; i < dim * dim; i++)
		{
			for (int j = 0; j < dim * dim; j++)
			{
				String s = getValueAt(i, j).replaceAll(" ", "");

				if (!s.equals(""))
				{
					return false;
				}
			}
		}

		return true;
	}
	
	boolean isSolvable()
	{
		for (int x = 0; x < dim * dim; x++)
		{
			if (Logic.checkRepeatingValues(getRow(x)))
			{
				return false;
			}
		}
		
		for (int x = 0; x < dim * dim; x++)
		{
			if (Logic.checkRepeatingValues(getColumn(x)))
			{
				return false;
			}
		}
		
		for (int x = 1; x <= dim * dim; x++)
		{
			if (Logic.checkRepeatingValues(getTable(findCoordsOfSector(x)).returnValues()))
			{
				return false;
			}
		}
		
		return true;
	}
	
	boolean validateSolve()
	{
		for (int x = 0; x < dim * dim; x++)
		{
			if (Logic.checkRepeatingValues(getRow(x)))
			{
				return false;
			}
		}
		
		for (int x = 0; x < dim * dim; x++)
		{
			if (Logic.checkRepeatingValues(getColumn(x)))
			{
				return false;
			}
		}
		
		for (int x = 1; x <= dim * dim; x++)
		{
			if (Logic.checkRepeatingValues(getTable(findCoordsOfSector(x)).returnValues()))
			{
				return false;
			}
		}
		
		if (hasEmptySlots())
		{
			return false;
		}
		
		setForeground(Color.blue);
		return true;
	}

	KD findCoordsOfSector(int s)
	{
		for (int i = 0; i < dim; i++)
		{
			for (int j = 0; j < dim; j++)
			{
				if (grids[i][j].getSector() == s)
				{
					return new KD(i, j);
				}
			}
		}

		return null;
	}

	char[] findOptions(int row, int col, int mode)
	{
		
		char[] toReturn = new char[mode * mode];
		
		if (mode == 3)
		{
			toReturn[0] = '1';
			toReturn[1] = '2';
			toReturn[2] = '3';
			toReturn[3] = '4';
			toReturn[4] = '5';
			toReturn[5] = '6';
			toReturn[6] = '7';
			toReturn[7] = '8';
			toReturn[8] = '9';
		}
		else
		if (mode == 4)
		{
			toReturn[0] = '0';
			toReturn[1] = '1';
			toReturn[2] = '2';
			toReturn[3] = '3';
			toReturn[4] = '4';
			toReturn[5] = '5';
			toReturn[6] = '6';
			toReturn[7] = '7';
			toReturn[8] = '8';
			toReturn[9] = '9';
			toReturn[10] = 'A';
			toReturn[11] = 'B';
			toReturn[12] = 'C';
			toReturn[13] = 'D';
			toReturn[14] = 'E';
			toReturn[15] = 'F';
		}

		char[] toCheck = getConnectedValues(row, col);

		for (int x = 0; x < toCheck.length; x++)
		{
			switch (toCheck[x])
			{
				case '0':
					toReturn = Logic.removeChar(toReturn, '0');
				break;
				
				case '1':
					toReturn = Logic.removeChar(toReturn, '1');
				break;

				case '2':
					toReturn = Logic.removeChar(toReturn, '2');
				break;

				case '3':
					toReturn = Logic.removeChar(toReturn, '3');
				break;

				case '4':
					toReturn = Logic.removeChar(toReturn, '4');
				break;

				case '5':
					toReturn = Logic.removeChar(toReturn, '5');
				break;

				case '6':
					toReturn = Logic.removeChar(toReturn, '6');
				break;

				case '7':
					toReturn = Logic.removeChar(toReturn, '7');
				break;

				case '8':
					toReturn = Logic.removeChar(toReturn, '8');
				break;

				case '9':
					toReturn = Logic.removeChar(toReturn, '9');
				break;
				
				case 'A':
					toReturn = Logic.removeChar(toReturn, 'A');
				break;

				case 'B':
					toReturn = Logic.removeChar(toReturn, 'B');
				break;

				case 'C':
					toReturn = Logic.removeChar(toReturn, 'C');
				break;

				case 'D':
					toReturn = Logic.removeChar(toReturn, 'D');
				break;

				case 'E':
					toReturn = Logic.removeChar(toReturn, 'E');
				break;
				
				case 'F':
					toReturn = Logic.removeChar(toReturn, 'F');
				break;
			}
		}

		return toReturn;
	}
	
	char[] getRow(int row)
	{
		char[] temp = new char[0];
		int[] sectors = sectorList.getSectorsOfRow(row);
		
		for (int i = 0; i < sectors.length; i++)
		{
			temp = Logic.addChar(temp, getTable(findCoordsOfSector(sectors[i])).returnValuesOfRow(row % dim));
		}
		
		return temp;
	}
	
	char[] getColumn(int col)
	{
		char[] temp = new char[0];
		int[] sectors = sectorList.getSectorsOfColumn(col);
		
		for (int i = 0; i < sectors.length; i++)
		{
			temp = Logic.addChar(temp, getTable(findCoordsOfSector(sectors[i])).returnValuesOfColumn(col % dim));
		}
		
		return temp;
	}
	
	boolean rowContainsSector(int row, int sector)
	{
		return sectorList.rowContainsSector(row, sector);
	}
	
	boolean columnContainsSector(int col, int sector)
	{
		return sectorList.columnContainsSector(col, sector);
	}

	int findSector (int row, int col)
	{
		int r = row / dim;
		int c = col / dim;

		return getTable(r, c).getSector();
	}

	char[] getConnectedValues(int row, int col)
	{
		char[] temp = new char[0];
		int sector = findSector(row, col);

		temp = Logic.addChar(temp, getTable(findCoordsOfSector(sector)).returnValues());
		temp = Logic.addChar(temp, getRow(row));
		temp = Logic.addChar(temp, getColumn(col));
		
		return temp;
	}
	
	int[] findHorizontalNeighboringSectors(int sector, int mode)
	{
		int[] toReturn = null;
		
		switch (mode)
		{
			case 3:
				toReturn = new int[2];
				switch (sector)
				{
					case 1:
						toReturn[0] = 2;
						toReturn[1] = 3;
					break;
					case 2:
						toReturn[0] = 1;
						toReturn[1] = 3;
					break;
					case 3:
						toReturn[0] = 2;
						toReturn[1] = 1;
					break;
					case 4:
						toReturn[0] = 5;
						toReturn[1] = 6;
					break;
					case 5:
						toReturn[0] = 6;
						toReturn[1] = 4;
					break;
					case 6:
						toReturn[0] = 5;
						toReturn[1] = 4;
					break;
					case 7:
						toReturn[0] = 8;
						toReturn[1] = 9;
					break;
					case 8:
						toReturn[0] = 7;
						toReturn[1] = 9;
					break;
					case 9:
						toReturn[0] = 8;
						toReturn[1] = 7;
					break;
				}
			break;
			
			case 4:
				toReturn = new int[3];
				
				switch (sector)
				{
					case 1:
						toReturn[0] = 2;
						toReturn[1] = 3;
						toReturn[2] = 4;
					break;
					case 2:
						toReturn[0] = 1;
						toReturn[1] = 3;
						toReturn[2] = 4;
					break;
					case 3:
						toReturn[0] = 2;
						toReturn[1] = 1;
						toReturn[2] = 4;
					break;
					case 4:
						toReturn[0] = 1;
						toReturn[1] = 2;
						toReturn[2] = 3;
					break;
					case 5:
						toReturn[0] = 6;
						toReturn[1] = 7;
						toReturn[2] = 8;
					break;
					case 6:
						toReturn[0] = 7;
						toReturn[1] = 8;
						toReturn[2] = 5;
					break;
					case 7:
						toReturn[0] = 8;
						toReturn[1] = 6;
						toReturn[2] = 5;
					break;
					case 8:
						toReturn[0] = 7;
						toReturn[1] = 6;
						toReturn[2] = 5;
					break;
					case 9:
						toReturn[0] = 10;
						toReturn[1] = 11;
						toReturn[2] = 12;
					break;
					case 10:
						toReturn[0] = 9;
						toReturn[1] = 11;
						toReturn[2] = 12;
					break;
					case 11:
						toReturn[0] = 10;
						toReturn[1] = 9;
						toReturn[2] = 12;
					break;
					case 12:
						toReturn[0] = 10;
						toReturn[1] = 11;
						toReturn[2] = 9;
					break;
					case 13:
						toReturn[0] = 14;
						toReturn[1] = 15;
						toReturn[2] = 16;
					break;
					case 14:
						toReturn[0] = 13;
						toReturn[1] = 15;
						toReturn[2] = 16;
					break;
					case 15:
						toReturn[0] = 14;
						toReturn[1] = 13;
						toReturn[2] = 16;
					break;
					case 16:
						toReturn[0] = 14;
						toReturn[1] = 15;
						toReturn[2] = 13;
					break;
				}
			break;
		}
		
		return toReturn;
	}
	
	int[] findVerticalNeighboringSectors(int sector, int mode)
	{
		int[] toReturn = null;
		
		switch (mode)
		{
			case 3:
				toReturn = new int[2];
				switch (sector)
				{
					case 1:
						toReturn[0] = 4;
						toReturn[1] = 7;
					break;
					case 2:
						toReturn[0] = 5;
						toReturn[1] = 8;
					break;
					case 3:
						toReturn[0] = 6;
						toReturn[1] = 9;
					break;
					case 4:
						toReturn[0] = 1;
						toReturn[1] = 7;
					break;
					case 5:
						toReturn[0] = 2;
						toReturn[1] = 8;
					break;
					case 6:
						toReturn[0] = 3;
						toReturn[1] = 9;
					break;
					case 7:
						toReturn[0] = 1;
						toReturn[1] = 4;
					break;
					case 8:
						toReturn[0] = 2;
						toReturn[1] = 5;
					break;
					case 9:
						toReturn[0] = 3;
						toReturn[1] = 6;
					break;
				}
			break;
			
			case 4:
				toReturn = new int[3];
				
				switch (sector)
				{
					case 1:
						toReturn[0] = 5;
						toReturn[1] = 9;
						toReturn[2] = 13;
					break;
					case 2:
						toReturn[0] = 6;
						toReturn[1] = 10;
						toReturn[2] = 14;
					break;
					case 3:
						toReturn[0] = 7;
						toReturn[1] = 11;
						toReturn[2] = 15;
					break;
					case 4:
						toReturn[0] = 8;
						toReturn[1] = 12;
						toReturn[2] = 16;
					break;
					case 5:
						toReturn[0] = 1;
						toReturn[1] = 9;
						toReturn[2] = 13;
					break;
					case 6:
						toReturn[0] = 2;
						toReturn[1] = 10;
						toReturn[2] = 14;
					break;
					case 7:
						toReturn[0] = 3;
						toReturn[1] = 11;
						toReturn[2] = 15;
					break;
					case 8:
						toReturn[0] = 4;
						toReturn[1] = 12;
						toReturn[2] = 16;
					break;
					case 9:
						toReturn[0] = 1;
						toReturn[1] = 5;
						toReturn[2] = 13;
					break;
					case 10:
						toReturn[0] = 6;
						toReturn[1] = 2;
						toReturn[2] = 14;
					break;
					case 11:
						toReturn[0] = 7;
						toReturn[1] = 3;
						toReturn[2] = 15;
					break;
					case 12:
						toReturn[0] = 8;
						toReturn[1] = 4;
						toReturn[2] = 16;
					break;
					case 13:
						toReturn[0] = 9;
						toReturn[1] = 1;
						toReturn[2] = 5;
					break;
					case 14:
						toReturn[0] = 10;
						toReturn[1] = 6;
						toReturn[2] = 2;
					break;
					case 15:
						toReturn[0] = 11;
						toReturn[1] = 3;
						toReturn[2] = 7;
					break;
					case 16:
						toReturn[0] = 4;
						toReturn[1] = 8;
						toReturn[2] = 12;
					break;
				}
			break;
		}
		
		return toReturn;
	}
	
	void clear()
	{
		for (int i = 0; i < dim * dim; i++)
		{
			for (int j = 0; j < dim * dim; j++)
			{
				setValueAt(i, j, "");
			}
		}
	}
}
class Main
{
	public static void main (String[] args)
	{
		SolveFrame sf = new SolveFrame(3);
	}
}