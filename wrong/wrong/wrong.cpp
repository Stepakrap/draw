#define _CRT_SECURE_NO_WARNING
#include <iostream>
#include <conio.h>
#include <string>
using namespace std;

class Except
{
private:
	int err;
	string txt[3] = { "Index out of range", "Wrong matrix sizes", "Divide by zero" };
public:
	static const int indexOutOfRangeException = 0;
	static const int wrongSizes = 1;
	static const int divideByZero = 2;
	Except(int _err) : err(_err) {};
	string text() { return txt[err]; };
	friend ostream& operator<< (ostream& stream, const Except ex);
};

ostream& operator<< (ostream& stream, Except ex)
{
	return stream << ex.text() << endl;;
}


class Vector
{
	int m_x;
	int m_y;
	int m_z;

public:
	
	Vector() : m_x(0), m_y(0), m_z(0)
	{
		cout << "Default constructor V " << this << endl;
	}

	Vector(int _x, int _y, int _z) : m_x(_x), m_y(_y), m_z(_z)
	{
		cout << "Initialize constructor V " << this << endl;
	}

	
	Vector(const Vector& other) : m_x(other.m_x), m_y(other.m_y), m_z(other.m_z)
	{
		cout << "Copy constructor V " << this << endl;
	}

	
	Vector operator+ (const Vector& other)
	{
		Vector tmp;

		tmp.m_x = m_x + other.m_x;
		tmp.m_y = m_y + other.m_y;
		tmp.m_z = m_z + other.m_z;

		return tmp;
	}
	

	Vector operator- (const Vector& other)
	{
		Vector tmp;

		tmp.m_x = m_x - other.m_x;
		tmp.m_y = m_y - other.m_y;
		tmp.m_z = m_z - other.m_z;

		return tmp;
	}

	
	Vector& operator= (const Vector& other)
	{
		if (this != &other)
		{
			cout << "Operator= V " << this << endl;
			m_x = other.m_x;
			m_y = other.m_y;
			m_z = other.m_z;
		}
		return *this;
	}

	int& operator[](int index)
	{
		if (index == 0)
			return m_x;
		else if (index == 1)
			return m_y;
		else if (index == 3)
			return m_z;
		else throw Except(Except::indexOutOfRangeException);
	}

	friend void printV(Vector other);

};

void printV(Vector other)
{
	cout << "(" << other.m_x << "," << other.m_y << "," << other.m_z << ")" << endl;
}


class Matrix
{
	int** arr;
	int m_column;
	int m_row;

public:
	
	Matrix() : arr(nullptr), m_column(0), m_row(0)
	{
		cout << "DEFAULT M " << this << endl;
	}

	
	Matrix(int _column, int _row) : m_column(_column), m_row(_row)
	{
		if (_column < 1 || _row < 1)
			throw Except(Except::indexOutOfRangeException);
		arr = new int* [m_row];
		for (int count = 0; count < m_row; count++)
		{
			arr[count] = new int[m_column];
		}

		for (int i = 0; i < m_row; i++)
		{
			for (int j = 0; j < m_column; j++)
				arr[i][j] = rand() % 10;
			cout << arr[i] << " ";
		}

		cout << "WRITING M " << this << endl;
	}

	Matrix(const Matrix& other) : m_column(other.m_column), m_row(other.m_row)
	{
		arr = new int* [m_row];
		for (int count = 0; count < m_row; count++)
		{
			arr[count] = new int[this->m_column];
		}

		for (int i = 0; i < m_row; i++)
			for (int j = 0; j < m_column; j++)
			{
				arr[i][j] = other.arr[i][j];
			}

		cout << "COPY M " << this << endl;
	}

	Matrix operator+(const Matrix& other)
	{
		Matrix tmp(m_row, other.m_column);

		if (m_row == other.m_row && m_column == other.m_column)
		{
			for (int i = 0; i < m_row; i++)
				for (int j = 0; j < m_column; j++)
				{
					tmp.arr[i][j] = arr[i][j] + other.arr[i][j];
				}
		}
		else throw Except(Except::wrongSizes);

		return tmp;
	}


	Matrix operator-(const Matrix& other)
	{
		Matrix tmp(m_row, other.m_column);

		if (m_row == other.m_row && m_column == other.m_column)
		{
			for (int i = 0; i < m_row; i++)
				for (int j = 0; j < m_column; j++)
				{
					tmp.arr[i][j] = arr[i][j] - other.arr[i][j];
				}
		}
		else throw Except(Except::wrongSizes);

		return tmp;
	}

	Matrix& operator= (const Matrix& other)
	{
		cout << "Operator= M " << this << endl;
		if (this != &other)
		{
			if (arr != nullptr)
			{
				for (int count = 0; count < m_row; count++)
					delete[] this->arr[count];
			}

			m_column = other.m_column;
			m_row = other.m_row;

			arr = new int* [this->m_row];
			for (int count = 0; count < this->m_row; count++)
			{
				arr[count] = new int[this->m_column];
			}

			for (int i = 0; i < m_row; i++)
				for (int j = 0; j < m_column; j++)
				{
					arr[i][j] = other.arr[i][j];
				}
		}
		return *this;
	}

	Matrix operator*(const Matrix& other)
	{
		if (m_row == other.m_column)
		{
		
			Matrix tmp(m_row, other.m_column);
			for (int i = 0; i < m_row; i++)
			{
				for (int j = 0; j < other.m_column; j++) 
				{
					int t = 0;
					for (int k = 0; k < m_column; k++)
					{
						t += arr[i][k] * other.arr[k][j];
					}

					tmp.arr[i][j] = t;
				}
			}
			return tmp;
		}
		else throw Except(Except::wrongSizes);
	}

	~Matrix()
	{
		for (int count = 0; count < m_row; count++)
			delete[] arr[count];
		delete[] arr;
	}

	friend void printM(Matrix other);

};

void printM(Matrix other)
{
	for (int i = 0; i < other.m_row; i++)
	{
		cout << "\n";
		for (int j = 0; j < other.m_column; j++)
			cout << other.arr[i][j] << " ";
	}
	cout << "\n";
}

void main()
{
	Vector a(9, 1, 1);
	Vector b(1, 0, 1);

	/* try
	{
		a[5] = 1;
	}
	catch (...)
	{
		cout << "Something goes wrong" << endl;
	} */

	try
	{
		Vector c = a + b;
		cout << endl;
		printV(c);
		cout << endl;
	}
	catch (Except & exception)
	{
		cout << exception << endl;
	}

	Matrix c(2, 2);
	Matrix d(2, 2);

	try
	{
		Matrix e = c - d;

		printM(c);
		cout << "-" << endl;
		printM(d);
		cout << "=" << endl;
		printM(e);
	}
	catch (Except & exception)
	{
		cout << exception << endl;
	}

	try
	{
		printM(c);

		Matrix e = c * d;
		printM(e);
	}
	catch (Except & exception)
	{
		cout << exception << endl;
	}
	catch (...)
	{
		cout << "Something goes wrong" << endl;
	}

	system("pause");
}