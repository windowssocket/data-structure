#include"SeqBinTree.h"

template<class Type>
void SeqBinTree<Type>::DoubleSize()
{
	Node *space=new Node[maxSize*=2];
	for(int i=0; i<length; ++i) space[i]=tree[i];  //copy the tree last
	delete[] tree;
	tree=space;
}

template<class Type>
void SeqBinTree<Type>::Assign(Type x, int i)  //assign to tree[i], if i is too large then double size
{
	while(i>=maxSize) DoubleSize(); //assign space for i
	tree[i].data=x;
	++length;
}

template<class Type>
int SeqBinTree<Type>::Height(int i, Node *t)const
{
	if(i==-1) return 0;
	else{
		int lt=Height(t[i].left,tree), rt=Height(t[i].right, tree);
		return 1+((lt>rt)? lt:rt) ;
	}
}

template<class Type>
void SeqBinTree<Type>::Create()
{
	queue<Type> Q;
	char a,b;
	Type x,tmp;

	cout<<"请输入根节点：";
	cin>>x;
	Assign(x,0);
	Q.push(x);

	int i=0,parent=0;  //parent save the current index of the current node
	while(!Q.empty()){
		tmp=Q.front();
		Q.pop();
		cout<<"请输入结点 "<<tmp<<" 的儿子类型（共00，01，10，11四种，你懂的）：";
		cin>>a>>b;

		if(a!='0'){
			cout<<"请输入结点 "<<tmp<<" 的左儿子结点：";
			cin>>x;
			tree[parent].left=++i;
			Assign(x,i);
			Q.push(x);
		}
		if(b!='0'){
			cout<<"请输入结点 "<<tmp<<" 的右儿子结点：";
			cin>>x;
			tree[parent].right=++i;
			Assign(x,i);
			Q.push(x);
		}
		++parent;  //each loop makes the current index +1
		cout<<endl;
	}
}

template<class Type>
void SeqBinTree<Type>::PreOrder()
{
	PreOrder(0,tree);
}

template<class Type>
void SeqBinTree<Type>::PreOrder(int i,Node *t)  //using recurssion
{
	cout<<t[i].data<<' ';
	if(t[i].left!=-1) PreOrder(t[i].left,t);
	if(t[i].right!=-1) PreOrder(t[i].right,t);
}

template<class Type>
void SeqBinTree<Type>::MidOrder()
{
	MidOrder(0,tree);
}

template<class Type>
void SeqBinTree<Type>::MidOrder(int i,Node *t)  //using recurssion
{
	if(t[i].left!=-1) MidOrder(t[i].left,t);
	cout<<t[i].data<<' ';
	if(t[i].right!=-1) MidOrder(t[i].right,t);
}

template<class Type>
void SeqBinTree<Type>::PostOrder()
{
	PostOrder(0,tree);
}

template<class Type>
void SeqBinTree<Type>::PostOrder(int i,Node *t)  //using recurssion
{
	if(t[i].left!=-1) PostOrder(t[i].left,t);
	if(t[i].right!=-1) PostOrder(t[i].right,t);
	cout<<t[i].data<<' ';
}