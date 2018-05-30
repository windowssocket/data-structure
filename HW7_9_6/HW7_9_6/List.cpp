#include"List.h"

template<class Type>
void List<Type>::Insert(Type x)
{
	node *p;
	for(p=head; p->next!=NULL; p=p->next);  //move p to the tail of the list
	p->next=new node(x);
}

template<class Type>
void List<Type>::MoveToHead(node *t)
{
	node *tmp=t->next;
	t->next=tmp->next;
	tmp->next=head->next;
	head->next=tmp;
}

template<class Type>
bool List<Type>::Search(Type x)
{
	for(node *q=head; q->next!=NULL; q=q->next){     //q is used as a pre. node of the q
		node *p=q->next;
		if(p->data==x){
			MoveToHead(q);  //move the frequent node to the head
			return true;
		}
	}
	return false;
}

template<class Type>
void List<Type>::Traverse()
{
	for(node *p=head->next; p!=NULL; p=p->next) cout<<p->data<<' ';
	cout<<endl;
}
