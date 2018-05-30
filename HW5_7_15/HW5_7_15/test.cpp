#include"SeqBinTree.h"
#include"SeqBinTree.cpp"

int main()
{
	SeqBinTree<char> t;
	t.Create();
	cout<<endl<<"size: "<<t.Size()
		<<endl<<"height:"<<t.Height();
	cout<<endl<<"PreOrder: ";
	t.PreOrder();
	cout<<endl<<"MidOrder: ";
	t.MidOrder();
	cout<<endl<<"PostOrder:";
	t.PostOrder();
	return 0;
}