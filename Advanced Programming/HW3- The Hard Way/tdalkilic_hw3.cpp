#include <fstream>
#include <sstream>
#include <iostream>
#include "DynIntStack.h"
#include <string>

using namespace std;

bool isExist (DynIntStack &stack1, DynIntStack stack3,string word,int &count)
{
	string y;
	int a;
	bool found = false;
	while (!stack1.isEmpty() && !found)
	{
		stack1.pop(y,a);

		if (y==word)  // while the match is seen the count will be incremented
		{
			found = true;
			stack1.push(y,a+1);
		}
		else  // if the word was not found pushing it to another stack
			stack3.push(y,a);
	}
	while (!stack3.isEmpty())  
	{ 
		stack3.pop(y,a);
		stack1.push(y,a); // getting the word again to original stack
	}
	return found;
}
void transfer (DynIntStack & stack1, DynIntStack & stack2, DynIntStack stack4,int count, int count2)
{   
	DynIntStack temp;
	bool flag2=false;
	string st;
	int i;
	while(!stack1.isEmpty())   // fixing the sequence of words in stack , reversing 
	{
		stack1.pop(st,i);
		temp.push(st,i);
	}
	stack1 = temp;

	while (!stack1.isEmpty())  // gets a word and checks if it exists in the other stack.
	{
		string x,y;
		stack1.pop(y,count);
		while (!stack2.isEmpty()) // while the stack is not empty it pops word
		{
			stack2.pop(x,count2);
			if (x==y)  // if the words in the 2 stacks matched
			{
				flag2=true;  
				if (count<count2)   // the lower # occurrence selected
					cout << "The word \"" << y << "\" occurred at least " << count << " time(s) in both files." << endl;
				else 
					cout << "The word \"" << y << "\" occurred at least " << count2 << " time(s) in both files." << endl;
				break;
			}
			stack4.push(x,count2);  //pushing the words  not to lose the words in the stack
		}
		while(!stack4.isEmpty()) 
		{
			stack4.pop(x,count2);
			stack2.push(x,count2);  //getting the words again to original stack
		}
	}
	if (flag2==false)  // if no matches founded between 2 stacks just show ---
	{
		cout << "---" << endl;
	}
}
int main()
{
	cout << "This program finds the common words of two files using stacks." << endl;
	cout << "--- " << endl;
	string file1, file2;
	int count=0;
	DynIntStack stack1, stack2,stack3, stack4;
	ifstream in1,in2;
	cout << "Enter the first file name:";
	cin >> file1;
	in1.open(file1.c_str());
	while(in1.fail())  // if it fails when opening file it starts to show message of rewriting
	{
		cout << "Enter the first file name:";
		cin >> file1;
		in1.open(file1.c_str());
	}
	string line,word;
	while(!in1.eof()) // until the last part of the file it continues reading the file
	{
		getline(in1, line);
		if(line != "") 
		{
			stringstream ss(line);
			while(ss>> word)
			{  
				if (!isExist(stack1,stack3,word,count)) // if the word has not found before it pushes only once
					stack1.push(word,1);
			}	
		}    
	}
	cout << "Enter the second file name:";
	cin >> file2;
	in2.open(file2.c_str());
	while(in2.fail())  // if the second file does not open
	{
		cout << "Enter the second file name:";
		cin >> file2;
		in2.open(file2.c_str());
	}
	while(!in2.eof()) // until the last part of the file it continues reading the file
	{
		getline(in2, line);
		if(line != "") 
		{
			stringstream ss(line);
			while(ss>> word)  // while reads file it gets string by string
			{
				if (!isExist(stack2,stack3,word,count))   // if the word is not found in the 
					stack2.push(word,1);
			}			
		}
	}
	string num;
	cout<< "Choose with respect to which file the result will be sorted to (1: first file, 2: second file):" ;
	cin >> num;
	while (num != "1" && num != "2") 
	{
		cout << "---" << endl;
		cout << "Invalid choice" << endl;
		cout << "---" << endl;
		cout << "Choose with respect to which file the result will be sorted to (1: first file, 2: second file):"; 
		cin >> num;
	}
	if (num== "1")
	{   
		transfer(stack1,stack2, stack4,count,count);
	}
	else if (num== "2")
	{   
		transfer(stack2,stack1, stack4,count,count);
	}
	return 0;
}