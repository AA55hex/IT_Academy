#pragma once
#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <string>
namespace render
{
class texture2D;

class shader_program
{
 public:
  shader_program(const std::string& vert_src, const std::string& frag_src);

  bool is_compiled() const;
  void use() const;

  shader_program& operator=(shader_program&&);
  shader_program(shader_program&&);

  ~shader_program();

  bool set_uniform(std::string u_name, int value);
  bool set_uniform(std::string u_name, const glm::mat4x4& value);

  shader_program(shader_program&) = delete;
  shader_program& operator=(shader_program&) = delete;

 private:
  bool create_shader(const std::string& source, GLenum s_type,
                     GLuint& shader_id);
  bool compile_status{false};
  GLuint id{0};
};
}  // namespace render
