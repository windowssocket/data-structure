#include"BinaryTree.h"

template<class Type>
void BinaryTree<Type>::Creat()
{
	queue<Node*> Q;
	char a,b;
	Type x;
	Node *tmp;   //save the node temporarily

	cout<<"��������ڵ㣺";
	cin>>x;
	root=new Node(x);
	Q.push(root);

	while(!Q.empty()){
		tmp=Q.front();
		Q.pop();
		cout<<"�������� "<<tmp->data<<" �Ķ������ͣ���00��01��10��11���֣��㶮�ģ���";
		cin>>a>>b;

		if(a!='0'){
			cout<<"�������� "<<tmp->data<<" ������ӽ�㣺";
			cin>>x;
			tmp->left=new Node(x);
			Q.push(tmp->left);
		}
		if(b!='0'){
			cout<<"�������� "<<tmp->data<<" ���Ҷ��ӽ�㣺";
			cin>>x;
			tmp->right=new Node(x);
			Q.push(tmp->right);
		}
		cout<<endl;
	}
}

template<class Type>
void BinaryTree<Type>::LevelQrder() //using queue to implementate the level order
{
	queue<Node*> Q;
	Node *tmp;
	Q.push(root);   //initialize the queue

	while(!Q.empty()){
		tmp=Q.front();
		Q.pop();
		cout<<tmp->data<<' ';  //visit node
		if(tmp->left!=NULL) Q.push(tmp->left);
		if(tmp->right!=NULL) Q.push(tmp->right);
	}
}

template<class Type>
bool BinaryTree<Type>::IsComplete()
{
	queue<Node*> Q;
	Node *tmp;
	Q.push(root);
	bool leafAppeared=false;

	while(!Q.empty()){
		tmp=Q.front();
		Q.pop();

		if(leafAppeared){    //every node after must be leaf node
			if(tmp->left!=NULL || tmp->right!=NULL) return false;
		}
		else if(tmp->left!=NULL){   //a complete tree can't leave left-child NULL while right-child not NULL
				Q.push(tmp->left);
				if(tmp->right==NULL) leafAppeared=true;  //leaf-node appeared
				else Q.push(tmp->right);
			}
		else{
			leafAppeared=true;  //leaf-node appeared
			if(tmp->right!=NULL) return false;
		}
	}

	return true;
}