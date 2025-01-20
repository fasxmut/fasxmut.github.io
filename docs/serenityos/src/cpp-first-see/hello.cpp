#include <LibCore/System.h>
#include <concepts>

int main()
{
	auto id = Core::System::fork();

	static_assert(std::same_as<decltype(id), AK::ErrorOr<int, AK::Error>>);
	AK::outln("id.is_error(): {}", id.is_error()?"true":"false");

	if (id.value() == 0)
	{
		AK::outln("I am child process.");
	}

	if (id.value() > 0)
	{
		AK::outln("I am parent process. My child process id is {}", id);
	}

	if (id.value() < 0)
	{
		AK::outln("Core::System::fork error");
	}
}

/*
id.is_error(): false
I am parent process. My child process id is {2472}
id.is_error(): false
I am child process.
*/
