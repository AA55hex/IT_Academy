#include "resources/resource_manager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#define STB_IMAGE_IMPLEMENTATION
#include "resources/stb_image.h"
namespace resources
{
resource_manager::resource_manager(const std::string& dir_path)
{
  size_t last_pos{dir_path.find_last_of("/\\")};
  path = dir_path;
  if (path.length() != 0 && path.length() - 1 != last_pos)
    {
      path += "/";
    }
}

std::shared_ptr<render::shader_program> resource_manager::load_shader_program(
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
      std::make_shared<render::shader_program>(vert_src, frag_src);

  std::shared_ptr<render::shader_program> result{shader_program_map[prg_name]};

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
std::shared_ptr<render::shader_program> resource_manager::get_shader_program(
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

std::shared_ptr<render::texture2D> resource_manager::load_texture2D(
    const std::string& texture_name, const std::string& filepath)
{
  int width, height, channels;
  std::string full_path = path + filepath;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* data =
      stbi_load(full_path.c_str(), &width, &height, &channels, 0);
  if (data == nullptr)
    {
      std::cerr << "Resource manager: can't to load texture " << texture_name
                << std::endl
                << "Filepath: " << filepath << std::endl;
      return nullptr;
    }
  render::color_format format;
  switch (channels)
    {
      case 3:
        format = render::color_format::rgb;
        break;
      case 4:
        format = render::color_format::rgba;
        break;
      default:
        format = render::color_format::rgba;
        break;
    }
  texture_map[texture_name] =
      std::make_shared<render::texture2D>(width, height, data, format);
  stbi_image_free(data);
  return texture_map[texture_name];
}
std::shared_ptr<render::texture2D> resource_manager::get_texture2D(
    const std::string& texture_name)
{
  auto it = texture_map.find(texture_name);
  if (it == texture_map.end())
    {
      std::cerr << "Resource_manager: texture <" << texture_name
                << "> not found" << std::endl;
      return nullptr;
    }
  return it->second;
}

std::shared_ptr<sound::wav_sound> resource_manager::load_wav(
    const std::string& wav_name, const std::string& filepath)
{
  using namespace std;

  std::string full_path = path + filepath;

  SDL_AudioSpec audio_spec_from_file{};
  uint8_t* sample_buffer_from_file = nullptr;
  uint32_t sample_buffer_len_from_file = 0;

  clog << "loading sample buffer from file: " << filepath << endl;

  if (SDL_LoadWAV(full_path.c_str(), &audio_spec_from_file,
                  &sample_buffer_from_file,
                  &sample_buffer_len_from_file) == nullptr)
    {
      cerr << "Resource_manager:: audio load runtime error: can't parse and "
              "load audio samples from file\n";
      return nullptr;
    }

  clog << "audio buffer from file size: " << sample_buffer_len_from_file
       << " B (" << sample_buffer_len_from_file / double(1024 * 1024) << ") Mb"
       << endl;

  wav_map[wav_name] = std::make_shared<sound::wav_sound>(
      sample_buffer_from_file, sample_buffer_len_from_file);

  return wav_map[wav_name];
}
std::shared_ptr<sound::wav_sound> resource_manager::get_wav(
    const std::string& wav_name)
{
  auto it = wav_map.find(wav_name);
  if (it == wav_map.end())
    {
      std::cerr << "Resource_manager: wav_sound <" << wav_name << "> not found"
                << std::endl;
      return nullptr;
    }
  return it->second;
}

}  // namespace resources
