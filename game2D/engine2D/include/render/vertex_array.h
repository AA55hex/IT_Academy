#pragma once
#include <glad/glad.h>
#include "index_buffer.h"
#include "vertex_buffer.h"

namespace render
{
class vertex_buffer;
class vertex_buffer_descriptor;

class vertex_array
{
 public:
  vertex_array();

  void bind() const;
  void detach() const;

  void bind_vertex_buffer(const vertex_buffer& buffer,
                          const vertex_buffer_descriptor& descriptor);

  unsigned int get_arrays_count() const { return va_arrays_count; }

  vertex_array(vertex_array&&);
  vertex_array& operator=(vertex_array&&);

  ~vertex_array();

  vertex_array(vertex_array&) = delete;
  vertex_array& operator=(vertex_array&) = delete;

 private:
  GLuint id{0};
  unsigned int va_arrays_count{0};
};
}  // namespace render
