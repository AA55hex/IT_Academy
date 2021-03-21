#include "render/index_buffer.h"

namespace render
{
index_buffer::index_buffer()
{
  glGenBuffers(1, &id);
  restore(0, nullptr);
}
index_buffer::index_buffer(const unsigned int count, const void* data)
{
  glGenBuffers(1, &id);
  restore(count * element_size, data);
}

void index_buffer::bind() const { glBindBuffer(buffer_type, id); }
void index_buffer::detach() const { glBindBuffer(buffer_type, 0); }

void index_buffer::update(const unsigned int count, const void* data)
{
  glBindBuffer(buffer_type, id);
  glBufferSubData(buffer_type, 0, count * element_size, data);
}

index_buffer::index_buffer(index_buffer&& buffer)
{
  id = buffer.id;
  buffer.id = 0;
}

index_buffer& index_buffer::operator=(index_buffer&& buffer)
{
  glDeleteBuffers(1, &id);

  id = buffer.id;
  buffer.id = 0;

  return *this;
}

void index_buffer::restore(const unsigned int size, const void* data)
{
  glBindBuffer(buffer_type, id);
  glBufferData(buffer_type, size, data, GL_STATIC_DRAW);
  this->size = size;
}

index_buffer::~index_buffer() { glDeleteBuffers(1, &id); }
}  // namespace render
