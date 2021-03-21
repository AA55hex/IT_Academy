#pragma once
#include <SDL2/SDL.h>
#include <array>
#include <string_view>
#include <vector>
#include "glad/glad.h"
namespace engine_lib
{
enum class event_type
{
  key_down = SDL_KEYDOWN,
  key_up = SDL_KEYUP
};

enum class keyboard
{
  w = SDLK_w,
  a = SDLK_a,
  s = SDLK_s,
  d = SDLK_d,
  lctrl = SDLK_LCTRL,
  space = SDLK_SPACE,
  escape = SDLK_ESCAPE,
  enter = SDLK_KP_ENTER
};

struct key_bind
{
  key_bind(keyboard keycode, std::string_view name)
      : key{keycode}, key_name{name}
  {
  }
  keyboard key;
  std::string_view key_name;
};

struct key_event
{
  key_event(key_bind bnd, event_type t) : bind{bnd}, type{t} {}
  key_bind bind;
  event_type type;
};

class engine
{
 public:
  class render_manager;
  class device_manager;
  engine();
  bool inicialize();
  void uninitialize();
  ~engine();
  render_manager *renderer;
  device_manager *device;

 private:
  SDL_Window *window;
};

class engine::render_manager
{
 public:
  render_manager(SDL_Window *window);
  int inicialize();
  int swap_buffers();

  //  static void set_pointer(GLint index, gl_type type);

  //  static void enable_vaa(GLuint index);
  //  static void disable_vaa(GLuint index);

  //  static void set_uniform(const std::string &uniform_name, GLuint block);
  //  static void set_uniform(const std::string &uniform_name, const texture
  //  &t); static void set_uniform(const std::string &uniform_name,
  //                          const gl_matrix4x4 &mtx);
  //  static void set_uniform(const std::string &uniform_name, const gl_vector2
  //  &v); static void set_uniform(const std::string &uniform_name, const
  //  gl_vector4 &v);

 private:
  SDL_Window *window;
  SDL_GLContext gl_context;
};

class device_manager
{
  int read_input_list(std::vector<key_event> &input);
  int read_input(key_event &input);
};
//----------Enums----------//
/// buffer type
/// drawing type
//----------Classes/Structures----------//
/// vbo/vebo
/// vao
/// program
/// shader -?
/// rgb_color
/// texture_2d

// class gl_program;
// class gl_shader;
// gl_manager
/// bind buffer
///// bind vbo
///// bind vebo
/// va pointer
/// enable/disable vaa
///
/// bind/reset vao
///
/// load shader
/// create shader
///
/// load program
/// create program
/// binary save
///
/// load texture
///
/// set uniform*
///// set matrix 4x4
///// set texture
///
/// draw elements
///
/// add/set/unset vao

// create shader
// create program
// bind vbo
// VAO with vbo, binds, uniforms
// draw fragments
/// set vbo
/// set mvp matrix
//

struct rgb_color
{
  float r{0};
  float g{0};
  float b{0};
};

struct gl_matrix4x4
{
  gl_matrix4x4();
  gl_matrix4x4(float);
  static gl_matrix4x4 rotate_2d(float angle);
  static gl_matrix4x4 scale(float x_scale, float y_scale);
  static gl_matrix4x4 move(float x_delta, float y_delta, float z_delta);
  float values[4][4]{0};
  static const int width{4};
  static const int height{4};
};

gl_matrix4x4 operator*(const gl_matrix4x4 &left, const gl_matrix4x4 &right);

struct gl_vector2
{
  float x{0};
  float y{0};
};
struct gl_vector4
{
  float x{0};
  float y{0};
  float z{0};
  float w{1};
};

// gl_matrix4x4 operator*(const gl_vector4 &left, const gl_vector2 &right);

// struct vertex_buffer_object
//{
//  gl_vector4 pos;
//  gl_vector2 t_pos;
//  rgb_color color;
//};
//-------------------------------------------------
#pragma pack(push, 1)
struct gl_object
{
  gl_object();
  virtual GLuint get_id() { engine::device_manager *mgr; }
  virtual ~gl_object() = 0;
  // virtual void restore();
  gl_object(const gl_object &) = delete;
  gl_object &operator=(const gl_object &) = delete;

 protected:
  GLuint id;
};
#pragma pack(pop)

struct gl_buffer : public gl_object
{
  virtual void bind() = 0;
};

struct shader : public gl_object
{
  shader(const std::string &src);
  ~shader() override;
};

struct program : public gl_buffer
{
  program(const shader &v_shader, const shader &f_shader);
  shader &get_vertex_shader();
  shader &get_fragment_shader();
  ~program() override;
};

struct vertex_buffer_array : public gl_buffer
{
  vertex_buffer_array();
  ~vertex_buffer_array() override;
};

struct vetex_element_array : public gl_buffer
{
  vetex_element_array();
  ~vetex_element_array() override;
};

struct vertex_attribute_object : public gl_buffer
{
  vertex_attribute_object();
  static void set_default();
  ~vertex_attribute_object() override;
};

struct texture : public gl_buffer
{
  texture(GLsizei width, GLsizei height, void *pixels);
  static void active_block(GLuint block);
  ~texture() override;

 protected:
  GLsizei width;
  GLsizei height;
};

enum gl_type
{
  mat4x4,
  vec2,
  vec4,
  color
};

struct vaa_manager
{
 public:
  static void set_pointer(GLint index, gl_type type);

  static void enable_vaa(GLuint index);
  static void disable_vaa(GLuint index);
};

struct uniform_manager
{
  static void set_uniform(const std::string &uniform_name, GLuint block);
  static void set_uniform(const std::string &uniform_name, const texture &t);
  static void set_uniform(const std::string &uniform_name,
                          const gl_matrix4x4 &mtx);
  static void set_uniform(const std::string &uniform_name, const gl_vector2 &v);
  static void set_uniform(const std::string &uniform_name, const gl_vector4 &v);
};

struct data_loader
{
  static program *load_program(std::string *path);
  static shader *load_shader(std::string *path);
  static texture *load_texture(std::string *path);
};

class buffer_manager
{
  void buffer_data();
};

}  // namespace engine_lib
