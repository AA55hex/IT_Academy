#include "gfx.h"

namespace render
{
void gfx1::set_uniforms(const uniforms& unf)
{
  mouse_x = unf.f0;
  mouse_y = unf.f1;
  radius = unf.f2;
}
vertex gfx1::vertex_shader(const vertex& vtx)
{
  vertex result{vtx};
  return result;
}
rgb_color gfx1::fragment_shader(const vertex& vtx)
{
  rgb_color out{};
  out.r = static_cast<uint8_t>(vtx.r);
  out.g = static_cast<uint8_t>(vtx.g);
  out.b = static_cast<uint8_t>(vtx.b);

  double dx = std::abs(mouse_x - vtx.x);
  double dy = std::abs(mouse_y - vtx.y);
  if (dx * dx + dy * dy < radius * radius)
    {
      std::swap(out.r, out.g);
      std::swap(out.g, out.b);

      //      out.r = out.r ^ out.g;
      //      out.g = out.g & out.b;
      //      out.b = out.b | out.r;
    }

  return out;
}
gfx1::~gfx1() {}
}  // namespace render
