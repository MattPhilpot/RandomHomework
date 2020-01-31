import java.util.Scanner;
public class backwardsInt
{
	public static int tehCOUNTERofDETH = 0;
	public static void main(String args[])
	{
		Scanner scan = new Scanner(System.in);
		System.out.print("Please enter a number: ");
		String iLoveStringCheez = scan.nextLine();
		System.out.print("You entered: "+iLoveStringCheez+"\n");
		tehCOUNTERofDETH = iLoveStringCheez.length()-1;
		System.out.print("The new number is: ");
		rawr(iLoveStringCheez, tehCOUNTERofDETH);
	}
	static String rawr(String iLoveStringCheez, int countbob)
	{
		if(countbob>=0)
		{
			System.out.print(iLoveStringCheez.charAt(countbob));
			rawr(iLoveStringCheez, countbob-1);
		}
		return "\n";
	}
}
