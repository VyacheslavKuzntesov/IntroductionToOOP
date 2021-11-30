#include<iostream>

using namespace std;
using std::cin;
using std::cout;
using std::endl;

class String;
String operator+(const String& left, const String& right);

class String
{

	int size;			//Размер строки в байтах
	char* str;			//Указатель на строку в динамической памяти

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
	explicit String(int size = 80) :size(size), str(new char[size] {})
	{
		//this->size = size;
		//this->str = new char[size] {};
		cout << "DefConstruct:\t" << this << endl;
	}
	String(const char* str) :size(strlen(str) + 1), str(new char[size] {})
	{
		//this->size = strlen(str) + 1;
		//this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = str[i];
		cout << "Constructor:\t" << this << endl;
	}
	String(const String& other) :size(other.get_size()), str(new char[size] {})
	{
		//this->size = other.get_size();
		//this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "CopyConstructor:" << this << endl;
	}
	String(String&& other) :size(other.size), str(other.str)
	{
		//this->size = other.size;
		//this->str = other.str;			//Копируем указатель на уже выделенную память,принадлежащую другому объекту
		other.str = nullptr;			//Зануляем указатель в другом объекте что бы десируктор не смог удалить память которая ему пренадлежит.
		other.size = 0;
		cout << "MoveConstructor:" << this << endl;
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

	String& operator=(String&& other)
	{
		if (this == &other)return *this;
		delete[] this->str;
		this->size = other.size;
		this->str = other.str;
		other.str = nullptr;
		other.size = 0;
		cout << "MoveAssigment:\t" << this << endl;
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

#define CONSTRUCTORS_CHECK
//#define OPERATOR_PLUS_CHECK
//#define CONSTRUCTOR_CALLING

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

#ifdef OPERATOR_PLUS_CHECK
	String str1 = "Hello ";
	String str2 = "World";
	cout << "n\----------------------------------------------------------------" << endl;
	String str3;
	str3 = str1 + str2;	//Неявно вызываем оператор +
	cout << "n\----------------------------------------------------------------" << endl;
	cout << str3 << endl;
	//cout << operator+(str1, str2) << endl;	//Явный вызов оператора +
	//str1 += str2;
	//str1.print();  
#endif // OPERATOR_PLUS_CHECK

#ifdef CONSTRUCTOR_CALLING
	String str1;
	cout << str1 << endl;
	String str2 = "Hello";
	cout << str2 << endl;
	String str3 = str2;
	cout << str3 << endl;

	String str4();			//Здесь Не создается никакой объект, эта строка не вызывает конструктор по умалчанию явным образом.Здесь обявляется функция str4 которая ничего
	//cout << str4<<endl;
	String str5{};//Явный вызов конструктора по умалчанию
	str5.print();
#endif // CONSTRUCTOR_CALLING


}

/*
	ИСПОЛЬЗОВАНИЕ ДИНАМИЧЕСКОЙ ПАМЯТИ В КЛАССАХ
	Если хотя бы одна переменная(член) класса являеться указателем то скорее всего она указывает на какуюта область в памяти если это так то конструктор этого класса будет выделять динамическую память.
	Если хотя бы один конструктор выделяет память при помощи оператора new то все конструкторы класса будут выделять память при помощи оператора new.
	Если конструкторы выделяют память при помощи new то в таком классе обязательно должен деструктор с оператором delete.
	В таких классах обязательно должны быть написанны конструктор копирования и оператор присваивания и эти методы должны выполнять глубокое копирование(Deep cope) то есть выделять память оператором new и копировать все элементы динамического массива принадлежащего одного объекта в другой обэкт по скольку не явные конструктор копирования и присваивания выполняют поверхносное копирования(Shallow copy) тоесть вместо выделение памяти и копирования содержимого просто копируют адрес массива принадлежащего другому объекту и тогда возникает ситуация когда существуют два и более объектов использующих одну и туже область динамической памяти.
	
	
	MOVE-МЕТОДЫ ИЛИ МЕТОДЫ ПЕРЕНОСА
	К move-методам относятся:

	1.Конструктор переноса - Вызывается неявно всякий раз когда создаваемый объект нужно сделать точной копией временного безымянного объекта. Временный безымянный объект создается всякий раз когда функция возвращает объект на место вызова по значению например оператор + возвращает объект result на место вызова по значению а не по ссылке по скольку result является локальным объектом и его нельзя вернуть по ссылке и result копируеться на место вызова конструктором копирования причём после этого result удаляеться из памяти на копирования объекта который сейчас будет удалён тратятся ресурсы оперативной памяти и процесорного времени что в свою очередь снижает производительность.
		А почему вместо копирования удаляемого объекта на место вызова не взять и перенести его содержимое не удалая его. Для этого в языке С++ и появились move-методы 
	
	Move-методы выполняют поверхносное копирования тоесть место того что бы выделять новую память под объект и копировать содержимое другого объекта выделеную память move-методы просто копируют адрес памяти принадлежащей другому объекту а такой же указатель в другом объекте зануляют для того что бы деструктор не смог удалить память.
	Конструктор переноса работает так как не должен работать конструктор переноса

	2.Оператор присваивания переноса - делает существующий объект точной копией временого безымяного объекта


	Move-методы принимают так называемую Reference to r-value: Class&&
	Move-методы впервые появились в стандарте C++11
	Move-методы повышают скорость работы классах которые используют динамическую память в классах не использующих динамическую память методы не имеют смысла

	СПОСОБЫ ВЫЗОВА И НАПИСАНИЯ КОНСТРУКТОРА
*/