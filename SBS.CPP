#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<stdlib.h>
#include<string.h>
#include<iomanip.h>
#include<time.h>
///Progressive overflow
#define shopfile "shopper5.txt"
#define indexfile "index5.txt"
#define recsize 60
#define max 100

fstream file,indfile,indfile1,file1;
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

void opener(fstream &sfile, char *fn , int mode)
{
	sfile.open(fn,mode);
	if(!sfile)
	{
		cout<<"Unable to open file \n";
		exit(1);
	}
}

class product
{
	public:
		char key[15],pname[20];
		int price, qty;
		void initial();
		int read();
		void search(int addr, char k[]);
		void display(int addr, char k[]);
		void displayalldata();
		void remove(char key[15]);
}s;

class index
{ public:
		char ikey[15];
		void intl();
		void readi();
}id[20],ind1;

void product::remove(char key[])
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
	file.open(shopfile,ios::in|ios::out);
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
		file.getline(pname,20,'|');
		file.getline(a,10,'|');
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
 getch();
 file.close();
 return;
}
void product::initial()
{
	int i,j;
	file1.open(shopfile,ios::app|ios::nocreate);
	if(!file1)
	{
		   file1.open(shopfile,ios::out);
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

int product ::read()
{
	char a[10], b[5];
	cout<<"Enter product key:";		cin>>key;
	for(int j=0; j<indsize; j++    )
	{
		if(strcmp(id[j].ikey,key)==0)
		{
			cout<<"Key already exists"<<endl;
			getch();
			clrscr();
			return -1;
		}
	}
	cout<<"Enter the Name:";		cin>>pname;
	cout<<"Enter Price:";  		cin>>price;
	strcpy(buffer, key);			strcat(buffer, "|");
	strcat(buffer,pname);			strcat(buffer,"|");
	itoa(price,a,10);
	strcat(buffer,a); 			strcat(buffer,"|");
	return 1;
}

void store(int addr)
{
	char dummy[10];
	int flag=0,i;
	file.open(shopfile,ios::in|ios::out);
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

void product::search(int addr, char k[])
{
	int i;
	char dummy[10],a[10];
	i=addr;
	file.open(shopfile,ios::in|ios::out);
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
			file.getline(pname,20,'|');
			file.getline(a,10,'|');
		       price= atoi(a);
			cout<<"Key="<<key<<"\nName="<<pname<<"\nPrice="<<price;
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

void product::display(int addr, char k[])
{
	int i;
	char dummy[10],a[10];
	i=addr;
	file.open(shopfile,ios::in|ios::out);
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
			file.getline(pname,20,'|');
			file.getline(a,10,'|');
		       price= atoi(a);
			cout<<endl;
			cout<<setw(15)<<key<<setw(20)<<pname<<setw(10)<<price;
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
 }

void index::intl()
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

void index::readi()
{
	opener(indfile,indexfile,ios::out);
	for(int i=0;i<indsize;i++){
	    indfile<<id[i].ikey<<"#";
    }
	indfile.close();
}

void product::displayalldata()
{
	int addr;
	ind1.intl();
	clrscr();
	cout<<"\n Display all items:\n";
	cout<<setw(15)<<"Key"<<setw(20)<<"Pname"<<setw(20)<<"Price"<<endl;
	for(int j=0; j<indsize; j++    )
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

void admin_menu()
{
	int ch,addr;
	char skey[15];
	clrscr();
	cout<<"\nPlease enter your name:\n ";
	char name[20];
	cin>>name;
	cout<<"\nEnter your password: \n";
	char pass[10];
	cin>>pass;
	if(strcmp(pass,"ISE123")==0)
	{
		clrscr();
		cout<<"\n\tWelcome "<<name<<endl;
		getch();
	}
	else
	{
	cout<<"INVALID PASSWORD!!!! \n";
	cout<<"enter 1 to exit, any other to continue";
	int a;
	cin>>a;
	if(a==1)
	exit(0);
	admin_menu();
	}
	clrscr();
	s.initial();
	ind1.intl();
	do
	{
	cout<<"\n";
    cout<<"\t\t ================================================\n";
	cout<<"\t\t|         Administrator Menu             |\n";
	cout<<"\t\t ================================================\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t|\t1. Add an item \t\t\t|\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t|\t2. Search an item \t\t|\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t|\t3. Display all items\t\t|\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t|\t4. Delete an item \t\t|\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t|\t5. Modify an item \t\t|\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\t|\t6.Exit \t\t\t\t|\n";
	cout<<"\t\t-------------------------------------------------\n";
	cout<<"\t\tInput number Associated with Action: ";
	int option;
	cin>>option;
	switch(option)
	{
		case 1:cout<<endl<<"\n Add a new item " <<endl;
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
		case 4: cout<<"Enter key of element to be deleted:";
			cin>>skey;
			s.remove(skey);
			break;
		case 5: cout<<"Enter key of element to be modified:\n";
			cin>>skey;
			s.remove(skey);
			cout<<endl<<"\nEnter modified item\n " <<endl;
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

void staff_menu()
{
	clrscr();
	cout<<"\nDear staff, \nPlease enter your name:\n ";
	char names[20];
		int addr,n=0;
		cin>>names;
		char k1[30][15], name[30][20], a[10];
		int qty[30], price[30];
	ind1.intl();
	clrscr();
	cout<<"\n Product Menu:\n";
	cout<<setw(15)<<"Key"<<setw(20)<<"Pname"<<setw(10)<<"Price"<<endl;
	for(int j=0; j<indsize; j++    )
	{
		addr=hash(id[j].ikey);
		s.display(addr,id[j].ikey);
	}
	getch();
	for(int k=0;;k++)
	{
		cout<<"\n Enter the product key: \n";
		cin>>k1[k];
		cout<<"\nEnter the number of items: \n";
		cin>>qty[k];
		int i;
		file.open(shopfile,ios::in|ios::out);
		if(!file)
		{
			cout<<"File not opened ";
			getch();
		}
		i=hash(k1[k]);
		addr=hash(k1[k]);
		do
		{
			char dummy[10],key[15];
			file.seekg(i*recsize,ios::beg);
			file.getline(dummy,5,'\n');
			if(strcmp(dummy,"####")==0)
				break;
			file.seekg(i*recsize,ios::beg);
			file.getline(key,15,'|');
			if(strcmp(key,k1[k])==0)
			{
				found=1;
				file.getline(name[k],20,'|');
				file.getline(a,10,'|');
					price[k]= atoi(a);
			}
			else
			{
				i++;
				if(i%max==0)
					i=0;
			}
		}while(i!=addr);
		file.close();
		if(found==0)
			cout<<"\nInvalid key\n";
		else
			n++;
		cout<<"Do you want to enter more items? (y/n) \n";
		char ans;
		cin>>ans;
		if(ans=='n')
			break;
		found=0;
	}
	int sale[30],totals=0;
	clrscr();
	cout<<"\n\t\t\t\t INVOICE  \n\n";
	cout<<"--------------------------------------------------------------------------------\n";
	time_t now = time(0);
	tm *ltm = localtime(&now);
	cout<<"Date ";
	cout<<ltm->tm_mday<<"/"<<1+ltm->tm_mon<<"/";
	cout<<1900+ltm->tm_year<<"\n";
	cout<<"Time ";
	cout<<ltm->tm_hour<<":";
	cout<<ltm->tm_min<<":";
	cout<<ltm->tm_sec<<"\n";
	int nt=0;
	cout<<"User: "<<names<<endl;
	cout<<setiosflags(ios::left);
	cout<<"-----------------------------------------------------------------------------\n";
	cout<<setw(15)<<"ProductID"<<setw(20)<<"Item"<<setw(10)<<"Cost"<<setw(10)<<"Quantity"<<setw(10)<<"Amount"<<endl;
	cout<<"-----------------------------------------------------------------------------\n";
	for(int m=0; m<n; m++)
	{
		nt=nt+qty[m];
		sale[m]=price[m]*qty[m];
		totals=totals+sale[m];
		cout<<setw(15)<<k1[m]<<setw(20)<<name[m]<<setw(10)<<price[m]<<setw(10)<<qty[m]<<setw(10)<<sale[m]<<endl;
	}
	cout<<"--------------------------------------------------------------------------------\n";
	cout<<"Net Amount:" <<totals<<endl;
	cout<<"--------------------------------------------------------------------------------\n";
	cout<<"Total quantity:"<<nt<<endl;
	cout<<"Total items:"<<n<<endl;
	cout<<"--------------------------------------------------------------------------------\n";
}

void main()
{
	clrscr();
	cout<<"\n\n\n\n \t\t\t ****************************** "<<endl  ;
	cout<<" \t\t\t WELCOME TO STORE BILLING SYSTEM "<<endl  ;
	cout<<" \t\t\t ****************************** "<<endl  ;
	cout<<"\n\n\t\t\t\t\t\t\t PROJECT BY:\n\t\t\t\t\t\t\t -> Deethya J Reddy \n\t\t\t\t\t\t\t -> Dravyashree M \n";
	cout<<"\n\n\n";
	cout<<"\t *****************\n";
	cout<<"\t Who are you? \n";
	cout<<"\t *****************\n";
	cout<<"\t 1.ADMINISTRATOR \n";
	cout<<"\t *****************\n";
	cout<<"\t 2.BILLING STAFF \n";
	cout<<"\t *****************\n";
	cout<<"\t 3.EXIT \n";
	cout<<"\t *****************\n";
	cout<<"\n\nEnter your choice:";
	int ch;
	cin>>ch;
	switch(ch)
	{
		case 1:
			clrscr();
			admin_menu();
			break;
		case 2:
			clrscr();
			staff_menu();
			break;
		case 3:
			cout<<"Thank you for using our program \n";
			getch();
			exit(0);
			break;
		default: cout<<"\nPlease enter valid choice \n";
			getch();
			clrscr();
			main();
			break;
	 }
	getch();
}
