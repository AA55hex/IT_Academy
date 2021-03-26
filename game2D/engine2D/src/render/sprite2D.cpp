#include "render/sprite2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include "glad/glad.h"
#include "render/renderer.h"
#include "render/shader_program.h"
#include "render/texture2D.h"
#include "render/vertex_array.h"
#include "render/vertex_buffer_descriptor.h"
namespace render
{
sprite2D::sprite2D(std::shared_ptr<texture2D> texture_, std::string subtexture_,
                   std::shared_ptr<shader_program> program_)
    : program{program_}, texture{texture_}
{
  vba = vertex_array{};
  vba.bind();
  // spite vba description
  float sprite_pos[]{0, 0, 0, 1, 1, 0, 1, 1};
  sprite_vbo = vertex_buffer{sizeof(sprite_pos), sprite_pos};

  vertex_buffer_descriptor sprite_descriptor{};
  sprite_descriptor.add_element_descriptor_float(2, false);

  vba.bind_vertex_buffer(sprite_vbo, sprite_descriptor);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 2, nullptr);

  // texture vba description
  texture2D::subtexture2D subtexture{texture_->get_subtexture(subtexture_)};
  float tex_pos[]{subtexture.left_bottom.x, subtexture.left_bottom.y,
                  subtexture.left_bottom.x, subtexture.right_top.y,
                  subtexture.right_top.x,   subtexture.left_bottom.y,
                  subtexture.right_top.x,   subtexture.right_top.y};
  texture_vbo = vertex_buffer{sizeof(tex_pos), tex_pos};

  vertex_buffer_descriptor texture_descriptor{};
  texture_descriptor.add_element_descriptor_float(2, false);

  vba.bind_vertex_buffer(texture_vbo, texture_descriptor);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 2, nullptr);

  // index buffer description
  unsigned int indices[]{1, 0, 2, 3};
  vebo = index_buffer{4, indices};
  vebo.bind();

  vba.detach();
  vebo.detach();
}

void sprite2D::render(const glm::vec2& position, const glm::vec2& size,
                      float rotation)
{
  glm::mat4x4 model{1};

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

  renderer::draw(vba, vebo, *program, GL_TRIANGLE_FAN);
  vba.detach();
}

sprite2D::~sprite2D() {}
}  // namespace render
