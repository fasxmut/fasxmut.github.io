//[d0016_cobalt_main_entry_points_cpp
/*`
c++ boost::cobalt main entry points
-
Posted on Apr 29, 2024
-
See [@https://www.boost.org/libs/cobalt]
-
[@https://cppfx.xyz/logs Logs Home]
-
d0016
*/

/*`
[h1 [role cyan cpp boost::cobalt main entry points]]

c++ boost::cobalt main entry points, co_main or cobalt::run
*/

/*`
[h1 [role cyan co_main]]

[!c++]
```
cobalt::main co_main(int argc, char * argv[])
{
	std::cout << "Hello boost::cobalt!" << std::endl;
	co_return 0;
}
```
*/

/*`
[h1 [role cyan cobalt::run]]

main can not have coroutines;

The entry called by cobalt::run can have coroutines;

The co_main can have coroutines;
*/

#include <boost/cobalt.hpp>
#include <iostream>

namespace cobalt = boost::cobalt;

class main_class
{
public:
	virtual ~main_class() = default;
public:
	cobalt::task<int> start()
	{
		co_await this->func();
		co_await this->fn();
		co_return 0;
	}
public:
	void speak()
	{
		std::cout << "Hello!" << std::endl;
	}
public:
	cobalt::promise<void> func()
	{
		std::cout << "1\n";
		co_return;
	}
	cobalt::task<void> fn()	// cobalt::task is the lazy version of cobalt::promise
	{
		std::cout << "2\n";
		co_return;
	}
};

int main()	// This main is global symbol.
{
	main_class main;	// This main is local symbol.
	main.speak();	// main: call global symbol; ::main: call local symbol;
	return cobalt::run(main.start());
}

//]

