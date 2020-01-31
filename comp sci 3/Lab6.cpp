//Matthew Philpot
//Computer Science 2050.002


#include <iostream>
#include <String>

using namespace std;

class linklist
{
     private:

         struct node
         {
			string name;
			string Address;
			int phone;
			string cityStateZip;
            node *link;
         }*p;

   public:

	linklist()
{
	p=NULL;
}

void append(string nam, string add, int phon, string cSZ)
{
	node *q,*t;

	if( p == NULL )
	{
		p = new node;
		p->name = nam;
		p->Address = add;
		p->phone = phon;
		p->cityStateZip = cSZ;
		p->link = NULL;
	}

	else
	{
		q = p;
		while( q->link != NULL )
		{
			q = q->link;
		}

		t = new node;
		t->name = nam;
		t->Address = add;
		t->phone = phon;
		t->cityStateZip = cSZ;
		t->link = NULL;
		q->link = t;
	}
}

void add_as_first(string nam, string add, int phon, string cSZ)
{
	node *q;

	q = new node;
	q->name = nam;
	q->Address = add;
	q->phone = phon;
	q->cityStateZip = cSZ;
	q->link = p;
	p = q;
}

void addafter(int c, string nam, string add, int phon, string cSZ)
{
	--c;
	node *q,*t;
	int i;
	for(i=0,q=p;i<c;i++)
	{
		q = q->link;
		if( q == NULL )
		{
			cout<<"\nThere are less than "<<c<<" elements.";
			return;
		}
	}

	t = new node;
	t->name = nam;
	t->Address = add;
	t->phone = phon;
	t->cityStateZip = cSZ;
	t->link = q->link;
	q->link = t;
}


void del(int num)
{
	--num;
	node *q, *r;
	q = p;
	
	if(num == 0)
	{
		p = q->link;
		//delete q;
	}

	else
	{
		bool found = true;
		for(int i = 1; i < num; ++i)
		{
			q = q->link;
			if(q == NULL)
			{
				found = false;
				break;
			}
		}

		r = q;
		q = q->link;
		r->link = q->link;
		delete q;
	}
	
}


void display(int num)
{
	node *q;
	cout<<endl;
	q = p;
	bool found = true;
	for(int i = 1; i < num; ++i)
	{
		q = q->link;
		if(q == NULL)
		{
			found = false;
			break;
		}
	}
	
	if(found == true)
	{
		cout << "\n\nName: " << q->name;
		cout << "\nAddress: " << q->Address;
		cout << "\nCity, State, Zip: " << q->cityStateZip;
		cout << "\nPhone #: " << q->phone;
	}
	else
	{
		cout << "\n\nThere were fewer elements than what was requested to view\n";
	}
}

int count()
{
	node *q;
	int c=0;
	for( q=p ; q != NULL ; q = q->link )
	{
		c++;
	}

	return c;
}

~linklist()
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
	linklist ll;
	ll.add_as_first("Matthew Philpot", "3904 Immel Dr.", 2144600780, "Flower Mound, TX, 75022");
	ll.add_as_first("Matthew Philpot", "3904 Immel Dr.", 2144600780, "Flower Mound, TX, 75022");
	ll.add_as_first("Matthew Philpot", "3904 Immel Dr.", 2144600780, "Flower Mound, TX, 75022");
	ll.add_as_first("Matthew Philpot", "3904 Immel Dr.", 2144600780, "Flower Mound, TX, 75022");
	ll.append("Matthew Philpot", "3904 Immel Dr.", 2144600780, "Flower Mound, TX, 75022");
	ll.addafter(4, "Matthew Philpot", "3904 Immel Dr.", 2144600780, "Flower Mound, TX, 75022");
	cout<<"No. of elements = "<<ll.count();

	cout<<"\n\n\nNo. of elements = "<<ll.count();

	ll.display(1);
	ll.display(2);
	ll.display(3);
	ll.display(4);
	ll.display(5);
	ll.display(6);

	ll.del(4);

	cout << "***************";
	cout << "\n******************";
	
	ll.display(1);
	ll.display(2);
	ll.display(3);
	ll.display(4);
	ll.display(5);

	cout<<"\n\n\nNo. of elements = "<<ll.count();
	return 0;
}