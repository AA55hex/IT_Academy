#pragma once
#include <SDL2/SDL.h>
#include <experimental/string_view>
#include <vector>

namespace task
{
enum class event_type
{
  key_down = SDL_KEYDOWN,
  key_up = SDL_KEYUP
};

enum class keyboard
{
  w = SDLK_w,
  a = SDLK_a,
  s = SDLK_s,
  d = SDLK_d,
  lctrl = SDLK_LCTRL,
  space = SDLK_SPACE,
  escape = SDLK_ESCAPE,
  enter = SDLK_KP_ENTER
};

struct key_bind
{
  typedef std::experimental::string_view string_view;
  key_bind(keyboard keycode, string_view name) : key{keycode}, key_name{name} {}
  keyboard key;
  string_view key_name;
};

struct key_event
{
  typedef std::experimental::string_view string_view;

  key_event(key_bind bnd, event_type t) : bind{bnd}, type{t} {}
  key_bind bind;
  event_type type;
};

class iengine
{
 public:
  virtual bool inicialize() = 0;
  virtual bool read_input(std::vector<key_event> &input) = 0;
  virtual void uninitialize() = 0;
  virtual ~iengine();
};

class game
{
};

class lib_reloader
{
};

iengine *create_engine();
void destroy_engine(iengine *e);

}  // namespace task
