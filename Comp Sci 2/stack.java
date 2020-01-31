public class stack
{
	public int size;
	char x;
	char y;
	
	stack(char c, char v)
	{
		size = 0;
		x=c;
		y=v;
	}
	void add()
	{
		size++;
	}	
	void remove()
	{
		size--;
	}
	void display()
	{
		try{Thread.sleep(1500);}catch (Exception e){};
		if(size==0)
			System.out.println("\n\n\nProgram is properly balanced between "+x+" and "+y);
		if(size<0)
		{
			size=Math.abs(size);
			System.out.println("\n\n\nProgram has "+size+" too few "+x);
		}
		if(size>0)
		{
			System.out.println("\n\n\nProgram has "+size+" too few "+y);
		}
		try{Thread.sleep(1500);}catch (Exception e){};
	}
}