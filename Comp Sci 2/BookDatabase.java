import java.util.Scanner;
import java.io.*;

class Book
{
	String Author;
	String Editor;
	String Title;
	String ISBN; //identification number
	String Publisher;
	String PubDate;
	String KeywordList;
	
	Book(String A, String E, String T, String I, String P, String PUB, String K)
	{
		Author = A;
		Editor = E;
		Title = T;
		ISBN = I;
		Publisher = P;
		PubDate = PUB;
		KeywordList = K;
	}
	
	void set_author(String x)
	{
		Author = x;
	}
	
	void set_editor(String x)
	{
		Editor = x;
	}
	
	void set_title(String x)
	{
		Title = x;
	}
	
	void set_ISBN(String x)
	{
		ISBN = x;
	}
	
	void set_publisher(String x)
	{
		Publisher = x;
	}
	
	void set_pubdate(String x)
	{
		PubDate = x;
	}
	
	void set_keywords(String x)
	{
		KeywordList = x;
	}
}

class BookDatabase
{
	String DatabaseName;
	Book[] lib = new Book[0];
	
	Scanner scan = new Scanner(System.in);

	void BookDatabase(String BaseName)
	{
		DatabaseName = BaseName;
		System.out.println("Database '"+DatabaseName+"' created...\n\n\n");
	}
	
	void addBook(String A, String E, String T, String I, String P, String PUB, String K)
	{
		Book[] temp = new Book[lib.length + 1];
		
		for (int i = 0; i < lib.length; i++)
		{
			temp[i] = lib[i];
		}
		
		temp[lib.length] = new Book(A, E, T, I, P, PUB, K);
		
		lib = temp;
	}
	
	int Where_is_it(String title)
	{
		int y = 0;
		for(int x = 0;x<lib.length;x++)
		{
			
			if(lib[x].Title.equals(title))
				y = x;
		}
		return y;	
	}
	
	void remove_book(String title)
	{
		Book[] temp = new Book[lib.length-1];
		int x = 0;
		while(x<lib.length)
		{
			if(!lib[x].Title.equals(title))
			{
				temp[x] = lib[x];
			}
			if(lib[x].Title.equals(title))
			{
				x--;
			}
			x++;
		}
		System.out.println("Book Removed!");
	} 
	
	void edit_information(String title)
	{
		String Author;
		String Editor;
		String Title;
		String ISBN; //identification number
		String Publisher;
		String PubDate;
		String KeywordList;
		Scanner scan = new Scanner(System.in);
		int title_spot = Where_is_it(title);
		System.out.print("What part of this book would you like to change? ");
		String answer = scan.nextLine();
		if(answer.toLowerCase().equals("title"))
		{
			System.out.print("What would you like to change the Title to? ");
			answer = scan.nextLine();
			lib[title_spot].set_title(answer);
		}
		if(answer.toLowerCase().equals("author"))
		{
			System.out.print("What would you like to change the Author to? ");
			answer = scan.nextLine();
			lib[title_spot].set_author(answer);	
		}
		if(answer.toLowerCase().equals("publisher"))
		{
			System.out.print("What would you like to change the Publisher to? ");
			answer = scan.nextLine();
			lib[title_spot].set_publisher(answer);
		}
		if(answer.toLowerCase().equals("editor"))
		{
			System.out.print("What would you like to change the Editor to? ");
			answer = scan.nextLine();
			lib[title_spot].set_editor(answer);
		}
		if(answer.toLowerCase().equals("isbn"))
		{
			System.out.print("What would you like to change the ISBN to? ");
			answer = scan.nextLine();
			lib[title_spot].set_ISBN(answer);
		}
		if(answer.toLowerCase().equals("publish date"))
		{
			System.out.print("What would you like to change the Publish Date to? ");
			answer = scan.nextLine();
			lib[title_spot].set_pubdate(answer);
		}
		if(answer.toLowerCase().equals("keywords") || answer.toLowerCase().equals("keyword"))
		{
			System.out.print("What would you like to change the Keywords to?");
			answer = scan.nextLine();
			lib[title_spot].set_keywords(answer);
		}		
	}
	
	void displayAll()
	{
		for (Book b : lib)
		{
			System.out.println("Title:        "+b.Title);
			System.out.println("Author :      "+b.Author);
			System.out.println("Editor:       "+b.Editor);
			System.out.println("Publisher:    "+b.Publisher);
			System.out.println("Publish Date: "+b.PubDate);
			System.out.println("ISBN:         "+b.ISBN);
			System.out.println("Keywords:     "+b.KeywordList);
			System.out.println();
		}
	}
	
	void displayBook(String title, int ig)
	{
		for (Book b : lib)
		{
			if (b.Title.equals(title) && ig==0)
			{
				System.out.println("Title:        "+b.Title);
				System.out.println("Author :      "+b.Author);
				System.out.println("Editor:       "+b.Editor);
				System.out.println("Publisher:    "+b.Publisher);
				System.out.println("Publish Date: "+b.PubDate);
				System.out.println("ISBN:         "+b.ISBN);
				System.out.println("Keywords:     "+b.KeywordList);
				System.out.println();
			}
			if (b.Author.equals(title) && ig==1)
			{
				System.out.println("Title:        "+b.Title);
				System.out.println("Author :      "+b.Author);
				System.out.println("Editor:       "+b.Editor);
				System.out.println("Publisher:    "+b.Publisher);
				System.out.println("Publish Date: "+b.PubDate);
				System.out.println("ISBN:         "+b.ISBN);
				System.out.println("Keywords:     "+b.KeywordList);
				System.out.println();
			}
			if (b.Editor.equals(title) && ig==2)
			{
				System.out.println("Title:        "+b.Title);
				System.out.println("Author :      "+b.Author);
				System.out.println("Editor:       "+b.Editor);
				System.out.println("Publisher:    "+b.Publisher);
				System.out.println("Publish Date: "+b.PubDate);
				System.out.println("ISBN:         "+b.ISBN);
				System.out.println("Keywords:     "+b.KeywordList);
				System.out.println();
			}
			if (b.Publisher.equals(title) && ig==3)
			{
				System.out.println("Title:        "+b.Title);
				System.out.println("Author :      "+b.Author);
				System.out.println("Editor:       "+b.Editor);
				System.out.println("Publisher:    "+b.Publisher);
				System.out.println("Publish Date: "+b.PubDate);
				System.out.println("ISBN:         "+b.ISBN);
				System.out.println("Keywords:     "+b.KeywordList);
				System.out.println();
			}
			if (b.PubDate.equals(title) && ig==4)
			{
				System.out.println("Title:        "+b.Title);
				System.out.println("Author :      "+b.Author);
				System.out.println("Editor:       "+b.Editor);
				System.out.println("Publisher:    "+b.Publisher);
				System.out.println("Publish Date: "+b.PubDate);
				System.out.println("ISBN:         "+b.ISBN);
				System.out.println("Keywords:     "+b.KeywordList);
				System.out.println();
			}
			if (b.ISBN.contains(title) && ig==5)
			{
				System.out.println("Title:        "+b.Title);
				System.out.println("Author :      "+b.Author);
				System.out.println("Editor:       "+b.Editor);
				System.out.println("Publisher:    "+b.Publisher);
				System.out.println("Publish Date: "+b.PubDate);
				System.out.println("ISBN:         "+b.ISBN);
				System.out.println("Keywords:     "+b.KeywordList);
				System.out.println();
			}
			if (b.KeywordList.contains(title) && ig==6)
			{
				System.out.println("Title:        "+b.Title);
				System.out.println("Author :      "+b.Author);
				System.out.println("Editor:       "+b.Editor);
				System.out.println("Publisher:    "+b.Publisher);
				System.out.println("Publish Date: "+b.PubDate);
				System.out.println("ISBN:         "+b.ISBN);
				System.out.println("Keywords:     "+b.KeywordList);
				System.out.println();
			}
		}
	}
	
void save_database()
{
	try
	{ 
	   	FileWriter fstream = new FileWriter(DatabaseName+".txt");
		BufferedWriter out = new BufferedWriter(fstream);
 
	    for( int i=0; i<lib.length; i++)
    	{
    		out.newLine();
			out.write(lib[i].Title);
			out.newLine();
			out.write(lib[i].Author);
			out.newLine();
			out.write(lib[i].Editor);
			out.newLine();
			out.write(lib[i].Publisher);
			out.newLine();
			out.write(lib[i].PubDate);
			out.newLine();
			out.write(lib[i].ISBN);
			out.newLine();
			out.write(lib[i].KeywordList);
			out.newLine();
			out.write("//");
		}
		out.newLine();
		out.write("////");
		out.close();
	}
	catch (Exception e)
	{
		System.out.println("Error: " + e.getMessage());
	}
}
	
	void load_database(String name)
	{
		File reader = new File(name);
		
		try 
		{
			Scanner scan = new Scanner(reader);
			do
			{
				String tit = scan.nextLine();
				String aut = scan.nextLine();
				String ed = scan.nextLine();
				String pub = scan.nextLine();
				String date = scan.nextLine();
				String isbn = scan.nextLine();
				String key = scan.nextLine();
				addBook(aut,ed,tit,isbn,pub,date,key);
				
			}
			while(!scan.nextLine().equals("////"));
		}
		catch (Exception e)
		{
			
		}
	}
}

class BooksMain
{
	public static void main(String r[])
	{
		Scanner scan = new Scanner(System.in);
		System.out.println("Hi, welcome to Matthew Philpot's Book Database!\n\n");		
		boolean menu = true;
		BookDatabase book1 = new BookDatabase();
		while(menu)
		{//big while
			System.out.println("\nWhat would you like to do with your Book Database?\n--------------------------------------------------\n-Create One\n-Delete One\n-Edit One\n-List all Databases\n-Save Database\n-Load Database\n-Exit\n");
			String answer = scan.nextLine();
			answer.toLowerCase();	
			if(answer.equals("save") || answer.equals("save database"))
			{
				book1.save_database();
			}
			if(answer.contains("load") || answer.equals("load database"))
			{
				System.out.print("\nWhat Database would you like to load?  ");
				String itt = scan.nextLine();
				book1.load_database(itt);
			}
			if(answer.equals("exit"))
			{
				System.out.println("\n\n");
				menu = false;
			}
			if(answer.equals("delete") || answer.equals("delete a book database") || answer.contains("delete database"))
			{
				try
				{
					System.out.print("Enter the Database to be deleted: ");
					String fileName = scan.nextLine();
					File target = new File(fileName);
					if (!target.exists()) 
					{
		       			System.err.println("File " + fileName+ " not present to begin with!");
		     			}
		     			if (target.delete())
		       			System.err.println("** Deleted " + fileName + " **");
		     			else
		       			System.err.println("Failed to delete " + fileName);	
				}
	       		catch (SecurityException e) {}
	    	}	
			if(answer.equals("create") || answer.equals("create one") || answer.equals("create a new book database") || answer.equals("new") || answer.contains("new database") || answer.contains("edit"))
			{//main menu if
				if(answer.equals("create") || answer.equals("create a new book database") || answer.equals("new") || answer.contains("new database"))
				{
					System.out.println("\nWhat would you like to name it?");
					String basename = scan.nextLine();
					book1.BookDatabase(basename);
				}
				boolean menurepeat = true;
				while(menurepeat)
				{//while
					System.out.println("\nWhat would you like to do?\n--------------------------\n-Add a Book\n-Delete a Book\n-Edit a Book\n-Display a Book\n-Display all Books\n-Exit to Main Menu\n");
					answer = scan.nextLine();
					System.out.println();
					if(answer.equals("add") || answer.equals("add a book") || answer.equals("add book"))
					{
						String Author;
						String Editor;
						String Title;
						String ISBN; //identification number
						String Publisher;
						String PubDate;
						String KeywordList;
						System.out.println("\nPlease enter book details...\n");
						System.out.print("Author: ");
						Author = scan.nextLine();
						System.out.print("Editor: ");	
						Editor = scan.nextLine();
						System.out.print("Title: ");	
						Title = scan.nextLine();
						System.out.print("ISBN: ");	
						ISBN = scan.nextLine();
						System.out.print("Publisher: ");	
						Publisher = scan.nextLine();
						System.out.print("Publish Date: ");	
						PubDate = scan.nextLine();
						System.out.print("Keyword(s): ");	
						KeywordList = scan.nextLine();
						System.out.print("Add Book? (yes or no) ");
						String answer1 = scan.nextLine();
						if(answer1.equals("yes"))
							book1.addBook(Author,Editor,Title,ISBN,Publisher,PubDate,KeywordList);
						menurepeat = true;
					}
					if(answer.equals("delete") || answer.equals("delete a book") || answer.equals("delete book"))
					{
						System.out.println("What book would you like to delete? Please use the Title.");
						String remove = scan.nextLine();
						book1.remove_book(remove);
						menurepeat = true;
					}
					if(answer.equals("edit") || answer.equals("edit a book") || answer.equals("edit book"))
					{
						System.out.print("What book would you like to edit?   ");
						String rawrness = scan.nextLine();
						book1.edit_information(rawrness);
					}
					if(answer.equals("display a book") || answer.equals("display book"))
					{
						String search;
						System.out.println("What criteria would you like to use to display a book or books?");
						String it = scan.nextLine();
						it.toLowerCase();
						if(it.equals("author"))
						{
							System.out.println("What "+it+" would you like to search for?");
							search = scan.nextLine();
							book1.displayBook(it,0);	
						}
						if(it.equals("editor"))
						{
							System.out.println("What "+it+" would you like to search for?");
							search = scan.nextLine();
							book1.displayBook(it,1);
						}
						if(it.equals("title"))
						{
							System.out.println("What "+it+" would you like to search for?");
							search = scan.nextLine();
							book1.displayBook(it,2);
						}
						if(it.equals("isbn"))
						{
							System.out.println("What "+it+" would you like to search for?");
							search = scan.nextLine();
							book1.displayBook(it,3);
						}
						if(it.equals("publisher"))
						{
							System.out.println("What "+it+" would you like to search for?");
							search = scan.nextLine();
							book1.displayBook(it,4);
						}
						if(it.equals("publish date"))
						{
							System.out.println("What "+it+" would you like to search for?");
							search = scan.nextLine();
							book1.displayBook(it,5);
						}
						if(it.contains("keyword"))
						{
							System.out.println("What "+it+" would you like to search for?");
							search = scan.nextLine();
							book1.displayBook(it,6);
						}
						menurepeat = true;
					}
					if(answer.equals("display all books") || answer.equals("display all") || answer.equals("display"))
					{
						book1.displayAll();
						menurepeat = true;
					}
					if(answer.equals("exit") || answer.equals(""))
					{
						menurepeat = false;
						menu = true;
					}
				}//while
			}//main menu if
		}//big while
	}
}