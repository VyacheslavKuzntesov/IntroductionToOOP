#include"Fraction.h"
int Fraction::get_integer()const
{
	return integer;
}
int Fraction::get_numerator()const
{
	return numerator;
}
int Fraction::get_denominator()const
{
	return denominator;
}

void Fraction::set_integer(int integer)
{
	this->integer = integer;
}
void Fraction::set_numerator(int numerator)
{
	this->numerator = numerator;
}
void Fraction::set_denominator(int denominator)
{
	if (denominator == 0)denominator = 1;
	this->denominator = denominator;
}
//										Constructors:
Fraction::Fraction()
{
	this->integer = 0;
	this->numerator = 0;
	this->denominator = 1;
	cout << "DefaultConstructor:" << this << endl;
}
Fraction::Fraction(int integer)
{
	this->integer = integer;
	this->numerator = 0;
	this->denominator = 1;
	cout << "SingleConstructor:" << this << endl;
}
Fraction::Fraction(double decimal) //number)
{
	/*this->integer = (int)number;
	int i = 1;
	for (i; ((number * pow(10, i))-(int)(number*pow(10,i)))!=0; i++);
	this->numerator = (number - (int)number) * pow(10, i);
	this->denominator = pow(10, i);
	this->reduce();*/

	this->integer = decimal;
	decimal -= integer;
	this->denominator = 1e+9;
	numerator = (decimal + 1e-10) * denominator;
	reduce();
}
Fraction::Fraction(int numerator, int denominator)
{
	this->integer = 0;
	this->numerator = numerator;
	set_denominator(denominator);
	cout << "Constructor:\t" << this << endl;
}
Fraction::Fraction(int integer, int numerator, int denominator)
{
	this->integer = integer;
	this->numerator = numerator;
	set_denominator(denominator);
	cout << "Constructor:\t" << this << endl;
}
Fraction::Fraction(const Fraction& other)
{
	this->integer = other.integer;
	this->numerator = other.numerator;
	this->denominator = other.denominator;
	cout << "CopyCostructor:\t" << this << endl;
}
Fraction::~Fraction()
{
	cout << "Destructor:\t" << this << endl;
}

//										Methods:
Fraction& Fraction::to_improper()
{
	numerator += integer * denominator;
	integer = 0;
	return *this;
}

Fraction& Fraction::to_proper()
{
	integer = numerator / denominator;
	numerator %= denominator;
	return *this;
}

Fraction Fraction::inverted()const
{
	Fraction inverted = *this;
	inverted.to_improper();
	int buffer = inverted.numerator;
	inverted.numerator = inverted.denominator;
	inverted.denominator = buffer;
	return inverted;
}

Fraction Fraction::inverted_numerator_minus()const
{
	Fraction inverted = *this;
	if (inverted.numerator < 0 && inverted.integer != 0)inverted.numerator = inverted.numerator * -1;
	return inverted;
}

Fraction& Fraction::reduce()
{
	int more, less, rest;
	if (numerator > denominator)
	{
		more = numerator;
		less = denominator;
	}
	else
	{
		more = denominator;
		less = numerator;
	}
	do
	{
		rest = more % less;
		more = less;
		less = rest;
	} while (rest);
	int GCD = more;
	numerator /= GCD;
	denominator /= GCD;
	return *this;
	//GCD - Greatest Common Divisor (Ќаибольший общий делитель)
}

void Fraction::print()const
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

Fraction& Fraction::operator=(const Fraction& other)
{
	this->integer = other.integer;
	this->numerator = other.numerator;
	this->denominator = other.denominator;
	cout << "CopyAssignment:\t" << this << endl;
	return *this;
}

Fraction& Fraction::operator+=(Fraction other)
{
	this->to_improper();
	other.to_improper();
	this->numerator = (this->numerator * other.get_denominator()) + (other.get_numerator() * this->denominator);
	this->denominator = this->denominator * other.get_denominator();
	this->to_proper();
	return *this;
}

Fraction& Fraction::operator-=(Fraction other)
{
	this->to_improper();
	other.to_improper();
	this->numerator = (this->numerator * other.get_denominator()) - (other.get_numerator() * this->denominator);
	this->denominator = this->denominator * other.get_denominator();
	this->to_proper();
	*this = this->inverted_numerator_minus();
	return *this;
}

Fraction& Fraction::operator*=(const Fraction other)
{
	/*this->to_improper();
	other.to_improper();
	this->numerator = this->get_numerator() * other.get_numerator();
	this->denominator = this->get_denominator() * other.get_denominator();
	return this->to_proper();*/
	return *this = *this * other;
}

Fraction& Fraction::operator/=(Fraction other)
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
Fraction& Fraction::operator++()
{
	integer++;
	return *this;
}

Fraction Fraction::operator++(int)
{
	Fraction old = *this;
	integer++;
	return old;
}

Fraction& Fraction::operator--()
{
	integer--;
	return *this;
}

Fraction Fraction::operator--(int)
{
	Fraction old = *this;
	integer--;
	return old;
}

//							Type-cast operators:

Fraction::operator int()const
{
	return integer;
}

Fraction::operator double()const
{
	//double result = integer+((double)numerator/denominator);

	//double result = numerator;
	//result /= denominator;
	//result += integer;
	//return result;

	return integer + (double)numerator / denominator;
}

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

bool operator==(Fraction left, Fraction right)
{
	/*left.to_improper();
	right.to_improper();*/
	return (left.to_improper().get_numerator() * right.get_denominator()) == (right.to_improper().get_numerator() * left.get_denominator());
	/*if ((left.get_numerator()*right.get_denominator()) == (right.get_numerator()*left.get_denominator()))
	{
		return true;
	}
	else return false;*/
}

bool operator!=(const Fraction& left, const Fraction& right)
{
	/*left.to_improper();
	right.to_improper();*/
	return !(left == right);
	//return (left.to_improper().get_numerator() * right.get_denominator()) != (right.to_improper().get_numerator() * left.get_denominator());
	/*if ((left.get_numerator() * right.get_denominator()) != (right.get_numerator() * left.get_denominator()))
	{
		return true;
	}
	else return false;*/
}

bool operator>(Fraction left, Fraction right)
{
	/*left.to_improper();
	right.to_improper();*/
	return (left.to_improper().get_numerator() * right.get_denominator()) > (right.to_improper().get_numerator() * left.get_denominator());
	/*if ((left.get_numerator() * right.get_denominator()) < (right.get_numerator() * left.get_denominator()))
	{
		return true;
	}
	else return false;*/
}

bool operator<(Fraction left, Fraction right)
{
	/*left.to_improper();
	right.to_improper();*/
	return (left.to_improper().get_numerator() * right.get_denominator()) < (right.to_improper().get_numerator() * left.get_denominator());
	/*if ((left.get_numerator() * right.get_denominator()) > (right.get_numerator() * left.get_denominator()))
	{
		return true;
	}
	else return false;*/
}

bool operator>=(const Fraction& left, const Fraction& right)
{
	/*left.to_improper();
	right.to_improper();*/
	return !(left < right);
	//return left > right || left == right;
	//return (left.to_improper().get_numerator() * right.get_denominator()) >= (right.to_improper().get_numerator() * left.get_denominator());
	/*if ((left.get_numerator() * right.get_denominator()) >= (right.get_numerator() * left.get_denominator()))
	{
		return true;
	}
	else return false;*/
}

bool operator<=(Fraction left, Fraction right)
{
	/*left.to_improper();
	right.to_improper();*/
	return !(left > right);
	//return left < right || left == right;
	//return (left.to_improper().get_numerator() * right.get_denominator()) <= (right.to_improper().get_numerator() * left.get_denominator());
	/*if ((left.get_numerator() * right.get_denominator()) <= (right.get_numerator() * left.get_denominator()))
	{
		return true;
	}
	else return false;*/
}

ostream& operator<<(ostream& os, const Fraction& obj)
{
	if (obj.get_integer())os << obj.get_integer();
	if (obj.get_numerator())
	{
		if (obj.get_integer())os << "(";
		os << obj.get_numerator() << "/" << obj.get_denominator();
		if (obj.get_integer())os << ")";
	}
	else if (obj.get_integer() == 0) os << 0;
	return os;
}

istream& operator>>(istream& is, Fraction& obj)
{
	/*int integer;
	int numerator;
	int denominator;
	is >> integer >> numerator >> denominator;
	obj.set_integer(integer);
	obj.set_numerator(numerator);
	obj.set_denominator(denominator);*/

	const int SIZE = 80;
	char buffer[SIZE] = {};
	//is >> buffer;
	is.getline(buffer, SIZE);
	//5
	//1/2
	//2(3/4)
	//2 3/4
	char delimiters[] = "() /"; // –азделители по которым мы будем делить строку
	char* number[5];		//¬ это массиве будут хранитьс€ указатели на числа в buffer
	int n = 0;		//—четчик прочитаных из строки чисел
	for (char* pch = strtok(buffer, delimiters); pch; pch = strtok(NULL, delimiters))
	{
		number[n++] = pch;
	}
	switch (n)
	{
		// int atoi(char* str) - преобразует строкув целое число
	case 1:obj.set_integer(atoi(number[0])); break;
	case 2:
		obj.set_numerator(atoi(number[0]));
		obj.set_denominator(atoi(number[1]));
		break;
	case 3:
		obj.set_integer(atoi(number[0]));
		obj.set_numerator(atoi(number[1]));
		obj.set_denominator(atoi(number[2]));
	}
	return is;
}
