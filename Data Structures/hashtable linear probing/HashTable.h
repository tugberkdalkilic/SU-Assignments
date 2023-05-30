#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;


class HashTable
{
public:
	HashTable (int capacity) : array(capacity) {}

	bool isFull ()
	{
		if (array.capacity()== currentsize)
			return true;
		return false;
	}
	bool insert (const int & value, int & probing)
	{
		int position=0;
		if (isFull()|| findposition(value,position,probing))
			return false;
		else
		{
			probing=0;
			int currentpos= findPos(value);
			while (isActive(currentpos)&& probing <array.capacity())
			{
				probing++;
				currentpos++;
				if(currentpos == array.capacity())
					currentpos=0;
			}
			array[currentpos]= HashEntry(value, ACTIVE);
			currentsize++;
			return true;
		}

	}

	bool remove (const int & value, int &probing)
	{
		probing=0;
		int position=0;
		if (findposition(value,position,probing))
		{
			array[position].info = DELETED;
			currentsize--;
			return true;
		}
		else 
			return false;
	}
	bool find (const int & value, int & probing)
	{
		probing=0;
		int position=0;
		if (findposition(value,position,probing))
			return true;
		else 
			return false;
	}
	double HashTable::loadfact()
	{
		return double (currentsize-1)/array.capacity();
	}

	void HashTable::setsize()
	{
		currentsize=0;
	}
	int HashTable:: returnsize()
	{
		return currentsize;
	}
	enum EntryType {ACTIVE,EMPTY,DELETED};

private:

	struct HashEntry
	{
		int element;
		EntryType info;
		HashEntry( int e=0, EntryType i = EMPTY ) 
			: element( e ), info(i){}
	};

	vector <HashEntry> array;
	int currentsize;


	bool isActive (int currentPos) 
	{
		return array[currentPos].info == ACTIVE;
	}

	int findPos (const int & value) 
	{
		int position=myhash(value);
		int count=0;
		while (array[position].element!=value && array[position].info!= EMPTY && count< array.capacity())
		{
			if ( array[position].info== DELETED)
				return position;
			position++; 
			if (position==array.capacity())
				position=0;
			count++;
		}
		return position;
	}

	bool findposition (const int & value, int & position, int &probing)
	{
		position= myhash(value);
		if (array[position].info== EMPTY)
			return false;
		while (array[position].element!= value && probing < array.capacity() && array[position].info!= EMPTY)
		{
			position++;
			if (position==array.capacity())
				position=0;
			probing++;
		}
		if (array[position].element == value && array[position].element== ACTIVE)
			return true;
		else
			return false;
	}
	int myhash (const int& value)
	{
		int s=value;
		s= s % array.capacity();
		return s;
	}
};


#endif