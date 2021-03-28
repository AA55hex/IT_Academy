#pragma once
#include <render/frame_structures.h>
#include <memory>
#include <string>
#include "index_buffer.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
namespace render
{
class texture2D;
class shader_program;

class sprite2D
{
 public:
  sprite2D(std::shared_ptr<texture2D> texture, std::string subtexture,
           std::shared_ptr<shader_program> program);

  void render(const render_settings& settings);
  void render(const render_settings& settings,
              const frame_descriptor& f_discriptor);

  ~sprite2D();

  sprite2D(sprite2D&&);
  sprite2D& operator=(sprite2D&&);

  sprite2D(sprite2D&) = delete;
  sprite2D& operator=(sprite2D&) = delete;

  const frame_descriptor& get_current_frame() { return frame; }

 private:
  frame_descriptor frame;

  std::shared_ptr<shader_program> program;
  std::shared_ptr<texture2D> texture;

  vertex_array vba;
  vertex_buffer sprite_vbo;
  vertex_buffer texture_vbo;
  index_buffer vebo;
};
}  // namespace render
