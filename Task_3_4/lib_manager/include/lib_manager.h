#pragma once

namespace lmanager
{
enum class lib_update_status
{
  no_chages,
  detected,
  on_update,
  updated
};

class lib_manager
{
 public:
  lib_manager(const char* libname);
  lib_update_status update_status();
  lib_update_status get_lib_status();
  lib_update_status try_update();
};
}  // namespace lmanager
