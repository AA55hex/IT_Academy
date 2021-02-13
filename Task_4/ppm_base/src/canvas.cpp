#include "ppm_base.h"
#include "render.h"
namespace render
{
canvas::canvas(size_t width_, size_t height_)
    : height{height_},
      width{width_},
      pixels{new std::vector<rgb_color>(height_ * width_)}
{
}

canvas::canvas(canvas&& right)
{
  pixels = right.pixels;
  right.pixels = nullptr;
  height = right.height;
  width = right.width;
}

rgb_color& canvas::operator[](const coordinate& pos)
{
  return (*pixels)[pos.y * width + pos.x];
}
rgb_color canvas::operator[](const coordinate& pos) const
{
  return (*pixels)[pos.y * width + pos.x];
}

size_t canvas::get_height() const { return height; }
size_t canvas::get_width() const { return width; }

void canvas::clear(rgb_color color)
{
  std::fill(pixels->begin(), pixels->end(), color);
}

size_t canvas::size() const { return pixels->size(); }

canvas::iterator canvas::begin() { return pixels->begin(); }
canvas::iterator canvas::end() { return pixels->end(); }

canvas& canvas::operator=(const canvas& right)
{
  delete pixels;
  *pixels = *(right.pixels);
  height = right.height;
  width = right.width;
  return *this;
}

canvas& canvas::operator=(canvas&& right)
{
  delete pixels;
  pixels = right.pixels;
  right.pixels = nullptr;
  height = right.height;
  width = right.width;
  return *this;
}

rgb_color* canvas::data() const { return pixels->data(); }

canvas::~canvas() { delete pixels; }
}  // namespace render
