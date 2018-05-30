#include"Pascal.h"

void main()
{
	Pascal file;
	file.Open("Pascal.txt");
	
	if(file.CheckMatch()) cout<<"it is matched"<<endl;
	else cout<<"not matched"<<endl;
}
