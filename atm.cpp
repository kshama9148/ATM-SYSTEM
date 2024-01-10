#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include <cstdlib> 
#include <ctime>
using namespace std;
class atm{
	public:
		string fname,lname,buffer,buffer1,buffer2,buffer3,acntno,pinno,amnt,date;
		string dob,phone,add;
		int amt;
		atm *link;
		int  acnt;
		int pin;
		int address_list[100];
		string acnt_list[100];
		int count;
		atm(){
			count=-1;
		}
		 //static int pin=pins;
		void new_user();
		int search_index(string key);
		int existing_user();
		void search_withdraw(string act);
		void pack();
		string extract_acnt();
		void create_index();
		void sort_index();
		string unpack();
		void write_to_file();
		void write_to_file_again();
		int delete_old_entry_of_acount(string act);
		int delete_old_entry_of_transaction(string act_no);
		void write_to_transaction();
		void pack_again_trans(string act,string pin,string time,string amt);
		void random();
		void search_deposit(string);
		string unpack_pin(string buffer);
		string unpack_amnt(string buffer3);
		void unpack_all_acnt_no(string);
		void pack_again_acount(string,string,string,string);
		void pack_again_trans(string,string,string );
		void unpack_acnt_no();
		int hash(string);
		int balance_enquiry(string);
		void search();
		void hash_insert(string,string,string,int);
		void unpack_balance();
		int delete_old_trans(string);
		void write_to_transfile_again();
		int search(string);
		void display_hash();
		void disp();
		int delete_old_user(string);
		void search_balance(string);
		string compress(string);
		void search_user(string);
		string string_strdate_alternative();
		void hash_insert_stat(string,string,string,int);
		void unpack_pin_stat();
		void  mini_stat(string);
		void display_hash_stat();
                string unpack_date(string);
                void search_date(string);
		
};
atm *h[29];
  void atm::random(){
	srand(time(0)); 
    pin = rand()%100000; 
    acnt=rand()%100000;
    cout<<"\n $ ------------------------------------- $\n";
	cout<<"\n YOUR GENERTAED ACCOUNT NUMBER IS "<<acnt;
	cout<<"\n YOUR GENERATED PIN NUMBER IS "<<pin<<endl;
	cout<<"\n $ ------------------------------------- $\n";	
  }
  string atm ::string_strdate_alternative()
{
 char cptime[50];
 time_t now = time(NULL);
 strftime(cptime, 50, "%b-%d-%Y", localtime(&now)); //short month name
 return std::string(cptime);
}
  void atm::new_user(){
	
	cout<<"PLEASE ENTER YOUR FIRST NAME:";
	cin>>fname;
	cout<<"PLEASE ENTER YOUR LAST NAME:";
	cin>>lname;
	cout<<"PLEASE ENTER YOUR DATE-OF-BIRTH IN THE FORMAT DD/MM/YY:";
	cin>>dob;
	cout<<"PLEASE ENTER YOR PHONE NUMBER:";
	cin>>phone;
	cout<<"ENTER YOUR CITY NAME: ";
	cin>>add;
	cout<<"PLEASE ENTER INITIAL DEPOSIT AMOUNT:";
	cin>>amt;
	//cout<<"YOUR CARD REQUIRES TIME FOR ACTIVATION .....\n \nPLEASE REVISIT ATM AFTER SOME TIME\n \n \t THANKYOU....\n \n";
	
}

  void atm::pack(){
	//for string conversion
	ostringstream str1;
	str1 << pin;
	ostringstream str2;
	str2 << amt;
	ostringstream str3;
	str3 << acnt;
	string pin_no = str1.str();
	string total_amt = str2.str();
	string acnt_no = str3.str();
	int amnt;
	//string address=tolower(add);
	//string comp=compress(add);
		//char date[9];
	//_strdate(date);
	string date=string_strdate_alternative();
	buffer.erase();
	buffer=fname+'|'+lname+'|'+dob+'|'+phone+'|'+add+'$'+'\n';
	buffer1.erase();
	buffer1=acnt_no+'|'+pin_no+'|'+total_amt+'|'+date+'$'+'\n';
	buffer2.erase();
	buffer2=acnt_no+'|'+date+'|'+total_amt+'$'+'\n';
	
	
  }
  
     

  void atm::write_to_file(){
	int pos;
	ostringstream str3;
	str3 << acnt;
	string acnt_no = str3.str();
	fstream file;
	file.open("user.txt",ios::out|ios::app);
	file<<buffer;
	file.close();
	file.open("acount.txt",ios::out|ios::app);
	file<<buffer1;
	file.close();
	
	acnt_list[++count]=acnt_no;
	address_list[count]=pos;
	//sort_index();
    file.open("transaction.txt",ios::out|ios::app);
	file<<buffer2;
	file.close();
	create_index();
  }

  string atm::extract_acnt(){
	string acnt;
	int i=0;
	acnt.erase();
	while(buffer[i]!='|')
	acnt+=buffer[i++];
	return acnt;
  }

  void atm::create_index(){
	fstream file;
	int pos;
	string acnt;
	count=-1;
	file.open("acount.txt",ios::in);
	while(!file.eof()){
		pos=file.tellg();
		buffer.erase();
		getline(file,buffer);
		if(buffer[0]!='*'){
			if(buffer.empty()) break;
			acnt=extract_acnt();
			acnt_list[++count]=acnt;
			address_list[count]=pos;
		}
	}
	
	file.close();
	sort_index();
	buffer.erase();
  }

  void atm::sort_index(){
	int i,j,temp_address;
	string temp_acnt;
	for(int i=0;i<=count;i++){
		for(int j=i+1;j<=count;j++){
			if(acnt_list[i]>acnt_list[j]){
				temp_acnt=acnt_list[i];
				acnt_list[i]=acnt_list[j];
				acnt_list[j]=temp_acnt;
				temp_address=address_list[i];
				address_list[i]=address_list[j];
				address_list[j]=temp_address;
			}
		}
	}
	
  }

  int atm::search_index(string key){
	int low=0,high=count,mid=0,flag=0,pos;
	while(low<=high){
		mid=(low+high)/2;
		 if(acnt_list[mid]==key){
			flag=1;
			break;
		 }
		 if(acnt_list[mid]>key) high=mid-1;
		 if(acnt_list[mid]<key)  low=mid+1;
	 }
	 if(flag)
	 return mid;
	 else
	 return -1;
  }
  
  
  void atm:: search_withdraw(string key){
	int pos=0,address,counter=0;
	char c;
	string pin_num,amt;
	fstream file;
	buffer2.erase();
	pos=search_index(key);
	
	if(pos==-1)
	cout<<"YOUR ACCOUNT NUMBER IS NOT BEEN REGISTRED!!!!!!! \n";
	else if(pos>=0){
		
		file.open("acount.txt");
		address=address_list[pos];
		file.seekp(address,ios::beg);
		getline(file,buffer2);
		//cout<<buffer2;
		
		cout<<"PLEASE ENTER YOUR PIN NUMBER:";
		cin>>pin_num;
		while(!file.eof()){
		
		string p=unpack_pin(buffer2);
		
		if(pin_num==p)   {
		cout<<"ENTER THE AMOUNT YOU WISH TO WITHDRAW FROM YOUR ACOUNT:";
		cin>>amt;
		int amnt = atoi(amt.c_str());
		string a=unpack_amnt(buffer2);
		int d = atoi(a.c_str());
		//cout<<buffer2;
		if(amnt<=d)
		{
            int b = atoi(amt.c_str()); 
			int c = atoi(a.c_str()); 
			c=c-b; 
			//char date[9];
			//_strdate(date); 
			ostringstream string1;
	        string1 << c;
	        string withdrawl_amt = string1.str();
	        cout<<"PLEASE COLLECT YUR CASH:  "<<amnt<<endl;
	        string date=string_strdate_alternative();
		    pack_again_acount(key,p,withdrawl_amt,date); 
			pack_again_trans(key,date,withdrawl_amt);  
	        
            
		}
		
		else{
			cout<<" \nSORRY YOU DONT HAVE ENOUGH BALANCE IN YOUR ACOUNT \n";
		}
		
	}
	    else{
	    	
	    	
	    	cout<<"\n YOU HAVE ENTERED WRONG PIN NUMBER SO YOUR ACCOUNT WILL BE BLOCKED\n";                 
		    delete_old_entry_of_acount(key);
		    delete_old_trans(key);
		    delete_old_user(key);
		}
		
			
		
	    cout<<"ENTEER c TO CONTINUE";
	    cin>>c;
	    if(c=='c')
	    break;
		 
		   }
		   
        file.close();        
		
			} 
		
}

void atm::pack_again_acount(string act ,string p, string amnt,string date){
	buffer1.erase();
	buffer1=act+'|'+p+'|'+amnt+'|'+date+'$'+'\n';
	if(delete_old_entry_of_acount(act))
	write_to_file_again();
	
}
void atm::pack_again_trans(string act,string p,string amnt){
	buffer2.erase();
	buffer2=act+'|'+p+'|'+amnt+'$'+'\n';
	if(delete_old_trans(act))
	write_to_transfile_again();
}



	void atm::write_to_file_again(){
		fstream file;
		file.open("acount.txt",ios::out|ios::app);
	    file<<buffer1;
	    file.close();
	    create_index();
	    
	}
	
	void atm::write_to_transfile_again(){
		fstream file;
		file.open("transaction.txt",ios::out|ios::app);
	    file<<buffer2;
	    file.close();
	    create_index();
	    
	    
	}

int atm::delete_old_entry_of_acount(string act_no) {         
	fstream file;         
	int pos, i,flag=0;         
	//pos=moify_search(act_no); 
	pos=search_index(act_no);        
	if(pos>=0)  {   
	              
	
	
	//cout<<"wrong acount number";
	//else if(pos>=0){
		file.open("acount.txt");
		int address=address_list[pos];
		file.seekp(address,ios::beg);         
	file.put('*');                 
	flag=1;                 
	file.close();
	for(i=pos;i<count;i++)                  
	{                          
	acnt_list[i]=acnt_list[i+1];                          
	address_list[i]=address_list[i+1];       
	}      
	 count--;    
	 } 
	   else       
	   cout<<"record not found\n";
	             
	        
	if(flag==1) 
	return 1;         
	else         
	return 0;
	 } 
	 
	int atm::delete_old_trans(string act_no) {         
	fstream file;      
	int pos, flag=0;         
	pos=search(act_no);         
	if(pos>=0)         
	{                 
	file.open("transaction.txt");                 
	file.seekp(pos,ios::beg);                 
	file.put('*');                 
	flag=1;                 
	file.close();         
	}         
	if(flag==1) 
	return 1;         
	else         
	return 0; 
	 } 
	 
	 int atm::delete_old_user(string act_no) {         
	fstream file;      
	int pos, flag=0;         
	pos=search(act_no);         
	if(pos>=0)         
	{                 
	file.open("user.txt");                 
	file.seekp(pos,ios::beg);                 
	file.put('*');                 
	flag=1;                 
	file.close();         
	}         
	if(flag==1) 
	return 1;         
	else         
	return 0; 
	 } 
	 
	 
	  

void atm:: search_deposit(string key){
	int pos=0,address;
	char c;
	string pin_num,amnt;
	fstream file;
	buffer2.erase();
	pos=search_index(key);
	if(pos==-1)
	cout<<"YOUR ACCOUNT NUMBER IS NOT BEEN REGISTERED WITH US!!!!!! \n";
	else if(pos>=0){
		file.open("acount.txt");
		address=address_list[pos];
		file.seekp(address,ios::beg);
		getline(file,buffer2);
		
		cout<<"PLEASE ENTER YOUR PIN NUMBER:";
		cin>>pin_num;
		while(!file.eof()){
		
		string p=unpack_pin(buffer2);
		if(pin_num==p)   {
		cout<<"ENTER AMOUNT YOU WISH TO DEPOSIT:";
		cin>>amnt;
		string a=unpack_amnt(buffer2);
		//cout<<buffer2;
		
            int b = atoi(amnt.c_str()); 
			int c = atoi(a.c_str()); 
			c=c+b;  
			ostringstream string1;
	        string1 << c;
	        string total_amt = string1.str();
	        //char date[9];
			//_strdate(date);
		    string date=string_strdate_alternative();
	        cout<<"\n PLEASE PLACE YOUR CASH IN THE SLOT PROVIDED:  "<<amnt<<endl;
	        pack_again_acount(key,p,total_amt,date);
            pack_again_trans(key,date,total_amt);
            
		
		
		
		
	}
	    else{
	    	
	    	cout<<"\n YOU HAVE ENTERD WRONG PIN HENCE YOUR ACCOUNT WILL BE BLOCKED SORY!!!!!!!\n";   
			delete_old_entry_of_acount(key);  
			delete_old_trans(key);
			delete_old_user(key);
			
			return ;            
		}
		
	    cout<<"ENTER c TO CONTINUE";
	    cin>>c;
	    c=tolower(c);
	    if(c=='c')
	    break;
		   
		   }
		   
        file.close();        
		
			} 
		
}

	 	
	string atm::unpack_pin(string buffer2){
	int ch=1,i=0;       
	ostringstream str1;
	str1 << pin;
	ostringstream str2;
	str2 << amt;
	ostringstream str3;
	str3 << acnt;
	string pin_no = str1.str();
	string total_amt = str2.str();
	string acnt_no = str3.str();  
	string date;
	acnt_no.erase();         
	while(buffer2[i]!='|')         
	acnt_no+=buffer2[i++];         
	pin_no.erase();         
	i++;         
	while(buffer2[i]!='|')         
	pin_no+=buffer2[i++]; 
	total_amt.erase();
	i++;
	while(buffer2[i]!='|')         
	total_amt+=buffer2[i++];
	date.erase();
	i++;
	while(buffer[i]!='$')         
	date+=buffer2[i++];
	return pin_no;
	
	}
	
	string atm::unpack_amnt(string buffer3){
	int ch=1,i=0;       
	ostringstream str1;
	str1 << pin;
	ostringstream str2;
	str2 << amt;
	ostringstream str3;
	str3 << acnt;
	string pin_no = str1.str();
	string total_amt = str2.str();
	string acnt_no = str3.str();  
	string date;
	acnt_no.erase();         
	while(buffer3[i]!='|')         
	acnt_no+=buffer3[i++];         
	pin_no.erase();         
	i++;         
	while(buffer3[i]!='|')         
	pin_no+=buffer3[i++]; 
	total_amt.erase();
	i++;
	while(buffer3[i]!='|')         
	total_amt+=buffer3[i++];
	date.erase();
	i++;
	while(buffer[i]!='$')         
	date+=buffer3[i++];
	//return pin_no;
	return total_amt;
	buffer3.erase();
	}

string atm::unpack_date(string buffer3){
	int ch=1,i=0;       
	ostringstream str1;
	str1 << pin;
	ostringstream str2;
	str2 << amt;
	ostringstream str3;
	str3 << acnt;
	string pin_no = str1.str();
	string total_amt = str2.str();
	string acnt_no = str3.str(); 
        string date; 
	acnt_no.erase();         
	while(buffer3[i]!='|')         
	acnt_no+=buffer3[i++];         
	date.erase();         
	i++;         
	while(buffer3[i]!='|')         
	date+=buffer3[i++]; 
	
	return date;
	buffer3.erase();
	}


string atm:: unpack() {         
	int ch=1,i=0;       
	ostringstream str1;
	str1 << pin;
	ostringstream str2;
	str2 << amt;
	ostringstream str3;
	str3 << acnt;
	string pin_no = str1.str();
	string total_amt = str2.str();
	string acnt_no = str3.str(); 
	string date; 
	acnt_no.erase();         
	while(buffer[i]!='|')         
	acnt_no+=buffer[i++];         
	pin_no.erase();         
	i++;         
	while(buffer[i]!='|')         
	pin_no+=buffer[i++]; 
	total_amt.erase();
	i++;
	while(buffer[i]!='|')         
	total_amt+=buffer2[i++];
	date.erase();
	i++;
	while(buffer[i]!='$')         
	date+=buffer2[i++];
	//return pin_no;
	return acnt_no;
	
	 } 
	 
	 int atm::search(string key) {  
	        ifstream file;         
			int flag=0,pos=0;         
			file.open("transaction.txt",ios::in);         
			while(!file.eof())         
			{                 
			buffer.erase();                 
			pos=file.tellg();                 
			getline(file,buffer);                 
			string acnt_no=unpack();                 
			if(key==acnt_no)                 
			{                        
			                     
			return pos;                 
			}         
			}         
			file.close();         
			if(flag==0)         
			{ 
  
                //cout<<"\n not found..\n";                 
				return -1;  
} } 
	 


int atm::existing_user(){
	string act,pin;
	ifstream file;
	int ch;
main:	cout<<"SELECT YOUR OPTION: \n";
	cout<<"\n $ ----------------------------- $\n";
	cout<<"\n \t 1.BALANCE ENQUIRY \n \t 2.WITHDRAWL \n \t 3.DEPOSIT\n \t 4.EXIT\n ";
	cout<<"\n $ ----------------------------- $\n";
	cout<<"\n ENTER YOUR CHOICE";
	cin>>ch;
	switch(ch){
		case 1:search();
		goto main;
		break;
		
		case 2:cout<<"PLEASE ENTER YOUR ACCOUNT NUMBER: ";
		cin>>act;
		search_withdraw(act);
		goto main;
		break;
		
		case 3:cout<<"PLEASE ENTER YOUR ACCOUNT NUMBER: ";
		cin>>act;
		search_deposit(act);
		goto main;
		break;
		
		case 4:exit(1);
		break;
		
	}
	
	
        
        
	}

	void atm::hash_insert(string acnt1,string pin1,string amnt1,int hash_key)
{
	atm *p,*prev,*curr;
	p=new atm;
	p->acntno=acnt1;
	p->pinno=pin1;
	p->amnt=amnt1;
	
	p->link=NULL;
	prev=NULL;
	curr=h[hash_key];
	if(curr==NULL)
	{
		h[hash_key]=p;
		//display_hash();
		return;
		
	}
	
	
	while(curr!=NULL)
	{
		prev=curr;
		curr=curr->link;
		
	}
	prev->link=p;


}
void atm::display_hash(){
	for(int i = 0; i <29; i++)
{
    if(h[i] != NULL)
        cout<<"key is" <<i<<"value is"<< h[i]->acntno  << endl;
        

}
}

	
	
	void atm:: unpack_balance(){
	string acnt,pin,amnt;
	fstream file;
	file.open("transaction.txt",ios::in);
	int i=0,j,count1;
	
		acnt.erase();
		while(buffer[i]!='|')
		acnt+=buffer[i++];
		pin.erase();
		i++;
		while(buffer[i]!='|')
		pin+=buffer[i++];
		amnt.erase();
		i++;
		while(buffer[i]!='$')
		amnt+=buffer[i++];
		

		count1=0;
		for(j=0;j<acnt.size();j++)
		{
			count1=count1+acnt[j];
			count1=count1%29;
		}
		
		
		//	cout<<"count is"<<count<<endl;
		hash_insert(acnt,pin,amnt,count1);
		file.close();
		

}

void atm:: search()
{
	//create_index();
	fstream file;
	buffer.erase();
	string acnt,pin,amnt;
	int j,count1,i=0;
	atm *curr;
	
	cout<<"PLEASE ENTER YOUR REGISTERED ACCOUNT NUMBER:";
	cin>>acnt;
	file.open("transaction.txt",ios::in);
	
	while(!file.eof())
	{
		
		getline(file,buffer);
		unpack_balance();
		
    }
	
	file.close();
	count1=0;
	for(j=0;j<acnt.size();j++){
	
		count1=count1+acnt[j];
	    count1=count1%29;
	}
	//cout<<"hash value of your entered key is"<<count1;
	//int cnt=hash(count);
	curr=h[count1];
	//cout<<"curr is"<<;
	if(curr==NULL)
	{
		cout<<"\n YOU DONT HAVE ACCOUNT IN OUR BANK \n PLEASE CREATE THE ACCOUNT !!!!!\n thankyou \n";
		return;
	}

	do
	{
		if(curr->acntno==acnt)
		{
		    cout<<"\n YOUR ACCOUNT HAS BEEN UPDATED \n \n";
			cout<<"\n YOUR ACCOUNT NUMBER IS:"<<curr->acntno<<"\n YOUR TRANSACTION DATE IS:"<<curr->pinno<<"\n YOUR BALANCE AMOUNT IS:";
			curr=curr->link;
			search_balance(acnt);
			return;
		}
		else
		{
			curr=curr->link;
		}
}
	while(curr!=NULL);
	if(curr==NULL)
	{
		cout<<"\n you dont have account in our atm \n please create account first !!!!!\n thankyou";
		return;
	}
	
}

void atm::search_balance(string acnt){
	fstream file;
	string buffer2;
	int address;
	buffer2.erase();
	int pos=search_index(acnt);
	
	 if(pos>=0){
		file.open("acount.txt");
		address=address_list[pos];
		file.seekp(address,ios::beg);
		getline(file,buffer2);
		//cout<<buffer2;
	//cout<<"buffer value is"<<buffer2;
	amnt=unpack_amnt(buffer2);
	cout<<amnt<<endl;

}
	file.close();
}

void atm::disp() {         
int i;  
string buffer;       
//         
for(i=0;i<=count;i++)  
{
        ostringstream str3;
	str3 << acnt_list[i];
	string acnt = str3.str(); 
        ostringstream str2;
	str2 << address_list[i];
	string address = str2.str(); 
buffer+=acnt+' '+address+'\n';
}
fstream file;
file.open("index.txt",ios::out|ios::app);
file<<buffer;

cout << endl << "INDEX FILE " << endl;
for(i=0;i<=count;i++)  

cout<<endl<<acnt_list[i]<<" "<<address_list[i];         
cout<<"\n";         

} 

void atm::hash_insert_stat(string pin1,string amnt1,string date1,int hash_key)
{
	atm *p,*prev,*curr;
	p=new atm;
	//p->acntno=acnt1;
	p->pinno=pin1;
	p->amnt=amnt1;
	p->date=date1;
	p->link=NULL;
	prev=NULL;
	curr=h[hash_key];
	if(curr==NULL)
	{
		h[hash_key]=p;
		//display_hash_stat();
		return;
		
	}
	
	
	while(curr!=NULL)
	{
		prev=curr;
		curr=curr->link;
		
	}
	prev->link=p;


}
void atm::display_hash_stat(){
	for(int i = 0; i <29; i++)
{
    if(h[i] != NULL)
        cout<<"key is" <<i<<"value is"<< h[i]->pinno  << endl;
        

}
}

	
	
	void atm:: unpack_pin_stat(){
	string acnt,pin,amnt;
	fstream file;
	file.open("acount.txt",ios::in);
	int i=0,j,count1;
	
		acnt.erase();
		while(buffer[i]!='|')
		acnt+=buffer[i++];
		pin.erase();
		i++;
		while(buffer[i]!='|')
		pin+=buffer[i++];
		amnt.erase();
	    i++;
		while(buffer[i]!='|')         
		amnt+=buffer[i++];
		date.erase();
		i++;
		while(buffer[i]!='$')         
		date+=buffer[i++];
		//return pin_no;
		

		count1=0;
		for(j=0;j<pin.size();j++)
		{
			count1=count1+pin[j];
			count1=count1%29;
		}
		
		
		//	cout<<"count is"<<count<<endl;
		hash_insert_stat(pin,amnt,date,count1);
		file.close();
		

}

void atm:: mini_stat(string pin)
{
	//create_index();
	fstream file;
	buffer.erase();
	string acnt,amnt,date;
	int j,count1,i=0;
	atm *curr;
	
	
	file.open("acount.txt",ios::in);
	
	while(!file.eof())
	{
		
		getline(file,buffer);
		unpack_pin_stat();
		
    }
	
	file.close();
	count1=0;
	for(j=0;j<pin.size();j++){
	
		count1=count1+pin[j];
	    count1=count1%29;
	}
	//cout<<"hash value of your entered key is"<<count1;
	//int cnt=hash(count);
	curr=h[count1];
	//cout<<"curr is"<<;
	if(curr==NULL)
	{
		cout<<"\n YOU DONT HAVE ACCOUNT IN OUR BANK \n PLEASE CREATE THE ACCOUNT !!!!!\n thankyou \n";
		return;
	}

	do
	{
		if(curr->pinno==pin)
		{
		    //cout<<"\n YOUR ACCOUNT HAS BEEN UPDATED \n \n";
			cout<<"\n ACCORDING TO YOUR PIN NUMBER IS:"<<curr->pinno<<endl<<" YOUR BALANCE AMOUNT IS:"<<curr->amnt<<endl<<" ON DATE :"<<curr->date<<endl<<endl<<"____________________________________________"<<endl;
			curr=curr->link;
			//search_date(acnt);
			//return;
		}
				//curr=curr->link;
		
}
	while(curr!=NULL);
	
	
	
}



	
/*int hash(int count){
	return count%29;
}*/
	
	int main(){
	atm a1;
	int choice;
        string pin;
	a1.create_index();
	//a1.disp();
	
	while(1){
	
	cout<<"\n SELECT YOUR OPTION:\n";
	cout<<"\n $ ----------------------------- $\n";
	cout<<"\n \t 1.NEW USER \n \t 2.EXISTING USER \n \t 3.MINI STATEMENT\n\t 4.EXIT";
	cout<<"\n $ ----------------------------- $\n";
	cout<<"\n CHOOSE YOUR OPTION: \n";
	cin>>choice;
	
	
	switch(choice){
		case 1:a1.new_user();
		a1.random();
		a1.pack();
		a1.write_to_file();
		break;
		case 2:a1.existing_user();
		break;
                case 3:cout<<"PLEASE ENTER YOUR REGISTERED PIN NUMBER: ";
		cin>>pin;
		a1.mini_stat(pin);
		break;
                case 4:return 0;
		break;
		default:cout<<"OOPS!!!! YOU HAVE ENTERED WRONG CHOICE";
		
	}
}

}

