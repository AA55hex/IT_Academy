#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <memory>
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
  sprite2D(std::shared_ptr<texture2D> texture,
           std::shared_ptr<shader_program> program, const glm::vec2& size,
           const glm::vec2& position, float scale = 1.0f,
           float rotation = 0.0f);

  void set_scale(float new_scale);
  void set_rotation(float new_rotation);
  void set_program(std::shared_ptr<shader_program> prg);
  void set_position(const glm::vec2& position);
  void render();

  ~sprite2D();

  sprite2D(sprite2D&&);
  sprite2D& operator=(sprite2D&&);

  sprite2D(sprite2D&) = delete;
  sprite2D& operator=(sprite2D&) = delete;

 private:
  std::shared_ptr<shader_program> program;
  std::shared_ptr<texture2D> texture;
  glm::vec2 position;
  glm::vec2 size;
  float scale{1.0f};
  float rotation{0.0f};

  vertex_array vba;
  vertex_buffer sprite_vbo;
  vertex_buffer texture_vbo;
  index_buffer vebo;
};
}  // namespace render
