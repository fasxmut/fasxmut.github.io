//[d0003_std_predicate_std_relation_cpp
/*`
std::predicate and std::relation - Posted on Dec 13, 2023 - See [@https://en.cppreference.com/w/cpp/concepts/relation std::relation] - [@https://cppfx.xyz/logs Logs Home] - d0003
*/

/*`
[h1 [role cyan std::predicate and std::relation]]

cpp/c++ standard concepts: std::predicate and std::relation


*/

/*`
[h1 [role cyan Headers]]
*/
#include <utxcpp/core.hpp>
#include <utxcpp/numeric.hpp>	// utx::iota
#include <concepts>
#include <algorithm>
#include <vector>

/*`
[h1 [role cyan std::predicate]]

std::predicate

[!c++]
```
template <typename fn_xt, typename ... args_list>
concept predicate =
	std::regular_invocable<fn_xt, args_list ...>
		&&
	boolean-testable<std::invoke_result_t<fn_xt, args_list ...>>
;
```

* 1. It requires fn_xt fn is callable with args ... .
* 2. It requires the calling result is boolean-testable, aka., returns true or false.

*/

/*`
[h2 code]

std::predicate c++ example
*/
class is_even_class
{
public:
	template <utx::integral_uct type_xtt>
	utx::mbx operator()(const type_xtt & value_xvv) const
	{
		return value_xvv % type_xtt{2} == 0;
	}
};

static_assert(std::predicate<is_even_class, utx::ux32>);
static_assert(! std::predicate<is_even_class, utx::fx64>);

template <typename type_xt, typename type_yt>
concept transform_fn = std::predicate<type_xt, type_yt> && utx::integral_uct<type_yt>;

template <utx::integral_uct type_xt>
class transform_class
{
public:
	template <transform_fn<type_xt> type_xtt>
	void operator()(const auto & input, auto & output, const type_xtt & fn) const
	{
		std::ranges::transform(
			input,
			std::back_inserter(output),
			fn
		);
	}
};

class run_op1
{
public:
	void operator()() const
	{
		utx::print("std::transform and std::predicate, is-even-test:");
		std::vector<utx::ix64> input(7);
		utx::iota(input, 11);
		utx::print("input:", input);
		std::vector<utx::mbx> output;
		transform_class<utx::ix64>{}(input, output, is_even_class{});
		utx::print("output:", output);
	}
};

/*`
[h1 [role cyan std::relation]]

std::relation

[!teletype]
```
template <typename r_xt, typename t_xt, typename u_xt>
concept relation =
	std::predicate<r_xt, t_xt, t_xt>
		&&
	std::predicate<r_xt, u_xt, u_xt>
		&&
	std::predicate<r_xt, t_xt, u_xt>
		&&
	std::predicate<r_xt, u_xt, t_xt>
;
```

* std::relation specifies that r_xt defines a binary relation over the set of expressions whose type and value category are those encoded by either t_xt or u_xt.
* Returns boolean-testable result.

*/

/*`
[h2 code]

std::relation c++ example
*/

class fizz_box
{
public:
	utx::ix32 value;
};
class buzz_box
{
public:
	utx::ix32 value;
};

template <typename type_xt>
concept fizz_buzz =
	utx::same_as<utx::remove_cvref_t<type_xt>, fizz_box>
		||
	utx::same_as<utx::remove_cvref_t<type_xt>, buzz_box>
;

class rlt_class
{
public:
	template <fizz_buzz fb_xtt, fizz_buzz fb_ytt>
	utx::mbx operator()(const fb_xtt & x, const fb_ytt & y) const
	{
		return x.value == y.value;
	}
};

static_assert(std::relation<rlt_class, fizz_box, buzz_box>);
static_assert(! std::relation<is_even_class, utx::ix32, utx::ix64>);

class rlt_u_class
{
public:
	template <fizz_buzz fb_xtt, fizz_buzz fb_ytt>
	void operator()(const fb_xtt & x, const fb_ytt & y, const std::relation<fb_xtt, fb_ytt> auto fn) const
	{
		utx::print("result:", fn(x, y));
	}
};

class run_op2
{
public:
	void operator()() const
	{
		auto rlt_u = rlt_u_class{};
		auto rlt = rlt_class{};
		rlt_u(fizz_box{7}, buzz_box{7}, rlt);
		rlt_u(fizz_box{-7}, fizz_box{7}, rlt);
	}
};

/*`
[h1 [role cyan main]]
*/

int main()
{
	run_op1{}();
	run_op2{}();
}

/*`
[h1 [role cyan See Also]]

[@https://cppfx.xyz/utxcpp/basic_concepts.html utxcpp basic concepts]

[@https://cppfx.xyz/utxcpp/utx_remove_cvref_t.html utx::remove_cvref_t]

[@https://cppfx.xyz/utxcpp/utx_mbx.html utx::mbx]

[@https://cppfx.xyz/utxcpp/class_types.html utxcpp class types]

[@https://cppfx.xyz/utxcpp/utx_ux32.html utx::ux32]

[@https://cppfx.xyz/utxcpp/utx_fx64.html utx::fx64]

[@https://cppfx.xyz/utxcpp/utx_ix64.html utx::ix64]

[@https://cppfx.xyz/utxcpp/utx_iota.html utx::iota]

[@https://cppfx.xyz/utxcpp/utx_ix32.html utx::ix32]

[@https://cppfx.xyz/utxcpp/utx_print.html utx::print]


*/

//]

