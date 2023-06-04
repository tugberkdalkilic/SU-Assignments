#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "strutils.h"
using namespace std;
struct node 
{     
	int quant, price, multp;
	struct node* next;
	struct node* prev;
	string item;

	node (string s="", int a=0, int b=0, node * link=NULL, node *d =NULL )
		: item(s), quant(a), price(b),multp(b*a), next (link), prev(d)
	{}
};
node * AddInOrder(node *& head, string word,int x, int z, int &counter,int &v)
{   

	node * temp = new node;
	node *newNode= new node;
	node *ptr= new node;
	v= temp->quant;
	if (head == NULL)      // if the added node is the first node
	{   
		temp->item= word;
		temp->quant =x;
		temp->price =z;
		temp->multp =temp->quant*temp->price;
		head=temp;		
		temp->prev= head;
		temp->next = head; 
		counter++;
		cout << "The item "<< word << " of quantity " << x << " is added to the list." << endl;
	}
	else 
	{    
		node *s=head;
		bool flag=false;
		for (int i = 0;i < counter;i++)
		{
			if (s->item == word) // if the item has entered before
			{
				flag=true;
			}
			else
			{
				flag= false;
			}
			s = s->next;
		}
		temp->item= word;
		temp->quant =x;
		temp->price =z;
		temp->multp =temp->quant*temp->price;

		ptr=head;
		for (int i=0; i<counter-1; i++)  // if the total.price of item is still greater than the other nodes
		{
			if (ptr->multp < temp->multp)
				ptr=ptr->next;
		}
		if (temp->multp <ptr->multp)  // case of finding a bigger value of total. price
		{
			ptr -> prev-> next =newNode;
			newNode->prev =ptr->prev;
			newNode ->next=ptr;
			ptr->prev=newNode;
		}
		else if (temp->multp== ptr->multp) // if the total.prices are equal 
		{
			if (temp->item > ptr->item) // the bigger string goes to right
			{
				ptr->next->prev= newNode;
				newNode->next=ptr->next;
				newNode->prev=ptr;
				ptr->next=newNode;
			}
			else                       // otherwise it goes left
			{
				ptr->prev->next= newNode;
				newNode->prev= ptr->prev;
				newNode->next= ptr;
				ptr->prev=newNode;
			}
		}
		else   // if the current node has the biggest total.price
		{
			ptr->next= newNode;
			newNode->prev= ptr;
			newNode->next=head;
		}
		if (!flag)
		{
			head->next= temp;
			temp->prev =head;
			temp->next = NULL;
			counter++;
			cout << "The item "<< word << " of quantity " << x << " is added to the list." << endl;
		}
		else
		{ 
			int q= temp-> quant;
			temp-> quant= x+q;
			cout << "The quantity of the item " << word << " is increased by " << x <<". The final quantity is " << x+q<<"."<< endl;
			v=temp->quant;
		}

	}
	return head;
}
void DeleteOneNode (node * toBeDeleted, node * & head, int &counter)
	/* pre: toBeDeleted points to the node to be deleted from the list
	post: deletes the node pointed by toBeDeleted, updates head if changes */
{
	node * ptr;
	if (head=NULL)  // if the list is empty
	{
		cout << "The shopping list is empty." << endl;
	}
	else if (toBeDeleted == head)  //if the node to be deleted is the first node
	{
		head = head->next;
		delete toBeDeleted;
		counter--;
		cout << "The item " << toBeDeleted << " is deleted from the list." << endl;
	}
	else if (toBeDeleted!= head) //if the node to be deleted is in the middle or at the end
	{
		ptr = head;
		while (ptr->next != toBeDeleted)
		{
			ptr = ptr->next;
		}
		//after while ptr point to the node just before toBeDeleted

		//connect the previous node to the next node and delete
		ptr->next = toBeDeleted->next;
		delete toBeDeleted;
		counter--;
		cout << "The item " << toBeDeleted << " is deleted from the list." << endl;
	}
	else  // if the word is not found in the list
		cout << "The item " << toBeDeleted << " could not be found in the list." << endl;
}
void print (node *head, int counter)
{
	node* temp = head;
	if (temp== NULL)
	{
		cout <<"The shopping list is empty." << endl;
		return;
	}
	temp=head->prev;  // starting from right to left
	for (int i=0; i<counter; i++)
	{
		cout << "Item:" << temp -> item << endl;
		cout << "Quantity:" << temp -> quant << endl;
		cout << "Est.price:" << temp ->price << endl;
		temp=temp->prev;
		cout << "---" << endl;
	}

}
void reverseprint (node *head,int counter)
{   
	node* temp= head;
	if (temp== NULL)
		cout <<"The shopping list is empty." << endl;

	for (int i=0; i<counter; i++)  
	{   
		cout << "Item:" << temp -> item << endl;
		cout << "Quantity:" << temp -> quant << endl;
		cout << "Est.price:" << temp ->price << endl;
		temp=temp->next;
		cout << "---" << endl;
	}	
}
int cost(node *head,int counter)  // calculates total cost
{
	node* temp= head;
	int totalcost=0;
	for (int i=0; i<counter; i++)  // iterates by passing 1 node
	{
		totalcost+=temp->multp;
		temp= temp-> next;
	}
	return totalcost;
}
int main ()
{  
	int counter=0;
	struct node* head=NULL;
	struct node* tail=NULL;
	cout<<"This program helps Alan with gathering the shopping list for his psychedelic breakfast." << endl;
	cout << "---" << endl;
	cout << "MENU" << endl;
	cout << "1. Add item to the shopping list" << endl;
	cout << "2. Delete item from the shopping list" << endl;
	cout << "3. Print the shopping list" << endl;
	cout << "4. Print the shopping list in reverse order"<< endl;
	cout << "5. Show total estimated cost of the list" << endl;
	cout << "6. Exit" << endl;
	cout << "---" << endl;
	string choice;
	cout << "Enter your choice: ";
	cin >> choice;
	cout << "---" << endl;
	int y=atoi(choice);  // converting first input to int
	int v=0, j=0;  // updating the quantity and total cost of items
	bool flag=true;

	while (flag)
	{   
		string answer,line,tword;
		tword="";
		if (y== 1)
		{
			cout << "Enter name for the item:";
			cin >> answer;
		
			getline(cin, line);
			tword=answer;
			stringstream ss(line);
			
			while (ss >> answer )
			{   
				tword+= answer+ " ";
			}
			tword= tword.substr(0, tword.length()-1);
			toUpper
			int x,z;
			cout << "Enter quantity for the item:";
			cin >> x;
			cout << "Enter estimated price for the item:";
			cin >> z;
			cout << "---"<< endl;
			AddInOrder(head ,answer,x,z, counter,v);
		}
		else if (y==2)
		{	
			cout << "Enter an item name to delete from the list:";
			cin >> answer;
			getline(cin, line);
			stringstream ss(line);
			while (ss >> answer )
			{
				cout << answer;
			}
			ToUpper(answer);
			DeleteOneNode(head, head,counter);
		}
		else if (y==3)
		{	
			print(head,counter);
		}
		else if (y==4)
		{	
			reverseprint(head,counter);
		}
		else if (y==5)
		{	
			cout << "The total estimated price of " << counter << " kinds of items is: " << cost(head,counter) << endl;
		}
		else if (y==6)
		{	
			cout << "Clearing the shopping list..." << endl;
			cout << "Exiting the program..." << endl;
			exit(1);
		}
		else
		{
			cout << "This is not a valid option!" << endl;
		}
		cout<< "---" << endl;
		cout << "MENU" << endl;
		cout << "1. Add item to the shopping list" << endl;
		cout << "2. Delete item from the shopping list" << endl;
		cout << "3. Print the shopping list" << endl;
		cout << "4. Print the shopping list in reverse order"<< endl;
		cout << "5. Show total estimated cost of the list" << endl;
		cout << "6. Exit" << endl;
		cout << "---"<< endl;
		cout << "Enter your choice: " ;
		cin >> choice;
		y=atoi(choice);

		cout << "---" << endl;
	}
	return 0;
}