#include <SDL.h>
#include <SDL_version.h>
#include <algorithm>
#include <array>
#include <string_view>
#include <vector>
#include "engine.h"

namespace engine_lib
{
const std::array<key_bind, 8> bind_list{{{keyboard::w, "Up"},
                                         {keyboard::a, "Left"},
                                         {keyboard::s, "Down"},
                                         {keyboard::d, "Right"},
                                         {keyboard::lctrl, "Ctrl"},
                                         {keyboard::space, "Space"},
                                         {keyboard::escape, "Escape"},
                                         {keyboard::enter, "Enter"}}};

int engine::read_input_list(std::vector<key_event>& input)
{
  using namespace std;
  SDL_Event event{};
  int update_count{0};
  while (SDL_PollEvent(&event))
    {
      switch (event.type)
        {
          case SDL_KEYUP:
          case SDL_KEYDOWN:
            if (event.key.repeat == 0)
              {
                const auto iterator =
                    find_if(bind_list.begin(), bind_list.end(),
                            [&](const key_bind& bind) {
                              return static_cast<SDL_KeyCode>(bind.key) ==
                                     event.key.keysym.sym;
                            });
                if (iterator != bind_list.end())
                  input.push_back(key_event(
                      *iterator, static_cast<event_type>(event.type)));
                update_count++;
              }
            break;
          default:
            break;
        }
    }

  return update_count;
}

int engine::read_input(key_event& input)
{
  using namespace std;

  SDL_Event event{};
  int event_status{SDL_PollEvent(&event)};
  bool capture_status{false};

  while (event_status && event.key.repeat == 0)
    {
      switch (event.type)
        {
          case SDL_KEYUP:
          case SDL_KEYDOWN:
            {
              const auto iterator =
                  find_if(bind_list.begin(), bind_list.end(),
                          [&](const key_bind& bind) {
                            return static_cast<SDL_KeyCode>(bind.key) ==
                                   event.key.keysym.sym;
                          });
              if (iterator != bind_list.end())
                {
                  input =
                      key_event(*iterator, static_cast<event_type>(event.type));
                  capture_status = true;
                }
              break;
            }
          default:
            break;
        }

      if (capture_status) break;

      event_status = SDL_PollEvent(&event);
    }

  return event_status;
}

void engine::uninitialize() { SDL_DestroyWindow(window); }

engine::~engine()
{
  if (window != nullptr) uninitialize();
}

}  // namespace engine_lib
