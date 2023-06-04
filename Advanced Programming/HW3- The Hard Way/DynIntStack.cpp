#include <iostream>
#include "DynIntStack.h"
#include <string>
using namespace std;

DynIntStack::DynIntStack()
{
	top = NULL; 
}

DynIntStack::~DynIntStack()
{
	StackNode * temp;
	
	while(top != NULL)
	{
		temp = top;
		top = top->next;
		
		delete temp;
	}
}

void DynIntStack::push(string num,int count)
{
	StackNode *newNode;

	// Allocate a new node & store Num
	newNode = new StackNode;
	newNode->value = num;
	newNode->counting=count;

	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert NewNode before top
	{
		newNode->next = top;
		top = newNode;
		
	}
}

void DynIntStack::pop(string & num,int &count)
{
	StackNode *temp;

	if (isEmpty())
	{
		cout << "The stack is empty.\n";
	}
	else	// pop value off top of stack
	{
		num = top->value;
		count = top->counting;
		temp = top->next;
		delete top;
		top = temp;
	}
}
bool DynIntStack::isEmpty(void)
{
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}
/*int DynIntStack:: countsame (string num)
{
	StackNode *temp; 	
	//temp = new StackNode(top,value,next);
	temp = top;
	temp->counting=0;
	if (isEmpty())
	{
		return 0;
	}
	else 
	{   
		while (temp!=NULL)
		{  
			if (num==temp->value)
			{
				temp->counting+=1;
			}
			temp=temp->next;
		}
	}

	return temp->counting;
}*/

/*void DynIntStack::print (string num,int numoccurred)
{
	StackNode *temp= top;
	while (temp!=NULL)
	{   
		cout << "The word" << num << " occurred at least" << numoccurred << " time(s) in both files." << endl;
		temp=temp->next;
	}

}
string DynIntStack::find (string num)
{
	return top->value;
}

string DynIntStack::find2 (string num)
{
	string not = "";
	StackNode *temp=top;
	while (temp!=NULL)
	{
		if (temp->value==num)
			return num;
		else 
			temp=temp->next;
	}
	return not;
}
bool DynIntStack::finish (string num)
{
	StackNode *temp=top;
	while (temp!=NULL)
	{
		temp=temp->next;
	}
	return false;
}*/