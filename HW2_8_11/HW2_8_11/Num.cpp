#include"Num.h"

Num::~Num()
{
	node *p=head, *tmp=p;
	while(p!=NULL)
	{
		p=p->next;
		delete tmp;
		tmp=p;
	}
}


Num& Num::operator =(const Num &R)
{
	if(this==&R) return *this;
	else
	{
		Num::~Num();  //destruct lost data
		head=new node(0);
		node *p=R.head, *q=head;
		
		q->data=p->data;
		while(p->next=NULL)
		{
			p=p->next;
			q->next=new node(p->data);
			q=q->next;
		}
		sign=R.sign;
		
		return *this;

	}
}


istream& operator>>(istream &is, Num &num)
{
	char c;
	node *tmp;
	
	num.~Num();
	num.head=new node(0);
	num.sign=true;
	
	is.read(&c,1);
	while((c<'0' || c>'9') && c!='-') is.read(&c,1); //ignore extra digits

	if(c=='-')
	{
		num.sign=false;
		is.read(&c,1);
	}
	num.head->data=c-'0';
	
	is.read(&c,1);
	while('0'<=c && c<='9')
	{
		tmp=num.head;
		num.head=new node(c-'0');
		num.head->next=tmp;
		is.read(&c,1);
	}
	
	return is;

}


ostream& operator<<(ostream &os, const Num &num)  //using stack to save numbers, ignore the leading '0'
{
	stack<int> S;
	node *p;

	for(p=num.head; p!=NULL; p=p->next) S.push(p->data);

	while(S.size()>1 && S.top()==0) S.pop();   //ignore the 0 at top

	if(!num.sign && S.top()!=0) os<<'-';    //in case of '-0'
	while(!S.empty())
	{
		os<<S.top();
		S.pop();
	}

	return os;
}


Num operator+(const Num& n1, const Num& n2)  //include plus and minus
{
	Num *sum=new Num;

	delete sum->head;
	
	if(n1.sign==n2.sign)  //carry out "plus"
	{
		sum->head=Plus(n1.head,n2.head);
		sum->sign=n1.sign;
	}
	else  //carry out "minus"
	{
		if(Bigger(n1.head,n2.head))  //Abs(n1)>Abs(n2)
		{
			sum->head=Minus(n1.head, n2.head);
			sum->sign=n1.sign;
		}
		else
		{
			sum->head=Minus(n2.head, n1.head);
			sum->sign=n2.sign;
		}
	}

	return *sum;
}


node* Plus(node *p1, node *p2)
{
	node *head=new node(0),*p=head;
	int m=0,d1,d2; //d1,d2 is the current digit of n1,n2.  m is save plus digit

	while(true)
	{
		if(p1) d1=p1->data;
		else d1=0;
		if(p2) d2=p2->data;
		else d2=0;

		p->data=(d1+d2+m)%10;
		m=(d1+d2+m)/10;

		if(p1!=NULL) p1=p1->next;
		if(p2!=NULL) p2=p2->next;

		if(p1==NULL && p2==NULL && m==0) break;
		else
		{
			p->next=new node(0);
			p=p->next;
		}
	}

	return head;
}


node* Minus(node *p1, node *p2)
{
	node *head=new node(0),*p=head;
	int m=0,d1,d2;   //d1,d2 is the current digit of n1,n2.  m is save minus digit
	stack<int> S;

	while(true)
	{
		if(p1) d1=p1->data;
		else d1=0;
		if(p2) d2=p2->data;
		else d2=0;

		p->data=(10+d1-d2-m)%10;
		if(d1-m<d2) m=1;
		else m=0;

		if(p1!=NULL) p1=p1->next;
		if(p2!=NULL) p2=p2->next;

		if(p1==NULL && p2==NULL && m==0) break;
		else
		{
			p->next=new node(0);
			p=p->next;
		}
	}



	return head;
}


bool Bigger(node *p1, node *p2)
{
	stack<int> S1,S2;
	
	while(p1!=NULL) { S1.push(p1->data); p1=p1->next;}
	while(p2!=NULL) { S2.push(p2->data); p2=p2->next;}

	while(S1.size()>1 && S1.top()==0) S1.pop();   //ignore the 0 at top
	while(S2.size()>1 && S2.top()==0) S2.pop();   //ignore the 0 at top

	if(S1.size()!=S2.size()) return S1.size()>S2.size(); //the longer is the bigger
	else
	{
		while(!S1.empty())  //bit by bit compare
		{
			if(S1.top()!=S2.top()) return(S1.top()>S2.top());
			else
			{
				S1.pop();
				S2.pop();
			}
		}

		return true;
	}
}
