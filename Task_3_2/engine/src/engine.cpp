#include "engine.h"
#include <SDL_version.h>
#include <SDL.h>
#include <string_view>
#include <vector>
#include <array>
#include <algorithm>
typedef std::experimental::string_view string_view;


namespace task
{


class engine_imp final : public engine
{
public:
	virtual bool inicialize()
	{

		window = SDL_CreateWindow("game-3.1",
								  SDL_WINDOWPOS_CENTERED,
								  SDL_WINDOWPOS_CENTERED,
								  640,
								  480,
								  SDL_WINDOW_OPENGL);
		return true;
	}
	bool read_input(std::vector<key_event>& input)
	{
		using namespace std;
		const array<key_bind, 8> binds
		{
			{
				{ keyboard::w, "Up" },
				{ keyboard::a, "Left" },
				{ keyboard::s, "Down" },
				{ keyboard::d, "Right" },
				{ keyboard::lctrl, "Ctrl" },
				{ keyboard::space, "Space" },
				{ keyboard::escape, "Escape" },
				{ keyboard::enter, "Enter" }
			}
		};
		SDL_Event event{};
		bool updated{false};
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYUP:
			case SDL_KEYDOWN:
				if(event.key.repeat == 0)
				{
					const auto iterator = find_if(binds.begin(),
												  binds.end(),
												  [&](const key_bind& bind)
													{return static_cast<SDL_KeyCode>(bind.key) == event.key.keysym.sym;} );
					if(iterator != binds.end())
						input.push_back(key_event(*iterator,
												  static_cast<event_type>(event.type)));
					updated = true;
				}
				break;
			default:
				break;
			}
		}
		return updated;
	}
	SDL_Window* window;
	void uninitialize() final
	{
		SDL_DestroyWindow(window);
	}
	~engine_imp()
	{
		if(window != nullptr)
			uninitialize();
	}
};
engine::~engine(){}


engine* create_engine()
{
	engine* result = new engine_imp();
	return result;
}

}
