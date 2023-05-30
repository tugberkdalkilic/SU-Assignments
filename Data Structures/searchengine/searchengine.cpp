#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "strutils.h"


using namespace std;

template <class Q>
struct docNode 
{
	Q num;
	docNode<Q> *down;
	docNode<Q> (Q a=0,  docNode<Q> * link=NULL)
		: num(a), down (link)
	{}
};
template <class T,class Q>
struct mainNode 
{
	T wor;
	mainNode<T,Q> *next;
	docNode<Q> *down;
	mainNode<T,Q> (T wor="",  mainNode<T,Q> * link=NULL)
		: wor(wor), next (link)
	{}
};
template <class T,class Q>
class linkedlist
{
private:
	mainNode<T,Q> *head;

public:
	linkedlist<T,Q> ();

	~linkedlist<T,Q>();

	void insert(T word,Q number);
	linkedlist<T,Q>(const linkedlist<T,Q> & rhs);
	void intersect(vector<T> vec, Q a);
};
template<class T,class Q>
linkedlist<T,Q>::linkedlist()
{
	head=NULL;
}
template<class T, class Q>
linkedlist<T,Q>::linkedlist(const linkedlist <T,Q> & rhs) : head(NULL)
{
	*this = rhs;
}
template<class T,class Q>
linkedlist<T,Q>::~linkedlist()
{
	mainNode<T,Q> *ptr=head;
	while (ptr!=NULL)
	{
		mainNode<T,Q> *tmp= ptr->next;
		delete ptr;
		ptr=tmp;
	}
} 

template<class T,class Q>
void linkedlist<T,Q>::insert(T word,Q number)
{
	mainNode<T,Q> *temp= new mainNode<T,Q>;    
	docNode<Q> *temp1= new docNode<Q>;
	docNode<Q> * tempdoc=NULL;
	temp->down=temp1;
	if (head == NULL)  // eðer linkedlistim boþsa ilk elemanlarý yerleþtiriyorum
	{
		temp->wor = word;
		temp1->num= number;
		head=temp;
		head->down=temp1;
	}
	else
	{
		mainNode<T,Q> *temp2=head, *temp3 =head; // eðer linkedlistte bulunan bir kelime ise sadece yanýndaki document numarasýný sorted bir þekilde linkedlist e ekliyorum
		if (word== temp2->wor)   // word headdeki kelimeye eþitse
		{
			tempdoc=temp2->down;
			if (tempdoc-> num > number)  // 
			{
				temp2->down=temp1;  // SONRADAN EKLEME
				temp1->num=number;
				temp1->down=tempdoc;
			}
			else if (tempdoc->num ==number)
				return;
			else
			{
				while(tempdoc->down!=NULL && tempdoc->down->num < number) 
				{
					tempdoc= tempdoc->down;
				}
				temp1->num= number;
				tempdoc->down=temp1;  // DEÐÝÞTÝ
				//tempdoc=tempdoc->down;
			}
		}

		else if (word < temp2->wor ) // 2.KELÝME ÝÇÝN -eðer kelime(araba) head deki kelimeden(balýk) küçükse , araba head deki kelime balýk ise head den sonraki node un kelimesi oluyo
		{
			temp->next=temp2;
			temp->wor=word;
			temp1->num=number;
			head=temp;
		}
		else // eðer kelime linkedlist teki kelimelerden büyükse kelimeyi linked listte sýralý olcak þekilde yerleþtiriyorum
		{
			while (word> temp2->wor && temp2->next!=NULL) // kelime linkedlist deki kelimelerden büyükse
			{
				temp2= temp2->next;
			}
			if (word== temp2->wor)  // eðer kelime önceden linked list e eklendiyse document numarasýný sýralý olarak ekliyorum
			{
				tempdoc=temp2->down;
				if (tempdoc-> num >= number)
				{
					temp1->num=number;
					temp1->down=tempdoc;
					temp2->down=temp1;
				}
				else
				{
					while(tempdoc->down!=NULL && tempdoc->down->num < number)
					{
						tempdoc =tempdoc->down;
					}
					tempdoc->down= temp1;
					temp1->num= number;
				}
			}
			/*else if (word < temp2->wor) // eðer kelime linkedlistteki kelimeden küçükse
			{
			temp->next= temp2;
			temp1->num=number;
			temp2=temp2->next;
			}*/
			else   // eðer kelime listedeki bütün kelimelerden büyükse kelimeyi ve doc numarasýný listenin sonuna ekliyorum
			{
				temp->wor=word;
				temp1->num=number;
				temp2->next=temp;
				//temp->next=NULL;
			}
		}
	}
}

template<class T,class Q>
void linkedlist<T,Q>:: intersect (vector<T>vec, Q a) // bu fonksiyon ilk 2 kelimenin ortak doc numaralarýný içeren linked list ile linkedlistte arayacaðým kelimenin document numaralarýný karþýlaþtýrýyo)
{
	string word="";
	docNode<Q> *temp=head->down;
	vector <Q> vect;
	vector <Q> vectend;
	bool foundboth=true;
	for (int i=0; i<vec.size(); i++)
	{
		word=vec[i];
		mainNode<T,Q> *tmp= head;
		while (tmp->next!=NULL && tmp->wor < word)
		{
			tmp=tmp->next;
		}
		if (tmp->wor==word)
		{
			temp=tmp->down;
			while (temp!=NULL)
			{
				vect.push_back(temp->num);
				temp=temp->down;
			}
		}
		/*else if (tmp->next->wor==word)
		{
			temp=tmp->down;
			while (temp!=NULL)
			{
				vect.push_back(temp->num);
				temp=temp->down;
			}
		}*/
		else
		{
			foundboth=false;
		}
	}
	if (!foundboth)
	{
		for (int u=0; u<vec.size(); u++)
			{
				cout << vec[u] << " ";
			}
			cout << 0 << endl;
	}
	else 
	{
		int count=0;
		for (int j=0; j<vec.size(); j++)
		{
			cout << vec[j] << " " ;
		}
		for (int i=0; i<vect.size(); i++)
		{
			count=0;
			for (int k=i+1; k<vect.size(); k++)
			{
				if (vect[i]== vect[k] && i!=k)
				{
					count++;
				}
			}
			if (count==a-1)
			{
				int h;
				if (vectend.size()==0)
				{
					vectend.push_back(vect[i]);
				}
				else
				{
					bool cont = true;
					for (h=0; cont && h<vectend.size(); h++)
					{
						if (vectend[h]==vect[i])
						{
							cont = false;
						}
					}
					if (cont)
					{
						vectend.push_back(vect[i]);
					}
				}
			}
		}
		cout << vectend.size() << " "  ;
		for (int g=0; g<vectend.size(); g++)
		{
			cout << vectend[g] << " ";
		}
		cout << endl;
	}

}
int main()
{
	string file="docdb.txt";
	ifstream in;
	in.open(file.c_str());
	string line, word;

	linkedlist<string,int> ll;
	int number;

	while(!in.eof()) // until the last part of the file it continues reading the file
	{
		getline(in, line);
		if(line != "") 
		{
			stringstream ss(line);
			while(ss>> word >> number)  // aldýðým kelimeleri linkedliste yerleþtirme
			{  
				ToLower(word);
				ll.insert(word,number);
			}
		}
	}
	int a;
	string b;  // gelecek olan inputlarda ilk girilen sayý kendisinden sonra gelecek kelime sayýsýný belirtiyo
	vector<string> vec;
	bool flag=true;
	while (flag)
	{
		cin >> a ;
		if (a==0)          //yeni 2 satýr
			flag=false;
		for (int f=0; f<a; f++) 
		{
			cin>>b;
			vec.push_back(b);	
		}
		if (flag)
		ll.intersect(vec,a);
		while(vec.size()!=0)
		{
			vec.pop_back();
		}
	}
	return 0;
}







