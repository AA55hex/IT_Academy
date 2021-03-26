#include <glm/vec2.hpp>
#include <iostream>
#include "core/engine.h"
#include "glm/vec2.hpp"
#include "input/input_event.h"
#include "input/input_manager.h"
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
  engine::inicialize(1280, 720, "test", true);

  resources::resource_manager mgr{"res/"};
  auto prg{mgr.load_shader_program("test_prg", "shaders/test_shader.vert",
                                   "shaders/test_shader.frag")};
  auto texture{mgr.load_texture_atlas2D(
      "texture", "textures/tanks.png",
      std::vector<std::string>{"test1", "test2", "test3"}, 16, 16)};
  texture->add_subtexture("test", glm::vec2{1, 1},
                          glm::vec2{1 - 16.f / 256, 1 - 16.f / 256});

  auto sound{mgr.load_wav("highlands", "sound/highlands.wav")};
  using namespace render;
  renderer::clear_color(0.33f, 0.66f, 0.99f, 0.0f);

  float size{200.0f / 200};
  sprite2D sprite{texture, "test1", prg};
  sprite2D sprite0{texture, "test2", prg};
  sprite2D sprite1{texture, "test3", prg};

  float rotation{0};
  sound::sound_buffer main_buffer{};
  main_buffer.use();
  sound->play();
  bool continue_play{true};
  while (continue_play)
    {
      // rotation += 15;
      input::input_event event{};
      while (input::input_manager::read_input(&event))
        {
          if (event.type == input::event_type::quit) continue_play = false;
        }
      sprite.render(glm::vec2{0, 0}, glm::vec2{0.5, 0.5}, rotation);
      sprite1.render(glm::vec2{-0.5, -0.5}, glm::vec2{0.2, 0.2}, rotation);
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
