//[d0011_sycl_copy_method_cpp
/*`
sycl copy method
-
Posted on Mar 31, 2024
-
See [@https://sycl.tech]
-
[@https://cppfx.xyz/logs Logs Home]
-
d0011
*/

/*`
[h1 [role cyan sycl cpp copy method]]

sycl c++ copy method

```
sycl::queue q;
q.copy(src, dst, size);
```
*/

//`[*main program]

#include <sycl/sycl.hpp>
#include <iostream>

int main()
{
	constexpr int data_size = 11;
	sycl::queue q{sycl::gpu_selector_v};
	float * data = sycl::malloc_shared<float>(data_size, q);
	q.parallel_for(
		data_size,
		[=] (sycl::item<1> item)
		{
			sycl::id<1> id = item.get_id();
			data[id] = sycl::sqrt((float)id);
		}
	);
	q.wait();
	float * data_host = new float[data_size];
	q.copy(data, data_host, data_size);
	sycl::free(data, q);
	
	for (float & x: std::span{data_host, data_size})
		std::cout << x << ' ';
	std::cout << std::endl;
	
	delete [] data_host;
}

//]

