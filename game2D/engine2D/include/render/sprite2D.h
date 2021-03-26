#pragma once
#include <glad/glad.h>
#include <glm/vec2.hpp>
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

  void render(const glm::vec2& position, const glm::vec2& size,
              float rotation = 0.0f);

  ~sprite2D();

  sprite2D(sprite2D&&);
  sprite2D& operator=(sprite2D&&);

  sprite2D(sprite2D&) = delete;
  sprite2D& operator=(sprite2D&) = delete;

 private:
  std::shared_ptr<shader_program> program;
  std::shared_ptr<texture2D> texture;

  vertex_array vba;
  vertex_buffer sprite_vbo;
  vertex_buffer texture_vbo;
  index_buffer vebo;
};
}  // namespace render
