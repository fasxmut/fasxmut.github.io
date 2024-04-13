//[d0014_cobalt_op_cpp_boost_cpp
/*`
cobalt op c++ boost
-
Posted on Apr 13, 2024
-
See [@https://www.boost.org/libs/cobalt]
-
[@https://cppfx.xyz/logs Logs Home]
-
d0014
*/
/*`
[h1 [role cyan cobalt op - cpp boost]]
*/

/*`
[h2 cobalt::use_op_t::as_default_on_t]

[h3 cobalt/example/echo_server.cpp]

```
using tcp_acceptor = cobalt::use_op_t::as_default_on_t<tcp::acceptor>;
using tcp_socket = cobalt::use_op_t::as_default_on_t<tcp::socket>;
```

====>

[h3 cobalt/include/boost/cobalt/op.hpp]

```
template <typename T>
using as_default_on_t =
	typename T::template rebind_executor<
		executor_with_default<typename T::executor_type>
	>::other;
```

[~(rebind_executor is used to replace existed executor with another executor of a type.)]

====>

[h3 cobalt/include/boost/cobalt/op.hpp]

```
// Adapts an executor to add the @c use_op_t completion token as the default.
template <typename InnerExecutor>
struct executor_with_default : InnerExecutor
{
	// Specify @c use_op_t as the default completion token type.
	typedef use_op_t default_completion_token_type;
	...
};
```

So I think [*[~boost::cobalt::use_op_t::as_default_on_t]] is used to replace executor in a type with another executor, to let that type support boost::cobalt coroutine, by adding [*cobalt::op] to the type; but I am not sure my inference.

*/

/*`
[h2 cobalt op - What is it?]

So after all, then, the key issue is, what is cobalt op?

[h2 the tiny example example/delay.cpp used cobalt op, Don't ignore it]

[h3 [role blue *-:) -------------------------------------------------------------------------------- (:-]]

I didn't quite understand what cobalt op is. I read the boost::cobalt example [*[~example/delay.cpp]] when I learned cobalt at the first time, because that example is very short and simple.

[!c++]
```
// Copyright (c) 2023 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/cobalt/main.hpp>
#include <boost/cobalt/op.hpp>
#include <boost/asio/steady_timer.hpp>

using namespace boost;

cobalt::main co_main(int argc, char * argv[]) // <1>
{
	asio::steady_timer tim{co_await asio::this_coro::executor, // <2>
		std::chrono::milliseconds(std::stoi(argv[1]))}; // <3>
	co_await tim.async_wait(cobalt::use_op); // <4>
	co_return 0; // <5>
}
                               
```

The [_cobalt::use_op] is passed, I did not quite care it at first time. But after I learned more, I found I have to understand it before using boost::asio networking with boost::cobalt.

[h3 [role blue *-:) -------------------------------------------------------------------------------- (:-]]

But the documentation of cobalt op I found is only helpful for me with one sentence:

[_An operation in cobalt is an awaitable wrapping an asio operation.]

([@https://www.boost.org/doc/libs/master/libs/cobalt/doc/html/index.html#cobalt_operation])

[h3 [role blue *-:) -------------------------------------------------------------------------------- (:-]]

Then I opened the source code [*[_boost/cobalt/op.hpp]], got [~boost::cobalt::op], [~boost::cobalt::use_op_t], [~boost::cobalt::use_op] .

[h3 [role blue -:) -------------------------------------------------------------------------------- (:- In retrospect, and comparison]]

* [role green [*asio::steady_timer async_wait ->]]

[!c++]
```
template<
typename WaitToken = default_completion_token_t<executor_type>>
auto async_wait(
	WaitToken && token = default_completion_token_t< executor_type >()
);
```

([@https://www.boost.org/doc/libs/1_84_0/doc/html/boost_asio/reference/basic_waitable_timer/async_wait.html])

[h4 token]

The completion token that will be used to produce a completion handler, which will be called when the timer expires. Potential completion tokens include [~use_future], [~use_awaitable], [~yield_context], or a function object with the correct completion signature.

* [role green [*use_future ->]]

A completion token object that causes an asynchronous operation to return a future.

```
constexpr use_future_t use_future;
```

([@https://www.boost.org/doc/libs/1_84_0/doc/html/boost_asio/reference/use_future.html])

eg.

```
std::future<std::size_t> my_future = my_socket.async_read_some(my_buffer, boost::asio::use_future);
```

* [role green [*use_awaitable ->]]

A completion token object that represents the currently executing coroutine.

```
constexpr use_awaitable_t use_awaitable;
```

([@https://www.boost.org/doc/libs/1_84_0/doc/html/boost_asio/reference/use_awaitable.html])

eg.

```
std::size_t n = co_await my_socket.async_read_some(buffer, use_awaitable);
```

??? = co_await ???(???, use_awaitable);

nice, -:)


* [role green [*use_op ->]]

If the completion [*token] is cobalt::use_op, what do you think what it is?
*/

/*`
[h1 [role cyan wait_op example]]

[@https://www.boost.org/doc/libs/1_84_0/libs/cobalt/doc/html/index.html#delay_op]
*/

/*`
[h1 [role cyan cobalt op examples]]

At last I write some cobalt op c++ small crappy examples.

[h2 asio socket]

boost::asio::ip::tcp::socket

[!c++]
```
#include <boost/cobalt.hpp>
#include <boost/asio.hpp>

namespace cobalt = boost::cobalt;
namespace asio = boost::asio;

using asio_socket = asio::ip::tcp::socket;
using cobalt_asio_socket = cobalt::use_op_t::as_default_on_t<asio_socket>;

cobalt::main co_main(int argc, char * argv[])
{
	asio::io_context io_context;
	asio_socket socket{io_context};
	cobalt_asio_socket socket2{io_context};
	auto * buff = new char[80];
	//co_await socket.async_read_some(asio::buffer(buff, 80)); // ERROR!
	auto value = co_await socket2.async_read_some(asio::buffer(buff, 80)); // OK!
	static_assert(std::integral<decltype(value)>);
	delete [] buff;
	co_return 0;
}
```

Returned [*value] is the data read in bytes.

[h2 asio acceptor]

boost::asio::ip::tcp::acceptor

[!c++]
```
#include <boost/cobalt.hpp>
#include <boost/asio.hpp>

namespace cobalt = boost::cobalt;
namespace asio = boost::asio;

using asio_socket = asio::ip::tcp::socket;
using co_socket = cobalt::use_op_t::as_default_on_t<asio_socket>;

using asio_acceptor = asio::ip::tcp::acceptor;
using co_acceptor = cobalt::use_op_t::as_default_on_t<asio_acceptor>;

cobalt::main co_main(int argc, char * argv[])
{
	asio::io_context io_context;
	asio_acceptor acceptor1{io_context};
	co_acceptor acceptor2{io_context};
	
	asio_socket socket1{io_context};
	co_socket socket2{io_context};
	
	//acceptor1.async_accept(socket1); // ERROR
	acceptor1.async_accept(socket2, [] (boost::system::error_code ec) {}); // OK
	//co_await acceptor1.async_accept(socket2, [] (boost::system::error_code ec) {}); // ERROR (.async_accept returns void)
	
	co_await acceptor2.async_accept(socket2); // OK, co_await returns void
	co_await acceptor2.async_accept(socket1); // OK, co_await returns void
	
	co_return 0;
}
```
*/

/*`
[h2 beast::tcp_stream]

boost::beast::tcp_stream

([@https://www.boost.org/libs/beast])

```
#include <boost/cobalt.hpp>
#include <boost/asio.hpp>
#include <boost/beast.hpp>

namespace cobalt = boost::cobalt;
namespace asio = boost::asio;
namespace beast = boost::beast;

using tcp_stream = beast::tcp_stream;
using co_tcp_stream = cobalt::use_op_t::as_default_on_t<tcp_stream>;

cobalt::main co_main(int argc, char * argv[])
{
	asio::io_context io_context;

	tcp_stream stream1{io_context};
	co_tcp_stream stream2{io_context};
	
	asio::ip::tcp::endpoint endpoint;
	
	stream1.async_connect(endpoint, [] (boost::system::error_code ec) {}); // OK
	//co_await stream1.async_connect(endpoint, [] (boost::system::error_code ec) {}); // ERROR (.async_connect returns void)
	//stream1.async_connect(endpoint); // ERROR
	
	co_await stream2.async_connect(endpoint); // OK, co_await returns void

	co_return 0;
}
```

*/

/*`
[h1 [role cyan End]]
*/

#include <boost/cobalt.hpp>
#include <iostream>

namespace cobalt = boost::cobalt;

cobalt::main co_main(int argc, char * argv[])
{
	std::cout << "Hello c++!" << std::endl;
	co_return 0;
}

//]

