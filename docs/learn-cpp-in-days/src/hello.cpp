#include <iostream>

class one_class
{
private:
	int x;
public:
	one_class()	// constructor overloading
	{
		x = 3;
	}
	one_class(int x1)	// constructor overloading
	{
		x = x1;
	}
public:
	~one_class()
	{
		std::cout << "This is destructor." << std::endl;
	}
public:
	void set()	// method overloading
	{
		x = 2;
	}
	void set(int x1)	// method overloading
	{
		x = x1;
	}
	void set(float x1)	// method overloading
	{
		x = static_cast<int>(x1) + 10000;
	}
public:
	void print()
	{
		std::cout << "x is " << x << std::endl;
	}
};

int main()
{
	auto obj1 = one_class{};
	auto obj2 = one_class{23};

	obj1.print();
	obj2.print();

	obj1.set();
	obj1.print();

	obj2.set(3);
	obj2.print();

	obj2.set(3.2f);
	obj2.print();
}

x is 3
x is 23
x is 2
x is 3
x is 10003
This is destructor.
This is destructor.
