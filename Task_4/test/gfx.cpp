#include "gfx.h"
namespace render
{
gfx1::gfx1(canvas& cnv) : owner{cnv} {}
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

  const double dx = std::abs(mouse_x - vtx.x);
  const double dy = std::abs(mouse_y - vtx.y);

  const double delta = dx * dx + dy * dy;
  const double max_delta = radius * radius;

  //  if (delta < max_delta)
  //    {
  const double avg{(vtx.r + vtx.g + vtx.b) / 3.0};

  const double coef{delta / max_delta};
  const double reverse_coef{max_delta / delta};

  out.r *= /*reverse_coef*/ coef * avg / out.r;
  out.g *= /*reverse_coef*/ coef * avg / out.g;
  out.b *= /*reverse_coef*/ coef * avg / out.b;
  //    }

  return out;
}
gfx1::~gfx1() {}
}  // namespace render
