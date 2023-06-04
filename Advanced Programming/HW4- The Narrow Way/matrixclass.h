#include <iostream>
#include <fstream>

#ifndef _matrixclass
#define _matrixclass
                                                    // Tugberk Dalkilic - tdalkilic 1.8.2018
using namespace std;
template <class T>
class Matrix2D
{
	friend istream &operator>><T> (istream& is, Matrix2D & mat);
	friend ostream &operator<< <T> (ostream& os, Matrix2D<T>& mat);

private: 
	int rows, cols;
	T ** data;
public:
	Matrix2D<T>(int r, int c);
	int GetIndex(int i, int j);
	void SetIndex(int i, int j, T val);
	Matrix2D<T>();
	~Matrix2D<T>();
	Matrix2D<T>& operator += ( Matrix2D<T>& m);
	void Matrix2D<T>::copy(Matrix2D<T>& m);
	Matrix2D<T>&operator =(Matrix2D<T>& m);
	Matrix2D (const Matrix2D & copy);
	friend Matrix2D<T> operator + <T> ( Matrix2D<T> &lhs, Matrix2D<T> &rhs);
};


template <class T>
Matrix2D<T>::Matrix2D(int r, int c)    // constructor
{
	rows=r;
	cols=c;
	data = new T* [rows]; 

	for (int i = 0; i<rows; i++) 
		data[i] = new T[cols];

}
template <class T>
Matrix2D<T>::Matrix2D()   // default constructor
{
	rows=0;
	cols=0;
	data=NULL;
}

template <typename T>
Matrix2D<T>::~Matrix2D()  // destructor
{   
	for (int i=0; i<rows; i++)
	{
		delete [] data[i];
	}
	delete [] data;
}
template <typename T>
int Matrix2D<T>::GetIndex(int i, int j)
{
	return data[i][j];
}
template <class T>
void Matrix2D<T>::SetIndex(int i, int j, T value)
{
	data[i][j] = value;
}

template <class T>
istream& operator>> (istream& is, Matrix2D<T>& mat)  
{
	string line;
	int i=0, j=0, row=0, col;
	while (getline(is,line))
	{
		col=0;
		row++;  // every getline increments row 1
		T t;
		stringstream ss(line);
		while (ss>> t)  
		{
			col++;   // counts the number of cols
		}
	}
	is.clear();
	is.seekg(0);

	mat.rows=row;
	mat.cols=col;
	mat.data = new T* [mat.rows]; // creating new array to fill the elements

	for (int i = 0; i<mat.rows; i++) 
		mat.data[i] = new T[mat.cols];  

	int k = 0;
	while(getline(is,line))  // putting the elements into empty matrix
	{
		stringstream sss(line);
		T a;
		for (int j=0; j<mat.cols; j++)
		{
			sss>>a;
			mat.data[k][j]=a;
		}
		k++;
	}

	return is;
}
template <class T>
ostream& operator<<(ostream& out, Matrix2D<T>& m)  // writing operator
{
	int i, j; 

	for (i = 0; i < m.rows; i++) 
	{ 
		for (j= 0 ; j< m.cols ; j++) 
			out << setw(5) << m.data[i][j] ;  // writing the elements of matrix
		out << endl;
	} 

	return out;
}
template <class T>
Matrix2D<T> &Matrix2D<T>::operator+=( Matrix2D<T>& m)
{
	for (int j=0; j< m.rows; j++)
	{
		for(int i=0; i < m.cols; i++)
		{
			data[j][i] += m.data[j][i];
		}
	}
	return *this;
}
template <class T>
void Matrix2D<T>::copy(Matrix2D<T>& m)  // same as copy constructor that is used in =operator
{
	rows = m.rows;
	cols = m.cols;
	//data = m.data;

	data = new T* [rows]; 

	for (int i = 0; i<rows; i++) 
		data[i] = new T[cols];


	for (int j=0 ; j < m.rows; j++)
	{
		for(int i=0; i <m.cols ; i++)
		{
			data[j][i] = m.data[j][i];
		}
	}
}
template <class T>
Matrix2D<T> &Matrix2D<T>:: operator = (Matrix2D<T>& m)
{
	if(this != &m)                            // deletes all the item in *this and copies the matrix that comes with parameter
	{
		for (int i=0; i<rows; i++)
		{
			delete [] data[i];
		}
		delete [] data;
		copy(m);
	}
	return *this;
}

template <class T>
Matrix2D<T>::Matrix2D (const Matrix2D<T> & copy)  // copy constructor
{
	rows=copy.rows;
	cols=copy.cols;

	data = new T* [rows];   // makes deep copy, creating new arrays for matrix

	for (int i = 0; i<rows; i++) 
		data[i] = new T[cols];

	for (int i = 0; i<rows; i++) 
	{
		for (int j=0; j<cols; j++)
		{
			data[i][j] = copy.data[i][j];
		}
	}
}

template <class T>
Matrix2D<T> operator + ( Matrix2D<T> &lhs, Matrix2D<T> &rhs) 
{
	Matrix2D<T> tmp(lhs.rows,lhs.cols);       // creating a temp matrix
	for (int i=0; i< lhs.rows; i++)
	{
		for(int j=0; j < lhs.cols; j++)   
		{
			tmp.data[i][j] = lhs.data[i][j]+rhs.data[i][j];   // adding 2 elements and equalising the temp matrix that returns as result
		}
	}
	return tmp;
}

#endif
