#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class str
{
private:
	char* arr = new char;

public:

	str()
	{
		(char)realloc(arr, 1);
		int i = 0;
		for (i; i < 1; i++)
		{
			arr[i] = (char)rand() % 128;
		}

		arr[i] = '\0';
		cout << "Default constructor " << this << endl;
	}


	str(int num)
	{
		(char)realloc(arr, num + 1);
		int i = 0;
		for (i; i < num; i++)
		{
			arr[i] = (char)rand() % 128;
		}

		arr[i] = '\0';
		cout << "Num constructor " << this << endl;
	}

	str(const char* other)
	{
		int i = 0;
		(char)realloc(arr, strlen(other) + 1);

		memcpy(arr, other, strlen(other) * sizeof(char));
		arr[strlen(other)] = '\0';

		cout << "\" \" constructor " << this << endl;
	}


	str(const str& other)
	{
		arr = other.arr;
		cout << "Copy constructor " << this << endl;
	}

	bool operator==(const str& other)
	{
		if (arr == other.arr)
			return true;
		else return false;
	}

	bool operator>(const str& other) const
	{
		if (strlen(arr) > strlen(other.arr))
			return true;
		else false;
	}

	bool operator<(const str& other) const
	{
		if (strlen(arr) < strlen(other.arr))
			return true;
		else false;
	}


	str& operator= (const str& other)
	{
		if (this != &other)
		{
			arr = other.arr;
		}
		return *this;
	}

	str operator+(const str& c)
	{
		str tmp;
		tmp = strcat(arr, c.arr);

		return tmp;
	}

	char& operator[](int index) 
	{
		if (index < 0 || index >= strlen(arr)) {
			cout << "Incorrect number" << endl;
		}
		else return arr[index];
	}


	~str()
	{
		delete[] arr;
	}

	friend ostream& operator<<(ostream& stream, const str& _str);
	friend istream& operator>>(istream& stream, str& _str);
};

ostream& operator<<(ostream& stream, const str& _str)
{
	stream << _str.arr << endl;
	return stream;
}

istream& operator>>(istream& stream, str& _str)
{
	char ss[255];
	stream.getline(ss, 255);
	_str = ss;
	return stream;
}

int main()
{

	str a("100");
	str b(5);
	str c;
	cout << b << endl;

	a = c;

	if (a == b) cout << "yes" << endl;
	else cout << "no" << endl;

	cout << b[1] << endl;

	cout << "all done" << endl;
	system("pause");
}