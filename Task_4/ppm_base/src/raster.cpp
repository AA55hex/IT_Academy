#include <math.h>
#include <render.h>
#include <algorithm>
#include <vector>
namespace render
{
double get_hypotenuse(double c1, double c2)
{
  return std::sqrt(c1 * c1 + c2 * c2);
}

double interpolate(const double begin, const double end, const double t)
{
  assert(t >= 0.0);
  assert(t <= 1.0);
  return begin + (end - begin) * t;
}
vertex interpolate(const vertex& begin, const vertex& end, const double c)
{
  const double x{interpolate(begin.x, end.x, c)};
  const double y{interpolate(begin.y, end.y, c)};

  const double r{interpolate(begin.r, end.r, c)};
  const double g{interpolate(begin.g, end.g, c)};
  const double b{interpolate(begin.b, end.b, c)};

  const double u{interpolate(begin.u, end.u, c)};
  const double v{interpolate(begin.v, end.v, c)};

  return vertex{x, y, r, g, b, u, v};
}

vertex get_subcoordinate(const vertex& top, const vertex& bottom,
                         const vertex& middle)
{
  /// y = coef * (x - x_const) + y_const;
  /// coef = (y - y_const) / (x - x_const);
  /// x = ((y - y_const) / coef) + x_const;
  /// prelude = ((y - y_const) / coef);

  const double x_const{top.x};
  const double y_const{top.y};

  const double target_y{middle.y};

  const double coef{(bottom.y - y_const) / (bottom.x - x_const)};

  const double prelude{(target_y - y_const) / coef};

  const double target_x{prelude + x_const};

  const double vtx_coef{get_hypotenuse(top.x - target_x, top.y - target_y) /
                        get_hypotenuse(top.x - bottom.x, top.y - bottom.y)};

  vertex result{interpolate(top, bottom, vtx_coef)};

  result.y = middle.y;

  return result;
}

void rastered_triangle::raster_line(const vertex& left, const vertex& right)
{
  const size_t pixel_count{
      static_cast<size_t>(std::abs(std::round(left.x - right.x)) + 1)};
  for (size_t it{0}; it < pixel_count; it++)
    {
      double coef{static_cast<double>(it) / pixel_count};
      vertex buff{interpolate(left, right, coef)};
      rgb_color color{gfx->fragment_shader(buff)};
      const coordinate pos{static_cast<size_t>(std::round(buff.x)),
                           static_cast<size_t>(std::round(buff.y))};
      owner[pos] = color;
    }
}

void rastered_triangle::horizontal_raster(const vertex& vtx, const vertex& left,
                                          const vertex& right)
{
  const size_t line_count{
      static_cast<size_t>(std::abs(std::round(vtx.y - left.y)) + 1)};
  for (size_t it{0}; it < line_count; it++)
    {
      double coef{static_cast<double>(it) / line_count};
      vertex l_buff{interpolate(left, vtx, coef)};
      vertex r_buff{interpolate(right, vtx, coef)};
      raster_line(l_buff, r_buff);
    }
}

void rastered_triangle::rasterize(const vertex& vtx1, const vertex& vtx2,
                                  const vertex& vtx3)
{
  std::vector<vertex> result{};
  std::array<vertex, 3> ordered_y{vtx1, vtx2, vtx3};
  std::sort(
      ordered_y.begin(), ordered_y.end(),
      [](const vertex& left, const vertex& right) { return left.y < right.y; });
  const vertex top{ordered_y[0]};
  const vertex middle{ordered_y[1]};
  const vertex bottom{ordered_y[2]};

  const vertex horizontal{get_subcoordinate(top, bottom, middle)};

  horizontal_raster(top, middle, horizontal);
  horizontal_raster(bottom, middle, horizontal);
}

void rastered_triangle::rastered_draw(std::map<int, vertex>& vertexes,
                                      const std::vector<int>& indexes)
{
  for (auto it{indexes.begin()}; it < indexes.end(); it += 3)
    {
      const vertex& vtx1{gfx->vertex_shader(vertexes[it[0]])};
      const vertex& vtx2{gfx->vertex_shader(vertexes[it[1]])};
      const vertex& vtx3{gfx->vertex_shader(vertexes[it[2]])};
      rasterize(vtx1, vtx2, vtx3);
    }
}

void rastered_triangle::set_gfx_program(gfx_program& prg) { gfx = &prg; }

rastered_triangle::rastered_triangle(canvas& cnv) : triangle_render{cnv} {}

}  // namespace render
