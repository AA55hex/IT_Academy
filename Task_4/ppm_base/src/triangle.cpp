#include <math.h>
#include <render.h>
#include <algorithm>
#include <vector>
namespace render
{
coordinate operator-(coordinate left, size_t right)
{
  left.x -= right;
  left.y -= right;
  return left;
}

triangle_render::triangle_render(canvas& cnv) : line_render(cnv) {}

std::vector<coordinate> triangle_render::get_coordinates(coordinate pos1,
                                                         coordinate pos2,
                                                         coordinate pos3)
{
  using namespace std;

  std::vector<coordinate> result{};

  using line = pair<coordinate, coordinate>;
  for (auto [start, end] :
       {line{pos1, pos2}, line{pos2, pos3}, line{pos3, pos1}})
    {
      std::vector<coordinate> buff{
          line_render::get_line_coordinates(start, end)};
      buff.pop_back();
      for (auto it : buff)
        {
          result.push_back(it);
        }
    }
  return result;
}

void triangle_render::indexed_draw(std::map<int, coordinate>& vertexes,
                                   const std::vector<int>& indexes,
                                   rgb_color color)
{
  for (auto it{indexes.begin()}; it < indexes.end(); it += 3)
    {
      std::vector<coordinate> buff{
          get_coordinates(vertexes[it[0]], vertexes[it[1]], vertexes[it[2]])};
      std::for_each(buff.begin(), buff.end(),
                    [&](render::coordinate& c) { owner[c] = color; });
    }
}

triangle_render::~triangle_render() {}
}  // namespace render
