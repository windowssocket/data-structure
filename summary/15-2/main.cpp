#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

template <class T>
class jumplist
{
    struct node    //�����еĽ������
    {
        T data;
        int type;
        node** next;
        node() {}
        node (int t)
        {
            type=t;
            next=new node*[t+1];
            for(int i=0; i<=t; ++i) next[i]=NULL;
        }
        node(T x,int t)
        {
            data=x;
            type=t;
            next=new node*[t+1];
            for(int i=0; i<=t; ++i) next[i]=NULL;
        }
    };
    node* head;//ָ��ͷ����ָ��
    int size;//��

public:
    jumplist()
    {
        head=new node(0);
        size=0;
        srand(time(NULL));
    }
    ~jumplist();
    void insert(T x);
    void remove(T x);
    bool find(T x);
    void show();
};

template <class T>
jumplist <T>::~jumplist()
{
    node *p=head,*q;
    while(p!=NULL)   //�ͷ�ÿ�����
    {
        q=p;
        p=p->next[0];
        delete [] q->next; //�ͷŽڵ��е�ָ������
        delete q;
    }
}

template <class T>
bool jumplist<T>::find(T x)
{
    node *p;
    p=head;
    for(int i=head->type; i>=0; --i) //����߲�����ʼ����
    {
        while(p->next[i]&&p->next[i]->data<x) //���ҵ�i����
            p=p->next[i];
        if(p->next[i]&&p->next[i]->data==x) return true;//�ҵ�
    }
    return false;
}

template <class T>
void jumplist<T>::remove(T x)
{
    int i;
    node *p,**last=new node*[head->type];
    p=head;
    for(i=head->type; i>=0; --i) //�ҵ���ɾ��������ǰ��
    {
        while(p->next[i]&&p->next[i]->data<x) p=p->next[i];
        last[i]=p;
    }
    if(p->next[0]==NULL||p->next[0]->data>x) return;
    p=p->next[0];
    --size;
    for(i=p->type; i>=0; --i) //����ɾ�ڵ����������ɾȥ
    {
        if(last[i]->next[i]==p)last[i]->next[i]=p->next[i];
    }
    delete [] p->next;
    delete p;
}

template <class T>
void jumplist<T>::insert(T x)
{
    int level,randnum,i;
    node *p,*newp,**last; //last�ǲ���������ǰһ���
    node *oldhead;
    last=new node*[head->type];
    p=head;
    for(i=head->type; i>=0; --i) //�ҵ������������ǰ��
    {
        while(p->next[i]&&p->next[i]->data<x) p=p->next[i];
        if(p->next[i]&&p->next[i]->data==x) return;
        last[i]=p;
    }
        //���ɲ����������
        ++size;
        level=0;
        randnum=rand()*size/(RAND_MAX+1);
        while(randnum>1)
        {
            ++level;
            randnum/=2;
        }
        newp=new node(x,level);
        if(level>head->type) //����Ĳ��������,��Ҫ�޸�ͷ���
        {
            oldhead=head;
            head=new node(level);
            while(level>oldhead->type) head->next[level--]=newp;
            level=oldhead->type;
            for(i=0; i<=level; ++i) head->next[i]=oldhead->next[i];
            for(i=0; i<=level; ++i) if(last[i]==oldhead) last[i]=head;
            delete oldhead;
        }
        for(i=level; i>=0; --i) //��������������
        {
            newp->next[i]=last[i]->next[i];
            last[i]->next[i]=newp;
        }
}

template <class T>
void jumplist<T>::show()
{
    node *p;
    p=head;
    cout<<"��������Ԫ��:";
    while(p->next[0]) //���ҵ�0����
    {
        cout<<p->next[0]->data<<" ";
        p=p->next[0];
    }
	cout<<endl;
}


int main()
{
    jumplist<int> a;
    a.insert(2);
    a.insert(8);
    a.insert(11);
    a.insert(13);
    a.insert(19);
    a.insert(25);
    a.show();
    a.remove(13);
    a.show();
}
