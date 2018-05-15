#include<iostream>
#include<cstring>
#include<cstdlib>
#include<string>
using namespace std;
class Book{//ʵ�����࣬������������ţ��Ƿ��ϼܵ���Ϣ 
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
void Book::info() {//չʾ��Ŀ����Ϣ 
	cout<<name<<ends;
	cout<<id<<ends;
	if(onshelf==1)
	cout<<"�ɽ��"<<endl;
	else
	cout<<"�ѽ��"<<endl; 
}
class Bookbase{//�鼮��Դ�������캯��Ϊ���ļ����뵽�ڴ棬������ز���������д���ļ������������� 
	public://��ʵ����Ŀ����ӣ���ѯ�ȹ��� 
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
		cout<<"��ʧ��"<<endl;
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
		cout<<"��ʧ��"<<endl;
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
Book *Bookbase::seekbook(int bookid){//���Һ������ṩ��ŷ���Book���ָ�� 
	for(int i=0;i<number;i++){
		if(book[i].getid()==bookid){
			cout<<"���ҳɹ�"<<endl; 
			return &book[i];
		}
	}
	cout<<"����ʧ��"<<endl;
	return NULL; 
} 
void Bookbase::seekbook(char *namee){//���Һ������ṩ������ʾ�������Ŀ����Ϣ 
	int flag=0;
	for(int i=0;i<number;i++){
		if(strstr(book[i].getname(),namee)!=NULL){
		cout<<book[i].getname()<<endl;
		flag=1;
		}
	}
	if(flag==1)
	cout<<"����Ϊ���в��ҽ��"<<endl;
	else
	cout<<"δ���ҵ������Ŀ"<<endl; 
}
void Bookbase::info(){//��ʾ��Ŀ����Ϣ 
	for(int i=0;i<number;i++){
		book[i].info() ;
	}
}
class Ebook{//���� ������ 
	public:
		char *getname(){
			return name;
		}
		void add(); //����ʱ����һ�����ļ�������Ϊ�鼮���� 
		void reading();
		void show();
	private:
		int tag;//��ǩ��ʾ��״̬ 
		char *name;
}; //��δʵ����ع��� 
class Mamber{//�����࣬��ʵ�ֽ��飬���飬�����Ķ��Ȳ��� 
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
	private://����һ����Ǳ�ʾ�Ƿ���ڴ��û������ߵ���Ϣ�������������Լ������Ŀ 
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
void Mamber::borrow(char *name){//������޸��ļ��е���Ŀ״̬ 
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
	cout<<"����ɹ�"<<endl; 
}
void Mamber::return_(char *name){//������޸��ļ������Ŀ״̬ 
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
	cout<<"�黹�ɹ�"<<endl;
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
void Mamber::reading(char *fname){//�ṩ��Ŀ���ƣ����ļ������Ķ� 
	FILE *fp;
	if((fp=fopen(fname,"r"))==NULL){
		cout<<"δ�ҵ������Ŀ"<<endl;
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
class Mamberbase{//���߹���⣬�������ߵ���Ϣ�����룬�Լ����ĵ���Ϣ��δ��ȫʵ�� 
	public:		 //����ӣ�ɾ������ 
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
/*Mamberbase::Mamberbase() {//���캯�����ļ���Ϣ�����ڴ������ز��� 
	FILE *fp;
	char *ptr;
	int c;
	if((fp=fopen("mamberdata.txt","r+"))==NULL){
		cout<<"��ʧ��"<<endl;
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
		cout<<"��ʧ��"<<endl;
		exit(0); 
	}
	fclose(fp);
	//��δ��ȫʵ�� 
}
void Mamberbase::info() {
	for(int i=0;i<number;i++){
		mamber[i].show() ;
	}
}
//���߹�������������δ��ȫʵ�� 
int main(){
	char b[10]="dafang";
	Mamber a(2017202020,123456,0,b);//����δ��ȫʵ����غ��������������һ������ 
	cout<<"1:����"<<endl;			//��û��ʵ����֤�Ƿ���ڴ��û��ȹ��� 
	cout<<"2:����"<<endl; 
	cout<<"3:�����Ķ�"<<endl;
	cout<<"4:����"<<endl;
	cout<<"5:¼��"<<endl; 
	int x;
	cin>>x;
	if(x==1){
		char bookname[20];
		cout<<"����������"<<endl; 
		getchar();
		gets(bookname);
		a.borrow(bookname); 
	}
	else if(x==2){
		char bookname[20];
		cout<<"����������"<<endl; 
		getchar();
		gets(bookname);
		a.return_(bookname); 
	}
	else if(x==3){
		char bookname[20];
		cout<<"����������"<<endl; 
		getchar();
		gets(bookname);
		a.reading(bookname) ;
	}
	else if(x==4){
		Bookbase y;
		char bookname[20];
		cout<<"����������"<<endl; 
		//getchar();
		gets(bookname);
		//strcat(bookname,".txt");
		y.seekbook(bookname); 
	}
	else if(x==5){
		Bookbase y;
		int id;
		char bookname[20];
		cout<<"����������"<<endl; 
		getchar();
		gets(bookname);
		cout<<"��������"<<endl;
		cin>>id;
		y.addbook(id,bookname,1);
		cout<<"��ӳɹ�"<<endl;  
	}
	return 0;
}
