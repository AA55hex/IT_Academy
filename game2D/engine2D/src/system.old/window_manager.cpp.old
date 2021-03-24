#include "system/window_manager.h"
#include <iostream>
#include "glad/glad.h"
namespace core
{
window_manager::window_manager(const std::string& title, int width_,
                               int height_)
    : width{width_}, height{height_}
{
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

  window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, width, height,
                            SDL_WINDOW_OPENGL);

  if (window == nullptr)
    {
      const char* err_log{SDL_GetError()};
      std::cerr << "window_manager::Failed to create window: " << err_log;
    }

  gl_context = SDL_GL_CreateContext(window);
  SDL_GL_MakeCurrent(window, gl_context);

  if (!gladLoadGLES2Loader(SDL_GL_GetProcAddress))
    {
      std::cerr << "window_manager: Failed to load Glad";
    }
}

void window_manager::swap_buffers() { SDL_GL_SwapWindow(window); }
window_manager::~window_manager()
{
  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(window);
}

window_manager::window_manager(window_manager&& mgr)
{
  window = mgr.window;
  gl_context = mgr.gl_context;
  width = mgr.width;
  height = mgr.height;

  mgr.window = nullptr;
  mgr.gl_context = nullptr;
}
window_manager& window_manager::operator=(window_manager&& mgr)
{
  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(window);

  window = mgr.window;
  gl_context = mgr.gl_context;
  width = mgr.width;
  height = mgr.height;

  mgr.window = nullptr;
  mgr.gl_context = nullptr;

  return *this;
}
}  // namespace core
