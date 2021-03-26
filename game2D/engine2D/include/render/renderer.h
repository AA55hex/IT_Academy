#include <glad/glad.h>

namespace render
{
class vertex_array;
class index_buffer;
class shader_program;

class renderer
{
 public:
  static void swap_buffers();
  static void draw(const vertex_array& vao, const index_buffer& vebo,
                   const shader_program& program, GLenum mode = GL_TRIANGLES);
  static void set_viewport(int x, int y, int width, int height);
  static void clear_color(float r, float g, float b, float a);
  static void clear();

  renderer() = delete;
};

}  // namespace render
