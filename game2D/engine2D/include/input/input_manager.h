#pragma once
#include <glm/vec2.hpp>
#include "input_event.h"

namespace input
{
class input_manager
{
  input_manager() = delete;

 public:
  static bool read_input(input_event* event);
  static glm::vec2 get_mouse_state();
};
}  // namespace input
