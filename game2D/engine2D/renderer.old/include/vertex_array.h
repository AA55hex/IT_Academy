#pragma once
#include <glad/glad.h>
#include "index_buffer.h"
#include "vertex_buffer.h"

namespace renderer
{
class vertex_array
{
 public:
  vertex_array();

  void bind();
  void detach();

  void bind_vertex_buffer(const vertex_buffer& buffer);
  void bind_index_buffer(const index_buffer& buffer);

  void set_pointer(unsigned int index, int size, bool normalized, int stride,
                   const void* offset);
  void enable_array(unsigned int index);
  void disable_array(unsigned int index);

  vertex_array(vertex_array&&);
  vertex_array& operator=(vertex_array&&);

  ~vertex_array();

  vertex_array(vertex_array&) = delete;
  vertex_array& operator=(vertex_array&) = delete;

 private:
  GLuint id;
};
}  // namespace renderer
