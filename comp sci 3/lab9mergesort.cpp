//Matthew Philpot
//Computer Science 2050.002

//It's 3am in the morning... so tired... but it's done... rabble rabble rabble

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


struct Node {
	Node(int d) : data(d), next(0) { }  
	Node *next;
	int data;
};



Node* makeList(int size)
{		
	
	Node *head;
	Node *node;
	Node *prev;
	for (int i = 0; i < size; i++)
	{
		node = new Node(1+rand()%1000); 
		if (i == 0){head = node;}
		if(i != 0){prev->next = node;}
		node->next = NULL;
		prev = node;
		}
	return (head);
}

void display(Node *head)
{
	Node *node;
	if(head == NULL)
	{
		cout<<"The list is empty!\n";
	}

	if(head != NULL)
	{
		for (node = head; node->next != NULL; node = node->next) 
		{
			cout<<"\n"<<node->data;
		}

		cout<<"\n"<<node->data;
	}
}



void end(Node *head)
{

	Node *nodeTemp;
	Node *node;
	
	if (head!=NULL)
	{
		for (node = head ; node->next!=NULL ; node = nodeTemp) 
		{
			nodeTemp = node->next;
			delete node;
		}
	}
}

Node* merge(Node *a, Node *b)
{
	
	Node *pTemp;
	Node *sorted;
	
	int value = a->data;
	
	pTemp = a;	
	sorted = a;
	
	while(pTemp->next != NULL)
	{
		pTemp = pTemp->next;
	}
	pTemp->next = b;

	while(a->next != NULL)
	{
		value = a->data;
		pTemp = a;
		while(pTemp->next != NULL)
		{
			pTemp = pTemp->next;
			
			if (pTemp->data<value)
			{
				value = pTemp->data;
				pTemp->data = a->data;
				a->data = value;
			}
		}
		a = a->next;
		
	}
	
	return(sorted);
}



Node* mergeSort(Node *head)
{
	
	Node *tmnode;
	Node *node;
	
	if (head->next != NULL)
	{
		
		int i = 0,size = 0;
		
		for(tmnode = head; (tmnode->next) != NULL; tmnode = tmnode->next)
			size++;
	
		tmnode = head;
		

		for(i = 0; i < size/2; i++)
		{
			tmnode = tmnode->next;
		}
		
		node = tmnode->next;
		tmnode->next = NULL;
		head = mergeSort(head);
		node = mergeSort(node);
		head = merge(head,node);
	}
	return(head);	
}


void main()
{
	
	int size = 0;
	
	while (size <= 0){	
		cout << "Enter list size: ";
		cin >> size;
	}
	
	Node* p = makeList(size);
	
	cout<<"\nThe original list is:";
	display(p);
	
	p = mergeSort(p);	
	cout << "\n\nThe sorted list is:";
	display(p);
	
	cout<<"\n\n";
	end(p);	
}