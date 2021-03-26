#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <map>
#include <string>
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
  struct subtexture2D
  {
    glm::vec2 left_bottom{0.f};
    glm::vec2 right_top{1.f};
  };

  texture2D(int width, int height, const void* data, color_format format,
            const GLenum filter = GL_LINEAR,
            const GLenum wrapMode = GL_CLAMP_TO_EDGE);

  void bind() const;

  int get_width() const;
  int get_height() const;

  ~texture2D();

  texture2D(texture2D&&);
  texture2D& operator=(texture2D&&);

  const subtexture2D& add_subtexture(std::string key,
                                     const subtexture2D& subtexture);
  const subtexture2D& add_subtexture(std::string key, glm::vec2 left_bottom,
                                     glm::vec2 right_top);
  const subtexture2D& get_subtexture(std::string key) const;

  texture2D(texture2D&) = delete;
  texture2D& operator=(texture2D&) = delete;

  static void active_texture(unsigned int offset);

 private:
  void restore(int width, int height, const void* data, color_format format);
  GLuint id{0};
  int height{0};
  int width{0};

  std::map<std::string, subtexture2D> subtexture_map{};
  const texture2D::subtexture2D default_texture{};
};

}  // namespace render
