#include "index_buffer.h"

namespace renderer
{
index_buffer::index_buffer() { init(0, nullptr); }
index_buffer::index_buffer(const unsigned int count, const void* data)
{
  init(count, data);
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

void index_buffer::init(const unsigned int count, const void* data)
{
  glGenBuffers(1, &id);
  glBindBuffer(buffer_type, id);
  glBufferData(buffer_type, count * element_size, data, GL_STATIC_DRAW);
}

index_buffer::~index_buffer() { glDeleteBuffers(1, &id); }
}  // namespace renderer
