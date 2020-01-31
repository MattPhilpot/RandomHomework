import java.io.*;
import java.util.*;
public class TOWERSofHANOI
{
	static int numMoves=0;
	public static void main(String[] args)
    {
    	 Scanner scan = new Scanner(System.in);
         int howtall;
         char AAA='A', BBB='B', CCC='C';
         System.out.print("Please Enter Number of Rings? ");
         howtall = scan.nextInt();
         TEHtowers(howtall, AAA, BBB, CCC);
         System.out.println();
    }
	static void moveTHATthing(char AAA, char BBB)
    {
         numMoves++;
         System.out.print(AAA+" to ");
         System.out.println(BBB);
         System.out.print(((numMoves % 20)==0) ? '\n' : ' ');
    }
	static void TEHtowers(int   height, char  AAA, char  BBB, char  CCC)
    {
        if (height >= 1)
        {
           TEHtowers(height-1, AAA, CCC, BBB); 
           moveTHATthing(AAA, BBB);
           TEHtowers(height-1, CCC, BBB, AAA);
        }
    }
	static int getThatNum()
    {
        String OMGpanKaKeS;
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in)); 
        try
        {
           OMGpanKaKeS = in.readLine();
           int i = Integer.valueOf(OMGpanKaKeS).intValue();
           return i;
        }
        catch (Exception e)
        {
           System.err.println("The number you input is not right you retard. Enter a number greater than 1");
           return 1;
        }
    }
}