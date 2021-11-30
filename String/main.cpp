#include<iostream>

using namespace std;
using std::cin;
using std::cout;
using std::endl;

class String;
String operator+(const String& left, const String& right);

class String
{

	int size;			//������ ������ � ������
	char* str;			//��������� �� ������ � ������������ ������

public:

	int get_size()const
	{
		return size;
	}

	const char* get_str()const
	{
		return str;
	}

	char* get_str()
	{
		return str;
	}

	//								Constructors:
	explicit String(int size = 80)
	{
		this->size = size;
		this->str = new char[size] {};
		cout << "DefConstruct:\t" << this << endl;
	}
	String(const char* str)
	{
		this->size = strlen(str) + 1;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = str[i];
		cout << "Constructor:\t" << this << endl;
	}
	String(const String& other)
	{
		this->size = other.get_size();
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "CopyConstructor:" << this << endl;
	}
	~String()
	{
		delete[] this->str;
		this->str = nullptr;
		this->size = 0;
		cout << "Destructor:\t" << this << endl;
	}
	//								Operators:

	String& operator=(const String& other)
	{
		if (this == &other)return *this;
		delete[] this->str;
		this->size = other.get_size();
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "CopyAssigment:\t" << this << endl;
		return *this;
	}

	const char& operator[](int i)const
	{
		return str[i];
	}

	char& operator[](int i)
	{
		return str[i];
	}

	String& operator+=(const String& right)
	{
		/*String result(this->size + right.get_size() - 1);
		for (int i = 0; i < this->size; i++)
			result[i] = this->str[i];
		for (int i = 0; i < right.get_size(); i++)
			result[i + this->get_size() - 1] = right[i];
		delete[] this->str;
		this->size += right.get_size() - 1;
		this->str = new char[size] {};
		*this = result;
		return *this;*/
		return *this = *this + right;
	}

	//								Methods:
	void print()const
	{
		cout << "Size:\t" << size << endl;
		cout << "Str:\t" << str << endl;
	}
};

String operator+(const String& left, const String& right)
{
	String result(left.get_size() + right.get_size() - 1);
	for (int i = 0; i < left.get_size(); i++)
		//result.get_str()[i] = left.get_str()[i];
		result[i] = left[i];
	for (int i = 0; i < right.get_size(); i++)
		//result.get_str()[i + left.get_size() - 1] = right.get_str()[i];
		result[i + left.get_size() - 1] = right[i];
	return result;
}

ostream& operator<<(ostream& os, const String& obj)
{
	return os << obj.get_str();
}

//#define CONSTRUCTORS_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTORS_CHECK
	String str(5);
	str.print();

	String str1 = "Hello";
	str1 = str1;
	//str1.print();
	cout << str1 << endl;

	String str2 = str1;
	cout << str2 << endl;

	String str3;
	str3 = str2;
	cout << str3 << endl;

	int a = 2;
	int b = 3;
	a = b;
	cout << a << endl;
#endif // CONSTRUCTORS_CHECK

	String str1 = "Hello ";
	String str2 = "World";
	String str3 = str1 + str2;	//������ �������� �������� +
	cout << str3 << endl;
	cout << operator+(str1, str2) << endl;	//����� ����� ��������� +
	str1 += str2;
	str1.print();
}

/*
	������������� ������������ ������ � �������
	���� ���� �� ���� ����������(����) ������ ��������� ���������� �� ������ ����� ��� ��������� �� ������� ������� � ������ ���� ��� ��� �� ����������� ����� ������ ����� �������� ������������ ������.
	���� ���� �� ���� ����������� �������� ������ ��� ������ ��������� new �� ��� ������������ ������ ����� �������� ������ ��� ������ ��������� new.
	���� ������������ �������� ������ ��� ������ new �� � ����� ������ ����������� ������ ���������� � ���������� delete.
	� ����� ������� ����������� ������ ���� ��������� ����������� ����������� � �������� ������������ � ��� ������ ������ ��������� �������� �����������(Deep cope) �� ���� �������� ������ ���������� new � ���������� ��� �������� ������������� ������� �������������� ������ ������� � ������ ����� �� ������� �� ����� ����������� ����������� � ������������ ��������� ������������ �����������(Shallow copy) ������ ������ ��������� ������ � ����������� ����������� ������ �������� ����� ������� �������������� ������� ������� � ����� ��������� �������� ����� ���������� ��� � ����� �������� ������������ ���� � ���� ������� ������������ ������.
	
	
*/