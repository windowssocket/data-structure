#include"Set.h"
#include"Set.cpp"

int main()
{
	Set<int> s,t,r,q;
	q.Output();
	s.Input();
	t.Input();
	r=s+t;
	r.Output();
	r=s-t;
	r.Output();
	r=s*t;
	r.Output();
	return 0;
}