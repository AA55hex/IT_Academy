#include <glad/glad.h>
namespace render
{
enum class color_format
{
  red = GL_RED,
  green = GL_GREEN,
  blue = GL_BLUE,
  alpha = GL_ALPHA,
  rgb = GL_RGB,
  rgba = GL_RGBA
};

class texture2D
{
 public:
  texture2D(int width, int height, const void* data, color_format format);

  void bind() const;

  int get_width() const;
  int get_height() const;

  ~texture2D();

  texture2D(texture2D&&);
  texture2D& operator=(texture2D&&);

  texture2D(texture2D&) = delete;
  texture2D& operator=(texture2D&) = delete;

  static void active_texture(unsigned int offset);

 private:
  void restore(int width, int height, const void* data, color_format format);
  GLuint id{0};
  int height{0};
  int width{0};
};

}  // namespace render
