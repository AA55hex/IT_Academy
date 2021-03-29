#include "render/index_buffer.h"

namespace render
{
index_buffer::index_buffer() : count{0}
{
  glGenBuffers(1, &id);
  restore(0, nullptr);
}
index_buffer::index_buffer(const unsigned int count_, const unsigned int* data)
    : count{count_}
{
  glGenBuffers(1, &id);
  restore(count * element_size, data);
}

void index_buffer::bind() const { glBindBuffer(buffer_type, id); }
void index_buffer::detach() const { glBindBuffer(buffer_type, 0); }

void index_buffer::update(const unsigned int count_, const unsigned int* data)
{
  // count = count_;
  glBindBuffer(buffer_type, id);
  glBufferSubData(buffer_type, 0, count_ * element_size, data);
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

  count = buffer.count;
  buffer.count = 0;

  return *this;
}

void index_buffer::restore(const unsigned int size, const unsigned int* data)
{
  count = size;
  glBindBuffer(buffer_type, id);
  glBufferData(buffer_type, size, data, GL_STATIC_DRAW);
}

index_buffer::~index_buffer() { glDeleteBuffers(1, &id); }
}  // namespace render
