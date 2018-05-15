#include<iostream>
#include<cstring>
#include<cstdlib>
#include<string>
using namespace std;
class Book{//实体书类，包括书名，编号，是否上架等信息 
	public:
		char *getname(){
			return name;
		}
		int getid(){
			return id;
		}
		int isonshelf(){
			return onshelf;
		}
		void setname(char *namee){
			strcpy(name,namee);
		}
		void setid(int idd){
			id=idd;
		}
		void setonshelf(int a){
			onshelf=a;
		}
		void info();
		int borrowbook();
		void returnbook();
	private:
		int id;
		char name[10];
		int onshelf;
};
void Book::info() {//展示书目的信息 
	cout<<name<<ends;
	cout<<id<<ends;
	if(onshelf==1)
	cout<<"可借出"<<endl;
	else
	cout<<"已借出"<<endl; 
}
class Bookbase{//书籍资源管理，构造函数为把文件读入到内存，进行相关操作后重新写入文件（析构函数） 
	public://可实现书目的添加，查询等功能 
		Bookbase();
		~Bookbase();
		void addbook(int idd,char *namee,int isonshelf);
		Book *seekbook(int bookid);
		void seekbook(char *namee);
		void info();
		int getnumber(){
			return number;
		}
	private:
		int number;
		Book book[100];
}; 
Bookbase::Bookbase() {
	FILE *fp;
	char str[20],bookname[10],str2[10];
	int len;
	char x;
	if((fp=fopen("bookdata.txt","r+"))==NULL){
		cout<<"打开失败"<<endl;
		exit(0); 
	}
	for(int i=0; ;i++){
	fgets(str,20,fp);
	sscanf(str,"%[^,]",bookname);
	sscanf(strchr(str,',')+1,"%[^,]",str2);
	len=strlen(str);
	x=str[len-2];
	book[i].setname(bookname);
	book[i].setid(atoi(str2));
	book[i].setonshelf(x-'0');
	if(feof(fp)){
		number=i+1;
		break;
		}
	}
	fclose(fp);
}
Bookbase::~Bookbase() {
	FILE *fp;
	if((fp=fopen("bookdata.txt","w"))==NULL){
		cout<<"打开失败"<<endl;
		exit(0); 
	}
	for(int i=0;i<number;i++){
		fprintf(fp,"%s,%d,%d\n",book[i].getname(),book[i].getid(),book[i].isonshelf());
	}
	fclose(fp);
}
void Bookbase::addbook(int idd,char *namee,int isonshelf) {
	number++;
	book[number-1].setid(idd);
	book[number-1].setname(namee);
	book[number-1].setonshelf(isonshelf);   
}
Book *Bookbase::seekbook(int bookid){//查找函数，提供编号返回Book类的指针 
	for(int i=0;i<number;i++){
		if(book[i].getid()==bookid){
			cout<<"查找成功"<<endl; 
			return &book[i];
		}
	}
	cout<<"查找失败"<<endl;
	return NULL; 
} 
void Bookbase::seekbook(char *namee){//查找函数，提供书名显示出相关书目的信息 
	int flag=0;
	for(int i=0;i<number;i++){
		if(strstr(book[i].getname(),namee)!=NULL){
		cout<<book[i].getname()<<endl;
		flag=1;
		}
	}
	if(flag==1)
	cout<<"以上为所有查找结果"<<endl;
	else
	cout<<"未查找到相关书目"<<endl; 
}
void Bookbase::info(){//显示书目的信息 
	for(int i=0;i<number;i++){
		book[i].info() ;
	}
}
class Ebook{//电子 论文类 
	public:
		char *getname(){
			return name;
		}
		void add(); //增加时创造一个新文件，内容为书籍内容 
		void reading();
		void show();
	private:
		int tag;//标签表示其状态 
		char *name;
}; //暂未实现相关功能 
class Mamber{//读者类，可实现借书，还书，在线阅读等操作 
	public:
		Mamber(int id,int password,int count,char *na);
		int getid(){
			return id;
		}
		char *getname(){
			return name;
		}
		void borrow(char *name);
		void return_(char *name);
		char* seek(char*name);
		void changepassword();
		void reading(char *a);
		void setmamber(int idd,int word,int countt,char *namee,char*na);
		void show();
	private://设置一个标记表示是否存在此用户，读者的信息，借阅数量，以及借的书目 
		int tag; 
		int id,password,count;	
		char name[10];
		char books[20];
};
void Mamber::setmamber(int idd,int word,int countt,char *namee,char *na){
	id=idd;
	password=word;
	count=countt;
	strcpy(name,namee);
	strcpy(books,na);
} 
void Mamber::show() {
	cout<<name<<ends<<id<<endl;
	cout<<count<<ends<<books<<endl;
}
void Mamber::borrow(char *name){//借书后修改文件中的书目状态 
	int word;
	cout<<"Please input your password."<<endl;
	cin>>word;
	if(word!=password){
		cout<<"The password is wrong."<<endl;
	}
	else{
	count++;
	}
	FILE *fp;
	if((fp=fopen("bookdata.txt","r+"))==NULL){
		cout<<"there is sth. wrong."<<endl;
		exit(0);
	}
	rewind (fp);
	char str[50],bookname[20];
	for(int i=0; ;i++){
	fgets(str,50,fp);
	sscanf(str,"%[^,]",bookname);
	if(strcmp(bookname,name)==0){
		fseek(fp,-3L,1);
		fputc('0',fp);
		break;
		}
	}
	fclose(fp);
	cout<<"借书成功"<<endl; 
}
void Mamber::return_(char *name){//还书后修改文件里的书目状态 
	count--;
	FILE *fp;
	if((fp=fopen("bookdata.txt","r+"))==NULL){
		cout<<"there is sth. wrong."<<endl;
		exit(0);
	} 
	rewind (fp);
	char str[50],bookid[20];
	for(int i=0; ;i++){
	fgets(str,50,fp);
	sscanf(str,"%[^,]",bookid);
	if(strcmp(bookid,name)==0){
		fseek(fp,-3L,1);
		fputc('1',fp);
		break;
		}
	}
	fclose(fp);
	cout<<"归还成功"<<endl;
}
void Mamber::changepassword() {
	int word,newword;
	cout<<"Please input your password"<<endl;
	cin>>word;
	if(word==password){
		cout<<"input your new password"<<endl;
		cin>>newword;
		password=newword;
	}
	else
	cout<<"The password is wrong."<<endl;
}
void Mamber::reading(char *fname){//提供书目名称，打开文件在线阅读 
	FILE *fp;
	if((fp=fopen(fname,"r"))==NULL){
		cout<<"未找到相关书目"<<endl;
		exit(0); 
	}
	char x;
	while((x=fgetc(fp))!=EOF){
		cout<<x;
	}
} 
Mamber::Mamber(int idd,int word,int countt,char *na){
	id=idd;
	password=word;
	count=countt;
	strcpy(name,na);
} 
class Mamberbase{//读者管理库，包含读者的信息，密码，以及借阅的信息，未完全实现 
	public:		 //可添加，删除读者 
		Mamberbase();
		~Mamberbase();
		void addmamber(int idd,int word,int countt,char *namee);
		void deletemamber(int idd);
		void info();
		int getnumber(){
			return number;
		}
	private:
		int number;
		Mamber mamber[100];	
};
/*Mamberbase::Mamberbase() {//构造函数把文件信息读入内存进行相关操作 
	FILE *fp;
	char *ptr;
	int c;
	if((fp=fopen("mamberdata.txt","r+"))==NULL){
		cout<<"打开失败"<<endl;
		exit(0); 
	}
	char str[50],mname[10],mid[10],mword[10],bookname[20];
	for(int i=0; ;i++){
		fgets(str,50,fp);
		sscanf(str,"[^,]",mname);
		ptr=strchr(str,',')+1;
		sscanf(ptr,"[^,]",mid);
		ptr+=strlen(mid)+1;
		sscanf(ptr,"[^,]",mword);
		ptr+=strlen(mword)+1;
		c=*ptr-'0';
		strcpy(bookname,ptr+2);
		mamber[i].setmamber(atoi(mid),atoi(mword),c,mname,bookname) ;
		if(feof(fp)){
			number=i;
			break;
		}
	}
	fclose(fp);
}*/ 
Mamberbase::~Mamberbase() {
	FILE *fp;
	if((fp=fopen("mamberdata.txt","r+"))==NULL){
		cout<<"打开失败"<<endl;
		exit(0); 
	}
	fclose(fp);
	//暂未完全实现 
}
void Mamberbase::info() {
	for(int i=0;i<number;i++){
		mamber[i].show() ;
	}
}
//读者管理类其他函数未完全实现 
int main(){
	char b[10]="dafang";
	Mamber a(2017202020,123456,0,b);//由于未完全实现相关函数，这里仅声明一个对象 
	cout<<"1:借书"<<endl;			//并没有实现验证是否存在此用户等功能 
	cout<<"2:还书"<<endl; 
	cout<<"3:在线阅读"<<endl;
	cout<<"4:查找"<<endl;
	cout<<"5:录入"<<endl; 
	int x;
	cin>>x;
	if(x==1){
		char bookname[20];
		cout<<"请输入书名"<<endl; 
		getchar();
		gets(bookname);
		a.borrow(bookname); 
	}
	else if(x==2){
		char bookname[20];
		cout<<"请输入书名"<<endl; 
		getchar();
		gets(bookname);
		a.return_(bookname); 
	}
	else if(x==3){
		char bookname[20];
		cout<<"请输入书名"<<endl; 
		getchar();
		gets(bookname);
		a.reading(bookname) ;
	}
	else if(x==4){
		Bookbase y;
		char bookname[20];
		cout<<"请输入书名"<<endl; 
		//getchar();
		gets(bookname);
		//strcat(bookname,".txt");
		y.seekbook(bookname); 
	}
	else if(x==5){
		Bookbase y;
		int id;
		char bookname[20];
		cout<<"请输入书名"<<endl; 
		getchar();
		gets(bookname);
		cout<<"请输入编号"<<endl;
		cin>>id;
		y.addbook(id,bookname,1);
		cout<<"添加成功"<<endl;  
	}
	return 0;
}
