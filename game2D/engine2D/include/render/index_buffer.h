#pragma once
#include <glad/glad.h>
#include <string>
namespace render
{
class index_buffer
{
 public:
  index_buffer();
  index_buffer(const unsigned int count, const unsigned int* data);

  void bind() const;
  void detach() const;

  void restore(const unsigned int size, const unsigned int* data);
  void update(const unsigned int count, const unsigned int* data);

  ~index_buffer();

  index_buffer(index_buffer&&);
  index_buffer& operator=(index_buffer&&);

  index_buffer(index_buffer&) = delete;
  index_buffer operator=(index_buffer&) = delete;

  unsigned int get_count() const { return count; }

 private:
  GLuint id{0};
  unsigned int count{0};

  static const GLenum buffer_type{GL_ELEMENT_ARRAY_BUFFER};
  static const GLuint element_size{sizeof(GLuint)};
};
}  // namespace render
