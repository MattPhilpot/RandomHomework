//Written by Matthew Philpot
//I did not include user input, but culture1.java is perfect, while culutre2.java has missing brackets and paranthesis.
import java.util.*;
import java.io.*;
public class StackTest
{
	public static void z(String program, char first, char second)
	{
		stack k = new stack(first,second);
		System.out.println("\n\nStack-Tester is testing "+program+" for any irregularities between "+first+" and "+second+"\n\n");
		
		try
		{
			
			BufferedReader in = new BufferedReader(new FileReader(program));
			String str;
    	    while ((str = in.readLine()) != null) 
    	    {
    	    	try{Thread.sleep(400);}catch (Exception e){};
    	    	System.out.println(str);
    	    	for(int x=0;x<str.length();x++)
    	    	{
    	    		if(str.charAt(x)==first)
    	    			k.add();
    	    		if(str.charAt(x)==second)
    	    			k.remove(); 
    	    	}
    	    }
		}
		catch (IOException e) {};
		try{Thread.sleep(1000);}catch (Exception e){};
		System.out.println("\n\nProcessing...");
		k.display();
	}
	
	public static void main (String omgbbqpancakes[])
	{
		Scanner scan = new Scanner(System.in);
		String programName = "culture1.java";
		char x = '(';
		char y = ')';
		char z = '{';
		char w = '}';
		z(programName,x,y);
		z(programName,z,w);
		programName = "culture2.java";
		z(programName,x,y);
		z(programName,z,w);
	}
}