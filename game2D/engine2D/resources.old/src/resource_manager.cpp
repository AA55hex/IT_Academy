#include "resource_manager.h"
#include <fstream>
#include <iostream>
#include <sstream>
namespace renderer
{
resource_manager::resource_manager(const std::string& dir_path)
{
  size_t last_pos{dir_path.find_last_of("/\\")};
  path = dir_path;
  if (path.length() - 1 != last_pos)
    {
      path += "/";
    }
}

std::shared_ptr<shader_program> resource_manager::load_shader_program(
    const std::string& prg_name, const std::string& vert_path,
    const std::string& frag_path)
{
  std::string vert_src{get_file_data(vert_path)};
  if (vert_src.empty())
    {
      std::cerr << "Failed to load vertex shader" << std::endl;
    }
  std::string frag_src{get_file_data(frag_path)};
  if (frag_src.empty())
    {
      std::cerr << "Failed to load fragment shader" << std::endl;
    }
  shader_program_map[prg_name] =
      std::make_shared<shader_program>(vert_src, frag_src);

  std::shared_ptr<shader_program> result{shader_program_map[prg_name]};

  if (!result->is_compiled())
    {
      std::cerr << "Failed to load shader program <" << prg_name << ">"
                << std::endl
                << "> Vertex shader: " << vert_path << std::endl
                << "> Fragment shader: " << frag_path << std::endl;
      return nullptr;
    }

  return result;
}
std::shared_ptr<shader_program> resource_manager::get_shader_program(
    const std::string& prg_name)
{
  auto it{shader_program_map.find(prg_name)};
  if (it == shader_program_map.end())
    {
      std::cerr << "resource_manager: shader program <" << prg_name
                << "> not found" << std::endl;
      return nullptr;
    }
  return it->second;
}

std::string resource_manager::get_file_data(const std::string& additional)
{
  std::string filepath{path + additional};
  std::ifstream file{filepath, std::ios::binary};
  if (!file.is_open())
    {
      std::cerr << "Resource manager: wrong filepath " << filepath << std::endl;
      return "";
    }
  std::stringstream buff{};
  buff << file.rdbuf();
  return buff.str();
}
}  // namespace renderer
