#include <math.h>
#include <render.h>

namespace render
{
line_render::line_render(canvas& owner_) : owner{owner_} {}

std::vector<coordinate> line_render::get_coordinates(coordinate pos1,
                                                     coordinate pos2)
{
  std::vector<coordinate> result{};
  const int x_diff{static_cast<int>(pos2.x - pos1.x)};
  const int y_diff{static_cast<int>(pos2.y - pos1.y)};
  const int x_abs_diff{std::abs(x_diff)};
  const int y_abs_diff{std::abs(y_diff)};

  const bool strategy{x_abs_diff >= y_abs_diff};
  const int& main_diff{strategy ? x_diff : y_diff};
  const int& sub_diff{!strategy ? x_diff : y_diff};

  const int target_err{std::abs(main_diff) + 1};
  const int err_inc{std::abs(sub_diff) + 1};
  int err_sum{0};

  const int main_inc{main_diff >= 0 ? 1 : -1};
  const int sub_inc{sub_diff >= 0 ? 1 : -1};

  coordinate buff{pos1};

  size_t& main_buff{strategy ? buff.x : buff.y};
  size_t& sub_buff{!strategy ? buff.x : buff.y};
  for (int it{0}; it < target_err; it++)
    {
      result.push_back(buff);
      main_buff += static_cast<size_t>(main_inc);
      err_sum += err_inc;
      if (err_sum >= target_err)
        {
          // result.push_back(buff);
          sub_buff += static_cast<size_t>(sub_inc);
          err_sum -= target_err;
        }
    }
  return result;
}
// std::vector<pixel> line_render::get_pixels(coordinate pos1, coordinate pos2)
// {}
line_render::~line_render(){};
}  // namespace render
