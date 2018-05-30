#include"Text.h"

void main()
{
	Text a;
	a.Open("aaa.txt");
	a.del(2,1,2);
	a.ins(1,2,"qmas***a");
	a.List(1,3);
	a.Quit("aaa.txt");
}
