#include "render/renderer.h"

namespace render
{
void renderer::draw(GLenum mode, int count, const void* indices)
{
  glDrawElements(mode, count, GL_UNSIGNED_INT, indices);
}
void renderer::set_viewport(int x, int y, int width, int height)
{
  glViewport(x, y, width, height);
}
void renderer::clear_color(float r, float g, float b, float a)
{
  glClearColor(r, g, b, a);
}
void renderer::clear() { glClear(GL_COLOR_BUFFER_BIT); }
}  // namespace render
