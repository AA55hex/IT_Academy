#pragma once
#include <map>
#include <memory>
#include <string>
#include "render/shader_program.h"
#include "render/texture2D.h"
#include "sound/wav_sound.h"
namespace resources
{
class resource_manager
{
 public:
  resource_manager(const std::string& dir_path);

  resource_manager(resource_manager&&);
  resource_manager& operator=(resource_manager&&);

  std::shared_ptr<render::shader_program> load_shader_program(
      const std::string& prg_name, const std::string& vert_path,
      const std::string& frag_path);
  std::shared_ptr<render::shader_program> get_shader_program(
      const std::string& prg_name);

  std::shared_ptr<render::texture2D> load_texture2D(
      const std::string& texture_name, const std::string& filepath);
  std::shared_ptr<render::texture2D> get_texture2D(
      const std::string& texture_name);

  std::shared_ptr<sound::wav_sound> load_wav(const std::string& wav_name,
                                             const std::string& filepath);
  std::shared_ptr<sound::wav_sound> get_wav(const std::string& wav_name);

  resource_manager(resource_manager&) = delete;
  resource_manager& operator=(resource_manager&) = delete;

 private:
  std::string get_file_data(const std::string& additional);

  std::map<std::string, std::shared_ptr<render::shader_program>>
      shader_program_map;

  std::map<std::string, std::shared_ptr<render::texture2D>> texture_map;

  std::map<std::string, std::shared_ptr<sound::wav_sound>> wav_map;

  std::string path;
};
}  // namespace resources
