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

	BnlTree *root;   //保存根结点
	int length;      //根结点最大数目
	int nodeSize;    //结点数目

	void doubleSpace();
	void clearTree(Node* t);   //析构树
	void clearQueue(){clear(); delete[] root;}  //析构队列

public:
	bernoulli_queue():length(1),nodeSize(0){root=new BnlTree[1];root[0]=NULL;} //构造一个空队列
	bernoulli_queue(Type x):length(1),nodeSize(1){root=new BnlTree[1];root[0]=new Node(x);}
	bernoulli_queue(const bernoulli_queue &);
	~bernoulli_queue(){ clearQueue();}
	
	void clear();  //清空整个队列
	bool empty() const{return nodeSize==0;} //判断队列是否为空
	int size() const{return nodeSize;} //输出队列中的结点数
	const Type& top() const; //返回队列首元素值
	void pop(); //弹出队列首元素
	void push(const Type&); //将元素插入队列
	
	bernoulli_queue operator +(const bernoulli_queue &) const; //归并两个Bernoulli队列，也可以写作友元，写作友元函数时请注意声明方式
	bernoulli_queue& operator =(const bernoulli_queue &); //重载拷贝赋值

private:
	//拷贝一个贝努里树
	Node* copyTree(const Node* t)const{
		Node *r=NULL;
		if(t!=NULL){
			r=new Node(t->data);
			r->son=copyTree(t->son);
			r->brother=copyTree(t->brother);
		}
		return r;
	}
	
	//按优先级连接两颗贝努里树
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