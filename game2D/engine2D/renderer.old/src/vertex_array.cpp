#include "vertex_array.h"

namespace renderer
{
vertex_array::vertex_array() { glGenVertexArrays(1, &id); }

void vertex_array::bind() { glBindVertexArray(id); }
void vertex_array::detach() { glBindVertexArray(0); }

void vertex_array::bind_vertex_buffer(const vertex_buffer& buffer)
{
  glBindVertexArray(id);
  buffer.bind();
}
void vertex_array::bind_index_buffer(const index_buffer& buffer)
{
  glBindVertexArray(id);
  buffer.bind();
}

void vertex_array::set_pointer(unsigned int index, int size, bool normalized,
                               int stride, const void* offset)
{
  glVertexAttribPointer(index, size, GL_UNSIGNED_INT, normalized, stride,
                        offset);
}

void vertex_array::enable_array(unsigned int index)
{
  glEnableVertexAttribArray(index);
}

void vertex_array::disable_array(unsigned int index)
{
  glDisableVertexAttribArray(index);
}

vertex_array::vertex_array(vertex_array&& vao)
{
  id = vao.id;
  vao.id = 0;
}
vertex_array& vertex_array::operator=(vertex_array&& vao)
{
  glDeleteVertexArrays(1, &id);

  id = vao.id;
  vao.id = 0;

  return *this;
}

vertex_array::~vertex_array() { glDeleteVertexArrays(1, &id); }
}  // namespace renderer
