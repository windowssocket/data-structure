#ifndef _bernoulli_queue_h_
#define _bernoulli_queue_h_

#include<iostream>
using namespace std;

template <class Type>
class bernoulli_queue{
private:
	struct Node{
		Node* son,*brother;  //left-child is son while right-child is brother 
		Type data;

		Node():son(NULL),brother(NULL){}
		Node(Type item, Node* S=NULL, Node* B=NULL):data(item),son(S),brother(B){}
		~Node(){}
	};

	typedef Node* BnlTree;

	BnlTree *root;   //��������
	int length;      //����������Ŀ
	int nodeSize;    //�����Ŀ

	void doubleSpace();
	void clearTree(Node* t);   //������
	void clearQueue(){clear(); delete[] root;}  //��������

public:
	bernoulli_queue():length(1),nodeSize(0){root=new BnlTree[1];root[0]=NULL;} //����һ���ն���
	bernoulli_queue(Type x):length(1),nodeSize(1){root=new BnlTree[1];root[0]=new Node(x);}
	bernoulli_queue(const bernoulli_queue &);
	~bernoulli_queue(){ clearQueue();}
	
	void clear();  //�����������
	bool empty() const{return nodeSize==0;} //�ж϶����Ƿ�Ϊ��
	int size() const{return nodeSize;} //��������еĽ����
	const Type& top() const; //���ض�����Ԫ��ֵ
	void pop(); //����������Ԫ��
	void push(const Type&); //��Ԫ�ز������
	
	bernoulli_queue operator +(const bernoulli_queue &) const; //�鲢����Bernoulli���У�Ҳ����д����Ԫ��д����Ԫ����ʱ��ע��������ʽ
	bernoulli_queue& operator =(const bernoulli_queue &); //���ؿ�����ֵ

private:
	//����һ����Ŭ����
	Node* copyTree(const Node* t)const{
		Node *r=NULL;
		if(t!=NULL){
			r=new Node(t->data);
			r->son=copyTree(t->son);
			r->brother=copyTree(t->brother);
		}
		return r;
	}
	
	//�����ȼ��������ű�Ŭ����
	Node* linkTree(Node* r, Node* t)const{
		Node *p;
		if(r->son==NULL){
			if(r->data>t->data) {t->son=r; return t;}
			else {r->son=t; return r;}
		}

		if(r->data<=t->data){
			for(p=r->son; p->brother!=NULL; p=p->brother);
			p->brother=t;
			return r;
		}
		else{
			for(p=t->son; p->brother!=NULL; p=p->brother);
			p->brother=r;
			return t;
		}
	}
};

#endif