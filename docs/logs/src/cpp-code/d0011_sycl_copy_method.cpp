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
handler.copy(src, dst);
```
*/

//`[*main program]

#include <sycl/sycl.hpp>
#include <iostream>
#include <vector>
#include <numeric>
#include <span>

int main()
{
	sycl::queue queue{sycl::gpu_selector_v};
	std::vector<float> io_data(17);
	std::iota(io_data.begin(), io_data.end(), 1.0f);
	auto io_buffer = sycl::buffer<float, 1>{io_data.data(), sycl::range<1>{io_data.size()}};
	queue.submit(
		[&] (sycl::handler & handler)
		{
			auto io_accessor = sycl::accessor{io_buffer, handler, sycl::read_write};
			handler.parallel_for<class kn1>(
				sycl::range<1>{io_data.size()},
				[=] (sycl::item<1> item)
				{
					sycl::id<1> id = item.get_id();
					io_accessor[id] = sycl::cos<float>(io_accessor[id]);
				}
			);
		}
	);
	float * copied = new float[io_data.size()];
	queue.submit(
		[&] (sycl::handler & handler)
		{
			auto read = sycl::accessor{io_buffer, handler, sycl::read_only};
			handler.copy(read, copied);
		}
	);
	queue.wait();

	for (const auto & x: std::span{copied, copied+io_data.size()})
		std::cout << x << ' ';
	std::cout << std::endl;

	delete [] copied;
}

//]



