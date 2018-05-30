#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

static int defaultKey(const int &k) {return k;}

//��ϣ�����
template <class Type>
class hashTable
{
public:
	virtual bool find(const Type &x) const=0;
	virtual bool insert(const Type &x) =0;
	virtual bool remove(const Type &x) =0;
};

//��ɢ�б�������
template <class Type>
class closeHashTable:public hashTable<Type>
{
private:
	struct node//���
	{
		Type data;
		int state;
		node() {state=0;}
	};
	node *array;//���鵥Ԫ
	int size,num,deleted,limit;//���� ��ЧԪ�ظ��� ��ɾ��Ԫ�ظ��� �û�ָ���ı�ɾ��Ԫ�ص�������
	void doublespace()//�����ռ�
	{
		size=size*2;
		node *tmp=array;
		array=new node[size];
		num=0; deleted=0;
		for (int i=0; i<(size/2); i++)
		{
			if (tmp[i].state==1) insert(tmp[i].data);
		}
		delete [] tmp;
	}
public:
	closeHashTable(int length=101, int lim=1, int (*f)(const Type &x)=defaultKey);//���캯��
	~closeHashTable(){delete [] array;}//��������
	bool find(const Type &x) const;//����
	bool insert(const Type &x);//����
	bool remove(const Type &x);//ɾ��
	void rehash();//����ɢ��
protected:
	int (* key)(const Type &x);
};

//����������ʵ��
template <class Type>
closeHashTable<Type>::closeHashTable(int length, int lim , int (* f)(const Type &x))
{
	size=length;
	limit=lim;
	num=0;
	deleted=0;
	array=new node[size];
	key=f;
}

//���뺯��ʵ��
template <class Type>
bool closeHashTable<Type>::insert(const Type &x)
{
	int initPos,pos;
	initPos=pos=key(x) % size;
	do
	{
		if (array[pos].state!=1)
		{
			array[pos].data=x;
			array[pos].state=1;
			num++;										//��¼��ЧԪ�ظ���,���ж��Ƿ�ﵽ������һ��,���ﵽ����������
			if (num>=(size/2)) doublespace();
			return true;
		}
		if (array[pos].state==1 && array[pos].data==x)
			return true;
		pos=(pos+1) % size;
	}while (pos!=initPos);
	return false;
}

//ɾ��������ʵ��
template <class Type>
bool closeHashTable<Type>::remove(const Type &x)
{
	int initPos,pos;
	initPos=pos=key(x) % size;
	do
	{
		if (array[pos].state==0) return false;
		if (array[pos].state==1 && array[pos].data==x)
		{
			array[pos].state=2;
			num--;										//��ɾ���ɹ�,����ЧԪ�ؼ���һ��
			deleted++;									//��ɾ��Ԫ������һ��
			if (deleted>=limit) rehash();			//����ɾԪ�ض���������һ��,������ɢ��
			return true;
		}
		pos=(pos+1) % size;
	}while (pos!=initPos);
	return false;
}

//���Һ�����ʵ��
template <class Type>
bool closeHashTable<Type>::find(const Type &x) const
{
	int initPos,pos;
	initPos=pos=key(x) % size;
	do
	{
		if (array[pos].state==0) return false;
		if (array[pos].state==1 && array[pos].data==x) return true;
		pos=(pos+1) % size;
	}while (pos!=initPos);
	return false;
}

//����ɢ�к���
template <class Type>
void closeHashTable<Type>::rehash()
{
	node *tmp=array;
	array=new node[size];
	for (int i=0; i<size; i++)
	{
		if (tmp[i].state==1) insert(tmp[i].data);
	}
	deleted=0;					//����ɢ�к�,��ɾԪ��(���Ϊ2��Ԫ��)����Ϊ0
	delete [] tmp;
}

class matrix{
    public:
        matrix(int r,int c,int d):row(r),column(c),data(d){}
        matrix(){}
        bool operator==(const matrix &d)
        {
            if(row==d.row&&column==d.column) return true;
            else return false;
        }
        int row,column,data;
};

static int getkey(const matrix& a)
{
    return a.row*100+a.column;
}

int main()
{
    closeHashTable< matrix >hashlist(131,5,getkey);
    int r,d,count,i,j;
    double k;
    count=0;
    srand(time(NULL));
    for(i=0;i<100;i++)
    {
        for(j=0;j<100;j++)
        {
            r=rand()*100/(RAND_MAX+1);     //���ɷ���ĸ���
            if(r!=0) continue;             //��Ӧ��Ԫ��ֵΪ��
            d=rand()*1000/(RAND_MAX+1)+1;   //���ɾ���Ԫ��ֵ
            matrix b(i,j,d);
            hashlist.insert(b);
            ++count;
        }
    }
    k=(double)count/10000.0*100.0;
    cout<<"10000��Ԫ������"<<count<<"������Ԫ��"<<"ռ"<<k<<"%"<<endl;
}

