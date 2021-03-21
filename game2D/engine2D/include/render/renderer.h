#include <glad/glad.h>

namespace render
{
class renderer
{
 public:
  static void draw(GLenum mode, int count, const void* indices);
  static void set_viewport(int x, int y, int width, int height);
  static void clear_color(float r, float g, float b, float a);
  static void clear();

  renderer() = delete;
};

}  // namespace render
