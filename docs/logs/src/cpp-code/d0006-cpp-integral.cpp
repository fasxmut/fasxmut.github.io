//[d0006_cpp_integral
/*`
cpp: c++ integral type - Posted on Jan 31, 2024 - See [@https://en.cppreference.com/w/cpp/concepts/integral] - [@https://cppfx.xyz/logs Logs Home] - d0006
*/

/*`
[h1 [role cyan cpp integral type: std::integral]]

[*c++ integral type:]

bool, char, char8_t, char16_t, char32_t, wchar_t, short, int, long, long long

signed

unsigned

[*std::integral:]

[!c++]
```
template< class T >
concept integral = std::is_integral_v<T>; // (since C++20)
```

The concept integral<T> is satisfied if and only if T is an integral type.
*/

/*`
[h1 [role cyan c++ example]]
*/

#include <concepts>	// std::integral
#include <iostream>

int main()
{
	std::integral auto x = 9;
	std::cout << x << std::endl;
}

//]

