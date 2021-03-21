#include "render/texture2D.h"

namespace render
{
texture2D::texture2D(int width_, int height_, const void* data,
                     color_format format)
    : height{height_}, width{width_}
{
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(format), width, height, 0,
               static_cast<GLenum>(format), GL_UNSIGNED_BYTE, data);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_CLAMP_TO_EDGE);

  glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, 0);
}

void texture2D::bind() const { glBindTexture(GL_TEXTURE_2D, id); }

int texture2D::get_width() const { return width; }
int texture2D::get_height() const { return height; }

texture2D::~texture2D() { glDeleteTextures(1, &id); }

texture2D::texture2D(texture2D&& texture)
{
  id = texture.id;
  width = texture.width;
  height = texture.height;

  texture.id = 0;
}

texture2D& texture2D::operator=(texture2D&& texture)
{
  glDeleteTextures(1, &id);

  id = texture.id;
  width = texture.width;
  height = texture.height;

  texture.id = 0;

  return *this;
}

void texture2D::active_texture(unsigned int offset)
{
  GLenum buffer{GL_TEXTURE0 + offset};
  glActiveTexture(buffer);
}
}  // namespace render
