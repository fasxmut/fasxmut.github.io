#include <SoundPlayer.h>
#include <iostream>
#include <future>

namespace app
{

class cookie
{
private:
	float incrementer = 0.0f;
public:
	virtual ~cookie()
	{
		std::cout << std::endl;
		std::cout << "cookie destructor is called" << std::endl;
	}
	cookie() = default;
public:
	float get()
	{
		incrementer += 0.1f;
		if (incrementer >= 100.0f)
			incrementer = -100.0f;
		return incrementer;
	}
	void reset()
	{
		std::cout << "cookie reset ... " << std::flush;
		incrementer = 0.0f;
	}
};

}

int main()
{
	auto cookie = app::cookie{};
	auto player = BSoundPlayer{
		"player",
		[] (
			void * cookie__,
			void * buffer__,
			std::size_t size__,
			const media_raw_audio_format & format__
		)
		{
			if (format__.format != media_raw_audio_format::B_AUDIO_FLOAT)
			{
				std::cout << "Unsupported by this program." << std::endl;
				return;
			}
			auto dimy = size__ / sizeof float{};
			auto dimx = format__.channel_count;

			auto buffer = reinterpret_cast<float *>(buffer__);
			auto cookie = reinterpret_cast<app::cookie *>(cookie__);

			cookie->reset();

			for (int j=0; j<dimy; ++j)
			{
				for (int i=0; i<dimx; ++i)
				{
					buffer[j*dimx + i] = cookie->get();
				}
			}
		},
		{},
		&cookie
	};
	player.Start();
	std::this_thread::sleep_for(std::chrono::minutes(1));
	//player.Stop();
}

