#include"Set.h"

template<class Type>
Set<Type>::Set(const Set<Type> &S)
{
	if(this==&S) return;  //avoid copy itself
	else{
		elem=new Type[S.maxSize];
		for(int i=0; i<S.length; ++i) elem[i]=S.elem[i];
		maxSize=S.maxSize;
		length=S.length;
	}
}

template<class Type>
Set<Type> Set<Type>::operator+(const Set<Type> &s)const
{
	Set sum;  //save the union of the sets
	delete[] sum.elem;
	sum.maxSize=maxSize+s.maxSize;   //the possible max length of the sum
	sum.elem=new Type[sum.maxSize];

	//mnerge two sets to the sum, the same elems only cal once
	int i=0,j=0;
	while(i<length && j<s.length){
		if(elem[i]<s.elem[j]) sum.elem[sum.length++]=elem[i++];
		else if(elem[i]>s.elem[j]) sum.elem[sum.length++]=s.elem[j++];
		else ++j;
	}
	if(i==length) for( ;j<s.length; ++j) sum.elem[sum.length++]=s.elem[j];
	else if(j==s.length) for( ;i<length; ++i) sum.elem[sum.length++]=elem[i];

	return sum;
}

template<class Type>
Set<Type> Set<Type>::operator*(const Set<Type> &s)const
{
	Set ins;  //save the intersection of the sets
	delete[] ins.elem;
	ins.maxSize=(maxSize<s.maxSize)?maxSize:s.maxSize;   //the possible max length of the ins is the min size of the two sets
	ins.elem=new Type[ins.maxSize];

	int i=0,j=0;
	//mnerge two sets to the sum, only cal the samelems
	while(i<length && j<s.length){
		if(elem[i]<s.elem[j]) ++i;
		else if(elem[i]>s.elem[j]) ++j;
		else ins.elem[ins.length++]=elem[j++,i++];
	}

	return ins;
}

template<class Type>
Set<Type> Set<Type>::operator-(const Set<Type> &s)const
{
	Set dif;   //save the difference of the sets
	delete[] dif.elem;
	dif.maxSize=maxSize;
	dif.elem=new Type[dif.maxSize];  //the possible max length of the dif is the this->set maxSize

	int i=0,j=0;
	//mnerge two sets to the sum, cal the elems in this->set but not in s 
	while(i<length && j<s.length){
		if(elem[i]<s.elem[j]) dif.elem[dif.length++]=elem[i++];
		else if(elem[i]>s.elem[j]) ++j;
		else ++i,++j;
	}
	if(j==s.length) for( ;i<length; ++i) dif.elem[dif.length++]=elem[i];

	return dif;
}

template<class Type>
Set<Type>& Set<Type>::operator=(const Set<Type> &S)
{
	if(this==&S) return *this;  //avoid copy itself
	else{
		delete[] elem;
		elem=new Type[S.maxSize];
		for(int i=0; i<S.length; ++i) elem[i]=S.elem[i];
		maxSize=S.maxSize;
		length=S.length;
		return *this;
	}
}

template<class Type>
void Set<Type>::Input()
{
	int n;
	cout<<"请输入集合大小：";
	cin>>n;
	cout<<"请输入集合元素：";
	while(length<n){
		Type x;
		cin>>x;
		Set tmp(x);
		*this=*this+tmp;
	}
}

template<class Type>
void Set<Type>::Output()const
{
	if(length==0) cout<<"empty"<<endl;
	else{
		for(int i=0; i<length; ++i) cout<<elem[i]<<' ';
		cout<<endl;
	}
}