using namespace std;

struct StackNode
{   
	int counting;
	string value;
	StackNode *next;

};

class DynIntStack
{
private:
	StackNode *top;
public:
	DynIntStack(void);
	~DynIntStack(void);
	void push(string,int);
	void pop(string&,int&);
	bool isEmpty(void);
	/*int countsame(string);
	void print(string,int);
	string find(string);
	string find2(string);
	bool finish(string);*/
};
