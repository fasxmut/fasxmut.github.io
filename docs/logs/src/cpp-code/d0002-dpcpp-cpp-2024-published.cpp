//[d0002_dpcpp_cpp_2024_published_cpp
/*`
Intel dpcpp/cpp c++ sycl compiler 2024.0.0 (2024.0.0.20231017) published
- Posted on Nov 20, 2023
- See [@https://sycl.tech SYCL.tech]
- [@https://cppfx.xyz/logs Logs Home]
- d0002
*/

/*`
[h1 [role cyan dpcpp/cpp compiler]]

dpcpp/cpp compiler is a c++ compiler targeting c++ sycl GPU, FPGA programming by intel.
*/

/*`
[h1 [role cyan dpcpp/cpp 2024 Install Guid for Kubuntu Linux]]

Install c++ sycl dpcpp/cpp compiler for kubuntu linux.

[h2 Download dpcpp/cpp]

Visit
[@https://www.intel.com/content/www/us/en/developer/tools/oneapi/dpc-compiler.html
https://www.intel.com/content/www/us/en/developer/tools/oneapi/dpc-compiler.html
]

choose which version you want to use.

For example, I am choosing ['intel dpc++/c++ for linux 2024.0.0 offline installer],
[*l_dpcpp-cpp-compiler_p_2024.0.0.49524_offline.sh] ,

then download it.

[h2 Install dpcpp/cpp]

Now execute the installer as root user:

[!teletype]
```
$ su
# bash ./l_dpcpp-cpp-compiler_p_2024.0.0.49524_offline.sh
```

The install prcocess will ask you some questions to continue while installing on terminal, just follow it.

Commonly, the packages will be installed to /opt/intel/oneapi/

[h2 Configure it]

Configure it with [*setvars.sh], that's so easy.

Find where is setvars.sh:

[!teletype]
```
$ cd /opt/intel/oneapi
$ $ find . -name setvars.sh
./setvars.sh
```

Get the full path of the setvars.sh :

[!teletype]
```
$ realpath ./setvars.sh
/opt/intel/oneapi/setvars.sh
```

Now source it, to bash, csh or ksh :

[!teletype]
```
$ su -
# echo ". /opt/intel/oneapi/setvars.sh" >> /etc/bash.bashrc
# echo ". /opt/intel/oneapi/setvars.sh" >> ~/.bashrc
$ exit
$ echo ". /opt/intel/oneapi/setvars.sh" >> ~/.bashrc

		# Please logout and login again.
```

Your dpcpp/cpp compiler for sycl is working :

[!teletype]
```
$ dpcpp 
$ dpcpp --version
$ dpcpp --help
$ which dpcpp
/opt/intel/oneapi/compiler/2024.0/bin/dpcpp
$ cd /opt/intel/oneapi/compiler/2024.0/bin/../include
$ ls
std  sycl  xpti
$ ls sycl
```
*/

/*`
[h1 [role cyan c++ sycl example code]]

[h2 the c++ code]
*/

#include <sycl/sycl.hpp>
#include <utxcpp/core.hpp>

int main()
try
{
	sycl::queue queue{sycl::gpu_selector_v};
	auto max_cu = queue.get_device().get_info<sycl::info::device::max_compute_units>();
	auto lm_size = queue.get_device().get_info<sycl::info::device::local_mem_size>();
	utx::print("max compute units:", max_cu, "local mem size:", lm_size);
}
catch (const sycl::exception & exc)
{
	utx::printe("--------------------------------------------------------------------------------");
	utx::printe("sycl::exception:", exc.what());
}

/*`
[h2 Compile it]
[!teletype]
```
$ dpcpp prog.cpp -std=c++23 -o prog
```
*/

/*`
[h1 [role cyan See Also]]

[@https://www.intel.com/content/www/us/en/developer/tools/oneapi/dpc-compiler.html Intel dpcpp/cpp download]

[@https://www.khronos.org/sycl Khronos sycl]

[@https://cppfx.xyz/utxcpp/utx_print.html utx::print]

[@https://cppfx.xyz/utxcpp/utx_printe.html utx::printe]

[@https://cppfx.xyz/utxcpp Utxcpp]
*/

//]
