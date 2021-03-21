#include <SDL.h>
#include <SDL_version.h>
#include <algorithm>
#include <array>
#include <string_view>
#include <vector>
#include "engine.h"

namespace engine_lib
{
gl_matrix4x4::gl_matrix4x4() {}
gl_matrix4x4::gl_matrix4x4(float value)
{
  for (int it{0}; it < width; it++)
    {
      values[it][it] = value;
    }
}

gl_matrix4x4 gl_matrix4x4::rotate_2d(float angle)
{
  using namespace std;
  gl_matrix4x4 result{1};
  result.values[0][0] = cos(angle);
  result.values[0][1] = sin(angle);

  result.values[1][0] = -sin(angle);
  result.values[1][1] = cos(angle);
  return result;
}

gl_matrix4x4 gl_matrix4x4::scale(float x_scale, float y_scale)
{
  gl_matrix4x4 result{1};
  result.values[0][0] = x_scale;
  result.values[1][1] = y_scale;
  return result;
}

gl_matrix4x4 gl_matrix4x4::move(float x_delta, float y_delta, float z_delta)
{
  gl_matrix4x4 result{1};
  result.values[0][3] = x_delta;
  result.values[1][3] = y_delta;
  result.values[2][3] = z_delta;
  return result;
}

gl_matrix4x4 operator*(const gl_matrix4x4 &left, const gl_matrix4x4 &right)
{
  gl_matrix4x4 result{};
  for (int l_row{0}; l_row < gl_matrix4x4::width; l_row++)
    {
      for (int r_col{0}; r_col < gl_matrix4x4::height; r_col++)
        {
          for (int l_col{0}; l_col < gl_matrix4x4::height; l_col++)
            {
              result.values[l_row][r_col] +=
                  left.values[l_row][l_col] * right.values[l_col][r_col];
            }
        }
    }
  return result;
}

}  // namespace engine_lib
