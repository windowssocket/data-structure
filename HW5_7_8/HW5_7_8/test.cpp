#include"Tree.h"
#include"Tree.cpp"

int main()
{
	Tree<char> t;
	t.CreateTree();
	cout<<endl<<"前序遍历："<<endl;
	t.PreOrder();
	cout<<endl<<"后序遍历："<<endl;
	t.PostOrder();
	cout<<endl<<"层序遍历："<<endl;
	t.LevelOrder();
	cout<<endl;
	
	return 0;
}