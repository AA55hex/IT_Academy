#include <SDL2/SDL.h>
#include <iosfwd>
#include "glad/glad.h"
namespace gfx_engine
{
struct vertex
{
  float x{0};
  float y{0};
  float r{0};
  float g{0};
  float b{0};
};

struct triangle
{
  triangle() : vertexes{vertex{}, vertex{}, vertex{}} {}
  triangle(vertex v0, vertex v1, vertex v2) : vertexes{v0, v1, v2} {}
  vertex vertexes[3]{};
};

class engine
{
 public:
  engine();
  int inicialize();
  int render(const triangle&);
  int swap_buffers();
  ~engine();

 private:
  SDL_Window* window;
  SDL_GLContext gl_context;
  GLuint gl_program;
};

std::istream& operator>>(std::istream& in, vertex& v);

std::istream& operator>>(std::istream& in, triangle& t);

}  // namespace gfx_engine
