#include <render.h>

namespace render
{
struct gfx1 : render::gfx_program
{
  gfx1(canvas& cnv);
  double mouse_x{};
  double mouse_y{};
  double radius{};
  void set_uniforms(const uniforms&) override;
  vertex vertex_shader(const vertex& v_in) override;
  rgb_color fragment_shader(const vertex& v_in) override;
  ~gfx1() override;

 private:
  canvas& owner;
};

}  // namespace render
