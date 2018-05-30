#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//�ı��༭����
class text_editor
{
public:
	text_editor();
	~text_editor();
	void open(string str);
	void quit();
	void list(int n1,int n2);
	void del(int row,int col, int);
	void ins(int row,int col, string str);
private:
	string *data;
	int maxSize;
	int CurrentLength;
	void doubleSpace();
	string filename;
	ifstream infile;
	ofstream outfile;
};

//���ֺ�����ʵ��
text_editor::text_editor()
{
	maxSize=100;
	data=new string[maxSize];
	CurrentLength=0;
	filename="";
}

text_editor::~text_editor ()
{
	delete []data;
}

void text_editor::doubleSpace()
{
	string *temp=data;
	maxSize*=2;
	data=new string[maxSize];
	for (int i=0;i<CurrentLength;++i)
		data[i]=temp[i];
	delete []temp;
}

void text_editor::open(string str)
{
	CurrentLength=0;
	filename=str;
	infile.open(filename.c_str());
	string temp;
	while (getline(infile,temp))
	{
		if (CurrentLength==maxSize)
			doubleSpace();
		data[CurrentLength]=temp;
		CurrentLength++;
	}
	infile.close();
}//��ָ���ļ�,���ļ��ж���string���͵�����,���Ҵ���data��

void text_editor::quit()
{
	outfile.open(filename.c_str());
	for (int i=0;i<CurrentLength;++i)
		outfile<<data[i]<<endl;
	outfile.close();
}//��ָ���ļ�,��data��string���͵�����д�ص���ָ�����ļ�,���ر��ļ�

void text_editor::list (int n1,int n2)
{
	for (int i=n1-1;i<n2;++i)
		cout<<data[i]<<endl;
}//���ļ��ж���������д����Ļ��

void text_editor::del (int row,int col,int n)
{
	data[row-1].erase(col-1,n);
}//ͨ���⺯��erase,��ʵ�ִ�ָ��λ��ɾ���ַ��Ĺ���

void text_editor::ins (int row, int col, string str)
{
	data[row-1].insert(col-1,str);
}//ͨ���⺯��insert,��ʵ����ָ��λ�ò����ַ��Ĺ���

//���Գ���
void main()
{
	text_editor edit;
	string str;
	cout<<"�������ļ���: ";
	cin>>str;
	edit.open (str);
	int op;
	
	cout <<"������Ҫ���еĲ���"<<endl;
	cout <<"1 ���� list n1~n2;"<<endl
		 <<"2 ���� del ��,��,�ַ���;"<<endl
		 <<"3 ���� ins ��,��,�ַ���;"<<endl
		 <<"0 ���� quit"<<endl;
	cin>>op;
	while(op!=0)
	{
		switch (op)
		{
		case 0:{ edit.quit (); break; }
		case 1:{ cout<<"�������к�n1 n2: ";
				int n1,n2; cin >> n1 >> n2; 
				edit.list(n1,n2);
				break;
			   }
		case 2:{ cout<<"�������к�,�к�,�ַ���: ";
				int row,col,num; 
				cin>>row>>col>>num;
				edit.del (row,col,num);
				break;
			   }
		case 3:{ cout<<"�������к�,�к�,�ַ���: ";
				int row,col; 
				string str;
				cin>>row>>col;
				cin>>str;	
				edit.ins(row,col,str);
				break;
			   }
		}
		cout <<"������Ҫ���еĲ���"<<endl;
	    cout <<"1 ���� list n1~n2;"<<endl
		 <<"2 ���� del ��,��,�ַ���;"<<endl
		 <<"3 ���� ins ��,��,�ַ���;"<<endl
		 <<"0 ���� quit"<<endl;
	    cin>>op;
	} 
	system("pause");
}