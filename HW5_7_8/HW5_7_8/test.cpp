#include"Tree.h"
#include"Tree.cpp"

int main()
{
	Tree<char> t;
	t.CreateTree();
	cout<<endl<<"ǰ�������"<<endl;
	t.PreOrder();
	cout<<endl<<"���������"<<endl;
	t.PostOrder();
	cout<<endl<<"���������"<<endl;
	t.LevelOrder();
	cout<<endl;
	
	return 0;
}