#include"FunnyString.h"

FunnyString::FunnyString()
{
	code=new char[1];
	length=0;
}


FunnyString::FunnyString(char *str)
{
	for(length=0; str[length]; ++length);  //get the lenght of the str

	code=new char[length+1];
	for(int i=0; i<=length; ++i) code[i]=str[i];
}


FunnyString::FunnyString(FunnyString &S)
{
	if(this==&S) return;  //avoid copy itself
	else
	{
		code=new char[S.length+1];
		for(int i=0; i<=S.length; ++i) code[i]=S.code[i];

		length=S.length;
	}

}


FunnyString::~FunnyString()
{
	delete[] code;
}


int FunnyString::Length()const
{
	return length;
}


FunnyString& FunnyString::operator =(const FunnyString &S)
{
	if(this==&S) return *this;  //avoid assign itself
	else
	{
		delete[] code;
		code=new char[S.length+1];
		for(int i=0; i<=S.length; ++i) code[i]=S.code[i];

		length=S.length;
	}

	return *this;
}


FunnyString& FunnyString::operator +=(const FunnyString &S)
{
	return(*this=*this + S);
}


FunnyString& FunnyString::operator -=(const FunnyString &S)
{
	return(*this=*this - S);
}


FunnyString& FunnyString::operator *=(const FunnyString &S)
{
	return(*this=*this * S);
}


istream& operator>>(istream &is, FunnyString &str)
{
	int tmpLength=10;    //the temporary max lenght of the string, and we can double it if the string is out of range
	int i=0, restSpace=tmpLength;    //the rest space of the string can input int
	char *inCode,*tmpCode;           //temporary store the char of code input

	inCode=new char[tmpLength];
	
	while(true)
	{
		is.read(inCode+i,1);    //read a char from the istream to inCode[i]
		
		if(inCode[i]=='\n')
		{
			str.length=i;
			break;   //enter is used as a end of the input
		}

		++i;
		--restSpace;

		if(restSpace==0)    //if the string is out of range, double its length
		{
			tmpCode=new char[tmpLength];
			for(int i=0; i<tmpLength; ++i) tmpCode[i]=inCode[i];
			delete[] inCode;

			inCode=new char[tmpLength*2];   //double the length of the string
			for(int i=0; i<tmpLength; ++i) inCode[i]=tmpCode[i];
			delete[] tmpCode;

			restSpace=tmpLength;
			tmpLength*=2;
		}
	}

	delete[] str.code;
	
	str.code=inCode;
	str.code[str.length]='\0';

	return is;

}


ostream& operator<<(ostream &os, const FunnyString &str)
{
	os<<str.code;
	return os;
}


FunnyString operator+(const FunnyString &str1, const FunnyString &str2)
{
	int end,begin;
	FunnyString sum;

	for(end=str1.length-1, begin=0; str1.code[end]==str2.code[begin] && end>=0 && begin<str2.length; --end,++begin);
//if the end of str1 is equal to the begin of str2 then ignore them

	sum.length=end+str2.length-begin+1;    //get the length of sum
	delete[] sum.code;
	sum.code=new char[sum.length+1];

	for(int i=0; i<=end; ++i) sum.code[i]=str1.code[i];
	for(int i=end+1; i<=sum.length; ++i) sum.code[i]=str2.code[begin+i-end-1];

	return sum;
}


FunnyString operator-(const FunnyString &str1, const FunnyString &str2)
{
	FunnyString tmp,dif;

	delete[] tmp.code;
	tmp.code=new char[str1.length+1];
	tmp.length=0;

	for(int i=0; i<str1.length; ++i)
	{
		bool isInStr2=false;

		for(int j=0; j<str2.length; ++j)
			if(str1.code[i]==str2.code[j])
				isInStr2=true;

		if(!isInStr2)     //if str1[i] is not in str2 then put it to the dif
		{
			tmp.code[tmp.length]=str1.code[i];
			++tmp.length;
		}
	}

	delete[] dif.code;
	dif.length=tmp.length;
	dif.code=new char[dif.length+1];

	for(int i=0; i<dif.length; ++i) dif.code[i]=tmp.code[i];

	dif.code[dif.length]='\0';

	return dif;

}


FunnyString operator*(const FunnyString &str1, const FunnyString &str2)
{
	FunnyString prod;

	delete[] prod.code;
	prod.length=str1.length+str2.length;
	prod.code=new char[prod.length+1];

	for(int i=0,j=0,k=0; k<prod.length; ++i,++j)
	{
		if(i<str1.length)
		{
			prod.code[k]=str1.code[i];
			++k;
		}

		if(j<str2.length)
		{
			prod.code[k]=str2.code[j];
			++k;
		}
	}

	prod.code[prod.length]='\0';

	return prod;
}