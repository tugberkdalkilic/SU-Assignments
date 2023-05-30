#include "Binarytree.h"

Binarytree::Binarytree()
{
	root=NULL;
}
Binarytree::Binarytree(Binarytree  & rhs) : root(NULL)
{
	*this = rhs;
}

Binarytree::~Binarytree()
{
	Binary*  t;
	makeEmpty(t);
} 

bool Binarytree ::find ( string & a , int & b ) 
{
	Binary * inserted = root;
	if (root==NULL)
		return false;
	else if (inserted->wor== a)
	{
		b=inserted->num;
		return true;
	}
	else if (inserted->wor > a)
	{
		inserted=inserted->left;
		while (inserted!=NULL)
		{
			if (inserted->wor > a)
				inserted=inserted->left;
			else if (inserted->wor== a)
			{
				b= inserted->num;
				return true;
			}
			else
				inserted=inserted->right;
		}
		if (inserted==NULL)
			return false;
	}
	else
	{
		inserted=inserted->right;
		while (inserted!=NULL)
		{
			if (inserted->wor > a)
				inserted=inserted->left;
			else if (inserted->wor== a)
			{
				b= inserted->num;
				return true;
			}
			else
				inserted=inserted->right;
		}
		if (inserted==NULL)
			return false;
	}
}
void Binarytree:: insert ( string x , int & number) 
{
	Binary *temp= new Binary;    

	bool l=false,  r=false;

	if( root == NULL ) //  create a new node at the right place
	{
		temp->wor = x;
		temp->num= 256;
		root=temp;
	}
	else 
	{	
		Binary *inserted=root, *traversing=root;
		if (x < inserted-> wor)  // sol tree
		{
			inserted=inserted->left;
			if (inserted==NULL)
			{
				temp->wor = x;
				temp->num= number;
				root->left=temp;
			}
			else
			{
				while (inserted!=NULL)
				{
					if ( x < inserted->wor ) // yerleþtireceðim kelime küçük
					{
						traversing=inserted;
						inserted=inserted->left;
						if (inserted==NULL)
							l=true;
					}
					else  // yerleþtireceðim kelime büyükse
					{
						traversing=inserted;
						inserted=inserted->right;
						if (inserted==NULL)
							r=true;
					}
				}
				if (l)
				{
					temp->wor = x;
					temp->num= number;
					traversing->left=temp;
				}
				else if (r)
				{
					temp->wor = x;
					temp->num= number;
					traversing->right=temp;
				}
			}
		}

		else if (x > inserted->wor)  // right tree
		{
			inserted=inserted->right;
			if (inserted==NULL)
			{
				temp->wor = x;
				temp->num= number;
				root->right=temp;
			}
			else
			{
				while (inserted!=NULL)
				{
					if ( x < inserted->wor ) // yerleþtireceðim kelime küçük
					{
						traversing=inserted;
						inserted=inserted->left;
						if (inserted==NULL)
							l=true;
					}
					else  // yerleþtireceðim kelime büyükse
					{
						traversing=inserted;
						inserted=inserted->right;
						if (inserted==NULL)
							r=true;
					}
				}
				if (l)
				{
					temp->wor = x;
					temp->num= number;
					traversing->left=temp;
				}
				else if (r)
				{
					temp->wor = x;
					temp->num= number;
					traversing->right=temp;
				}
			}
		}
		else
			return;
	}
}
