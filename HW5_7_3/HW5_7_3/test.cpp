#include"BinaryTree.h"
#include"BinaryTree.cpp"

int main()
{
	BinaryTree<char> tree;
	tree.Creat();
	cout<<"层序遍历结果： ";
	tree.LevelQrder();
	cout<<endl;
	if(tree.IsComplete()) cout<<"是完全二叉树"<<endl;
	else cout<<"不是完全二叉树"<<endl;
	return 0;
}