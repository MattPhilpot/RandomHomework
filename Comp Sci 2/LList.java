public class LList {
	private Node headNode=null;
	private Node lastNode=null;
	private int numberOfNodes = 0;
	private int tempnodes = 0;
	
	public void addNode(int numberToAdd) 
	{
		++numberOfNodes;
		if(headNode==null) 
		{
			headNode=new Node(numberToAdd);
			lastNode=headNode;
		}
		
		else 
		{
			headNode.setPrev(new Node(headNode, numberToAdd));
			headNode = headNode.getPrev();
			headNode.setPrev(lastNode);
		}
		
	}
	
	public void appendNode(int numberToAdd) {
		++numberOfNodes;
		if(headNode==null) {
			headNode=new Node(numberToAdd);
			lastNode=headNode;
		}
		else {
			lastNode.setNext(new Node(numberToAdd, lastNode));
			lastNode = lastNode.getNext();
			lastNode.setNext(headNode);
		}
	}
	
	public void display()
	{
		tempnodes = numberOfNodes;
		display1(tempnodes);
	}
	
	public void display1(int y) 
	{
		int x = y-1;
		Node currentNode = headNode;
		for(int z = 0; z<numberOfNodes; ++z)
		{
			int w = currentNode.getData();
			if(z==x)
				System.out.print(w+" ");
			currentNode = currentNode.getNext();	
		}
		if(x!=0)
			display1(x);
	}
	
	public void displaynode(int where) {
		Node currentNode = headNode;
		if(where < numberOfNodes) {
			for(int i = 1; i < where; ++i) {
				currentNode = currentNode.getNext();
			}
			System.out.print(currentNode.getData());
		}
		else {
			System.out.println("There are less nodes that the number you wanted to see.");
		}
		System.out.println();
	}
}
