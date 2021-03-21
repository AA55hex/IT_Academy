#pragma once
#include <glad/glad.h>
#include <string>
namespace renderer
{
class index_buffer
{
 public:
  index_buffer();
  index_buffer(const unsigned int count, const void* data);

  void bind() const;
  void detach() const;

  void update(const unsigned int count, const void* data);

  ~index_buffer();

  index_buffer(index_buffer&&);
  index_buffer& operator=(index_buffer&&);

  index_buffer(index_buffer&) = delete;
  index_buffer operator=(index_buffer&) = delete;

 private:
  void init(const unsigned int count, const void* data);
  GLuint id{0};

  static const GLenum buffer_type{GL_ELEMENT_ARRAY_BUFFER};
  static const GLuint element_size{sizeof(GLuint)};
};
}  // namespace renderer
