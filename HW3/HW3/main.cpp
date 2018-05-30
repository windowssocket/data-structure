#include"FunnyString.h"

void main()
{
	FunnyString s1,s2;
	cout<<"please input s1:";
	cin>>s1;
	cout<<"please input s2:";
	cin>>s2;
	cout<<endl<<"The results are:"<<endl
		<<"s1+s2="<<s1+s2<<endl
		<<"s1-s2="<<s1-s2<<endl
		<<"s1*s2="<<s1*s2<<endl<<endl;

	cout<<"after s1+=s2 , s1="<<(s1+=s2)<<endl;
	cout<<"after s1-=s2 , s1="<<(s1-=s2)<<endl;
	cout<<"after s1*=s2 , s1="<<(s1*=s2)<<endl<<endl;

}