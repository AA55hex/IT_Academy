#pragma once
#include <SDL.h>
#include <string>
namespace core
{
class window_manager
{
 public:
  window_manager(const std::string& title, int width_, int height_);
  void swap_buffers();
  ~window_manager();

  window_manager(window_manager&&);
  window_manager& operator=(window_manager&&);

  window_manager(window_manager&) = delete;
  window_manager& operator=(window_manager&) = delete;

 private:
  SDL_Window* window;
  SDL_GLContext gl_context;
  int width;
  int height;
};

}  // namespace core
