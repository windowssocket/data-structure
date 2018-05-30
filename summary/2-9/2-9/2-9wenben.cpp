#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//文本编辑器类
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

//各种函数的实现
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
}//打开指定文件,从文件中读入string类型的数据,并且存入data中

void text_editor::quit()
{
	outfile.open(filename.c_str());
	for (int i=0;i<CurrentLength;++i)
		outfile<<data[i]<<endl;
	outfile.close();
}//打开指定文件,把data中string类型的数据写回到所指定的文件,最后关闭文件

void text_editor::list (int n1,int n2)
{
	for (int i=n1-1;i<n2;++i)
		cout<<data[i]<<endl;
}//从文件中读出的数据写到屏幕上

void text_editor::del (int row,int col,int n)
{
	data[row-1].erase(col-1,n);
}//通过库函数erase,简单实现从指定位置删除字符的功能

void text_editor::ins (int row, int col, string str)
{
	data[row-1].insert(col-1,str);
}//通过库函数insert,简单实现在指定位置插入字符的功能

//测试程序
void main()
{
	text_editor edit;
	string str;
	cout<<"请输入文件名: ";
	cin>>str;
	edit.open (str);
	int op;
	
	cout <<"请输入要进行的操作"<<endl;
	cout <<"1 代表 list n1~n2;"<<endl
		 <<"2 代表 del 行,列,字符数;"<<endl
		 <<"3 代表 ins 行,列,字符串;"<<endl
		 <<"0 代表 quit"<<endl;
	cin>>op;
	while(op!=0)
	{
		switch (op)
		{
		case 0:{ edit.quit (); break; }
		case 1:{ cout<<"请输入行号n1 n2: ";
				int n1,n2; cin >> n1 >> n2; 
				edit.list(n1,n2);
				break;
			   }
		case 2:{ cout<<"请输入行号,列号,字符数: ";
				int row,col,num; 
				cin>>row>>col>>num;
				edit.del (row,col,num);
				break;
			   }
		case 3:{ cout<<"请输入行号,列号,字符串: ";
				int row,col; 
				string str;
				cin>>row>>col;
				cin>>str;	
				edit.ins(row,col,str);
				break;
			   }
		}
		cout <<"请输入要进行的操作"<<endl;
	    cout <<"1 代表 list n1~n2;"<<endl
		 <<"2 代表 del 行,列,字符数;"<<endl
		 <<"3 代表 ins 行,列,字符串;"<<endl
		 <<"0 代表 quit"<<endl;
	    cin>>op;
	} 
	system("pause");
}