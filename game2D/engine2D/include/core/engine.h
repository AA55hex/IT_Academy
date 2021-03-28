#pragma once
#include <SDL.h>
#include <string>
namespace sound
{
class sound_buffer;
void audio_callback(void* userdata, Uint8* stream, int len);
}  // namespace sound

namespace render
{
class renderer;
}

namespace core
{
class igame;
class engine
{
 public:
  engine() = delete;
  static bool inicialize(int width, int height, std::string title,
                         bool gl_debug = false);
  static void dispose();
  static bool is_inicialized() { return inicialized; }

  static void play(igame& game);

 private:
  friend class sound::sound_buffer;
  friend void sound::audio_callback(void*, Uint8* stream, int len);

  inline static bool inicialized{false};
  static bool window_init(int width, int height, std::string title,
                          bool gl_debug);
  static bool audio_init();

  struct audio_data
  {
    SDL_AudioDeviceID audio_device;
    SDL_AudioSpec audio_device_spec;
  };

  struct window_data
  {
    SDL_Window* window;
    SDL_GLContext gl_context;
    int height;
    int width;
  };

  inline static audio_data audio{};
  inline static window_data window{};
};
}  // namespace core
