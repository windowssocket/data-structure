#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//�����򲻿���Ƕ������!!!

template <class elemType>			//ջ��(����ʵ��)
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

//���Գ���
void main()
{
	check();
	system("pause");
}

//������һ�����ʴ�����ʶ��,�ļ�����󷵻�ֵ0
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

//�����ļ�,���м��
//�ļ���ͷbegin ���� ���߽�βend ����ֱ�ӱ����˳�����
//if ֮��ض�Ҫ���� then
//else ֮ǰ�ض��� then 
//then ֮ǰ�ض��� if
//then �����û��else
void check()
{
	char str[100],text[50];
    ifstream inStream;
	int current,temp,n=0;
	seqStack<int> Stack;
	cout<<"�������ļ���: ";
	cin>>str;
	inStream.open(str);
	if(!inStream.is_open()) 
	{
		cerr<<"�ļ�������\n";
		return;
	}
    //Ѱ�Һ��������
    while((current=getnext(inStream))!=1)
	{
		if(current==2||current==3||current==4||current==5)
		{cout<<"����û����begin��ʼ\n";}
		inStream.close();
		return;
	}
	//û���ҵ�begin
	if(inStream.eof()){
		cerr<<"û�к�����\n";
		inStream.close();
		return;
	}
	//����if֮��ض�Ҫ����then��else֮ǰ�ض���then��then ֮ǰ�ض���if��then�����û��else��ԭ��ʹ�ö�ջ���б�������
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
				Stack.push(current);//����ifֱ�ӽ�ջ
				break;
			}
		case 4: { if((Stack.isEmpty()==1)||(Stack.pop()!=3)) {n++;break;}//����ջΪ�ջ��߳�ջ�Ĳ���if�������1
			else {
				Stack.push(3);
				Stack.push(4);
				break; }//����ǣ��ٰ�if��then������ջ
				}
		case 5: { if((Stack.isEmpty()==1)||((current=Stack.pop())!=4)) {n++; break;}//����ջΪ�ջ��߳�ջ�Ĳ���then�������1
				else {Stack.pop();break;}}//������ٰ�if��ջ
		}
	}
	 if (current!=2){cout<<"��������û����end����\n";return;}//������û��end�����
	 while(!Stack.isEmpty()){
		if(current==4){
			if((current=Stack.pop())!=3)
				n++;
		}
		if((current=Stack.pop())!=4) {n++;break;}
	 }//���������ջ�е�Ԫ���������Ĵ���
     if(inStream>>text){
		 cerr<<"���������ж�������\n";
	     inStream.close();
	     return;
	 }//���������ж�����������
	inStream.close();
	if(n==0) cout<<"�﷨��ȷ!\n";
	else cout<<"�˶δ����д��� "<<n<<"�Դ���\n";
}