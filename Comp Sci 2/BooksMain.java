public class BooksMain
{
	public static void main(String r[])
	{
		BookDatabase book1 = new BookDatabase("Employees");
		book1.addBook("Bob Lee, Joe Jim", "Fred", "Omg Pancakes", "1234", "that guy", "1/2/33", "omg, awesome, cool");
		book1.addBook("Bob Lee, Joe Jim", "Fred", "Omg Pancakes", "1234", "that guy", "1/2/33", "omg, awesome, cool");
		book1.displayAll();
	}
}