import java.util.Scanner;
public class LListMain {

	public static void main(String[] args) 
	{
		boolean repeat = true;
		LList linkedList = new LList();
		int x = 0;
		Scanner scan = new Scanner(System.in);
		System.out.println("New List Created.");
		while(repeat)
		{
			System.out.println("What would you like to do?\n1)Add Node\n2)Append Node\n3)Display Nodes\n4)Display a Certain Node\n5)Exit");
			x = scan.nextInt();
			if(x==1)
			{
				int y = 0;
				System.out.print("What number would you like to add to the node? ");
				y = scan.nextInt();
				System.out.println();
				linkedList.addNode(y);
			}
			if(x==2)
			{
				int y = 0;
				System.out.print("What number would you like to add to the node? ");
				y = scan.nextInt();
				System.out.println();
				linkedList.appendNode(y);
			}
			if(x==3)
			{
				System.out.println("\nDisplaying...\n");
				linkedList.display();
				System.out.println("\n");
			}
			if(x==4)
			{
				int y = 0;
				System.out.print("\nWhich node would you like to display? ");
				y = scan.nextInt();
				System.out.println();
				linkedList.displaynode(y);
				System.out.println();
			}
			if(x==5)
			{
				System.out.println("\nExiting... I will print out your list of nodes before you leave. =)\n");
				linkedList.display();
				System.out.println("\n\nGoodbye!");
				repeat=false;
			}
		}
		
	}
}