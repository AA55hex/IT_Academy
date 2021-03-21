#pragma once
#include <map>
#include <memory>
#include <string>
#include "shader_program.h"
namespace renderer
{
class resource_manager
{
 public:
  resource_manager(const std::string& dir_path);

  resource_manager(resource_manager&&);
  resource_manager& operator=(resource_manager&&);

  std::shared_ptr<shader_program> load_shader_program(
      const std::string& prg_name, const std::string& vert_path,
      const std::string& frag_path);
  std::shared_ptr<shader_program> get_shader_program(
      const std::string& prg_name);

  resource_manager(resource_manager&) = delete;
  resource_manager& operator=(resource_manager&) = delete;

 private:
  std::string get_file_data(const std::string& additional);

  std::map<std::string, std::shared_ptr<shader_program>> shader_program_map;
  std::string path;
};
}  // namespace renderer
