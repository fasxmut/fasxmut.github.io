//[d0005_cpp_uses_swift_cpp
/*`
cpp: c++ uses swift - Posted on Jan 30, 2024 - See [@https://www.swift.org/documentation/cxx-interop] - [@https://cppfx.xyz/logs Logs Home] - d0005

*/

/*`
[h1 [role cyan cpp: c++ uses swift language]]

cpp: c++ uses swift language
*/

/*`
[h1 [role cyan Install swift on KaOS Linux/kubuntu]]

# Download swift: [@https://www.swift.org]
# Extract swift to /swift/swift
# mkdir /swift/bin
# Add /swift/bin to environment variable PATH

# I don't want to expose swift shipped clang c++ compiler to mix with my own c++ compiler, so I add swift and swiftc to `/swift/bin/`:

`/swift/bin/swift`:

[!teletype]
```
exec /swift/swift/bin/swift $@
```

`/swift/bin/swiftc`:

[!teletype]
```
exec /swift/swift/bin/swiftc $@
```
*/

/*`
[h1 [role cyan Generate cpp header with exposed swift APIs]]

[*Generate c++ header]

[!teletype]
```
swiftc \
	-frontend -typecheck \
	swift-code.swift \
	-module-name code_box \
	-cxx-interoperability-mode=default \
	-emit-clang-header-path code_box.hpp
```
[*Use c++ header in c++]

[!c++]
```
// code_box.cpp
#include "code_box.hpp"

int main()
{
}
```

[*Compile c++ code]

[!teletype]
```
clang++ code_box.cpp -std=c++23 \
	-I /swift/swift/include \
	-I /swift/swift/lib/swift \
	-o code_box
```
*/

/*`
[h1 [role cyan c++ example]]
*/

#include <iostream>
//#include "code_box.hpp"

class swift_cpp_class
{
public:
	swift_cpp_class()
	{
		std::cout << "Hello c++!" << std::endl;
	}
};

int main()
{
	swift_cpp_class swift_cpp{};
}

/*`
[h1 [role cyan See Also]]

[@https://cppfx.xyz/utxcpp Utxcpp]
*/

//]

