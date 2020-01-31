public class Node {
	private int data;
	private Node nextNode=null;
	private Node prevNode=null;
	
	public Node(int number, Node next, Node prev) 
	{
		data=number;
		nextNode=next;
		prevNode=prev;
	}
	
	public Node(int number, Node prev) 
	{
		data=number;
		prevNode=prev;
	}
	
	public Node(Node next, int number) 
	{
		data = number;
		nextNode = next;
	}
	
	public Node(int number) 
	{
		data = number;
	}
	
	public Node getNext() 
	{
		return nextNode;
	}
	
	public void setNext(Node next) 
	{
		nextNode=next;
	}

	public Node getPrev() 
	{
		return prevNode;
	}
	
	public void setPrev(Node prev) 
	{
		prevNode = prev;
	}
	
	public int getData() 
	{
		return data;
	}
	
	public void setData(int number) 
	{
		data=number;
	}
}