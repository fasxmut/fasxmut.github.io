//[d0012_boost_cobalt_fast_cpp
/*`
boost::cobalt Fast
-
Posted on Apr 07, 2024
-
See [@https://www.boost.org/libs/cobalt]
-
[@https://cppfx.xyz/logs Logs Home]
-
d0012
*/

/*`
[h1 [role cyan boost::cobalt Fast]]

boost::cobalt Fast (c++)

[h1 [role cyan Install boost (at least 1.84)]]

[h2 Build and install b2 build]

[@https://www.bfgroup.xyz/b2]

[h2 Build and install boost]

[@https://www.boost.org]
*/

/*`
[h1 [role cyan boost::cobalt Hello World]]

co_return

[!c++]
```
#include <boost/cobalt.hpp>
#include <iostream>

namespace cobalt = boost::cobalt;

cobalt::main co_main(int argc, char * argv[])
{
	std::cout << "Hello c++ cobalt!" << std::endl;
	co_return 0;
}
```
*/

/*`
[h2 Compile the code:]

[!teletype]
```
g++ hello-world.cpp -std=c++23 -lboost_cobalt -o hello_world
```

[h2 Build with b2 build]

```
lib boost-cobalt : : <name>boost_cobalt ;
exe hello-world
	:
		hello-world.cpp
	:
		<library>boost-cobalt
;
```
*/

/*`
[h1 [role cyan delay with timer]]

co_await

co_return

The co_main function defines an implicit main when used and is the easiest way to set up an environment to run asynchronous code.

[!teletype]
```
#include <boost/cobalt.hpp>
#include <boost/cobalt/op.hpp>
#include <boost/asio/steady_timer.hpp>
#include <iostream>

namespace cobalt = boost::cobalt;
namespace asio = boost::asio;

cobalt::main co_main(int argc, char * argv[])
{
	std::cout << "begin" << std::endl;
	asio::steady_timer timer{
		co_await asio::this_coro::executor,
		std::chrono::seconds(2)
	};
	co_await timer.async_wait(cobalt::use_op);
	std::cout << "end\n";
	co_return 0;
}
```
*/

/*`
[h1 [role cyan generator]]

co_yield
*/

#include <boost/cobalt.hpp>
#include <boost/cobalt/op.hpp>
#include <iostream>
#include <thread>
#include <chrono>

namespace cobalt = boost::cobalt;

class generator_box
{
public:
	cobalt::generator<int> operator()() const
	{
		int i = 0;
		while (true)
			co_yield i++;
	}
};

cobalt::main co_main(int argc, char * argv[])
{
	auto g = generator_box{}();
	BOOST_COBALT_FOR(auto x, g)
	{
		std::cout << "x => " << (int)x << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	co_return 0;
}

//]

