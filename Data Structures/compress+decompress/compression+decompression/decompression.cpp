#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
	string dictionary[4096];
	for (int h=0; h<256; h++)
	{
		dictionary[h]=char(h);
	}
	ifstream in;
	string file= "compout.txt";
	in.open(file.c_str());
	int num;
	bool first=true;
	string str="";
	string hold="";
	int currentsize=256;
	ofstream out;
	out.open("decompout.txt");
	if (in>>num )
	{
		out << char(num);
		first=false;
		str= char(num);
	}
	while (in>>num)
	{
		if (num<= 255 )   // gelen þey tek karakter
		{
			out << char(num);
			dictionary[currentsize]= str+ char(num);
			str=char(num);
		}
		else if ( !dictionary[num].empty() && num>255) // sözlükte var ve en az 2 harfli
		{
			out << dictionary[num];
			dictionary[currentsize]= str+ dictionary[num].at(0); // öncesinde dictionary[currentsize]= s+ char(num);
			str= dictionary[num];
		}
		else if ( dictionary[num].empty())  // sözlükte yoksa
		{
			hold= str+ str.at(0);
			out << hold;
			dictionary[currentsize]= hold;
			str= hold;
		}
		currentsize++;
	}
	in.close();
	return 0;
}

