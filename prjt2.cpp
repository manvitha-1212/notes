
#include<iostream>

#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<iomanip>
#include<time.h>
using namespace std;

#define wishfile "wish1.txt"
#define indexfile "index1.txt"
#define recsize 60
#define max 100

fstream file,indfile,indfile1,file1,sfile;


int indsize=0,found=0;
char buffer[80],indy[15];

//Hashing
int hash(char key[])
{
	int i=0,sum=0;
	while(key[i]!='\0')
	{
		sum=sum+key[i]-48;
		i++;
	}
	return sum % max;
}



class wish 
{private : char key[15],goalname[20];
char category[20], targetdate[20],  status[20];
	public:
		void opener(fstream &sfile, char *fn , ios_base::openmode mode);

		void initial();
		int read();
void menu();
		void search(int addr, char k[]);
		void display(int addr, char k[]);
		void displayalldata();
		void remove(char key[]);
}s;

class index
{ public:void opener(fstream &sfile, char *fn , ios_base::openmode mode);
		char ikey[15];
		void intl();
		void readi();
}id[20],ind1;


void wish::opener(fstream &sfile, char *fn ,ios_base::openmode mode )
{
	sfile.open(fn,mode);
	if(!sfile)
	{
		cout<<"Unable to open file \n";
		exit(1);
	}
}


void wish::remove(char key[])
{
	int pos=-1,flag,addr,j;
	char k[20],dummy[150],a[10];
	ind1.intl();
	for(int i=0;i<=indsize;i++)
	{
		if(strcmp(id[i].ikey,key)==0)
		{
			pos=i;
			flag=1;
			break;
		}
	}
	if(flag==1)
	{
	for( i=pos;i<indsize; i++)
		id[i]=id[i+1];
		indsize--;
	ind1.readi();
	}else
	{
		return;
	}
	addr=hash(key);
	i=addr;
	file.open(wishfile,ios::in|ios::out);
 do
 {
	 file.seekg(i*recsize,ios::beg);
	 file.getline(dummy,5,'\n');
	 if(strcmp(dummy,"####")==0)
	 break;
	 file.seekg(i*recsize,ios::beg);
	 file.getline(k,15,'|');
	 if(strcmp(key,k)==0)
	 {
		found=1;
		file.getline(goalname,20,'|');
		//file.getline(a,10,'|');
		file.seekp(i*recsize,ios::beg);
		for(j=0;j<recsize-2;j++)
			file<<"#";
		file<<endl;
		break;
	 }
	 else
	 {
		i++;
		if(i%max==0)
		i=0;
	 }
 } while(i!=addr);
 if(found==0)
cout<<"\n\t\t\tRecord does not exist in hash file\n";

 file.close();
 return;
}

void wish::initial()
{
	int i,j;
	file1.open(wishfile,ios::app);
	if(!file1)
	{
		   file1.open(wishfile,ios::out);
		   if(!file1)
		   {
				cout<<"Unable to open a file\n";
				exit(1);
		   }
		   for(i=0;i<max;i++)
		   {
			  file1.seekp(i*recsize,ios::beg);
			  for(j=0;j<recsize-2;j++)
				  file1<<"#";
			  file1<<endl;
		   }
	}
	 file1.close();
}

int wish ::read()
{
	char a[10], b[5];
	cout<<"enter key  :";	
	cin>>key;
	for(int j=0; j<indsize; j++    )

{
		if(strcmp(id[j].ikey,key)==0)
		{
			cout<<"goal number already exists"<<endl;
			
			return -1;
		}
	}
	cout<<"Enter the goal name:";		
cin>>goalname;
	cout << "\n Enter Category: ";
    cin >> category;
    cout << "\nEnter Target-date(dd-mm-yyyy): ";
    cin >> targetdate;
    cout << "\nEnter Status(Active/Achieve): ";
    cin >> status;
	strcpy(buffer, key);			
strcat(buffer, "|");
	strcat(buffer,goalname);			
strcat(buffer,"|");

strcat(buffer,category);			
strcat(buffer,"|");




strcat(buffer,targetdate);			
strcat(buffer,"|");

strcat(buffer,status);			
strcat(buffer,"|");


strcat(buffer,goalname);			
strcat(buffer,"|");
	//itoa(price,a,10);
	//strcat(buffer,a); 			
//strcat(buffer,"|");
	return 1;
}


void store(int addr)
{
	char dummy[10];
	int flag=0,i;
	file.open(wishfile,ios::in|ios::out);
	file.seekg(addr*recsize,ios::beg);
	file.getline(dummy,5,'\n');
	if(strcmp(dummy,"####")==0)
	{
		 file.seekp(addr*recsize,ios::beg);
		 file<<buffer;
		 flag=1;
	}
	else
	{
		for(i=addr+1; i!=addr; i++)
		{
			if(i%max==0)
				i=0;
			file.seekg(i*recsize,ios::beg);
			file.getline(dummy,5,'\n');
			if(strcmp(dummy,"####")==0)
			{
				cout<<"\n Collision has occurred\n";
				file.seekp(i*recsize,ios::beg);
				file<<buffer;
				flag=1;
				break;
			}
		}
	}
	if(i==addr && (!flag))
			cout<<"Hash File is full, Record cannot be inserted\n";
		file.close();
		return;
}

void wish::search(int addr, char k[])
{
	int i;
	char dummy[10],a[10];
	i=addr;
	file.open(wishfile,ios::in|ios::out);
	do
	{
		file.seekg(i*recsize,ios::beg);
		file.getline(dummy,5,'\n');
		if(strcmp(dummy,"####")==0)
			break;
		file.seekg(i*recsize,ios::beg);
		file.getline(key,15,'|');
		if(strcmp(key,k)==0)
		{
			found=1;
			file.getline(goalname,20,'|');
			//file.getline(a,10,'|');
		       //price= atoi(a);
			cout<<"Key="<<key<<"\nGoal Name="<<goalname<<"\ncategory ="<<category<<"\n Target date =" <<targetdate<<"\nStatus="<<status;
				break;
		}
		else
		{
			i++;
			if(i%max==0)
				i=0;
		}
	}while(i!=addr);
	if(found==0)
		cout<<"\n Record does not exist in hash file\n";
	file.close();
	return;
}

void wish::display(int addr, char k[])
{
	int i;
	char dummy[10],a[10];
	i=addr;
	file.open(wishfile,ios::in|ios::out);
	do
	{
		file.seekg(i*recsize,ios::beg);
		file.getline(dummy,5,'\n');
		if(strcmp(dummy,"####")==0)
			break;
		file.seekg(i*recsize,ios::beg);
		file.getline(key,15,'|');
		if(strcmp(key,k)==0)
		{
			found=1;
			file.getline(goalname,20,'|');
			//file.getline(a,10,'|');
		       //price= atoi(a);
			cout<<endl;
			cout<<setw(15)<<key<<setw(20)<<goalname<<setw (20)<<category<<setw(20)<<targetdate<<setw(20)<<status;
				break;
		}
		else
		{
			i++;
			if(i%max==0)
				i=0;
		}
	}while(i!=addr);
	file.close();
	return;
 }void index::intl()
{
	       indfile1.open(indexfile, ios::in);
		if(!indfile1)
		{
			indsize=0;
			indfile1.open(indexfile,ios::out);
		   if(!indfile1)
		   {
				cout<<"Unable to open a file\n";
				exit(1);
		   }
		}
		for(indsize=0; ;indsize++)
		{
		       indfile1.getline(id[indsize].ikey,15,'#');
			if(indfile1.eof())
				break;
		}
		indfile1.close();
}




void wish::menu()
{
	int ch,addr;
	char skey[15];
	
	
	s.initial();
	ind1.intl();
	do
	{
	cout<<"\n";
    cout<<"\t\t ================================================\n";
	cout<<"\t\t|         Menu             |\n";
	cout<<"\t\t ================================================\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t|\t1. Add a goal\t\t\t|\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t|\t2. Search an goal \t\t|\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t|\t3. Display all goals\t\t|\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t|\t4. Delete an goal \t\t|\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t|\t5. Modify an goal \t\t|\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t|\t6.Exit \t\t\t\t|\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\tInput number Associated with Action: ";
	int option;
	cin>>option;
	switch(option)
	{
		case 1:cout<<endl<<"\n Add a goal " <<endl;
			    int t= s.read();
			    if(t==1)
			    {
				addr=hash(s.key);
				store(addr);
				ind1.intl();
				strcpy(id[indsize].ikey,s.key);
				indsize++;
				ind1.readi();
			    }
			break;
		case 2:cout<<"\n Enter key value:";
				cin>>skey;
				addr=hash(skey);
				s.search(addr,skey);
			break;
		case 3:s.displayalldata();
			break;
		case 4: cout<<"Enter key of goal to be deleted:";
			cin>>skey;
			s.remove(skey);
			break;
		case 5: cout<<"Enter key of goal to be modified:\n";
			cin>>skey;
			s.remove(skey);
			cout<<endl<<"\n goal to be modified\n " <<endl;
			     t= s.read();
			    if(t==1)
			    {
				addr=hash(s.key);
				store(addr);
				ind1.intl();
				strcpy(id[indsize].ikey,s.key);
				cout<<id[indsize].ikey<<endl;
				indsize++;
				ind1.readi();
			    }
			break;
		default:exit(0);
	}
	}while(1) ;
}






void index::readi()
{
	opener(indfile,indexfile,ios::out);
	for(int i=0;i<indsize;i++){
	    indfile<<id[i].ikey<<"#";
    }
	indfile.close();
}

void wish::displayalldata()
{
	int addr;
	ind1.intl();
	
	cout<<"\n Display all goals:\n";
	cout<<setw(15)<<"Key"<<setw(20)<<"goal name"<<setw(20)<<"category "<<setw(20)<<"target date " <<setw(20)<<"status"<<endl;
	for(int j=0; j<indsize; j++)
	{
		addr=hash(id[j].ikey);
		s.display(addr,id[j].ikey);
	}
	do
	{
	int a;
	cout<<"\nPress 1 to exit:";
	cin>>a;
	if(a==1)
	break;
	}while(1);
}


int main()
{
    wish project;
    project.menu();
    return 0;
}  


