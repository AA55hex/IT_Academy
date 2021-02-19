#include "gfx.h"
namespace render
{
gfx1::gfx1(canvas& text, canvas& k) : texture{text}, key{k} {}
void gfx1::set_uniforms(const uniforms& unf)
{
  max_width = unf.s0;
  max_height = unf.s1;
  v_line_x = unf.s3;
}
vertex gfx1::vertex_shader(const vertex& vtx)
{
  vertex result{vtx};

  result.x *= static_cast<double>(max_width - 1);
  result.y *= static_cast<double>(max_height - 1);

  result.u *= static_cast<double>(texture.get_width() - 1);
  result.v *= static_cast<double>(texture.get_height() - 1);

  return result;
}

rgb_color gfx1::fragment_shader(const vertex& vtx)
{
  coordinate text_pos{static_cast<size_t>(std::abs(vtx.u)),
                      static_cast<size_t>(std::abs(vtx.v))};
  coordinate key_pos{(text_pos.x * text_pos.x) % key.get_width(),
                     (text_pos.y * text_pos.y) % key.get_height()};
  rgb_color result{texture[text_pos]};
  rgb_color rgb_key{key[key_pos]};

  if (vtx.x <= static_cast<double>(v_line_x))
    {
      result.r ^= ((rgb_key.r * rgb_key.r) % 256);
      result.g ^= ((rgb_key.g * rgb_key.g) % 256);
      result.b ^= ((rgb_key.b * rgb_key.b) % 256);
    }

  //  out.r = static_cast<uint8_t>(vtx.r);
  //  out.g = static_cast<uint8_t>(vtx.g);
  //  out.b = static_cast<uint8_t>(vtx.b);

  //  const double dx = std::abs(mouse_x - vtx.x);
  //  const double dy = std::abs(mouse_y - vtx.y);

  //  const double delta = dx * dx + dy * dy;
  //  const double max_delta = radius * radius;

  //  if (delta > max_delta)
  //    {
  //      const double avg{(vtx.r + vtx.g + vtx.b) / 3.0};

  //      const double coef{delta / max_delta};
  //      const double reverse_coef{max_delta / delta};

  //      out.r = out.r ^ static_cast<uint8_t>(avg);
  //      out.g = out.g ^ static_cast<uint8_t>(avg);
  //      out.b = out.b ^ static_cast<uint8_t>(avg);
  //    }

  return result;
}
gfx1::~gfx1() {}
}  // namespace render
