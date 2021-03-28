#pragma once
#include <glm/vec2.hpp>
namespace render
{
struct frame_descriptor
{
  glm::vec2 left_bottom_uv{0.f};
  glm::vec2 right_top_uv{1.f};
};

struct render_settings
{
  glm::vec2 position{0};
  glm::vec2 size{1};
  int layer{0};
  float rotation{0};
};

}  // namespace render
