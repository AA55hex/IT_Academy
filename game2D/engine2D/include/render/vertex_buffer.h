#pragma once
#include <glad/glad.h>
namespace render
{
class vertex_buffer
{
 public:
  vertex_buffer();
  vertex_buffer(const unsigned int size, const void* data);

  void bind() const;
  void detach() const;

  void restore(const unsigned int size, const void* data);
  void update(const unsigned int size, const void* data);

  ~vertex_buffer();

  vertex_buffer(vertex_buffer&&);
  vertex_buffer& operator=(vertex_buffer&&);

  vertex_buffer(vertex_buffer&) = delete;
  vertex_buffer operator=(vertex_buffer&) = delete;

 private:
  GLuint id{0};
  unsigned int size{0};
  static const GLenum buffer_type{GL_ARRAY_BUFFER};
};
}  // namespace render
