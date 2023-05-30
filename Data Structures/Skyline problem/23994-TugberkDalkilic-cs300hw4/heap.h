#ifndef HEAP_H_
#define HEAP_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;
struct loc
{
	int locvalue;
	loc (int a=0)
		: locvalue(a)
	{}
};
struct building
{
	int value;
	int label;

	building (int a=0, int b=0)
		: value(a), label(b)
	{}
};

class Heap
{
public:
	Heap( int cap);
	~Heap();
	bool isEmpty( ) ;
	bool isFull( ) ;

	void insert( int value, int label);
	int remove ( int label);
	int getmax();

private:
	int  currentSize; // Number of elements in heap
	building * array;       // The heap array
	int capacity;
	loc * location;

	void percolateDown( int hole );
};

Heap::Heap(int cap)
{
	currentSize=0;
	capacity=cap;
	array= new building[cap+1];
	location = new loc[cap+1];
}

Heap::~Heap() // destructor
{
	if (!isEmpty())
	{
		delete [] array;
		delete [] location;
	}
}

bool Heap::isEmpty()  
{
	if (currentSize==0)
		return true;
	return false;
}
bool Heap::isFull()
{
	if (currentSize==capacity)
		return true;
	return false;
}
void Heap:: insert(int lab, int val)
{
	if( isFull( ) )
		return ;
	int hole = ++currentSize;  // Percolate up
	
	for( ; hole > 1 && val > array[ hole / 2 ].value; hole /= 2 )
	{
		array[ hole ].value = array[ hole / 2 ].value;
		array[ hole ].label = array[ hole / 2].label;
		location[array[hole].label].locvalue=hole;
	}
	array[ hole ].value = val;  // new positions updated
	array[ hole ].label = lab;
	location[lab].locvalue = hole;
	
}
int Heap::remove (int label)
{
	array[location[label].locvalue].value= array[currentSize].value;  // getting from leave to top and equalising to top index
	array[location[label].locvalue].label= array[currentSize].label;
	currentSize--;
	percolateDown(location[label].locvalue);
	return location[label].locvalue;

}
int Heap::getmax()
{
	return array[1].value;
}
void Heap:: percolateDown( int hole )  
{
	int child;
	int t1= array[hole].value;  // keeping the index values
	int t2= array[hole].label;

	for( ; hole * 2 <= currentSize; hole = child ) 
	{
		child = hole * 2;
		if( child != currentSize && array[ child + 1 ].value > array[ child ].value )  // going to leaves
			child++;
		if( array[ child ].value > t1 )  // if the child has more value than parent it changes
		{
			array[ hole ].value = array[ child ].value;
			array[ hole ].label = array[ child ].label;
			location[array[hole].label].locvalue= hole;
		}
		else
			break;
	}
	array[ hole ].value= t1;  // new positions updated
	array[ hole ].label= t2;
	location[array[hole].label]= hole;
}







#endif