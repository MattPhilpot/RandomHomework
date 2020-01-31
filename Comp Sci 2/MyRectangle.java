import java.util.Scanner;
public class MyRectangle
{
	public static void main(String args[])
	{
		double w = 0;
		double l = 0;
		int option = 0;
		boolean repeat = true;
		boolean smallrep = true;
		Scanner scan = new Scanner(System.in);
		while(repeat)
		{
			System.out.print("What would you like the dimensions of the rectangle to be? \nWidth? ");
			w = scan.nextDouble();
			System.out.print("Length? ");
			l = scan.nextDouble();
			TehRectangle MrRect = new TehRectangle(w,l);
			smallrep=true;
			while(smallrep)
			{
			
				System.out.println("\n\nWhat would you like to do with your Rectangle?\n1)Calculate the Area\n2)Calculate the Perimeter\n3)Print out the Length and Width of the Triangle\n4)Change the Deminsions of the Triangle\n5)Exit");
				option = scan.nextInt();
				switch(option)
				{
					case 1: System.out.println("The Area is: "+MrRect.area());repeat=false;break;
					case 2: System.out.println("The Perimeter is: "+MrRect.perimeter());repeat=false;break;
					case 3: MrRect.stats();repeat=false;break;
					case 4: smallrep=false;repeat=true;break;
					case 5: System.out.println("Goodbye!!");smallrep=false;repeat = false;break;
				}
			}
		}
	}
}