#pragma once
#include <glad/glad.h>
#include <string>
namespace renderer
{
class shader_program
{
 public:
  shader_program(const std::string& vert_src, const std::string& frag_src);

  bool is_compiled();
  void use() const;

  shader_program& operator=(shader_program&&);
  shader_program(shader_program&&);

  ~shader_program();

  shader_program(shader_program&) = delete;
  shader_program& operator=(shader_program&) = delete;

 private:
  bool create_shader(const std::string& source, GLenum s_type,
                     GLuint& shader_id);
  bool compile_status{false};
  GLuint id{0};
};
}  // namespace renderer
