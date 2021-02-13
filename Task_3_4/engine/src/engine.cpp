#include "engine.h"
#include <SDL.h>
#include <SDL_version.h>
#include <algorithm>
#include <array>
#include <string_view>
#include <vector>
typedef std::experimental::string_view string_view;

namespace task
{
class engine final : public iengine
{
 public:
  virtual bool inicialize()
  {
	window =
		SDL_CreateWindow("game-3.1", SDL_WINDOWPOS_CENTERED,
						 SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
	return true;
  }
  bool read_input(std::vector<key_event>& input)
  {
	using namespace std;
	const array<key_bind, 8> binds{{{keyboard::w, "Up"},
									{keyboard::a, "Left"},
									{keyboard::s, "Down"},
									{keyboard::d, "Right"},
									{keyboard::lctrl, "Ctrl"},
									{keyboard::space, "Space"},
									{keyboard::escape, "Escape"},
									{keyboard::enter, "Enter"}}};
	SDL_Event event{};
	bool updated{false};
	while (SDL_PollEvent(&event))
	  {
		switch (event.type)
		  {
			case SDL_KEYUP:
			case SDL_KEYDOWN:
			  if (event.key.repeat == 0)
				{
				  const auto iterator = find_if(
					  binds.begin(), binds.end(), [&](const key_bind& bind) {
						return static_cast<SDL_KeyCode>(bind.key) ==
							   event.key.keysym.sym;
					  });
				  if (iterator != binds.end())
					input.push_back(key_event(
						*iterator, static_cast<event_type>(event.type)));
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
  void uninitialize() final { SDL_DestroyWindow(window); }
  ~engine()
  {
	if (window != nullptr) uninitialize();
  }
};
iengine::~iengine() {}

iengine* create_engine()
{
  iengine* result = new engine();
  return result;
}

}  // namespace task
