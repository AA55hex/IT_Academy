#include "vertex_buffer.h"

namespace renderer
{
vertex_buffer::vertex_buffer() { init(0, nullptr); }
vertex_buffer::vertex_buffer(const unsigned int size, const void* data)
{
  init(size, data);
}

void vertex_buffer::bind() const { glBindBuffer(buffer_type, id); }
void vertex_buffer::detach() const { glBindBuffer(buffer_type, 0); }

void vertex_buffer::update(const unsigned int size, const void* data)
{
  glBindBuffer(buffer_type, id);
  glBufferSubData(buffer_type, 0, size, data);
}

vertex_buffer::vertex_buffer(vertex_buffer&& buffer)
{
  id = buffer.id;
  buffer.id = 0;
}

vertex_buffer& vertex_buffer::operator=(vertex_buffer&& buffer)
{
  glDeleteBuffers(1, &id);

  id = buffer.id;
  buffer.id = 0;

  return *this;
}

void vertex_buffer::init(const unsigned int size, const void* data)
{
  glGenBuffers(1, &id);
  glBindBuffer(buffer_type, id);
  glBufferData(buffer_type, size, data, GL_STATIC_DRAW);
}

vertex_buffer::~vertex_buffer() { glDeleteBuffers(1, &id); }
}  // namespace renderer
