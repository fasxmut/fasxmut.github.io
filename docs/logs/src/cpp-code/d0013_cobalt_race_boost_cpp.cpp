//[d0013_cobalt_race_boost_cpp_cpp
/*`
cobalt::race boost c++
-
Posted on Apr 08, 2024
-
See [@https://www.boost.org/libs/cobalt]
-
[@https://cppfx.xyz/logs - Logs Home]
-
d0013
*/

/*`
[h1 [role cyan cobalt::race boost cpp]]

boost::cobalt::race c++

cobalt::race is a function that waits for one coroutine out of a set that is ready in a pseudo-random way, to avoid starvation.

The race function can be used to co_await one awaitable out of a set of them.

It can be called as a variadic function with multiple awaitable or as on a range of awaitables.

[h1 [role cyan Return an integral index]]

If all awaitables return void, the cobalt::race returns an integral index.

[h1 [role cyan Return a variant]]

If not all awaitables return void, the cobalt::race returns a variant: boost::variant2::variant.

[h1 [role cyan std::vector]]

All awaitables can be pushed into std::vector, accepted by cobalt::race.
*/

/*`
[h1 [role cyan Main Program]]
*/

#include <boost/cobalt.hpp>
#include <iostream>
#include <vector>

namespace cobalt = boost::cobalt;

class devil_cat
{
public:
	cobalt::promise<void> fizz() const
	{
		std::cout << "fizz" << std::endl;
		co_return;
	}
	cobalt::promise<float> buzz() const
	{
		std::cout << "buzz" << std::endl;
		co_return 2.345f;
	}
	cobalt::promise<void> bray() const
	{
		std::cout << "bray" << std::endl;
		co_await [] () -> cobalt::promise<void>
		{
			co_return;
		}();
	}
	cobalt::promise<float> roar() const
	{
		std::cout << "roar" << std::endl;
		co_await [] () -> cobalt::promise<float>
		{
			co_return 7.29f;
		}();
		co_return 1.7;
	}
};

cobalt::main co_main(int argc, char * argv[])
{
	std::cout << "------------------------------------------------------------\n";
	{
		auto cat = devil_cat{};
		for (int i=0; i<3; ++i)
		{
			// rr is variant, because not all awaitables co_return void.
			switch(
				auto rr = co_await cobalt::race(cat.fizz(), cat.buzz(), cat.bray(), cat.roar());
				rr.index()
			)
			{
			case 0:
				std::cout << ".fizz() is called\n";
				break;
			case 1:
				std::cout << ".buzz() is called, value: " << boost::variant2::get<1>(rr) << std::endl;
				break;
			case 2:
				std::cout << ".bray() is called." << std::endl;
				break;
			case 3:
				std::cout << ".roar() is called, value: " << boost::variant2::get<3>(rr) << std::endl;
			}
		}
	}
	std::cout << "------------------------------------------------------------\n";
	{
		auto cat = devil_cat{};
		for (int i=0; i<3; ++i)
		{
			// rr is integral index, because all awaitables co_return void.
			switch (auto rr = co_await cobalt::race(cat.fizz(), cat.bray()))
			{
			case 0:
				std::cout << ".fizz() is called" << std::endl;
				break;
			case 1:
				std::cout << ".bray() is called" << std::endl;
				break;
			}
		}
	}
	std::cout << "------------------------------------------------------------\n";
	{
		auto cat = devil_cat{};
		std::vector<cobalt::promise<void>> vector;
		vector.push_back(cat.fizz());
		vector.push_back(cat.bray());
		// std::vector is accepted
		int rr = co_await cobalt::race(vector);
		std::cout << "index: " << rr << std::endl;
	}
	std::cout << "------------------------------------------------------------\n";
}

/*`
[h2 One possible output]

[!teletype]
```
------------------------------------------------------------
fizz
buzz
bray
roar
.fizz() is called
fizz
buzz
bray
roar
.roar() is called, value: 1.7
fizz
buzz
bray
roar
.roar() is called, value: 1.7
------------------------------------------------------------
fizz
bray
.fizz() is called
fizz
bray
.bray() is called
fizz
bray
.bray() is called
------------------------------------------------------------
fizz
bray
index: 0
------------------------------------------------------------
```
*/

//]
