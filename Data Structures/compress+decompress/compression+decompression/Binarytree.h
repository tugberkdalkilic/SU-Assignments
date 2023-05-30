#ifndef BINARYTREE_H_
#define BINARYTREE_H_
#include <string>
using namespace std;

struct Binary
{
	string wor;
	int num;
	Binary *left;
	Binary *right;
	Binary (string s="", int n=0, Binary * link=NULL , Binary * dict=NULL )
		: wor(s) ,num(n), left (link), right(dict){}
};

class Binarytree
{
private:

	Binary *root;
	void makeEmpty( Binary * & t)
	{
		if( t != NULL )
		{
			makeEmpty( t->left );
			makeEmpty( t->right );
			delete t;
		}
		t = NULL;
	}

public:
	
	Binarytree();

	~Binarytree();
	Binarytree(Binarytree& rhs);

	//Binarytree (int & rhs): currentsize (rhs.currentsize) {}

	void insert( string  x, int & number) ;
	bool find (  string & a, int & b) ;

};


#endif