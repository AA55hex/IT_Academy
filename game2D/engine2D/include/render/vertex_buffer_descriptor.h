#include <glad/glad.h>
#include <vector>
namespace render
{
// void vertex_array::set_pointer(unsigned int index, int size, bool normalized,
//                               int stride, const void* offset)
//{
//  glBindVertexArray(id);
//  glVertexAttribPointer(index, size, GL_FLOAT, normalized, stride, offset);
//}

class vertex_buffer_descriptor
{
 public:
  struct element_descriptor
  {
    int count;
    GLenum type;
    bool normalized;
    int size;
  };
  vertex_buffer_descriptor() {}
  int get_stride() const { return stride; }

  void add_element_descriptor_float(int count, bool normalized);
  const std::vector<element_descriptor>& get_descriptors() const
  {
    return descriptors;
  }

 private:
  int stride{};
  std::vector<element_descriptor> descriptors{};
};
}  // namespace render
