#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//本程序不考虑嵌套问题!!!

template <class elemType>			//栈类(线性实现)
class seqStack
{
private:
	elemType *elem;
	int top_p;
	int maxSize;
	void doubleSpace()
	{
		elemType *tmp=elem;
		elem=new elemType[2*maxSize];
		for(int i=0;i<maxSize;i++) 
			elem[i]=tmp[i];
		maxSize*=2;
		delete []tmp;
	}
public:
	seqStack(int initSize=10)
	{
		elem=new elemType[initSize];
		maxSize=initSize;
		top_p = -1;
	}
	~seqStack() {delete []elem;}
	bool isEmpty() const {return top_p==-1;}
	void push(const elemType &x)
	{
		if(top_p==maxSize-1) doubleSpace();
		elem[++top_p]=x;
	}
	elemType pop(){return elem[top_p--];}
	elemType top() const {return elem[top_p];}
};

int getnext(ifstream &inStream);

void check();

//测试程序
void main()
{
	check();
	system("pause");
}

//读入下一个单词串进行识别,文件读完后返回值0
int getnext(ifstream &inStream)
{
	char str[100];
	while(inStream>>str)
	{
		if(strcmp(str,"begin")==0) return 1;
		else if(strcmp(str,"end")==0) return 2;
		else if(strcmp(str,"if")==0) return 3;
		else if(strcmp(str,"then")==0) return 4;
		else if(strcmp(str,"else")==0) return 5;
		else return 6;
	}
	return 0;
}

//读入文件,进行检查
//文件开头begin 或者 或者结尾end 出错，直接报错并退出程序
//if 之后必定要跟随 then
//else 之前必定有 then 
//then 之前必定有 if
//then 后可以没有else
void check()
{
	char str[100],text[50];
    ifstream inStream;
	int current,temp,n=0;
	seqStack<int> Stack;
	cout<<"请输入文件名: ";
	cin>>str;
	inStream.open(str);
	if(!inStream.is_open()) 
	{
		cerr<<"文件不存在\n";
		return;
	}
    //寻找函数体起点
    while((current=getnext(inStream))!=1)
	{
		if(current==2||current==3||current==4||current==5)
		{cout<<"函数没有以begin开始\n";}
		inStream.close();
		return;
	}
	//没有找到begin
	if(inStream.eof()){
		cerr<<"没有函数体\n";
		inStream.close();
		return;
	}
	//根据if之后必定要跟随then，else之前必定有then，then 之前必定有if，then后可以没有else的原则使用堆栈来判别错误个数
     while(((current=getnext(inStream))!=2)&&(current!=0))
	{
		switch(current)
		{
		case 1: {
			       n++;
				   break;
				}
		case 3:
			{
				Stack.push(current);//看到if直接进栈
				break;
			}
		case 4: { if((Stack.isEmpty()==1)||(Stack.pop()!=3)) {n++;break;}//当堆栈为空或者出栈的不是if，错误加1
			else {
				Stack.push(3);
				Stack.push(4);
				break; }//如果是，再把if和then重新入栈
				}
		case 5: { if((Stack.isEmpty()==1)||((current=Stack.pop())!=4)) {n++; break;}//当堆栈为空或者出栈的不是then，错误加1
				else {Stack.pop();break;}}//如果是再把if出栈
		}
	}
	 if (current!=2){cout<<"函数体中没有以end结束\n";return;}//函数体没有end的情况
	 while(!Stack.isEmpty()){
		if(current==4){
			if((current=Stack.pop())!=3)
				n++;
		}
		if((current=Stack.pop())!=4) {n++;break;}
	 }//检查尚留在栈中的元素所产生的错误
     if(inStream>>text){
		 cerr<<"函数体外有多余的语句\n";
	     inStream.close();
	     return;
	 }//函数体外有多余的语句的情况
	inStream.close();
	if(n==0) cout<<"语法正确!\n";
	else cout<<"此段代码中存在 "<<n<<"对错误\n";
}