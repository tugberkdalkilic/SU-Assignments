#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include "HashTable.h"
#include <fstream>
using namespace std;

const int HASH_SIZE=10007;

struct table
{
	double loadfactor;
	int probe;
    int visit;
	table (double a=0.0, int s=0)
		: loadfactor(a), probe (s), visit (s)
	{}
};

table insertsuccess[HASH_SIZE+1];
table insertfail[HASH_SIZE+1];
table deletesuccess[HASH_SIZE+1];
table deletefail[HASH_SIZE+1];
table findsuccess[HASH_SIZE+1];
table findfail[HASH_SIZE+1];

int main() 
{ 
	ofstream out1, out2, out3, out4, out5, out6;
	out1.open("file1.csv");
	out2.open("file2.csv");
	out3.open("file3.csv");
	out4.open("file4.csv");
	out5.open("file5.csv");
	out6.open("file6.csv");
	
	HashTable hashtable(HASH_SIZE);
	hashtable.setsize();
	srand(7);
	int probing;
	int f=0;

	while (f<1000000 && !(hashtable.isFull()) ) 
	{
	    int i= hashtable.returnsize();
		int s= rand() %8;
		int a= rand() %(HASH_SIZE/20);
	
		if (s<6)
		{
			if(hashtable.insert(a,probing))
			{
				insertsuccess[i].loadfactor= hashtable.loadfact();
				insertsuccess[i].probe +=probing;
				insertsuccess[i].visit++;
			}
			else 
			{
				insertfail[i].loadfactor= hashtable.loadfact();
				insertfail[i].probe += probing;
				insertfail[i].visit++;
			}
		}
		else if (s==6)
		{
			if (hashtable.remove(a,probing))
			{
				deletesuccess[i].loadfactor= hashtable.loadfact();
				deletesuccess[i].probe += probing;
				deletesuccess[i].visit++;
			}
			else
			{
				deletefail[i].loadfactor = hashtable.loadfact();
				deletefail[i].probe+=probing;
				deletefail[i].visit++;
			}
		}
		else
		{
			if (hashtable.find(a,probing))
			{
				findsuccess[i].loadfactor=hashtable.loadfact();
				findsuccess[i].probe += probing;
				findsuccess[i].visit++;
			}
			else
			{
				findfail[i].loadfactor= hashtable.loadfact();
				findfail[i].probe+=probing;
				findfail[i].visit++;	
			}
		}
		f++;
	}

	for (int x=0; x<HASH_SIZE+1; x++)
	{
		if (insertsuccess[x].visit!=0 )
			out1 << x / (float) HASH_SIZE << ";" << insertsuccess[x].probe/ (float)(insertsuccess[x].visit) << endl;
		if (insertfail[x].visit!=0)
			out2 << insertfail[x].loadfactor << ";" << insertfail[x].probe/ (float)(insertfail[x].visit) << endl;
		if (deletesuccess[x].visit!=0)
			out3 << deletesuccess[x].loadfactor << ";" << deletesuccess[x].probe/ (float)(deletesuccess[x].visit) << endl;
		if (deletefail[x].visit!=0)
			out4 << x / (float) HASH_SIZE << ";" << deletefail[x].probe/ (float)(deletefail[x].visit) << endl;
		if(findsuccess[x].visit!=0)
			out5 << findsuccess[x].loadfactor << ";" << findsuccess[x].probe/ (float)(findsuccess[x].visit) << endl;
		if( findfail[x].visit!=0)
			out6 << findfail[x].loadfactor << ";" << findfail[x].probe/ (float)(findfail[x].visit) << endl;
	}
	out1.close();
	out2.close();
	out3.close();
	out4.close();
	out5.close();
	out6.close();

	return 0; 
} 