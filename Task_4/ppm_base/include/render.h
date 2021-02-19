#pragma once
#include <math.h>
#include <array>
#include <cassert>
#include <map>
#include <string>
#include <vector>
namespace render
{
struct rgb_color
{
  uint8_t r{0};
  uint8_t g{0};
  uint8_t b{0};
};

struct coordinate
{
  size_t x{0};
  size_t y{0};
  coordinate operator-(const coordinate& right) const
  {
    return coordinate{x - right.x, y - right.y};
  }
};

class canvas
{
 public:
  using iterator = std::vector<rgb_color>::iterator;
  canvas(size_t width_, size_t height_);
  canvas(size_t width_, size_t height_, const std::vector<rgb_color>& pixels);
  canvas(const canvas& right) = delete;
  canvas(canvas&& right);

  rgb_color& operator[](const coordinate& pos);
  rgb_color operator[](const coordinate& pos) const;
  size_t get_height() const;
  size_t get_width() const;

  void clear(rgb_color color);

  size_t size() const;

  iterator begin();
  iterator end();

  canvas& operator=(const canvas& right);

  canvas& operator=(canvas&& right);

  rgb_color* data() const;

  ~canvas();

 private:
  size_t height{0};
  size_t width{0};
  std::vector<rgb_color>* pixels;
};

class line_render
{
 public:
  line_render(canvas& cnv);
  std::vector<coordinate> get_line_coordinates(coordinate pos1,
                                               coordinate pos2);
  virtual ~line_render();

 protected:
  canvas& owner;
};

class triangle_render : public line_render
{
 public:
  triangle_render(canvas& cnv);
  std::vector<coordinate> get_coordinates(coordinate pos1, coordinate pos2,
                                          coordinate pos3);
  void indexed_draw(std::map<int, coordinate>& vertexes,
                    const std::vector<int>& indexes, rgb_color color);
  virtual ~triangle_render() override;
};

struct vertex
{
  double x{0};
  double y{0};
  double r{0};
  double g{0};
  double b{0};
  double u{0};
  double v{0};
};

struct uniforms
{
  double f0 = 0;
  double f1 = 0;
  double f2 = 0;
  double f3 = 0;
  double f4 = 0;
  double f5 = 0;
  double f6 = 0;
  double f7 = 0;
  size_t s0{0};
  size_t s1{0};
  size_t s3{0};
};

double interpolate(const double begin, const double end, const double t);
vertex interpolate(const vertex& begin, const vertex& end, const double c);

struct gfx_program
{
  virtual void set_uniforms(const uniforms&) = 0;
  virtual vertex vertex_shader(const vertex& v_in) = 0;
  virtual rgb_color fragment_shader(const vertex& v_in) = 0;
  virtual ~gfx_program() = default;
};

class rastered_triangle : public triangle_render
{
 public:
  rastered_triangle(canvas& cnv);
  void rastered_draw(std::map<int, vertex>& vertexes,
                     const std::vector<int>& indexes);
  void set_gfx_program(gfx_program& gfx);

 private:
  void rasterize(const vertex& vtx1, const vertex& vtx2, const vertex& vtx3);
  void horizontal_raster(const vertex& vtx, const vertex& left,
                         const vertex& right);
  void raster_line(const vertex& left, const vertex& right);
  gfx_program* gfx;
};
}  // namespace render
