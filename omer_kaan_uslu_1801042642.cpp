#include<iostream>
#include<string>
#include <time.h>

using namespace std;

string generate_secret(int digit)
{
	string str;
	int random;
	int i,j;
	char temp;
	/* assigning first digit of secret number which is not will be 0(with help of ASCII) */
	random=(rand()%9)+1;
	str=random+48;
	/*loop for assigning other elements of secret number */
	for(i=1;i<digit;i++) {
		random=(rand()%10);
		/*loop for checking duplicate elements */
		for(j=0;j<i;j++) {
			/* If there are duplicate elements, program forces to choose another number and assigning j as -1. So, for loop goes back to initial 0.*/
			if(str[j]==random+48) {
				j=-1;
				random=(rand()%10);
			}
		}
		/* random number is decided. it must be put. */
		temp=random+48;
		str=str+temp;
	}
	return str;
}

bool check_digit(string str){
	/* this function checks if the content of full string are integer or not.*/
	int i;
	for(i=0;i<str.length();i++) {
		if(!(str[i]=='1'||str[i]=='2'||str[i]=='3'||
			str[i]=='4'||str[i]=='5'||str[i]=='6'||
			str[i]=='7'||str[i]=='8'||str[i]=='9'||str[i]=='0'))
			return false;
	}
	return true;

}

int find_firstcount(string str1,string str2,int digits){
	/* First count is sum of elements which are placed correctly.*/
	int i,count=0;
	/*loop to check every element*/
	for(i=0;i<digits;i++){
		/*if condition in order to check if they are equal by the help of their indexes*/
		if(str1[i]==str2[i])
			count++;
	}
	return count;
}

int find_seccount(string str1,string str2,int digits,int firstcount) {
	/*Second count is sum of elements which are misplaced but equal.*/
	int i,j,count=0;
	/*This loop calculates sum of all equal elements without looking for if they are misplaced.*/
	for(i=0;i<digits;i++){
		/* second loop is to check every element from the other string(base string) */
		for(j=0;j<digits;j++) {
			if(str1[i]==str2[j]){
				count++;
				/* if elements are equal, second loop does not have to continue */
				break;
			}
		}
	}
	/*All equal elements are found. Function substracts right placed ones(first count) and returns second count value. */
	return count-firstcount;
}

bool check_unique(string str,int digits) {
	/*this function checks if all elements of string are unique*/
	int i,j;
	for(i=0;i<digits;i++) {
		/*assigning j as i+1 because there is no need to check back. That's the sense of outer loop.*/
		for(j=i+1;j<digits;j++){
			if(str[j]==str[i]){
				/*if there are equal ones, return false. */
				return false;
			}
		}
	}
	return true;
}

int main(int argv,char **argc) {
	/*in order to use rand() function correctly*/
	srand (time(NULL));
	string secretnumber;
	/* r mode */
	if(argc[1][0]=='-' && argc[1][1]=='r' && argc[1][2]=='\0')
	{
		/*If there is negative number, it's error. If there is an integer which is 0, that's also the error. */
		/*Input value must be 1 digit at most.*/ 
		if(argc[2][0]=='-' || argc[2][0]=='0'  || argc[2][1]!='\0') {
			cout<<"E0";
			exit(1);
		}
		/*checking if all elements are integer*/
		else if(!check_digit(argc[2])){
			cout<<"E2";
			exit(1);
		}
		int digits=argc[2][0]-48;
		int turn=1;
		secretnumber=generate_secret(digits);
		int firstcount,secondcount;
		string guessnumber;
		//cout<<secretnumber<<endl;
		while(true){
			if(turn==101){
				cout<<"FAILED";
				exit(1);
			}
			cin>>guessnumber;
			if (guessnumber.compare(secretnumber)==0)
			{/* end of the game*/
				cout<<"FOUND "<<turn;
				exit(1);
			}
			else if(!check_digit(guessnumber))
			{/*check if elements are integer*/
				cout<<"E2";
				exit(1);
			}
			else if(guessnumber.length()!=digits)
			{/*check if length of guessnumber is less or more than secretnumber */
				cout<<"E1";
				exit(1);
			}
			else if(guessnumber[0]=='0' || !check_unique(guessnumber,digits) )
				{/* check first digit's situation and uniqueness*/
				cout<<"E0";
				exit(1);
			}
			firstcount=find_firstcount(guessnumber,secretnumber,digits);
			secondcount=find_seccount(guessnumber,secretnumber,digits,firstcount);
			cout<<firstcount<<" "<<secondcount<<endl;
			turn++;
		}

	}
	/* u mode */
	else if(argc[1][0]=='-' && argc[1][1]=='u' && argc[1][2]=='\0') {
		secretnumber=argc[2];
		if(!check_digit(argc[2])) {/* check if all elements are integer*/
			cout<<"E2";
			exit(1);
		}
		/*If there is negative number, it's error. If there is an integer with left most digit 0, that's also the error. */
		else if(argc[2][0]=='-' || argc[2][0]=='0' || !check_unique(argc[2],secretnumber.length())) {
			cout<<"E0";
			exit(1);
		}
		int digits=secretnumber.length();
		int turn=1;
		int firstcount,secondcount;
		string guessnumber;
		//cout<<secretnumber<<endl;
		while(true){
			if(turn==101){
				cout<<"FAILED";
				exit(1);
			}
			cin>>guessnumber;
			if (guessnumber.compare(secretnumber)==0)
			{/* end of the game*/
				cout<<"FOUND "<<turn;
				exit(1);
			}
			else if(!check_digit(guessnumber))
			{/*check if elements are integer*/
				cout<<"E2";
				exit(1);
			}
			else if(guessnumber.length()!=digits)
			{/*check if length of guessnumber is less or more than secretnumber */
				cout<<"E1";
				exit(1);
			}
			else if(guessnumber[0]=='0' || !check_unique(guessnumber,digits) )
				{/* check first digit's situation and uniqueness*/
				cout<<"E0";
				exit(1);
			}
			firstcount=find_firstcount(guessnumber,secretnumber,digits);
			secondcount=find_seccount(guessnumber,secretnumber,digits,firstcount);
			cout<<firstcount<<" "<<secondcount<<endl;
			turn++;
	} 
		}
	else {/*if argc[1] is nor "-u", neither "-r", that's E0.*/
		cout<<"E0";
		exit(1);
	}
	

}
