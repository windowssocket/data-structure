#include"Tree.h"

template<class Type>
void Tree<Type>::CreateTree()
{
	queue<Node*> Q;
	int n;
	Type data,x;
	Node *tmp;

	cout<<"请输入根节点：";
	cin>>x;
	root=new Node(x);
	Q.push(root);

	while(!Q.empty()){
		tmp=Q.front();
		Q.pop();
		data=tmp->data;
		cout<<"请输入结点 "<<data<<" 的儿子数目：";
		cin>>n;
		
		//deal with sun-node
		if(n>0){
			cout<<"请输入结点 "<<data<<" 的儿子结点 1：";
			cin>>x;
			tmp->son=new Node(x);
			Q.push(tmp->son);
		}
		
		//deal with brother-node
		tmp=tmp->son;
		for(int i=2; i<=n; ++i,tmp=tmp->brother){
			cout<<"请输入结点 "<<data<<" 的儿子结点 "<<i<<"：";
			cin>>x;
			tmp->brother=new Node(x);
			Q.push(tmp->brother);
		}
		cout<<endl;
	}
}

template<class Type>
void Tree<Type>::PreOrder()
{
	PreOrder(root);
}

template<class Type>
void Tree<Type>::PreOrder(Node *t)  //recursion
{
	cout<<t->data<<' ';
	if(t->son!=NULL)
		for(Node *tmp=t->son; tmp!=NULL; tmp=tmp->brother)  //visit brother node one by one
			PreOrder(tmp);
}

template<class Type>
void Tree<Type>::PostOrder()
{
	PostOrder(root);
}

template<class Type>
void Tree<Type>::PostOrder(Node *t)  //recursion
{
	if(t->son!=NULL) PostOrder(t->son);
	cout<<t->data<<' ';
	if(t->brother!=NULL) PostOrder(t->brother);
}

template<class Type>
void Tree<Type>::LevelOrder()
{
	deque<Node*> L;  //using deque to implementate brother node is firster than son node
	Node *tmp;
	L.push_back(root);

	while(!L.empty()){
		tmp=L.front();
		L.pop_front();
		cout<<tmp->data<<' ';
		if(tmp->son!=NULL) L.push_back(tmp->son);
		if(tmp->brother!=NULL) L.push_front(tmp->brother);  //brother node first
	}
}