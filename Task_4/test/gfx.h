#include <render.h>

namespace render
{
struct gfx1 : render::gfx_program
{
  gfx1(canvas& text, canvas& k);
  void set_uniforms(const uniforms&) override;
  vertex vertex_shader(const vertex& v_in) override;
  rgb_color fragment_shader(const vertex& v_in) override;
  ~gfx1() override;

 private:
  canvas& texture;
  size_t v_line_x;
  canvas& key;
  size_t max_width;
  size_t max_height;
};

}  // namespace render
