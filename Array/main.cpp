#include<iostream>
using namespace std;

class Array;

class Array
{

	int rows;
	int cols;
	int* array;

public:

	int get_rows()const
	{
		return rows;
	}

	int get_cols()const
	{
		return cols;
	}

	int* get_array()
	{
		return array;
	}

	const int& operator[](int i)const
	{
		return array[i];
	}

	int& operator[](int i)
	{
		return array[i];
	}

	const int* get_array()const
	{
		return array;
	}

	Array(int rows = 2, int cols = 2)
	{
		this->rows = rows;
		this->cols = cols;
		this->array = new int[rows * cols]{};
		cout << "DefConstruct:\t" << this << endl;
	}

	Array(const Array& other)
	{
		this->rows = other.get_rows();
		this->cols = other.get_cols();
		this->array = new int[rows * cols];
		for (int i = 0; i < rows * cols; i++)
		{
			this->array[i] = other.array[i];
		}
		cout << "CopyConstructor:" << this << endl;
	}

	~Array()
	{
		delete[] this->array;
		this->array = nullptr;
		this->rows = 0;
		this->cols = 0;
		cout << "Destructor:\t" << this << endl;
	}

	Array& operator=(const Array& other)
	{
		delete[] this->array;
		this->rows = other.get_rows();
		this->cols = other.get_cols();
		this->array = new int[this->rows * this->cols]{};
		for (int i = 0; i < (this->rows * this->cols); i++)
		{
			this->array[i] = other[i];
		}
		cout << "CopyAssigment:\t" << this << endl;
		return *this;
	}

	void print()const
	{
		for (int i = 0; i < rows * cols; i++)
		{
			cout << array[i] << "\t";
			if (i != 0 && (i + 1) % cols == 0)cout << endl;
		}
	}

	Array random()
	{
		for (int i = 0; i < rows * cols; i++)array[i] = rand() % (100 - 1) + 1;
		return *this;
	}
};

Array operator+ (const Array& left, const Array& right)
{
	Array result(left.get_rows(), left.get_cols());
	for (int i = 0; i < result.get_rows() * result.get_cols(); i++)result[i] = left[i] + right[i];
	return result;
}

Array operator- (const Array& left, const Array& right)
{
	Array result(left.get_rows(), left.get_cols());
	for (int i = 0; i < result.get_rows() * result.get_cols(); i++)result[i] = left[i] - right[i];
	return result;
}

Array operator* (const Array& left, const Array& right)
{
	Array result(left.get_rows(), left.get_cols());
	int counter = 0;
	int counter1 = 0;
	for (int i = 0; i < result.get_rows() * result.get_cols(); i++, counter++)
	{
		if (counter == result.get_cols())counter = 0;
		if (i % result.get_rows() == 0 && i != 0)counter1 += result.get_rows();
		for (int j = 0; j < result.get_cols(); j++)result[i] += left[j + counter1] * right[(j == 0 ? j + counter : (j * result.get_cols() + counter))];
	}
	return result;
}

void main()
{
	setlocale(LC_ALL, "");
	Array A(3, 3);
	A.random();
	Array B(3, 3);
	B.random();
	A.print();
	cout << endl;
	B.print();
	cout << endl;
	Array C;
	C = A * B;
	C.print();
}