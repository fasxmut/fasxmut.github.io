//[d0009_chaiscript_cpp
/*`
chaiscript cpp
-
Posted on Mar 27, 2024
-
See [@https://chaiscript.com]
-
[@https://cppfx.xyz/logs Logs Home]
-
d0009
*/

/*`
[h1 [role cyan chaiscript cpp]]

chaiscript c++

chaiscript is a scripting language for c++.
*/

/*`
[h1 [role cyan chaiscript class]]

Using chaiscript class

[_[~[*chai-class.chai]]]

[!teletype]
```
class fizz_box
{
	auto value
	
	def fizz_box(val)
	{
		this.value = val
	}
	def get()
	{
		return this.value
	}
}

class buzz_box
{
	auto value
	
	def buzz_box(val)
	{
		this.value = fizz_box(val)
	}
	
	def get()
	{
		return this.value.get()
	}
	
	def print()
	{
		print("value is " + to_string(this.get()))
	}
}

auto box = buzz_box(123)
box.print()
```

*/

//]

