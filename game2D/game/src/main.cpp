#include <glm/vec2.hpp>
#include <iostream>
#include "core/engine.h"
#include "core/igame.h"
#include "glm/vec2.hpp"
#include "input/input_event.h"
#include "input/input_manager.h"
#include "render/index_buffer.h"
#include "render/renderer.h"
#include "render/shader_program.h"
#include "render/sprite2D.h"
#include "render/sprite_animator.h"
#include "render/vertex_array.h"
#include "render/vertex_buffer.h"
#include "resources/resource_manager.h"
#include "sound/sound_buffer.h"
class game : public core::igame
{
 public:
  game() {}
  bool inicialize() override
  {
    auto prg{mgr.load_shader_program("test_prg", "shaders/test_shader.vert",
                                     "shaders/test_shader.frag")};
    auto texture{mgr.load_texture_atlas2D(
        "texture", "textures/tanks.png",
        std::vector<std::string>{"test1", "test2", "test3"}, 16, 16)};

    auto sprite{mgr.load_sprite("sprite", "texture", "test_prg", "test1")};

    animator = render::sprite_animator{sprite};

    render::frame_descriptor buff{texture->get_subtexture("test1").left_bottom,
                                  texture->get_subtexture("test1").right_top};
    animator.add_frame(buff, 200);
    animator.add_frame({texture->get_subtexture("test2").left_bottom,
                        texture->get_subtexture("test2").right_top},
                       200);

    settings.size = glm::vec2{2.f / 16, 2.f / 16};
    return true;
  }

  void read_input(double) override
  {
    input::input_event event{};
    while (input::input_manager::read_input(&event))
      {
        if (event.type == input::event_type::quit) playing = false;
        //        if (event.type == input::event_type::mouse)
        //          {
        //            settings.position =
        //            input::input_manager::get_mouse_state();
        //          }
      }
  }
  void update_data(double duration) override { animator.update(duration); }
  void render_output() override { animator.render(settings); }

  ~game() override {}

 private:
  render::sprite_animator animator{nullptr};
  render::render_settings settings{};
  resources::resource_manager mgr{"res/"};
};

int main()
{
  using namespace core;
  engine::inicialize(1280, 720, "test", true);
  // auto sound{mgr.load_wav("highlands", "sound/highlands.wav")};

  render::renderer::clear_color(0.f, 0.f, 0.f, 0.0f);
  game my_game{};
  engine::play(my_game);

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
