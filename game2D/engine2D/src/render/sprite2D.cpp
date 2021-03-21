#include "render/sprite2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include "glad/glad.h"
#include "render/shader_program.h"
#include "render/texture2D.h"
#include "render/vertex_array.h"
namespace render
{
sprite2D::sprite2D(std::shared_ptr<texture2D> texture_,
                   std::shared_ptr<shader_program> program_,
                   const glm::vec2& size_, const glm::vec2& position_,
                   float scale_, float rotation_)
    : program{program_},
      texture{texture_},
      position{position_},
      size{size_},
      scale{scale_},
      rotation{rotation_}
{
  vba = vertex_array{};
  vba.bind();

  float sprite_pos[]{0, 0, 0, 1, 1, 0, 1, 1};
  sprite_vbo = vertex_buffer{sizeof(sprite_pos), sprite_pos};
  vba.bind_vertex_buffer(sprite_vbo);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 2, nullptr);

  float tex_pos[]{0, 0, 0, 1, 1, 0, 1, 1};
  texture_vbo = vertex_buffer{sizeof(tex_pos), tex_pos};
  vba.bind_vertex_buffer(texture_vbo);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 2, nullptr);

  unsigned int indices[]{1, 0, 2, 3};
  vebo = index_buffer{4, indices};
  vba.bind_index_buffer(vebo);

  vba.detach();
}

void sprite2D::set_scale(float new_scale) { scale = new_scale; }
void sprite2D::set_rotation(float new_rotation) { rotation = new_rotation; }
void sprite2D::set_program(std::shared_ptr<shader_program> prg)
{
  program = prg;
}
void sprite2D::set_position(const glm::vec2& new_position)
{
  position = new_position;
}
void sprite2D::render()
{
  glm::mat4x4 model{1};

  // model = glm::translate(model, glm::vec3{position.x, position.y, 0});
  model = glm::translate(model, glm::vec3{position.x + size.x * 0.5f,
                                          position.y + size.y * 0.5f, 0});
  model = glm::rotate(model, glm::radians(rotation), glm::vec3{0, 0, 1});
  model = glm::translate(model, glm::vec3{size.x * -0.5f, size.y * -0.5f, 0});
  model = glm::scale(model, glm::vec3{size, 1});

  vba.bind();

  program->use();
  program->set_uniform("model", model);

  texture2D::active_texture(0);
  texture->bind();
  program->set_uniform("s_texture", 0);

  glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);
  vba.detach();
}

sprite2D::~sprite2D() {}
}  // namespace render
