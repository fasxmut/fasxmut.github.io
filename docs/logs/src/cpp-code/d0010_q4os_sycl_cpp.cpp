//[d0010_q4os_sycl_cpp_cpp
/*`
q4os install sycl
-
Posted on Mar 31, 2024
-
See [@https://software.intel.com/dpcpp]
-
[@https://cppfx.xyz/logs Logs Home]
-
d0010
*/

/*`
[h1 [role cyan q4os kde linux install sycl cpp (dpcpp)]]
I will show you how to install dpcpp/cpp sycl c++ compiler on q4os kde linux.

[h1 [role cyan Find the dpcpp apt repo]]

[h2 Browse this url to find the link to get sycl:]

[@https://software.intel.com/dpcpp]

(click [_[*Get It Now]] at that page)

[h2 Select repo]

Select operating system: [*Linux]

Select distribution: [*APT Package Manager]

Then you will see how to add the intel software repo to your q4os linux. I am using q4os kde.

Jut follow them and add the repo.

[h1 [role cyan Install dpcpp/cpp]]

Install sycl c++ dpcpp/cpp.

[h2 Update]

```
apt update
```

[h2 Install]

```
apt install intel-oneapi-compiler-dpcpp-cpp
```

Before installing it, you can search it:

```
apt search intel-oneapi-compiler-dpcpp-cpp
```
*/

/*`
[h1 [role cyan Write sycl cpp program]]

Write sycl c++ pogram, using dpcpp/cpp

[h2 sycl-prog.cpp]
*/

#include <sycl/sycl.hpp>
#include <iostream>

int main()
{
	sycl::queue q{sycl::gpu_selector_v};
	
	float * data = sycl::malloc_shared<float>(37, q);
	
	q.parallel_for(
		37,
		[=] (sycl::item<1> item)
		{
			sycl::id id = item.get_id();
			data[id] = sycl::sqrt<float>(id);
		}
	);
	q.wait();
	for (int i=0; i<37; ++i)
		std::cout << data[i] << ' ';
	std::cout << std::endl;
	
	sycl::free(data, q);
}

/*`
[h2 Then you can compile and run sycl code]

You can use both dpcpp or icpx to compile the code:

[h3 Compile with dpcpp :]

```
dpcpp sycl-prog.cpp -std=c++23 -o sycl-prog
```

[h3 Compile with icpx :]

```
icpx -fsycl sycl-prog.cpp -std=c++23 -o sycl-prog
```
*/

/*`
[h1 [role cyan See Also]]

[@https://sycl.tech]

[@https://software.intel.com/dpcpp]

[@https://registry.khronos.org/SYCL sycl specification]

*/

//]

