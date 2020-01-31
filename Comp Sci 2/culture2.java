import java.io.*;

public class culture1
{
	public static void main(String[] args
	{
		try 
		{
    		BufferedReader in = new BufferedReader(new FileReader("culture1.java"));
    	    String str;
    	    while (str = in.readLine()) != null) 
    	    {
    	        System.out.println(str);
    	        if(str.length( > 5
    	          System.out.println("char at 5 is "+str.charAt(5));
    	    }
    	in.close();
    	} 
    	catch (IOException e {}    
}