//[d0001_utx_print_nested_print_cpp

/*`
Print nested ranges, tuples
- Posted on Nov 20, 2023
- See [@https://cppfx.xyz/utxcpp/utx_print.html utx::print]
- [@https://cppfx.xyz/logs Logs Home]
- d0001
*/

/*`
[h1 [role cyan utx::print]]

After merging old utx::print and print-all, utx::print does not only can print single values and range/tuple values, but also can print nested ranges, tuples.
*/

/*`
[h1 [role cyan Header]]

utx::print is included in [*utxcpp/print.hpp], however, you are encouraged to use [*utxcpp/core.hpp], which let it more simple to use. I am using utxcpp/core.hpp too.
*/

/*`
[h1 [role cyan Print nested ranges, tuples with utx::print]]
*/

#include <utxcpp/core.hpp>
#include <vector>

int main()
{
	std::vector<utx::ix32> vector1{1,2,3};
	std::vector<utx::ix32> vector2{2,3,4,5};
	std::vector<utx::ix32> vector3{-3,4,7,-1,11,0,1,9};
	std::vector vector4{vector1, vector2, vector3};
	std::vector vector5{vector4, vector4};
	std::vector vector6{vector5, vector5};
	std::tuple tuple1{vector5, vector6};
	std::tuple tuple2{vector6, tuple1};
	std::tuple tuple3{vector6, tuple1, tuple2};
	std::vector vector7{tuple3, tuple3};

	utx::print("nested vectors and tuples=>", vector5, vector6, tuple2, tuple3, vector7);
}

/*`
[h1 [role cyan Output]]

output:

[!teletype]
```
nested vectors and tuples=>
1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9

1 2 3
2 3 4 5
-3 4 7 -1 11 0 1 9
```
*/

/*`
[h1 [role cyan See Also]]

[@https://cppfx.xyz/utxcpp/utx_ix32.html utx::ix32]

[@https://cppfx.xyz/utxcpp/utx_print.html utx::print]
*/

//]

