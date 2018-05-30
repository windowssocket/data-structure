#include"Pascal.h"

bool Pascal::CheckMatch()
{
	const string BEGIN("begin"),END("end"),IF("if"),THEN("then"),ELSE("else"); //save the key words
	string str;
	stack<string> S;

	while(!fin.eof())
	{
		char c;
		
		do  //read a word
		{
			fin.read(&c,1);
			if(('a'<=c && c<='z')||('A'<=c && c<='Z')) str.push_back(c);
		}while(!fin.eof() && (('a'<=c && c<='z') || ('A'<=c && c<='Z') ));
		
		if(str==BEGIN) S.push(BEGIN);
		  
		if(str==END)  //when read "end" ,栈中所有"begin"（包括begin）之后的字符都出栈
		{
			if(S.empty()) return false;
			
			if(S.top()==IF) return false; //if...then is not matched
			while(S.top()!=BEGIN)
			{
				S.pop();
				if(S.empty()) return false;
			}
			S.pop();
		}

		if(str==IF)
		{
			if(!S.empty() && S.top()==IF) return false;  //everybody who learned Pascal konws that "if...if" is illegal
			else S.push(IF);
		}

		if(str==THEN)
		{
			if(S.empty())return false;
			
			if(S.top()!=IF) return false;
			else S.push(THEN);
		}

		if(str==ELSE)
		{
			if(S.empty())return false;
			
			if(S.top()!=THEN) return false;
			else
			{
				S.pop();
				S.pop();
			}
		}

		str.clear();
	}

	if(!S.empty())  //the stack can only have "if...then"
	{
		if(S.top()!=THEN) return false; //"if...then" is not matched
		while(!S.empty()) {
			if(S.top()==BEGIN) return false;
			S.pop();
		}
	}

	return true;
}

