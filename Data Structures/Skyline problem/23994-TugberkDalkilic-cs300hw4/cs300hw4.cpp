#include <iostream>
#include <string>
#include "heap.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
using namespace std;

struct vectortype
{
	int coord;
	int height;
	vectortype( int e=0, int h=0)
		: coord (e), height(h) {}
};
struct build
{
	int coordinate;
	int buildingnumber;
	int height;
	string direction;
	build( int e=0, int a=0, int h=0, string i="") 
		: coordinate( e ), buildingnumber (a), height(h),direction(i) {}
};

bool sorting(const build a, const build b)
{
	if(a.coordinate != b.coordinate)  // sorting for coordinate
		return (a.coordinate<b.coordinate);
	else                                       // if the coordinates equal sort by height
		return (a.height> b.height);
}
int main()
{
	ifstream in;
	in.open("input.txt");
	int num=0, numofbuildings, indexx=1;
	int xleft, heightt, xright;
	string line;
	in>> numofbuildings ; // get the number of buildings
	//numofbuildings=stoi(line);

	vector< build> arr(numofbuildings*2);
	vector< vectortype> vec(numofbuildings*2);



	Heap heap(numofbuildings);  // creating heap
	for (int i=0; i< numofbuildings; i++)  // putting into vector all values with directions heights and building numbers
	{
		in >> xleft >> heightt >> xright;
		build l(xleft, indexx, heightt, "left");
		build r(xright, indexx, heightt, "right");
		arr[num]=l;
		arr[num+1]=r;
		indexx++;
		num+=2;
	}
	std::sort(arr.begin(), arr.end(), sorting);
	
	if (arr[0].coordinate != 0 && arr[0].height!=0)
		cout << 0 << " " << 0 << endl;

	for (int k=0; k<arr.size(); k++)
	{
		
		if (arr[k].direction== "left")  
		{
			if (heap.isEmpty() || arr[k].height > heap.getmax() )  // the condition of finding a higher building 
			{
				int max= heap.getmax();
				if  ( (k!=0 && arr[k].coordinate!=arr[k-1].coordinate) ||( k!=0 && (arr[k].coordinate==arr[k-1].coordinate && arr[k].buildingnumber != arr[k-1].buildingnumber)) || k==0 )
					cout << arr[k].coordinate << " " << arr[k].height << endl;
			}
			heap.insert ( arr[k].buildingnumber, arr[k].height);
		}
		else  // it is right and delete
		{
			heap.remove(arr[k].buildingnumber);  // condition of not existing in same coordinate and same buildingnumber
			if  ( k!=arr.size()-1 && (arr[k].coordinate!=arr[k+1].coordinate && arr[k].buildingnumber!= arr[k+1].buildingnumber) || (k==arr.size()-1) )  
			{
				if ( arr[k].height > heap.getmax() && k!= arr.size()-1)   // if the height is greater so it outputs to console
					cout<< arr[k].coordinate << " " << heap.getmax() << endl;
				else if ( heap.isEmpty() )
					cout << arr[k].coordinate << " " << 0 << endl;		
			}
		}
	}
	in.close();
	return 0;
}

