//Matthew Philpot
//Computer Science

//cheers dude. Here is my ListOLinks of Queues

#include <iostream>

using namespace std;

class listOlinks
{
     private:

		 struct node
         {
			 int theNUMBER;
			 node *link;
         }*p;

   public:

	listOlinks()
	{
		p=NULL;
	}

	void enQueue(int num)
	{
			node *q,*t;
				if( p == NULL )
			{
				p = new node;
				p->theNUMBER = num;
				p->link = NULL;
			}
			else
			{
				q = p;
				while( q->link != NULL )
				q = q->link;
				t = new node;
				t->theNUMBER = num;
				t->link = NULL;
				q->link = t;
			}
		}

		void deQueue()
		{
		node *q,*r;
		q = p;
		if( q->theNUMBER == 0)
		{
			p = q->link;
			delete q;
			cout << "First Element Deleted";
			return;
		}

		r = q;
		while( q!=NULL )
		{
			if( q->theNUMBER == 0)
			{
				r->link = q->link;
				delete q;
				cout << "First Element Deleted";
				return;
			}

			r = q;
			q = q->link;
		}

	}



	void peek()
	{
		cout << "\nFirst Element: " << p->theNUMBER << "\n";
	}

	~listOlinks()
	{
		node *q;
		if( p == NULL )
		{
			return;
		}

		while( p != NULL )
		{
			q = p->link;
			delete p;
			p = q;
		}
	}

};

int main()
{
	listOlinks ll;
	ll.enQueue(0);
	ll.enQueue(1);
	ll.enQueue(2);
	ll.peek();
	ll.deQueue();
	ll.peek();
	return 0;
}