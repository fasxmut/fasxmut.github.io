//[d0004_std_views_zip_transpose_matrix_cpp

/*`
std::views::zip
- Posted on Jan 20, 2024
- See [@https://en.cppreference.com/w/cpp/ranges/zip_view std::views::zip]
- [@https://cppfx.xyz/logs Logs Home]
- d0004
*/

/*`
[h1 [role cyan std::views::zip]]

[@https://en.cppreference.com/w/cpp/ranges/zip_view std::ranges::zip_view, std::views::zip]

```
class std::ranges::zip_view;
```

std::ranges::zip_view is a range adaptor that takes one or more views, and produces a view whose ith element is a tuple-like value consisting of the ith elements of all views. The size of produced view is the minimum of sizes of all adapted views.

std::views::zip is a customization point object.

[h1 [role cyan c++ example]]

[h2 std::views::zip takes element from every ith element of every views]

```
auto tuples_in_one = std::view::zip(v1, v2, v3, v4, ...);
```

tuples_in_one is a view, and every element of tuples_in_one is a tuple, every element of the tuple is taken from ith element of every v1, v2, v3, ... .

[h2 Get every tuple]

```
for (auto tuple: tuples_in_one)
	...
```

[h2 Every tuple element reference]

```
for (using tuple = std::tuple<type1 &, type2 &, ...>; tuple tup: tuples_in_one)
{
	utx::print(std::get<0>(tup), std::get<1>(tup), ...);
}
```

[h2 Print]

```
std::cout << e1 << ' ' << e2 << ...;
```

[@https://cppfx.xyz/utxcpp/utx_print.html utx::print]

```
utx::print(e1, e2, ...);
```

*/

//`[h1 [role cyan Full c++ example (transpose matrix)]]

#include <utxcpp/core.hpp>
#include <ranges>
#include <vector>

int main()
{
	std::vector<std::vector<utx::ix32>> matrix =
		{
			{1,2,3,4},
			{5,6,7,8},
			{9,0,1,2},
			{3,4,5,6}
		};
	
	utx::print("matrix:", matrix);
	
	std::stringstream output;
	utx::print.set_ostream(output);
	
	for (
		using tuple = std::tuple<utx::ix32 &, utx::ix32 &, utx::ix32 &, utx::ix32 &>;
		tuple tup:
			std::views::zip(matrix[0], matrix[1], matrix[2], matrix[3])
	)
	{
		utx::print(tup);
	}
	
	utx::print.restore_ostream();
	
	utx::print("transposed matrix:\n", output.view());
}

/*`
[h1 [role cyan See Also]]

[@https://cppfx.xyz/utxcpp/utx_print.html utx::print]
*/

//]

