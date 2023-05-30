#include <iostream>
#include <string>
#include <fstream>
#include "Binarytree.h"
#include <vector>
using namespace std;

void compression (Binarytree & comp, string wordd)
{
	ifstream in;
	ofstream out;
	string file= "compout.txt";
	out.open(file.c_str());
	int dictsize=255;
	string compare, found;
	int range=2;
	int a=0;
	while (wordd.length() > range-1 && wordd.length()>2)
	{
		compare = wordd.substr(0,range);
		if (!comp.find(compare,a) ) 
		{
			if (range==2)
			{
				char ch=compare.at(0);
				out<< int(ch) << " "; 
			}
			else
			{
				found= wordd.substr(0,range-1);
				if (comp.find(found,a))
					out << a << " ";		
			}
			if (wordd.substr(range-1).length()> 1)
			{
				dictsize++;
				comp.insert(compare,dictsize);
				wordd= wordd.substr(range-1);	
				range=2;
			}
			else
			{
				wordd=wordd.substr(range-1);
				compare=wordd;
				char ch=compare.at(0);
				out<< int(ch) << " ";
			}
		}
		else
		{
			if(wordd.length()>2)
				range++ ;
		}
	}
	if (wordd.length()==2)
	{
		if (comp.find(wordd,a) ) 
		{
			out << a << " " ;
		}
		else
		{
			char j= wordd.at(0);
			char k= wordd.at(1);
			out << int(j) << " " << int(k) << "";
		}
	}
	else
	{
		char c= wordd.at(0);
		out << int (c) << " ";
	}

}


string takeword ()
{
	ifstream in;
	string file= "compin.txt";
	in.open(file.c_str());
	string word="";
	char ch;
	while(in.get(ch))
	{
		word= word+ch;
	}
	in.close();
	return word;
}
int main()
{
	ifstream in;
	ofstream out;

	string str;
	Binarytree comp;

	compression (comp, takeword());

	return 0;
}


