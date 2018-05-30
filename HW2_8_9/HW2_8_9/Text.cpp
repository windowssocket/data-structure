#include"Text.h"

void Text::Open(char *filename)
{
	ifstream fin(filename);
	char c;
	string str;

	while(!fin.eof())
	{
		fin.read(&c,1);
		if(c!='\n') str.push_back(c);
		else
		{
			if(!str.empty()) txt.push_back(str);
			str.clear();
		}

	}
}


void Text::Quit(char *filename)
{
	ofstream fon(filename);

	list<string>::iterator itr=txt.begin(), itre=txt.end();

	for( ;itr!=itre; ++itr) fon<<*itr<<endl;
}


void Text::List(int n1, int n2)
{
	list<string>::iterator itr=txt.begin();

	if(n1>txt.size() || n2>txt.size())
	{
		cout<<"没这么多行"<<endl;
		return;
	}

	for(int i=1; i<n1; ++i) ++itr;
	for(int i=n1; i<=n2; ++i) 
	{
		cout<<*itr<<endl;
		if(itr!=txt.end()) ++itr;
	}
}


void Text::del(int row, int col, int n)
{
	list<string>::iterator itr=txt.begin();
	string::iterator itrs;

	for(int i=1; i<row; ++i) ++itr;
	
	if(itr->length()<=col+n-1)    //avoid erase too much words
	{   
		cout<<"第"<<row<<"行没这么多数给你删"<<endl;
		return;
	}

	itrs=itr->begin();
	itr->erase(itrs+col-1,itrs+col+n-1);
}


void Text::ins(int row, int col, string str)
{
	list<string>::iterator itr=txt.begin();
	string::iterator itrs;

	for(int i=1; i<row; ++i) ++itr;
	for(int n=1; !str[n]; ++n);

	itrs=itr->begin();
	itr->insert(itrs+col-1, str.begin(), str.end());
}
