#include<iostream>
using namespace std;

class Fraction;
Fraction operator*(Fraction left, Fraction right); //Прототип функции умножить Прототип функции - это объявление функции

class Fraction
{
	int integer;		//целая часть
	int numerator;		//Числитель
	int denominator;	//Знаменатель

public:

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
	//										Constructors:
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "DefaultConstructor:" << this << endl;
	}
	Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "SingleConstructor:" << this << endl;
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "Constructor:\t" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator)
	{
		this->integer = integer;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "Constructor:\t" << this << endl;
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyCostructor:\t" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t" << this << endl;
	}

	//										Methods:
	Fraction& to_improper()
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}

	Fraction& to_proper()
	{
		integer = numerator / denominator;
		numerator %= denominator;
		return *this;
	}

	Fraction inverted()const
	{
		Fraction inverted = *this;
		inverted.to_improper();
		int buffer = inverted.numerator;
		inverted.numerator = inverted.denominator;
		inverted.denominator = buffer;
		return inverted;
	}

	Fraction inverted_numerator_minus()const
	{
		Fraction inverted = *this;
		if (inverted.numerator < 0 && inverted.integer != 0)inverted.numerator = inverted.numerator * -1;
		return inverted;
	}

	void print()const
	{
		if (integer)cout << integer;
		if (numerator)
		{
			if (integer)cout << "(";
			cout << numerator << "/" << denominator;
			if (integer)cout << ")";
		}
		else if (integer == 0) cout << 0;
		cout << endl;
	}

	//							Operators:

	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}

	Fraction& operator+=(Fraction other)
	{
		this->to_improper();
		other.to_improper();
		this->numerator = (this->numerator * other.get_denominator()) + (other.get_numerator() * this->denominator);
		this->denominator = this->denominator * other.get_denominator();
		this->to_proper();
		return *this;
	}

	Fraction& operator-=(Fraction other)
	{
		this->to_improper();
		other.to_improper();
		this->numerator = (this->numerator * other.get_denominator()) - (other.get_numerator() * this->denominator);
		this->denominator = this->denominator * other.get_denominator();
		this->to_proper();
		*this = this->inverted_numerator_minus();
		return *this;
	}

	Fraction& operator*=(const Fraction other)
	{
		/*this->to_improper();
		other.to_improper();
		this->numerator = this->get_numerator() * other.get_numerator();
		this->denominator = this->get_denominator() * other.get_denominator();
		return this->to_proper();*/
		return *this = *this * other;
	}

	Fraction& operator/=(Fraction other)
	{
		this->to_improper();
		other.to_improper();
		other = other.inverted();
		cout << this->get_denominator() << endl;
		this->numerator = this->numerator * other.get_numerator();
		this->denominator = this->denominator * other.get_denominator();
		return this->to_proper();
	}
	//											Increment/Decrement
	Fraction& operator++()
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

	Fraction& operator--()
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
};

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	/*Fraction result
		(
			left.get_numerator() * right.get_numerator(),
			left.get_denominator()*right.get_denominator()
		);*/
		/*result.set_numerator(left.get_numerator() * right.get_numerator());
		result.set_denominator(left.get_denominator() * right.get_denominator());*/
		//result.to_proper();
	return Fraction
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper();
}

Fraction operator/(const Fraction& left, const Fraction& right)
{
	/*left.to_improper();
	right.to_improper();*/
	/*return Fraction
	(
		left.to_improper().get_numerator() * right.get_denominator(),
		right.to_improper().get_numerator() * left.get_denominator()
	).to_proper();*/
	//--------------------------------------------------------------------
	return left * right.inverted();
}

Fraction operator+(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return Fraction
	(
		(left.get_numerator() * right.get_denominator()) + (right.get_numerator() * left.get_denominator()),
		left.get_denominator() * right.get_denominator()
	).to_proper();
}

Fraction operator-(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	Fraction result((left.get_numerator() * right.get_denominator()) - (right.get_numerator() * left.get_denominator()), left.get_denominator() * right.get_denominator());
	result.to_proper();
	result.inverted_numerator_minus();
	return result.inverted_numerator_minus();
}

//#define CONSTRUCTORS_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTORS_CHECK
	Fraction A;				//Default constructor
	A.print();

	double b = 3;
	Fraction B = 5;
	B.print();

	Fraction C(3, 4);
	C.print();

	Fraction D(4, 3, 4);
	D.print();
#endif // CONSTRUCTORS_CHECK

	int a = 2;
	int b = 3;
	int c = a * b;
	c++;

	Fraction A(2, 3, 4);
	Fraction B(3, 4, 5);
	A *= B;
	A.print();
	A = B++;
	A.print();
	B.print();
	/*Fraction C = A * B;
	C.print();

	C = A / B;
	C.print();

	C = A + B;
	C.print();

	C = A - B;
	C.print();

	A *= B;
	A.print();

	Fraction D(2, 3, 4);
	D /= B;
	D.print();

	A = D;
	A.print();

	A = Fraction(2, 3, 4);
	A += B;
	A.print();

	A = Fraction(2, 3, 4);
	A -= B;
	A.print();*/
}