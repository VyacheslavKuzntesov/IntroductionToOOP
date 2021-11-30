#include"Fraction.h"

//#define CONSTRUCTORS_CHECK
#define ARITHMETICAL_OPERATOR_CHECK
//#define ISTREAM_OPERATOR_CHECK
//#define COMPARISON_OPERATORS_CHECK
//#define TYPE_CONVERSIONS_BASIC
//#define CONVERSION_FROM_OTHER_TYPES_TO_CLASS
//#define CONVERSION_FROM_CLASS_TO_OTHER_TYPES

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

#ifdef ARITHMETICAL_OPERATOR_CHECK
	int a = 2;
	int b = 3;
	int c = a * b;
	c++;

	Fraction A(2, 3, 4);
	Fraction B(3, 4, 5);
	A *= B;
	A.print();
	A = B++;
	/*A.print();
	B.print();*/
	cout << A << endl;
	cout << B << endl;
	Fraction C = A * B;
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

	
#endif // ARITHMETICAL_OPERATOR_CHECK

#ifdef ISTREAM_OPERATOR_CHECK
	Fraction A;
	cout << "Введите простую дробь: "; cin >> A;
	cout << A << endl;
#endif // ISTREAM_OPERATOR_CHECK

#ifdef COMPARISON_OPERATORS_CHECK
	Fraction A(2, 1, 2);
	Fraction B(2, 5, 10);

	cout << (A != B) << endl;
#endif // COMPARISON_OPERATORS_CHECK

#ifdef TYPE_CONVERSIONS_BASIC
	int a = 2;		//No conversion
	double b = 3;	//Conversion from less to more
	int c = b;		//Conversion from more to less without data loss
	int d = 8.3;	//Conversion from more to less with data loss
	int e = a + b;	//2 conversions in both directions
					//2 преобразования в обоих направлениях  
#endif // TYPE_CONVERSIONS_BASIC

#ifdef CONVERSION_FROM_OTHER_TYPES_TO_CLASS
	double a = 2;		//conversion From int to double (from less to more)
	cout << a << endl;
	Fraction A = (Fraction)5;		//Conversion from int to double (from less to more)
	cout << A << endl;
	Fraction B;
	cout << "\n------------------------------------------------------------\n";
	B = Fraction(8);				//operator= (CopyAssigment)
	cout << "\n------------------------------------------------------------\n";
	cout << B << endl;
	//Fraction C = 12;	//explicit-конструктор невозможно вызвать так
	Fraction C(12);
#endif // CONVERSION_FROM_OTHER_TYPES_TO_CLASS

#ifdef CONVERSION_FROM_CLASS_TO_OTHER_TYPES
	Fraction A(2, 3, 4);
	int a = (int)A;
	cout << a << endl;
	double b = (double)A;
	cout << b << endl;
	int c = int(A);
	cout << c << endl;
#endif // CONVERSION_FROM_CLASS_TO_OTHER_TYPES

	/*Fraction A(2, 5, 10);
	cout << A.reduce() << endl;
	cout << Fraction(840, 3600).reduce() << endl;*/
	//Fraction A = 2.76;
	//cout << A << endl;
}

/*
	ПРЕОБРАЗОВАНИЕ ТИПОВ
	В языке С++ существует явное и неявное преобразование типов
	Явное преобразование выполняет программист а неявное компилятор
	Для того что бы явно преобразовать значение в другой тип данных необходимо желаеммый тип данных написать в круглых скобках перед значением:
	(type)value; C-like notation
	type(value); Functional notation

	Как явные так и не явные преобразования типов существуют от меньшего к большему так и от большего к меньшим при чём последнее может привести к потере данных при этом компилятор выдает уведомление Warning С4244: ... possible loss of data
	Все операторы С++ приводят свои операнды к наибольшему типу что бы избежать потерю данных кроме оператора присвоить(=)
	Оператор присвоить всегда приводит значение справа к типу слева если типы преобразуются и неважно приведёт это к потери данных или нет


	ПРЕОБРАЗОВАНИЕ ТИПОВ В ООП
	В ООП выделяют два направления преобразования типов:
	1. Другие типы в наш тип;
	2. Из нашего типа в другие типы;
	Для преобразования других типов данных в объекты нашего класса в классе должен быть конструктор с одним параметром и оператор присваивания при чём второй без первого не работает
	Если мы хотим значения какогото типа преобразовавать в объекты нашего класса то нам в классе должен быть конструктор с одним параметром желаемого типа

	Для того что бы запретить неявное преобразование других типов в наш перед конструктором надо написать ключевое слово explicit(явный) позволяет явные но запрещает неявные
	explicit конструктор не возможно вызвать оператором присвоить


	ПРЕОБРАЗОВАНИЕ ОБЪЕКТОВ НАШЕГО КЛАССА В ДРУГИЕ ТИПЫ
	Для преобразования объектов нашего класса в другие типы данных в классе должны быть соответсвующие операторы преобразования(Type-cast operators)
	Операторы преобразования - это самые обычные методы имя которых состоит из ключевого слова operator и спецификатора существующего типа данных
	operatot type()
	{
		conversion
		...
	}

	В операторох преобразования никогда не указуют тип возвращаемого значения он и так понятен по имени метода.
	Операторы преобразования могут быть перегруженны только в нутри класса их невозможно перегрузить за классом

	Ключевое слово explicit так же применима к оператором преобразования так же как и в конструкторах оно запрещает неявные преобразования типов но оставляет возможность явного преобразования
*/