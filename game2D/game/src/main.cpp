#include <glm/vec2.hpp>
#include <iostream>
#include "core/engine.h"
#include "glm/vec2.hpp"
#include "render/index_buffer.h"
#include "render/renderer.h"
#include "render/shader_program.h"
#include "render/sprite2D.h"
#include "render/vertex_array.h"
#include "render/vertex_buffer.h"
#include "resources/resource_manager.h"
#include "sound/sound_buffer.h"
struct rgb_color
{
  float r{0};
  float g{0};
  float b{0};
};

struct position
{
  float x{0};
  float y{0};
};

struct rgb_pos
{
  position pos;
  rgb_color color;
};

struct vertex
{
  float x{0};
  float y{0};
  float z{0};
  float r{0};
  float g{0};
  float b{0};
};

int main()
{
  using namespace engine;
  engine::inicialize(640, 480, "test", true);

  resources::resource_manager mgr{"res/"};
  auto prg{mgr.load_shader_program("test_prg", "shaders/test_shader.vert",
                                   "shaders/test_shader.frag")};
  auto texture{mgr.load_texture2D("texture", "textures/camera_200.png")};

  auto sound{mgr.load_wav("highlands", "sound/highlands.wav")};
  using namespace render;
  renderer::clear_color(0.33f, 0.66f, 0.99f, 0.0f);

  float size{200.0f / 200};
  sprite2D sprite{
      texture, prg, glm::vec2{size, 1}, glm::vec2{-0.5 * size, -0.5}, 1, 15};

  float rotation{15};
  sound::sound_buffer main_buffer{};
  main_buffer.use();
  sound->play();
  while (true)
    {
      sprite.set_rotation(rotation);
      rotation++;
      sprite.render();
      renderer::swap_buffers();
      renderer::clear();
    }
  engine::dispose();
  return 0;
}

// int gl_check();
// int main()
//{
//  using namespace core;
//  window_manager win_mgr{"test", 640, 480};

//  resources::resource_manager mgr{"res/"};
//  auto prg{mgr.load_shader_program("test_prg", "shaders/test_shader.vert",
//                                   "shaders/test_shader.frag")};
//  auto texture{mgr.load_texture2D("texture", "textures/blue_tex.jpg")};

//  using namespace render;
//  renderer::clear_color(0.33f, 0.66f, 0.99f, 0.0f);

//  position positions[4]{{-1, -1}, {-1, 1}, {1, 1}, {1, -1}};
//  vertex_buffer pos_vbo{sizeof(positions), positions};

//  position tex_pos[4]{{0, 0}, {0, 1}, {1, 1}, {1, 0}};
//  vertex_buffer tex_vbo{sizeof(tex_pos), tex_pos};

//  unsigned int indices[6]{0, 1, 2, 3};

//  index_buffer vebo{6, indices};

//  vertex_array vao{};

//  vao.enable_array(0);
//  vao.enable_array(1);

//  vao.bind_vertex_buffer(pos_vbo);
//  vao.set_pointer(0, 2, false, sizeof(position), nullptr);

//  vao.bind_vertex_buffer(tex_vbo);
//  vao.set_pointer(1, 2, false, sizeof(position), nullptr);

//  vao.bind_index_buffer(vebo);

//  prg->use();
//  texture->bind();
//  prg->set_uniform("tex", 0);

//  while (true)
//    {
//      renderer::draw(GL_TRIANGLE_FAN, 4, nullptr);

//      win_mgr.swap_buffers();
//      renderer::clear();
//    }
//  return 0;
//}
