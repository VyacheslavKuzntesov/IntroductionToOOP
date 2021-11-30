#include<iostream>
#include<math.h>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

using namespace std;

class Fraction
{
	bool minus;
	int integer;
	int numerator;
	int denominator;
public:
	bool get_minus()const
	{
		return minus;
	}

	int get_integer()const
	{
		return integer;
	}

	int get_numerator()const
	{
		return numerator;
	}

	int get_denominator()const
	{
		return denominator;
	}

	void set_minus(bool minus)
	{
		this->minus = minus;
	}

	void set_integer(int integer)
	{
		this->integer = integer;
	}

	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}

	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}

	Fraction reduce()
	{
		if (this->numerator >= this->denominator)
		{
			for (;this->numerator > this->denominator;)
			{
				this->numerator - this->denominator;
				this->integer++;
			}
		}
		return this;
	}

	Fraction(bool minus = false, int integer = 0, int numerator = 0, int denominator = 1)
	{
		this->minus = minus;
		this->integer = integer;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "Constructor:\t" << this << endl;
	}

	Fraction(const Fraction& other)
	{
		this->minus = other.minus;
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyCostructor:\t" << this << endl;
	}

	~Fraction()
	{
		cout << "Destructor:\t" << this << endl;
	}

	Fraction& operator=(const Fraction& other)
	{
		this->minus = other.minus;
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:\t" << this << endl;

		return *this;
	}

	Fraction operator++()
	{
		integer++;
		return *this;
	}

	Fraction operator++(int)
	{
		Fraction old = *this;
		integer++;
		return old;
	}

	Fraction operator--()
	{
		integer--;
		return *this;
	}

	Fraction operator--(int)
	{
		Fraction old = *this;
		integer--;
		return old;
	}

	void print()const
	{
		cout << "Ваша дробь = " << integer << " (" << numerator << "/" << denominator << ")" << endl;
	}
};



Fraction operator+(const Fraction& left, const Fraction& right)
{
	Fraction result;
	result.set_integer(left.get_integer() + right.get_integer());
	result.set_numerator((right.get_denominator() * left.get_numerator()) + (left.get_denominator() * right.get_numerator()));
	result.set_denominator(left.get_denominator() * right.get_denominator());
	return result;
}

Fraction operator-(const Fraction& left, const Fraction& right)
{
	Fraction result;
	result.set_integer(left.get_integer() - right.get_integer());
	if (result.get_integer() < 0)
	{
		result.set_numerator((right.get_denominator() * left.get_numerator()) - ((left.get_denominator() + ((result.get_integer() * right.get_numerator()) * -1)) * right.get_numerator()));
		result.set_integer(0);
	}
	else
	{
		result.set_numerator((right.get_denominator() * left.get_numerator()) - (left.get_denominator() * right.get_numerator()));
	}
	result.set_denominator(left.get_denominator() * right.get_denominator());
	return result;
}

Fraction operator*(const Fraction& left, const Fraction& right)
{
	Fraction result;
	result.set_numerator((left.get_numerator() + (left.get_integer() * left.get_denominator())) * (right.get_numerator() + (right.get_integer() * right.get_denominator())));
	result.set_denominator(left.get_denominator() * right.get_denominator());
	result.set_integer(0);
	return result;
}

Fraction operator/(const Fraction& left, const Fraction& right)
{
	Fraction result;
	result.set_numerator((left.get_numerator() + (left.get_integer() * left.get_denominator())) * right.get_denominator());
	result.set_denominator(left.get_denominator() * (right.get_numerator() + (right.get_integer() * right.get_denominator())));
	result.set_integer(0);
	return result;
}

ostream& operator<<(ostream& os, const Fraction& obj)
{
	os << "Ваша дробь = " << obj.get_integer() << " (" << obj.get_numerator() << "/" << obj.get_denominator() << ")" << endl;
	return os;
}

void main()
{
	setlocale(LC_ALL, "");

	Fraction A(0, 1, 2, 3);
	Fraction B(0, 4, 5, 6);

	A.print();
	B.print();

	cout << A << endl;
	cout << B << endl;

	(A + B).print();
	(A - B).print();
	(A * B).print();
	(A / B).print();

	Fraction C;
	C = (A + B);
	C.print();
	C.reduce();
	cout << C << endl;
	/*cout << (A - B).reduce() << endl;
	cout << (A * B).reduce() << endl;
	cout << (A / B).reduce() << endl;*/

	A = B;
	A.print();
	B.print();

	++A;
	--B;

	A.print();
	B.print();
}