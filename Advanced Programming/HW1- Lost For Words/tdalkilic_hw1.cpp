#include <iostream>
#include <string>
#include<sstream>
#include<fstream>   
#include <vector>

using namespace std;
bool columnlevel (const vector<vector<char> > & mat,int rows, int cols, string word)
{ 
	for (int i=0; i<rows - word.length()+1 ; i++) // incrementing row number to 
	{   
		for (int j=0; j<cols; j++)
		{   
			int tempx = i;  // cause of using for loop, i used temporary number not to increment row number twice
			int tempy = j;  // same reason for column
			bool found = true;  // it checks the matching true or not
			for (int k = 0; k < word.length()&& found ; k++)  // incrementing the index of word if the unmatching did not occur
			{
				char x = word.at(k);
				if(tempx <rows && x == mat[tempx][tempy])  // if char is same with the index , it increases row number
				{   
					tempx++;
				}
				else    // not matching
					found=false; 
			}
			if (found)               // if matching true, continues
				return true;
		}
	}
	return false;
}
bool reversecolumnlevel (const vector<vector<char> > & mat,int rows, int cols, string word)
{ 
	for (int i=rows-1; i>=word.length()-1; i--) // by starting searching from last row to first row in matrix
	{   
		for (int j=cols-1; j>=0; j--)  // by starting from last column, it goes to left
		{   
			int tempx = i;
			int tempy = j;
			bool found = true;
			for (int k = 0; k < word.length()&& found; k++) // incrementing word index
			{
				char x = word.at(k);
				if(tempx>=0 && x == mat[tempx][tempy])  // it checks the index in the word is same or not with the index in matrix
				{   
					tempx--;
				}
				else   // the index of word is not match with the index in the matrix
				{
					found=false;
				}
			}
			if (found)      // if matching true
				return true;
		}
	}
	return false;  // otherwise it is false
}

bool rowlevel (const vector<vector<char> > & mat,int rows, int cols, string word)
{   
	for (int j=0; j <= cols - word.length()+1; j++) // starting from first column to column that might reach to last column
	{ 
		for (int i=0; i<rows; i++) 
		{
			int tempx = i;  
			int tempy = j;
			bool found = true;
			for (int k = 0; k < word.length()&& found; k++)
			{
				char x = word[k]; // converting index of word to char
				if( tempy<cols && x == mat[tempx][tempy]) // if the index of word is same with the index in the matrix
				{
					tempy++;  // incrementing column
				}
				else  // word index and matrix index not matched
				{ 
					found = false;
				}
			}
			if (found)  // when indexes are same
				return true;
		}
	}

	return false;
}
bool reverserowlevel (const vector<vector<char> > & mat,int rows, int cols, string word)
{   
	for (int j=cols-1; j >= word.length()-1; j--)  // starting from last column
	{ 
		for (int i=rows-1; i>=0; i--) // starting from last row
		{
			int tempx = i;  // creating temporary number not to increment row number twice
			int tempy = j;  // same reason for column number
			bool found = true;
			for (int k = 0; k < word.length()&& found; k++)  
			{
				char x = word[k];
				if( tempy>=0 &&x == mat[tempx][tempy]) // if the match has occurred
				{
					tempy--;  // it searchs for the lower indexes of column
				}
				else  // unmatching
					found = false;

			}
			if (found)  // if the matching has seen
				return true;
		}
	}
	return false;
}
int diagonal (const vector<vector<char> > & mat,int rows, int cols, string word)
{
	for (int j=0; j<cols - word.length()+1; j++) // starting from the last column going to first column
	{ 
		for (int i=0; i<rows- word.length()+1; i++)  // starting from the last row going to first row
		{
			int tempx = i;
			int tempy = j;
			int count=0;  
			for (int k = 0; k < word.length(); k++) // incrementing the index of word
			{   
				char x = word.at(k);  // the index of word is converted to char
				if(tempx>=0 && tempy>=0 && x == mat[tempx][tempy])  // if the char is same with the index in the matrix
				{
					tempx++;
					tempy++;
					count++;  // incrementing the number of correct chars
				}
			}
			if (count== word.length()) // if the number of characters is equal to length of word user didnt use joker
				return 1;
			else if (count == word.length()-1) // user used 1 joker
				return 2;
		}
	}
	return 0;
}

int reversediagonal (const vector<vector<char> > & mat,int rows, int cols, string word)
{   
	int count;
	for (int j=cols-1; j>=0; j--) // starting from the last column going to first column
	{ 
		for (int i=rows-1; i>=0; i--) // starting from the last row going to first row
		{
			int tempx = i;  // because of using for loops, i equalised the row number to a temporary number to make incrementing number easily
			int tempy = j;  // same condition for column
			count=0;
			for (int k = 0; k < word.length(); k++)
			{
				char x = word.at(k);
				if(tempx>=0 && tempy>=0 && x == mat[tempx][tempy])   // if founded it goes northwest side
				{
					tempx--;
					tempy--;
					count++;   // counting the number of correct characters
				}
			}
			if (count== word.length())  // if the number of characters is equal to length of word user didnt use joker
				return 1;
			else if (count == word.length()-1) // user used 1 joker
				return 2;
		}
	}
	return 0; // the word is not found
}

int main()
{
	string fileName;
	vector<vector<char> > mat;
	cout << "This program allows you to play a Sunday morning puzzle on your computer."<< endl;
	cout << "---"<< endl;
	cout<<"Enter the matrix file name: ";
	cin>>fileName;

	ifstream input;
	input.open(fileName.c_str());

	while(input.fail()) // user enters wrong file name and gets filename again from the user
	{
		cout<< "Invalid file name!"<< endl;
		cout << "---" << endl;
		cout<<"Enter the matrix file name: ";
		cin>>fileName;
		input.open(fileName.c_str());
	}
	string line;
	while(!input.eof()) // until the last part of the file it continues reading the file
	{
		getline(input, line);
		if(line != "") // until the space in the matrix it reads the content of matrix
		{
			stringstream ss(line);
			char ch;
			vector<char> temp;
			while(ss.get(ch))
			{
				temp.push_back(ch);		
			}
			mat.push_back(temp);
		}
	}
	for (int i=0 ; i < (mat.size()-3) ; i++)  // checks the equality of each row numbers
	{
		if ( mat[i].size() != mat[i+1].size())
		{
			cout << "The matrix does not have row equality, terminating..."<< endl;
			return 0;
		}
	}
	int rows = mat.size();
	int cols = mat[0].size();
	int totalscore=0;
	string word;
	bool game=true;
	while (game)  // the condition of have not entered a word smaller than 3
	{   
		cout<< "---"<<endl;
		cout << "Enter a word: ";
		cin >> word;
		if (word.length() <3)  // if the entered word is smaller than 3, it executes the game
		{   
			game=false;
		}
		else
		{
			int c;
			if (rowlevel(mat,rows,cols,word) || reverserowlevel(mat,rows,cols,word)) // if the word is found in the row level 
			{	
				if (word.length()<6)
				{
					totalscore+= word.length();
					c= word.length();
				}
				else
				{
					totalscore+= word.length()+2;
					c= word.length()+2;
				}
				cout<< word<< " is found in the row level. It contributes " << c << " points."<< endl;
			}
			else if (columnlevel(mat,rows,cols,word)|| reversecolumnlevel(mat,rows,cols,word)) // if the word is found in the column level
			{ 
				if (word.length()<6)
				{
					totalscore+=word.length();
					c= word.length();
				}
				else
				{	
					totalscore+= word.length()+2;
					c= word.length()+2;
				}
				cout << word << " is found in the column level. It contributes " << c << " points." << endl;
			}
			else if (diagonal(mat,rows,cols,word)==1 || reversediagonal(mat,rows,cols,word)==1 )   // if the word is found in the diagonal line without using joker
			{
				if (word.length()<6)
				{
					totalscore+=word.length()*2;
					c= word.length()*2;
				}
				else
				{
					totalscore+= word.length()*2+2;
					c= word.length()*2+2;
				}
				cout << word << " is found in the diagonal level. It contributes " << c << " points." << endl;
			}
			else if (diagonal(mat,rows,cols,word)== 2 || reversediagonal(mat,rows,cols,word)== 2) // if the word is found in the diagonal line with using 1 joker
			{	
				if (word.length()<6)
				{
					totalscore+=word.length()*2-2;
					c= word.length()*2-2;
				}
				else
				{
					totalscore+= word.length()*2;
					c= word.length()*2;
				}
				cout << word << " is found in the diagonal level. One letter was replaced by joker. It contributes " << c << " points." << endl;
			}
			else if (diagonal(mat,rows,cols,word)== 0 || diagonal(mat,rows,cols,word)== 0 )  // not founded in the diagonal line even using 1 joker
			{	
				cout << word << " is not found in the matrix. 5 points are deducted." << endl;
				totalscore+= -5;
			}
			else  // the word is not found in anywhere
			{
				cout << word << " is not found in the matrix. 5 points are deducted." << endl;
				totalscore+= -5;
			}
		}
	}
	if (!game) // when a word smaller than 3 is entered and calculating total score
	{
		game=false;
		cout << "---" << endl;
		cout << "Game has ended." << endl;
		cout << "Total score of the words: " << totalscore << endl;
	}
	return 0;
}




