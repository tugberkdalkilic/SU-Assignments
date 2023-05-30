#include <iostream>
#include <string>
#include "strutils.h"

using namespace std;

bool controller1 (string s)
{  
	if(s.at(0)== '-' )
		return false;
	else if(s.at(0)== '+')
		return false;
	else if(s.at(0)== '/')
		return false;
	else if(s.at(0)== '*')
		return false;
	else 
		return true;
}

bool controller2 (string s)
{
	if (s.find("++") !=string::npos || s.find("--") !=string::npos || s.find("**")!=string::npos || s.find("//")!=string::npos)
		return false;
	else
		return true;
}
bool controller3 (string s)
{	
	if (s.find("/0")!=string::npos)
		return false;
	else
		return true;
	for (int i =0; i<s.length();i++)
		if(!(s.at(i) >= '0' && s.at(i)< '9'|| s.at(i)=='+'|| s.at(i)=='-'|| s.at(i)=='*'|| s.at(i)=='/'))
			return false;
}
bool controller4 (string s)
{
	if (s.at(s.length()-1)== '+' || s.at(s.length()-1)== '-' || s.at(s.length()-1)== '*' || s.at(s.length()-1)== '/')
		return false;
	else
		return true;
}
bool controller5(string s)
{	if (s.find("/0")!=string::npos)
return false;
else
	return true;
}
bool controller6(string s)
{
  for (int i = 0;i<s.length()-1; i++) 
  { 
	 if ( (s.at(i)<47 || s.at(i)>57 ) && (s.at(i) != 47 && s.at(i) != 45 && s.at(i) != 43 && s.at(i) != 42 ) )
	 return false;
  } 
  return true;
}

void calculation1 (string s)
{ 
	string currentNum ="";
	int ind=0, len;
	int num, sum = 0;

	len = s.length();

	for (int i=0; i<len; i++)
	{   
        if(s.at(i) == '+' || s.at(i) =='-')
		{
			num = atoi(currentNum);
			sum = sum + num;
			currentNum =s.at(i);
		}
		else
		{
		currentNum= currentNum+s.at(i);	
		}
	}
	num = atoi(currentNum);
	sum = sum + num;
	cout << sum << endl;
	cout << endl;
}
void calculation2 (string s)
{
	char op;
	string currentNum ="";
	int ind=0, len;
	double num,  result = 0;
	do
	{
		ind=0;
		while (s.at(ind)!= '*' && s.at(ind)!= '/')
		{	
			ind++;
		}
		if(atoi(s.substr(0, ind))!=0)
			result= atoi(s.substr(0, ind));
		s= s.substr(ind);
		len = s.length();

		ind =1;
		while(ind<len && s.at(ind) != '*' && s.at(ind) !='/')
		{
			ind++;
		}
		op= s.at(0);

		num= atoi(s.substr(1,ind-1));
		s= s.substr(ind);
		if ( op == '*' )
		{
			result =result*num;
        }
		else if (op == '/')
		{
			result = (double)result/num;
		}
	}
	while(s!="");
	cout << result << endl;
	cout << endl;
}

int main()
{	
	string s;
	cout << "Please enter the expression to calculate: " ;
	cin >> s ;  

	while ( s != "QUIT" && s != "quit" && s != "EXIT" && s != "exit" && s != "END" && s != "end")
	{   
		if (controller1(s)== true && controller2(s)==true  && controller3(s)==true  && controller4(s)==true && controller5(s)==true && controller6(s)==true)
		{   
			if (s.find('+') ==string::npos && s.find('-') ==string::npos)
			{ 
				if(s.find('*') !=string::npos || s.find('/') !=string::npos)
				calculation2(s);
				else{
					cout << s << endl;
					cout << endl;
				}
			}
			else{ 
				calculation1(s);
			}
		
		}
		else if (controller5(s)== false)
		{
			cout << "You cannot divide by 0"<<endl<<endl;
			
		}
		else if (controller1(s)== false || controller2(s)== false || controller3(s) == false || controller4(s) ==false || controller6(s)== false)
		{	
			cout << "Invalid entry" <<endl<<endl; 
		}

		cout << "Please enter the expression to calculate: " ;
		cin >> s;
	}
	cout << "GOOD BYE" << endl;
	return 0;
}