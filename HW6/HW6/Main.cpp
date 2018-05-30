#include<iostream>
#include<fstream>
#include"GH_SeqList.h"
#include"GH_SeqList.cpp"
using namespace std;

#define MaxSize 10  //the max size of the list

class Overflow{};  //the condition when the user input to many characters

void main()
{
	SeqList<char> list(MaxSize);
	ofstream os;   //point the file
	char filename[20];
	char c;   //temporarily save the character

	cout<<"Please input the characters:"<<endl;
	int i=0;  //the total char the user inputs
	while((c=cin.get()) != '\n')
	{
		if(c==' '|| c=='\t') continue;  //the spaces and tabs will be ignored
		++i;
		
		try
		{
			if(i>MaxSize) throw Overflow();  //error exception
			list.Insert(i,c);
		}

		catch(Overflow)  //error condition
		{
			cerr<<"You have input too many characters!"<<endl
				<<"the characters overflowed: ";
			
			cout<<'\"'<<c<<"\" ";
			while( (c=cin.get()) != '\n')
			{
				if(c==' ' || c=='\t') continue;  //the spaces and tabs will be ignored
				cout<<'\"'<<c<<"\" ";
			}
			
			cout<<"will be ignored!"<<endl<<endl;
			break;
		}
	}

	cout<<endl<<"Delete the first elem \""<<(c=list.Delete(1))<<"\" from the list"<<endl;
	cout<<"add it to the middle of the list"<<endl<<endl;
	list.Insert(list.Length()/2+1,c);

	cout<<"The final list is:"<<endl;
	for(int i=1; i<=list.Length(); ++i) cout<<list.Get(i)<<' ';  //output list

	cout<<endl<<endl<<"Input the file name you want to save:";
	cin>>filename;

	os.open(filename);
	for(int i=1; i<=list.Length(); ++i) os<<list.Get(i);  //put list into file
	os.close();

	cout<<"The list has been written to the file "<<filename<<endl
		<<"Thank you for using the class"<<endl;

}
