#include"BinaryTree.h"
#include"BinaryTree.cpp"

int main()
{
	BinaryTree<char> tree;
	tree.Creat();
	cout<<"������������ ";
	tree.LevelQrder();
	cout<<endl;
	if(tree.IsComplete()) cout<<"����ȫ������"<<endl;
	else cout<<"������ȫ������"<<endl;
	return 0;
}