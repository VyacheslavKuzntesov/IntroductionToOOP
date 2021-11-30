#pragma once
#include<iostream>
using namespace std;

class Fraction;
Fraction operator*(Fraction left, Fraction right); //Прототип функции умножить Прототип функции - это объявление функции
istream& operator>>(istream& is, Fraction& obj);
ostream& operator<<(ostream& os, const Fraction& obj);
bool operator<=(Fraction left, Fraction right);
bool operator>=(const Fraction& left, const Fraction& right);
bool operator<(Fraction left, Fraction right);
bool operator>(Fraction left, Fraction right);
bool operator!=(const Fraction& left, const Fraction& right);
bool operator==(Fraction left, Fraction right);
Fraction operator/(const Fraction& left, const Fraction& right);
Fraction operator*(Fraction left, Fraction right);
Fraction operator+(Fraction left, Fraction right);
Fraction operator-(Fraction left, Fraction right);

class Fraction
{
	int integer;		//целая часть
	int numerator;		//Числитель
	int denominator;	//Знаменатель

public:

	int get_integer()const;
	int get_numerator()const;
	int get_denominator()const;

	void set_integer(int integer);
	void set_numerator(int numerator);
	void set_denominator(int denominator);
	//										Constructors:
	Fraction();
	explicit Fraction(int integer);
	Fraction(double decimal);
	Fraction(int numerator, int denominator);
	Fraction(int integer, int numerator, int denominator);
	Fraction(const Fraction& other);
	~Fraction();

	//										Methods:
	Fraction& to_improper();
	Fraction& to_proper();
	Fraction inverted()const;
	Fraction inverted_numerator_minus()const;
	Fraction& reduce();

	void print()const;

	//							Operators:
	Fraction& operator=(const Fraction& other);
	Fraction& operator+=(Fraction other);
	Fraction& operator-=(Fraction other);
	Fraction& operator*=(const Fraction other);
	Fraction& operator/=(Fraction other);

	//											Increment/Decrement
	Fraction& operator++();
	Fraction operator++(int);
	Fraction& operator--();
	Fraction operator--(int);

	//							Type-cast operators:

	explicit operator int()const;
	explicit operator double()const;
};